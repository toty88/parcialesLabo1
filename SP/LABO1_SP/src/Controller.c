#include"Controller.h"

static int cliente_generateId(LinkedList* pArrayListClientes, int*);

static int cliente_generateId(LinkedList* pArrayListClientes, int *id) {

    int output = -1;
    static int bufferIdClientes = 0;
    if (id != NULL && !(ll_mapInt(pArrayListClientes, cliente_findMaxId, &bufferIdClientes)))
    {
        bufferIdClientes++;
        *id = bufferIdClientes;
        output = 0;
    }
    return output;
}

static int venta_generateId(LinkedList* pArrayListVentas, int*);

static int venta_generateId(LinkedList* pArrayListVentas, int *id) {

    int output = -1;
    static int bufferIdVentas = 0;
    if (id != NULL && !(ll_mapInt(pArrayListVentas, venta_findMaxId, &bufferIdVentas)))
    {
        bufferIdVentas++;
        *id = bufferIdVentas;
        output = 0;
    }
    return output;
}

int controller_loadClientesFromText(char* path, LinkedList* pArrayListClientes)
{
    FILE* in;
    int output = -1;
    in = fopen(path, "r");

    if(in != NULL)
    {
        if(!(parser_ClientesFromText(in, pArrayListClientes)))
        {
            output = 0;
        }
        fclose(in);
    }
    return output;
}

int controller_ListClientes(LinkedList* pArrayListClientes)
{
    int output = -1;
    if(pArrayListClientes != NULL)
    {
        if(!(ll_map(pArrayListClientes, cliente_print)))
        {
            output = 0;
        }
    }
    return output;
}

int controller_loadVentasFromText(char* path, LinkedList* pArrayListVentas)
{
    FILE* in;
    int output = -1;
    in = fopen(path, "r");

    if(in != NULL)
    {
        if(!(parser_VentasFromText(in, pArrayListVentas)))
        {
            output = 0;
        }
        fclose(in);
    }
    return output;
}

int controller_ListVentas(LinkedList* pArrayListVentas)
{
    int output = -1;
    if(pArrayListVentas != NULL)
    {
        if(!(ll_map(pArrayListVentas, venta_print)))
        {
            output = 0;
        }
    }
    return output;
}

int controller_isClienteCuitValid(char* cuit)
{
    int output = 0;
    int contador = 0;
    if(cuit != NULL && utn_isNumeric(cuit))
    {
        for(int x = 0; cuit[x] != '\0'; x++)
        {
            contador++;
        }
        if(contador == 11)
        {
            output = 1;
        }
    }
    return output;
}

int controller_addCliente(LinkedList* pArrayListClientes)
{
    int output = -1;
    int bufferId;
    char bufferNombre[SIZE_STR];
    char bufferApellido[SIZE_STR];
    char bufferCuit[SIZE_STR];
    Cliente* aux;
    if(pArrayListClientes != NULL)
    {
        if(!(utn_getStringWithOnlyNumbers("\n(A). Ingrese CUIT [11 numeros sin guiones]: ", "Error, solo numeros. Reintentos", bufferCuit, SIZE_STR, 2))
                && controller_isClienteCuitValid(bufferCuit))
        {
            if(!(ll_mapStr(pArrayListClientes, bufferCuit, cliente_DoesClientExist)))
            {
                output = -3;
            }
            else
            {
                if(!(cliente_generateId(pArrayListClientes, &bufferId))
                        && !(utn_getString("(B). Ingrese Nombre: ", "Error,  Reintentos", bufferNombre, SIZE_STR, 3))
                        && !(utn_getString("(C). Ingrese Apellido: ", "Error,  Reintentos", bufferApellido, SIZE_STR, 3)))
                {
                     aux = cliente_newParam(bufferId, bufferNombre, bufferApellido, bufferCuit);
                    if(aux != NULL && !(ll_add(pArrayListClientes, aux)))
                    {
                        output = 0;
                    }
                }
            }
        }
        else
        {
            output = -2;
        }
    }
    return output;
}



int controller_venderAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListClientes)
{
    int output = -1;
    int ventaMenuOption;
    int flagId = 0;
    int bufferID;
    int bufferVentaID;
    int bufferCantAfiches;
    char bufferNombreArchivo[SIZE_FILE_NAME];
    int bufferZona;
    Venta* nuevaVenta;

    do
    {
        if(!(menu_VenderAfiches(&ventaMenuOption)))
        {
            switch(ventaMenuOption)
            {
            case 1:
                if(!(ll_map(pArrayListClientes, cliente_print)))
                {
                    output = 1;

                }
                break;
            case 2:

                if(!(utn_getInt("\n(A). Ingrese ID Cliente: ", "Error, Reintentos", &bufferID, 2))
                        && !(ll_findByInt(pArrayListClientes, cliente_DoesIdExist, bufferID)))
                {
                    flagId = 1;
                }
                else
                {
                    printf("\n >>>>> ATENCION! ID NO ENCONTRADO, INTENTE DE NUEVO <<<<<\n");
                }
                break;
            case 3:
                if(flagId == 1)
                {
                    if(!(utn_getInt("(B). Ingrese Cantidad de Afiches: ", "Error, Reintentos", &bufferCantAfiches, 2))
                            && !(utn_getString("(C). Ingrese Nombre del Archivo con la imagen: ", "Error, Reintentos", bufferNombreArchivo, SIZE_FILE_NAME, 2))
                            && !(utn_getIntConMinMax("(D). Seleccione Zona\n(0). CABA\n(1). ZONA SUR\n(2). ZONA OESTE: ----> "
                                    , "Error, Reintentos", &bufferZona, 0, 2, 2))
                                    && !(venta_generateId(pArrayListVentas, &bufferVentaID)))
                    {

                        nuevaVenta = venta_newParam(bufferVentaID, bufferID, bufferNombreArchivo, bufferCantAfiches, bufferZona);
                        if(nuevaVenta != NULL && !(ll_add(pArrayListVentas, nuevaVenta)))
                        {
                            printf("nuevo id: %d", venta_getId_venta(nuevaVenta));
                            output = 0;
                        }
                    }
                }
                else
                {
                    printf("\n >>>>> ATENCION! INGRESAR ID CLIENTE PRIMERO (OPC 2) <<<<<\n");
                }
                break;
            case 4:
                printf("\n >>>>> VOLVIENDO AL MENU PRINCIPAL <<<<<\n");
                break;
            default:
                printf("\n >>>>> OPCION INVALIDA, VUELVA A INTENTAR <<<<<\n");
            }
        }

    }
    while(ventaMenuOption != 4);
    return output;
}
/* ################### POSIBLES FUNCIONES A FUTURO ############################ */

/*int controller_saveAsText2(char* path , Zona* pArrayZonas, pParser pCriterio)
{
    int output = -1;
    int lenZona;
    if(path != NULL && pCriterio != NULL && !(zona_len(pArrayZonas, &lenZona)))
    {
        FILE* out;
        out = fopen(path, "w");
        if(out != NULL)
        {
            if(!(pCriterio(out, pArrayZonas, lenZona)))
            {
                output = 0;
            }
            fclose(out);
        }
    }
    return output;
}*/

/*
static int envio_generateId(LinkedList* pArrayListProductos, int*);

static int envio_generateId(LinkedList* pArrayListProductos, int *id) {

    int output = -1;
    static int bufferId;
    if (id != NULL && !(ll_mapInt(pArrayListProductos, envio_findMaxId, &bufferId)))
    {
        bufferId++;
        *id = bufferId;
        output = 0;
    }
    return output;
}
*/

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListProductos LinkedList*
 * \return int
 *
 */
/*int controller_addProducto(LinkedList* pArrayListProductos)
{
    int output = -1;
    int bufferId;
    char bufferName[SIZE_NAME];
    int bufferHoras;
    float bufferSueldo;

    int idProducto;
    int idCamion;
    char nombreProducto[SIZE_NAME];
    char zonaDestino[SIZE_NAME];
    float kilometrosRecorridos;
    int tipoEntrega;

    if(pArrayListProductos != NULL)
    {
        if(!(envio_generateId(pArrayListProductos, &bufferId)) && !(utn_getString("Ingrese Nombre Producto: ", "Error,  reintentos", bufferName, SIZE_NAME, 3))
                && !(utn_getInt("Ingrese horas trabajadas: ", "Error, reintentos", &bufferHoras, 3))
                && !(utn_getFloat("Ingrese sueldo: ", "Error, reintentos", &bufferSueldo, 3)))
        {
            Producto* aux = envio_newParam(bufferId, bufferName, bufferHoras, bufferSueldo);
            if(aux != NULL && !(ll_add(pArrayListProductos, aux)))
            {

                output = 0;
            }
        }
    }
    return output;
}*/


/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListProductos LinkedList*
 * \return int
 *
 */
/*int controller_editProducto(LinkedList* pArrayListProductos)
{
    int output = -1;
    int modifyOption;
    int bufferId;
    int bufferIndex;
    Producto* pBufferAux;
    Producto bufferProducto;

    if(pArrayListProductos != NULL)
    {
        do
        {
            if(!(menu_ModifyProducto(&modifyOption)))
            {
                switch(modifyOption)
                {
                case 1:
                    if(!(controller_ListProducto(pArrayListProductos)))
                    {
                        printf("\n >>>>> EMPLEADOS LISTADOS CON EXITO <<<<<\n");
                    }
                    break;
                case 2:
                    if(!(utn_getInt("Ingrese ID Producto: ", "Error, reintentos", &bufferId, 3))
                            && !(ll_findByInt(pArrayListProductos, envio_compareById, bufferId, &bufferIndex)))
                    {
                        pBufferAux = (Producto*)ll_get(pArrayListProductos, bufferIndex);
                        if(pBufferAux != NULL)
                        {
                            printf("\n >>>>> EMPLEADOS ENCONTRADO: %s <<<<<\n", envio_getNombre(pBufferAux));
                            output = 1;
                        }
                    }
                    break;
                case 3:
                    if(!(utn_getString("Ingrese nuevo nombre: ", "Error, reintentos", bufferProducto.nombre, SIZE_NAME, 3))
                            && !(envio_setNombre(pBufferAux, bufferProducto.nombre)))
                    {
                        output = 0;
                    }
                    break;
                case 4:
                    if(!(utn_getInt("Ingrese nuevas horas: ", "Error, reintentos", &bufferProducto.horasTrabajadas, 3))
                                && !(envio_setHorasTrabajadas(pBufferAux, bufferProducto.horasTrabajadas)))
                    {
                        output = 0;
                    }
                    break;
                case 5:
                    if(!(utn_getFloat("Ingrese nuevo sueldo: ", "Error, reintentos", &bufferProducto.sueldo, 3))
                                && !(envio_setSueldo(pBufferAux, bufferProducto.sueldo)))
                    {
                        output = 0;
                    }
                    break;
                case 6:
                    printf("\n >>>>> VOLVLIENDO AL MENU PRINCIPAL <<<<<\n");
                    break;
                default:
                    printf("\n >>>>> OPCION INVALIDA <<<<<\n");
                }
            }

        }while(modifyOption != 6);
    }
    return output;
}*/

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListProductos LinkedList*
 * \return int
 *
 */
/*int controller_removeProducto(LinkedList* pArrayListProductos)
{
    int output = -1;
    int removeOption;
    int bufferId;
    int bufferBaja;
    int bufferIndex;
    int bufferListIndex;
    Producto* pBufferAux;

    if(pArrayListProductos != NULL)
    {
        do
        {
            if(!(menu_RemoveProducto(&removeOption)))
            {
                switch(removeOption)
                {
                case 1:
                    if(!(controller_ListProducto(pArrayListProductos)))
                    {
                        printf("\n >>>>> EMPLEADOS LISTADOS CON EXITO <<<<<\n");
                    }
                    break;
                case 2:
                    if(!(utn_getInt("Ingrese ID empleado: ", "Error, reintentos", &bufferId, 3))
                            && !(ll_findByInt(pArrayListProductos, envio_compareById, bufferId, &bufferIndex)))
                    {
                        pBufferAux = (Producto*)ll_get(pArrayListProductos, bufferIndex);
                        if(pBufferAux != NULL)
                        {
                            printf("\nEMPLEADO A DAR DE BAJA: %s (CONFIRMAR BAJA CON OPCION 3)\n", envio_getNombre(pBufferAux));
                            output = 1;
                        }
                    }
                    else
                    {
                        printf("\n >>>>> EMPLEADOS NO ENCONTRADO (VUELVA A LISTAR EMPLEADOS) <<<<<\n");
                    }
                    break;
                case 3:
                    if(!(utn_getInt("\t(0). CONFIRMAR BAJAR\n\t(1). DESCARTAR BAJA ------> ", "Error, reintentos", &bufferBaja, 3))
                            && bufferBaja == 0)
                    {
                        bufferListIndex = ll_indexOf(pArrayListProductos, pBufferAux);
                        if(bufferListIndex > 0 && !(envio_delete(pBufferAux)) && !(ll_remove(pArrayListProductos, bufferListIndex)))
                        {
                            output = 0;
                        }
                    }
                    break;
                case 4:
                    printf("\n >>>>> VOLVLIENDO AL MENU PRINCIPAL <<<<<\n");
                    break;
                default:
                    printf("\n >>>>> OPCION INVALIDA <<<<<\n");
                }
            }
        }
        while(removeOption != 4);

    }
    return output;
}*/

/*int controller_ReduceProducto(LinkedList* pArrayListProductos)
{ // falta agregar switch con varias funciones criterio
    int output = -1;
    float resultado = 0;
    if(pArrayListProductos != NULL)
    {
        if(!(ll_reduceFloat(pArrayListProductos, envio_SumOfSalaries, &resultado)))
        {
            printf("total sum of salaries: $%.2f pesos devaluados\n", resultado);
            output = 0;
        }
    }
    return output;
}*/

/*int controller_sortProducto(LinkedList* pArrayListProductos)
{
    int output = -1;
    int bufferOrder;
    int bufferSortMenu;
    if(pArrayListProductos != NULL)
    {
        do
        {
            if(!(menu_SortProducto(&bufferSortMenu)))
            {
                switch(bufferSortMenu)
                {
                case 1:
                    if(!(utn_getIntConMinMax("(0). ORDENAR DE FORMA DESCENDENTE\n(1). ORDENAR DE FORMA ASCENDENTE -----> "
                            , "Error, reintentos", &bufferOrder, 0, 1, 3))
                            && !(ll_sort(pArrayListProductos, envio_sortProductosById, bufferOrder)))
                    {
                        output = 0;
                    }
                    break;
                case 2:
                    if(!(utn_getIntConMinMax("(0). ORDENAR DE FORMA DESCENDENTE\n(1). ORDENAR DE FORMA ASCENDENTE -----> "
                            , "Error, reintentos", &bufferOrder, 0, 1, 3))
                            && !(ll_sort(pArrayListProductos, envio_sortProductosByName, bufferOrder)))
                    {
                        output = 0;
                    }
                    break;
                case 3:
                    if(!(utn_getIntConMinMax("(0). ORDENAR DE FORMA DESCENDENTE\n(1). ORDENAR DE FORMA ASCENDENTE -----> "
                            , "Error, reintentos", &bufferOrder, 0, 1, 3))
                            && !(ll_sort(pArrayListProductos, envio_sortProductosBySueldo, bufferOrder)))
                    {
                        output = 0;
                    }
                    break;
                case 4:
                    if(!(utn_getIntConMinMax("(0). ORDENAR DE FORMA DESCENDENTE\n(1). ORDENAR DE FORMA ASCENDENTE -----> "
                            , "Error, reintentos", &bufferOrder, 0, 1, 3))
                            && !(ll_sort(pArrayListProductos, envio_sortProductos, bufferOrder)))
                    {
                        output = 0;
                    }
                    break;
                case 5:
                    printf("\n >>>>> VOLVLIENDO AL MENU PRINCIPAL <<<<<\n");
                    break;
                default:
                    printf("\n >>>>> OPCION INVALIDA <<<<<\n");
                }
            }
        }while (bufferSortMenu !=5);
            output = 0;
    }
    return output;
}*/