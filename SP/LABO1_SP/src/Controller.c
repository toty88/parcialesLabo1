#include"Controller.h"

/* AUXILIARES - CARGA Y VOLCADO DE ARCHIVOS */

static int controller_generateId(char* path, int* bufferID);

static int controller_generateId(char* path, int* bufferID)
{
    int output = -1;
    int writtenValue;
    int id;
    char auxId[100];
    FILE* in;
    FILE* out;
    in = fopen(path, "r");
    if(in != NULL)
    {
        writtenValue = fscanf(in,"%s",auxId);
        if(writtenValue == 1)
        {
            id = atoi(auxId);
            if(id > 0)
            {
                id++;
                *bufferID = id;
                output = 0;
            }
        }
        fclose(in);
    }
    out = fopen(path, "w");
    if(out != NULL)
    {
        fprintf(out,"%d",id);
        fclose(out);
    }
    return output;
}

static int controller_ListClientes(LinkedList* pArrayListClientes);

static int controller_ListVentas(LinkedList* pArrayListVentas);

static int controller_clienteConMas_MenosAfichesComprados(LinkedList*, LinkedList*, int);

static int controller_ventaConMasAfichesVendidos(LinkedList*, LinkedList*);

static LinkedList*  controller_generarListaPorEstadoCompra(char*, LinkedList*, LinkedList*, int, int*);

static int controller_ListClientes(LinkedList* pArrayListClientes)
{
    int output = -1;
    if(pArrayListClientes != NULL)
    {
        printColumnClientes();
        if(!(ll_map(pArrayListClientes, cliente_print)))
        {
            output = 0;
        }
    }
    return output;
}

static int controller_ListVentas(LinkedList* pArrayListVentas)
{
    int output = -1;
    if(pArrayListVentas != NULL)
    {
        printColumnVentas();
        if(!(ll_map(pArrayListVentas, venta_printAcobrar)))
        {
            output = 0;
        }
    }
    return output;
}

/**
 * @fn int controller_ventaConMasAfichesVendidos(LinkedList*, LinkedList*)
 * @brief funcion privada que imprime por pantalla la venta individual que tiene mas afiches
 *
 * @param pArrayListClientesCobrados la linked list de Clientes YA cobrados
 * @param pArrayListVentas la linked list de Ventas
 * @return (-1) Error (0) Todo OK
 */
static int controller_ventaConMasAfichesVendidos(LinkedList* pArrayListClientesCobrados, LinkedList* pArrayListVentas)
{
    int output = -1;
    FILE* out;
    Venta* auxMaxAfichesVendidos;
    int totalAfichesVendidos;
    int ventasConIgualCantidad = 0;

    if(pArrayListClientesCobrados != NULL)
    {
        out = fopen("cobradas.txt", "r");
        if(out != NULL)
        {
            auxMaxAfichesVendidos = (Venta*)ll_filterByInt(pArrayListVentas, pArrayListClientesCobrados
                                                            ,cliente_venta_VentaConMasAfiches
                                                            ,&totalAfichesVendidos
                                                            ,&ventasConIgualCantidad
                                                            ,COBRADO);
            if(auxMaxAfichesVendidos != NULL)
            {
                if(ventasConIgualCantidad == 0)
                {
                    ll_mapDosEntidadesByInt(pArrayListClientesCobrados, pArrayListVentas, cliente_venta_printIdVentaCuitCliente, venta_getId_venta(auxMaxAfichesVendidos));
                }
                else
                {
                    printf("\n >>>>> EXISTEN VENTAS CON LA MISMA CANTIDAD MAXIMA DE AFICHES VENDIDOS: %d <<<<<\n", totalAfichesVendidos);
                }

                output = 0;
            }
            fclose(out);
        }
    }
    return output;
}

/**
 * @fn int controller_clienteConMas_MenosAfichesComprados(LinkedList*, LinkedList*, int)
 * @brief funcion privada que imprime por pantalla el cliente con MAS o MENOS afiches comprados
 *
 * @param pArrayListClientesCobrados la linked list de Clientes YA cobrados
 * @param pArrayListVentas la linked list de Ventas
 * @param max_min (0) cliente con menos afiches comprados (1) clientes con mas afiches comprados
 * @return (-1) Error (0) Todo OK
 */
static int controller_clienteConMas_MenosAfichesComprados(LinkedList* pArrayListClientesCobrados, LinkedList* pArrayListVentas, int max_min)
{
    int output = -1;
    void* aux;
    FILE* out;
    void* auxCliente;
    int afiches;
    int totalAfiches = 0;
    if(pArrayListClientesCobrados != NULL)
    {
        out = fopen("cobradas.txt", "r");
        if(out != NULL)
        {
            if(max_min == 0)
            {
                for(int x = 0; x < ll_len(pArrayListClientesCobrados); x++)
                {
                    aux = ll_get(pArrayListClientesCobrados, x);
                    if(!(ll_reduceIntMinMax(pArrayListVentas, aux, cliente_venta_TotalAfichesPorCliente, &totalAfiches, COBRADO))
                            && (afiches > totalAfiches || x == 0))
                    {
                        afiches = totalAfiches;
                        auxCliente = aux;
                        output = 0;
                    }
                }
                printColumnClientesConMenosAfiches();
            }
            else
            {
                for(int x = 0; x < ll_len(pArrayListClientesCobrados); x++)
                {
                    aux = ll_get(pArrayListClientesCobrados, x);
                    if(!(ll_reduceIntMinMax(pArrayListVentas, aux, cliente_venta_TotalAfichesPorCliente, &totalAfiches, COBRADO))
                            && (afiches < totalAfiches || x == 0))
                    {
                        afiches = totalAfiches;
                        auxCliente = aux;
                        output = 0;
                    }
                }
                printColumnClientesConMasAfiches();
            }
            cliente_printConAfiche(auxCliente, afiches);
            fclose(out);
        }
    }
    return output;
}

/**
 * @fn LinkedList controller_generarListaPorEstadoCompra*(char*, LinkedList*, LinkedList*, int, int*)
 * @brief funcion privada que genera una lista segun estado de compra de c/venta
 *
 * @param path el nombre del archivo y su ubicacion
 * @param pArrayListVentas la linked list de Ventas
 * @param pArrayListClientes la linked list de Clientes
 * @param estado el estado de la venta A_COBRAR o COBRADO
 * @param pResultado el int* donde se guarda el resultado de la generacion de la nueva lista
 * @return pNuevaListaClientes la nueva lista con todas las ventas en estado A_COBRAR o COBRADO
 */
static LinkedList* controller_generarListaPorEstadoCompra(char* path, LinkedList* pArrayListVentas
                                                          ,LinkedList* pArrayListClientes, int estado, int* pResultado)
{
    int output = -1;
    int ventas = 0;
    void* aux;
    FILE* out;
    LinkedList* pNuevaListaClientes;
    pNuevaListaClientes = ll_filterToNewListByInt(pArrayListClientes, pArrayListVentas, cliente_venta_isEstado, estado);
    if(pNuevaListaClientes != NULL)
    {
        out = fopen(path, "w");
        if(out != NULL)
        {
            for(int x = 0; x < ll_len(pNuevaListaClientes); x++)
            {
                aux = ll_get(pNuevaListaClientes, x);
                if(!(ll_reduceInt(pArrayListVentas, aux, cliente_venta_isEstado, &ventas, estado))
                        && !(parser_ClientesConTotalVentasToText(out, aux, ventas)))
                {
                    output = 0;
                }
            }
            fclose(out);
            if(output == 0)
            {
                *pResultado = output;
            }
        }
    }
    return pNuevaListaClientes;
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

int controller_saveClientesAsText(char* path , LinkedList* pArrayListClientes)
{
    int output = -1;
    if(path != NULL && pArrayListClientes != NULL)
    {
        FILE* out;
        out = fopen(path, "w");
        if(out != NULL)
        {
            if(!(parser_ClientesToText(out, pArrayListClientes)))
            {
                output = 0;
            }
            fclose(out);
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

int controller_saveVentasAsText(char* path , LinkedList* pArrayListVentas)
{
    int output = -1;
    if(path != NULL && pArrayListVentas != NULL)
    {
        FILE* out;
        out = fopen(path, "w");
        if(out != NULL)
        {
            if(!(parser_VentasToText(out, pArrayListVentas)))
            {
                output = 0;
            }
            fclose(out);
        }
    }
    return output;
}

/* ####################################### */

/* ADD - VENDER - MOD - COBRAR - INFORMES */

/**
 * @fn int controller_addCliente(LinkedList*)
 * @brief funcion que da de alta un cliente
 *
 * @param pArrayListClientes la linked list de Clientes
 * @return (-1) Error (-2) Cuit Invalido (-3) Cliente YA existente (0) Todo OK
 */
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
                && cliente_isValidCuitTXT(bufferCuit))
        {
            if(!(ll_mapStr(pArrayListClientes, bufferCuit, cliente_DoesClientExist)))
            {
                output = -3;
            }
            else
            {
                if(!(controller_generateId("clientes_id.txt", &bufferId))
                        && !(utn_getString("(B). Ingrese Nombre: ", "Error,  Reintentos", bufferNombre, SIZE_STR, 3))
                        && !(utn_getString("(C). Ingrese Apellido: ", "Error,  Reintentos", bufferApellido, SIZE_STR, 3)))
                {
                     aux = cliente_newParam(bufferId, bufferNombre, bufferApellido, bufferCuit);
                    if(aux != NULL && !(ll_add(pArrayListClientes, aux))
                            && !(controller_saveClientesAsText("clientes.txt", pArrayListClientes)))
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

/**
 * @fn int controller_venderAfiches(LinkedList*, LinkedList*)
 * @brief funcion que da de alta una venta de afiche
 *
 * @param pArrayListVentas la linked list de Ventas
 * @param pArrayListClientes la linked list de Clientes
 * @return (-1) Error (1) Sin Venta (0) Todo OK
 */
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
                if(!(controller_ListClientes(pArrayListClientes)))
                {
                    output = 1;
                }
                break;
            case 2:
                if(!(utn_getInt("\n(A). Ingrese ID Cliente: ", "Error, Reintentos", &bufferID, 2))
                        && !(ll_findByInt(pArrayListClientes, cliente_DoesIdExist, bufferID)))
                {
                    printf("\n >>>>> CLIENTE ENCONTRADO CON EXITO (CONTINUE OPCION 3) <<<<<\n");
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
                            && !(utn_getString("(C). Ingrese Nombre del Archivo [solo extension .tiff]: ", "Error, Reintentos", bufferNombreArchivo, SIZE_FILE_NAME, 2))
                            && venta_isValidNombre_archivo(bufferNombreArchivo)
                            && !(utn_getIntConMinMax("(D). Seleccione Zona\n(0). CABA\n(1). ZONA SUR\n(2). ZONA OESTE: ----> "
                                    , "Error, Reintentos", &bufferZona, 0, 2, 2))
                                    && !(controller_generateId("ventas_id.txt", &bufferVentaID)))
                    {

                        nuevaVenta = venta_newParam(bufferVentaID, bufferID, bufferNombreArchivo, bufferCantAfiches, bufferZona);
                        if(nuevaVenta != NULL && !(ll_add(pArrayListVentas, nuevaVenta))
                                && !(controller_saveVentasAsText("ventas.txt", pArrayListVentas)))
                        {
                            printf("\n >>>>> NUEVO ID DE VENTA #%d <<<<<\n", venta_getId_venta(nuevaVenta));
                            output = 0;
                        }
                    }
                    else
                    {
                        printf("\n >>>>> ATENCION! REVISE NOMBRE DE ARCHIVO Y/O ZONA ELEGIDA <<<<<\n");
                    }
                }
                else
                {
                    printf("\n >>>>> ATENCION! INGRESAR ID CLIENTE PRIMERO (OPCION 2) <<<<<\n");
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

/**
 * @fn int controller_modificarVentas(LinkedList*, LinkedList*)
 * @brief funcion que modifica una venta en estado A_COBRAR
 *
 * @param pArrayListVentas la linked list de Ventas
 * @param pArrayListClientes la linked list de Clientes
 * @return (-1) Error (1) Sin Modificacion (0) Todo OK
 */
int controller_modificarVentas(LinkedList* pArrayListVentas, LinkedList* pArrayListClientes)
{
    int output = -1;
    int modificarMenuOption;
    int pResultado = -1;
    int flagId = 0;
    int guardarCambios;
    int bufferVentaID;
    int bufferCantAfiches;
    int bufferZona;
    char bufferNombreArchivo[SIZE_FILE_NAME];
    Venta* auxVenta;
    do
    {
        if(!(menu_ModifyVenta(&modificarMenuOption)))
        {
            switch(modificarMenuOption)
            {
            case 1:
                if(!(controller_ListVentas(pArrayListVentas)))
                {
                    output = 1;
                }
                break;
            case 2:
                if(!(utn_getInt("\n(A). Ingrese ID Venta: ", "Error, Reintentos", &bufferVentaID, 2)))
                {
                    auxVenta = (Venta*)ll_findAndReturnElement(pArrayListVentas, venta_findVentaById, &pResultado, bufferVentaID);
                    if(pResultado == 0 && auxVenta != NULL && venta_getEstado(auxVenta) == A_COBRAR
                            && !(ll_mapDosEntidadesByInt(pArrayListClientes, pArrayListVentas, cliente_venta_print, bufferVentaID)))
                    {
                        flagId = 1;
                    }
                    else
                    {
                        printf("\n >>>>> ATENCION! ID NO ENCONTRADO, INTENTE DE NUEVO <<<<<\n");
                    }
                }
                break;
            case 3:
                if(flagId == 1)
                {
                    if(!(utn_getInt("(B). Ingrese Nueva Cantidad de Afiches: ", "Error, Reintentos", &bufferCantAfiches, 2))
                        && !(utn_getIntConMinMax("\n(0). CONFIRMAR CAMBIO"
                                "\n(1). ANULAR CAMBIO ----> ", "Error, Reintentos", &guardarCambios,0,1, 2))
                        && guardarCambios == 0
                        && !(venta_setCantidad_afiches(auxVenta, bufferCantAfiches)))
                    {
                        printf("\n >>>>> CANTIDAD DE AFICHES MODIFICADA CON EXITO <<<<<\n");
                        output = 0;
                    }
                }
                else
                {
                    printf("\n >>>>> ATENCION! DEBE INGRESAR ID VENTA, INTENTE OPCION 2 <<<<<\n");
                }

                break;
            case 4:
                if(flagId == 1)
                {
                    if(!(utn_getStringWithNumbersAndSymbols("(C). Ingrese Nuevo Nombre de Archivo [solo extension .tiff]: ",
                            "Error, Reintentos", bufferNombreArchivo, SIZE_FILE_NAME, 2))
                            && !(utn_getIntConMinMax("\n(0). CONFIRMAR CAMBIO"
                                "\n(1). ANULAR CAMBIO ----> ", "Error, Reintentos", &guardarCambios,0,1, 2))
                            && guardarCambios == 0
                            && !(venta_setNombre_archivo(auxVenta, bufferNombreArchivo)))
                    {
                        printf("\n >>>>> NOMBRE ARCHIVO MODIFICADO CON EXITO <<<<<\n");
                        output = 0;

                    }
                    else
                    {
                        printf("\n >>>>> ATENCION! ERROR AL QUERER MODIFICAR NOMBRE <<<<<\n");
                        output = 1;
                    }
                }
                else
                {
                    printf("\n >>>>> ATENCION! DEBE INGRESAR ID VENTA, INTENTE OPCION 2 <<<<<\n");
                }
                break;
            case 5:
                if(flagId == 1)
                {
                    if(!(utn_getIntConMinMax("(D). Seleccione Nueva Zona\n(0). CABA\n(1). ZONA SUR\n(2). ZONA OESTE: ----> "
                            , "Error, Reintentos", &bufferZona, 0, 2, 2))
                        && !(utn_getIntConMinMax("\n(0). CONFIRMAR CAMBIO"
                                "\n(1). ANULAR CAMBIO ----> ", "Error, Reintentos", &guardarCambios,0,1, 2))
                                && guardarCambios == 0
                                && !(venta_setZona(auxVenta, bufferZona)))
                    {
                        printf("\n >>>>> ZONA MODIFICADA CON EXITO <<<<<\n");
                        output = 0;

                    }
                }
                else
                {
                    printf("\n >>>>> ATENCION! DEBE INGRESAR ID VENTA, INTENTE OPCION 2 <<<<<\n");
                }
                break;
            case 6:
                if(output == 0 && !(controller_saveVentasAsText("ventas.txt", pArrayListVentas)))
                {
                    output = 0;
                    printf("\n >>>>> VOLVIENDO AL MENU PRINCIPAL <<<<<\n");
                }
                break;
            default:
                printf("\n >>>>> OPCION INVALIDA, VUELVA A INTENTAR <<<<<\n");
            }
        }

    }
    while(modificarMenuOption != 6);
    return output;
}

/**
 * @fn int controller_cobrarVentas(LinkedList*, LinkedList*)
 * @brief funcion que cambia el estado de una venta de A_COBRAR a COBRADO
 *
 * @param pArrayListVentas la linked list de Ventas
 * @param pArrayListClientes la linked list de Clientes
 * @return (-1) Error (1) Sin Modificacion (0) Todo OK
 */
int controller_cobrarVentas(LinkedList* pArrayListVentas, LinkedList* pArrayListClientes)
{
    int output = -1;
    int cobrarMenuOption;
    int flagId = 0;
    int pResultado = -1;
    int guardarCambios;
    int bufferVentaID;
    Venta* auxVenta;
    do
    {
        if(!(menu_CobrarVenta(&cobrarMenuOption)))
        {
            switch(cobrarMenuOption)
            {
            case 1:

                if(!(controller_ListVentas(pArrayListVentas)))
                {
                    output = 1;

                }
                break;
            case 2:
                if(!(utn_getInt("\n(A). Ingrese ID Venta: ", "Error, Reintentos", &bufferVentaID, 2)))
                {
                    auxVenta = (Venta*)ll_findAndReturnElement(pArrayListVentas, venta_findVentaById, &pResultado, bufferVentaID);
                    if(pResultado == 0 && auxVenta != NULL && venta_getEstado(auxVenta) == A_COBRAR
                            && !(ll_mapDosEntidadesByInt(pArrayListClientes, pArrayListVentas, cliente_venta_print, bufferVentaID)))
                    {
                        flagId = 1;
                    }
                    else
                    {
                        printf("\n >>>>> ATENCION! ID NO ENCONTRADO, INTENTE DE NUEVO <<<<<\n");
                    }
                }
                break;
            case 3:
                if(flagId == 1)
                {
                    if(!(utn_getIntConMinMax("\nMODIFICAR A ESTADO COBRADO\n(0). CONFIRMAR CAMBIO"
                                "\n(1). ANULAR CAMBIO ----> ", "Error, Reintentos", &guardarCambios,0,1, 2))
                        && guardarCambios == 0
                        && !(venta_setEstado(auxVenta, COBRADO)))
                    {
                        printf("\n >>>>> ESTADO MODIFICADO CON EXITO <<<<<\n");
                        output = 0;
                    }
                }
                else
                {
                    printf("\n >>>>> ATENCION! DEBE INGRESAR ID VENTA, INTENTE OPCION 2 <<<<<\n");
                }
                break;
            case 4:
                if(output == 0 && !(controller_saveVentasAsText("ventas.txt", pArrayListVentas)))
                {
                    output = 0;
                    auxVenta = NULL;
                    printf("\n >>>>> VOLVIENDO AL MENU PRINCIPAL <<<<<\n");
                }
                break;
            default:
                printf("\n >>>>> OPCION INVALIDA, VUELVA A INTENTAR <<<<<\n");
            }
        }
    }
    while(cobrarMenuOption != 4);
    return output;
}

/**
 * @fn int controller_generarInformes(LinkedList*, LinkedList*)
 * @brief funcion que llama a 3 funciones p/generar informes por separado
 *
 * @param pArrayListVentas la linked list de Ventas
 * @param pArrayClientes la linked list de Clientes
 * @return (-1) Error (0) Todo OK
 */
int controller_generarInformes(LinkedList* pArrayListVentas, LinkedList* pArrayClientes)
{
    int output = -1;
    int informesMenuOption;
    int pResultado = -1;
    int flagListaCobrados = 0;
    LinkedList* pArrayListClientesCobrados;
    LinkedList* pArrayListClientesACobrar;
    do
    {
        if(!(menu_generarInformes(&informesMenuOption)))
        {
            switch(informesMenuOption)
            {
            case 1:
                pArrayListClientesCobrados = controller_generarListaPorEstadoCompra("cobradas.txt", pArrayListVentas, pArrayClientes, COBRADO, &pResultado);
                if(pResultado == 0 && pArrayListClientesCobrados != NULL)
                {
                    printf("\n >>>>> COBRADAS.TXT GENERADO CON EXITO <<<<<\n");
                    flagListaCobrados = 1;
                    output = 0;
                }
                break;
            case 2:
                pArrayListClientesACobrar = controller_generarListaPorEstadoCompra("a_cobrar.txt", pArrayListVentas, pArrayClientes, A_COBRAR, &pResultado);
                if(pResultado == 0 && pArrayListClientesACobrar != NULL)
                {
                    printf("\n >>>>> A_COBRAR.TXT GENERADO CON EXITO <<<<<\n");
                    output = 0;
                }
                break;
            case 3:
                if(flagListaCobrados == 1)
                {
                    if(!(controller_clienteConMas_MenosAfichesComprados(pArrayListClientesCobrados,pArrayListVentas,1))
                            && !(controller_clienteConMas_MenosAfichesComprados(pArrayListClientesCobrados,pArrayListVentas,0))
                            && !(controller_ventaConMasAfichesVendidos(pArrayListClientesCobrados,pArrayListVentas)))
                    {
                        output = 0;
                    }
                }
                else
                {
                    printf("\n >>>>> ATENCION! PRIMERO DEBE GENERAR INFORME DE VENTAS COBRADAS (OPCION 1) <<<<<\n");
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
    while(informesMenuOption != 4);
    return output;
}


/* ############################################## */


/* ################### POSIBLES FUNCIONES A FUTURO ############################ */



/*
int controller_removeCliente(LinkedList* pArrayListClientes)
{
    int output = -1;
    int removeOption;
    int bufferId;
    int bufferBaja;
    int bufferListIndex;
    int pResultado = -1;
    Cliente* aux;

    if(pArrayListClientes != NULL)
    {
        do
        {
            if(!(menu_RemoveCliente(&removeOption)))
            {
                switch(removeOption)
                {
                case 1:
                    if(!(controller_ListClientes(pArrayListClientes)))
                    {
                        printf("\n >>>>> CLIENTES LISTADOS CON EXITO <<<<<\n");
                    }
                    break;
                case 2:
                    if(!(utn_getInt("Ingrese ID Cliente: ", "Error, reintentos", &bufferId, 2)))
                    {
                        aux = ll_findAndReturnElement(pArrayListClientes, cliente_DoesIdExist, &pResultado, bufferId);
                        if(pResultado == 0 && aux != NULL)
                        {
                            printf("\n >>>>> CLIENTE ENCONTRADO CON EXITO: %s (CONTINUE OPCION 3) <<<<<\n", cliente_getNombre(aux));
                            output = 1;
                        }
                        else
                        {
                            printf("\n >>>>> CLIENTE NO ENCONTRADO (VUELVA A LISTAR CLIENTES) <<<<<\n");
                        }
                    }
                    break;
                case 3:
                    if(!(utn_getInt("\t(0). CONFIRMAR BAJAR\n\t(1). DESCARTAR BAJA ------> ", "Error, reintentos", &bufferBaja, 2))
                            && bufferBaja == 0)
                    {
                        bufferListIndex = ll_indexOf(pArrayListClientes, aux);
                        if(bufferListIndex > 0
                                && !(cliente_delete(aux))
                                && !(ll_remove(pArrayListClientes, bufferListIndex))
                                && !(controller_saveClientesAsText("clientes.txt", pArrayListClientes)))
                        {
                            output = 0;
                        }
                    }
                    break;
                case 4:
                    printf("\n >>>>> VOLVLIENDO AL MENU PRINCIPAL <<<<<\n");
                    break;
                default:
                    printf("\n >>>>> OPCION INVALIDA, VUELVA A INTENTAR <<<<<\n");
                }
            }
        }
        while(removeOption != 4);

    }
    return output;
}

*/

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
