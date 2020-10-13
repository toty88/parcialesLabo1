#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"cliente_publicacion.h"


/**
 * @fn int rubro_Init(Rubro*, int)
 * @brief Funcion que setea el campo isEmpty de un elemento de tipo Rubro en TRUE
 *
 * @param ruArray: El puntero al array de tipo Rubro
 * @param lenRubro: La longitud del array de tipo Rubro
 * @return (-1) Error (0) todo OK
 */
int rubro_Init(Rubro *ruArray, int lenRubro)
{
    int output = -1;
    if (ruArray != NULL && lenRubro > 0)
    {
        for (int x = 0; x < lenRubro; x++)
        {
            ruArray[x].isEmpty = TRUE;
        }
        output = 0;
    }
    return output;
}

/**
 * @fn int rubro_ExisteRubro(Rubro*, int, int)
 * @brief Funcion que corrobora si existe un rubro en el array de tipo Rubro
 *
 * @param ruArray: El puntero al array de tipo Rubro
 * @param lenRubro: La longitud del array de tipo Rubro
 * @param bufferRubro: El numero de rubro que existe en un array de tipo Publicacion a comparar con los rubros del array de tipo Rubro
 * @return (0) No existe (1) Existe
 */
int rubro_ExisteRubro(Rubro *ruArray, int lenRubro, int bufferRubro)
{
    int output = 0;
    if(ruArray!=NULL && lenRubro>0 && bufferRubro>0)
    {
        for(int x = 0; x < lenRubro; x++)
        {
            if(ruArray[x].isEmpty == FALSE && ruArray[x].rubro == bufferRubro)
            {
                output = 1;
                break;
            }
        }
    }
    return output;
}

/**
 * @fn int rubro_GenerarRubros(Rubro*, int, Publicacion*)
 * @brief Funcion que carga el array de Rubros con numeros de rubros nuevos
 *
 * @param ruArray: El puntero al array de tipo Rubro
 * @param lenRubro: La longitud del array de tipo Rubro
 * @param puArray: El puntero al array de tipo Publicacion
 * @return (-1) Error (0) todo OK
 */
int rubro_GenerarRubros(Rubro *ruArray, int lenRubro, Publicacion *puArray)
{
    int output = -1;
    int contador = 0;

    if (!(rubro_Init(ruArray,lenRubro)) && ruArray != NULL && lenRubro > 0 && puArray != NULL)
    {
        for(int x = 0; x < lenRubro; x++)
        {
            if(!(rubro_ExisteRubro(ruArray, lenRubro, puArray[x].numeroRubro)) && puArray[x].isEmpty == FALSE)
            {
                ruArray[contador].rubro = puArray[x].numeroRubro;
                ruArray[contador].isEmpty = FALSE;
                contador++;
                output = 0;
            }
        }
    }
    return output;
}

/**
 * @fn int rubro_CalcularRubroConMasAvisos(Rubro*, int, Publicacion*, int, int*)
 * @brief Funcion que calcula el rubro que aparece en mas avisos
 *
 * @param ruArray: El puntero al array de tipo Rubro
 * @param lenRubro: La longitud del array de tipo Rubro
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param pResultado: El puntero a int donde se guardara el numero de Rubro que aparece en mas avisos
 * @return (-1) Error (0) todo OK
 */
int rubro_CalcularRubroConMasAvisos(Rubro *ruArray, int lenRubro, Publicacion *puArray, int lenPublicacion, int *pResultado)
{
    int output = -1;
    int bufferContador = 0;
    int bufferMax;

    if (ruArray != NULL && lenRubro > 0 && puArray != NULL && lenPublicacion > 0 && pResultado != NULL)
    {
        for (int x = 0; x < lenRubro; x++)
        {
            if (ruArray[x].isEmpty == FALSE)
            {
                for (int k = 0; k < lenPublicacion; k++)
                {
                    if (puArray[k].isEmpty == FALSE && ruArray[x].rubro == puArray[k].numeroRubro)
                    {
                        bufferContador++;
                    }
                }
                if (bufferMax < bufferContador || x == 0)
                {
                    bufferMax = bufferContador;
                    *pResultado = ruArray[x].rubro;
                    output = 0;
                }
                else if (bufferMax == bufferContador)
                {
                        *pResultado = -1;
                }

                bufferContador = 0;
            }
        }

    }
    return output;
}

/* FUNCIONES DE CLIENTES Y PUBLICACIONES */

/**
 * @fn int cliente_publicacion_CreatePublicidad(Publicacion*, int, Cliente*, int)
 * @brief Funcion que da de alta una publicidad
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_CreatePublicidad(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente)
{
    int output = -1;
    int opcion;
    int flag = 0;
    int bufferClienteID;
    int bufferPublicidadIndex;
    if (puArray != NULL && paArray != NULL && lenPublicacion > 0 && lenCliente > 0)
    {
        do
        {
            if (!(menu_ContratarPublicidad(&opcion)))
            {
                switch (opcion)
                {
                case 1:
                    if(cliente_printAll(paArray, lenCliente))
                    {
                        printf("Error al listar clientes\n");
                    }
                    break;
                case 2:
                    if (!(utn_getInt("INGRESE ID CLIENTE: ", "Error, reintentos",&bufferClienteID, 3))
                            && cliente_DoesIdExist(paArray, lenCliente, bufferClienteID))
                    {
                        flag = 1;
                    }
                    else
                    {
                        printf("ID INEXISTENTE\n");
                    }
                    break;
                case 3:
                    if (flag == 1)
                    {
                        if (!(publicacion_Create(puArray, lenPublicacion, &bufferPublicidadIndex)))
                        {
                            puArray[bufferPublicidadIndex].idCliente = bufferClienteID;
                            printf("El nuevo ID de PUBLICIDAD es: %d\n", puArray[bufferPublicidadIndex].id);
                            output = 0;
                        }
                    }
                    else
                    {
                        printf("Debe ingresar ID primero\n");
                    }
                    break;
                case 4:
                    if(flag == 0)
                    {
                        output = 1;
                    }
                    printf("VOLVIENDO AL MENU PRINCIPAL\n");
                    break;
                default:
                    printf("OPCION INVALIDA\n");
                }
            }
        } while (opcion != 4);
    }
    return output;
}

/**
 * @fn int cliente_publicacion_PrintPublicacionesConIdCliente(Publicacion*, int, Cliente*, int, int)
 * @brief Funcion que imprime todas las publicaciones de un Cliente en base al ID del mismo
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @param bufferClienteID: El ID de tipo entero que recibe y compara para imprimir
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_PrintPublicacionesConIdCliente(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente, int bufferClienteID)
{
    int output = -1;
    if(paArray != NULL && puArray != NULL && bufferClienteID >= 100)
    {
        for(int x = 0; x < lenCliente; x++)
        {
            for(int k = 0; k < lenPublicacion; k++)
            {
                if((paArray[x].id == bufferClienteID) && (paArray[x].id ==  puArray[k].idCliente))
                {
                    publicacion_PrintOne(puArray[k]);
                    output = 0;
                }
            }
        }
    }
    return output;
}

/**
 * @fn int cliente_publicacion_PrintPublicacionesActivasConIdCliente(Publicacion*, int, Cliente*, int, int)
 * @brief Funcion que imprime solo las publicaciones ACTIVAS de un Cliente en base al ID del mismo
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @param bufferClienteID: El ID de tipo entero que recibe y compara para imprimir
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_PrintPublicacionesActivasConIdCliente(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente, int bufferClienteID)
{
    int output = -1;
    int contadorID;
    if(paArray != NULL && puArray != NULL && bufferClienteID >= 100)
    {

        for(int x = 0; x < lenCliente; x++)
        {
            contadorID = 0;
            for(int k = 0; k < lenPublicacion; k++)
            {
                if((paArray[x].id == bufferClienteID) && (paArray[x].id ==  puArray[k].idCliente) && puArray[k].estado == ACTIVA)
                {
                    contadorID++;
                }
            }
            if(contadorID > 0)
            {
                printf("# %d %15s %15s %12s %10d\n", paArray[x].id, paArray[x].name,paArray[x].lastName, paArray[x].cuit, contadorID);
            }
            output = 0;
        }
    }
    return output;
}

/**
 * @fn int cliente_publicacion_PrintPublicacionesActivasClientes(Publicacion*, int, Cliente*, int)
 * @brief Funcion que imprime solo las publicaciones ACTIVAS de todos los Clientes
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_PrintPublicacionesActivasClientes(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente)
{
    int output = -1;
    if(puArray != NULL && paArray != NULL && lenPublicacion > 0 && lenCliente >0)
    {
        printColumnClientYpublicacionesActivas();
        for(int x = 0; x < lenCliente; x++)
        {
            if(paArray[x].isEmpty == FALSE)
            {
                cliente_publicacion_PrintPublicacionesActivasConIdCliente(puArray, lenPublicacion, paArray, lenCliente, paArray[x].id);
            }
        }
        output = 0;
    }
    return output;
}

/**
 * @fn int cliente_publicacion_RemoveClienteConPublicaciones(Publicacion*, int, Cliente*, int)
 * @brief Funcion que da de baja un Cliente y si tuviera, todas sus publicaciones
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_RemoveClienteConPublicaciones(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente)
{
    int output = -1;
    int flagBaja = 0;
    int opcionMenuBaja;
    int bufferResultado;
    int confirmaEliminacion;
    int bufferClienteID;
    int bufferClienteIndex;
    int bufferPublicacionIdex;

    if (paArray != NULL && puArray != NULL && lenCliente > 0 && lenPublicacion > 0)
    {
        do
        {
            if (!(menu_Baja(&opcionMenuBaja)))
            {
                switch (opcionMenuBaja)
                {
                case 1:
                    if (cliente_printAll(paArray, lenCliente))
                    {
                        printf("ERROR AL LISTAR EMPLEADOS\n");
                        opcionMenuBaja = 7;
                    }
                    break;
                case 2:
                    if (!(utn_getInt("\nINGRESE ID DE CLIENTE: ","Error, reintentos", &bufferClienteID, 3)))
                    {
                        if (cliente_FindById(paArray, lenCliente, bufferClienteID, &bufferClienteIndex))
                        {
                            printf("ID INVALIDO, VUELVA A LISTAR EMPLEADOS O SALGA\n");
                            output = 1;
                        }
                        else
                        {
                            bufferResultado = publicacion_FindByClientId(puArray, lenPublicacion, bufferClienteID, &bufferPublicacionIdex);
                            if(bufferResultado == 0)
                            {
                                printColumnPublicacionesDeUnCliente();
                                cliente_publicacion_PrintPublicacionesConIdCliente(puArray, lenPublicacion, paArray, lenCliente, bufferClienteID);
                                printf("\nCONFIRMAR BAJA DE %s %s Y SU/S PUBLICACION/ES?\n",paArray[bufferClienteIndex].name,paArray[bufferClienteIndex].lastName);
                            }
                            else
                            {
                                printf("\nEL CLIENTE NO POSEE PUBLICACIONES, CONFIRMAR BAJA DE %s %s?\n",paArray[bufferClienteIndex].name,paArray[bufferClienteIndex].lastName);
                            }

                            if (!utn_getIntConMinMax("(0). CONFIRMAR\n(1). CANCELAR: ","Error, reintentos", &confirmaEliminacion,0,1,3))
                            {
                                if (confirmaEliminacion == 0)
                                {
                                    paArray[bufferClienteIndex].isEmpty = TRUE;
                                    publicacion_Remove(puArray, lenPublicacion, bufferClienteID);
                                    output = 0;
                                }
                                else if (confirmaEliminacion == 1)
                                {
                                    output = 1;
                                }
                                else
                                {
                                    printf("OPCION INVALIDA\n");
                                }
                            }

                        }
                        flagBaja = 1;
                    }
                    break;
                case 3:
                    printf("SALIENDO AL MENU PRINCIPAL\n");
                    if(flagBaja == 0)
                    {
                        output = 1;
                    }
                    break;
                default:
                    printf("ERROR, OPCION INVALIDA\n");
                }
            }
            printf("\nPresione una tecla para continuar");
            __fpurge(stdin);
            getchar();
            system("clear");
        } while (opcionMenuBaja != 3);
    }
    return output;
}

/**
 * @fn int cliente_publicacion_PausarReanudarPublicacion(Publicacion*, int, Cliente*, int, char*, int)
 * @brief Funcion que permite pausar o reanudar una publicacion
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @param msg: El puntero a char que muestra mensaje de confirmacion para finalizar funcion
 * @param pausarOreanudar: (0) pausar (1) reanudar
 * @return (-1) Error (0) todo OK (1) sin cambios
 */
int cliente_publicacion_PausarReanudarPublicacion(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente, char *msg, int pausarOreanudar)
{
    int output = -1;
    int flagCase = 0;
    int bufferOpcionMenu;
    int confirmaEliminacion;
    int bufferClienteIndex;
    int bufferPublicacionID;
    int bufferPublicacionIndex;

    if(paArray != NULL && puArray != NULL && lenCliente > 0 && lenPublicacion > 0)
    {
        do
        {
            if(!(menu_PusarPublicacion(&bufferOpcionMenu)))
            {
                switch(bufferOpcionMenu)
                {
                case 1:
                    publicacion_printAll(puArray, lenPublicacion);
                    break;
                case 2:
                    if(!(utn_getInt("INGRESE ID DE PUBLICACION: ", "Error, reintentos", &bufferPublicacionID, 3))
                            && !(publicacion_FindById(puArray, lenPublicacion, bufferPublicacionID, &bufferPublicacionIndex))
                            && !(cliente_FindById(paArray, lenCliente, puArray[bufferPublicacionIndex].idCliente, &bufferClienteIndex)))
                    {
                        if(cliente_PrintOne(paArray[bufferClienteIndex]))
                        {
                            printf("ERROR AL IMPRIMIR PUBLICACIONES\n");
                        }
                    }
                    else
                    {
                        printf("ID INCORRECTO O INEXISTENTE\n");
                    }
                    break;
                case 3:
                    printf("%s\n", msg);
                    if (pausarOreanudar == 0 && !(utn_getIntConMinMax("(0). CONFIRMAR\n(1). CANCELAR: ","Error, reintentos", &confirmaEliminacion,0,1,3)))
                    {
                        puArray[bufferPublicacionIndex].estado = NO_ACTIVA;
                        output = 0;
                        flagCase = 1;
                    }
                    else
                    {
                        if(!utn_getIntConMinMax("(0). CONFIRMAR\n(1). CANCELAR: ","Error, reintentos", &confirmaEliminacion,0,1,3)
                                && confirmaEliminacion == 0)
                        {
                            puArray[bufferPublicacionIndex].estado = ACTIVA;
                            output = 0;
                            flagCase = 1;
                        }
                    }
                    if(confirmaEliminacion == 1)
                    {
                        output = 1;
                    }
                    break;
                case 4:
                    if(flagCase == 0)
                    {
                        output = 1;
                    }
                    printf("VOLVIENDO AL MENU PRINCIPAL\n");
                    break;
                default:
                    printf("OPCION INVALIDA, VUELVA A INTENTAR\n");
                }
            }
        }while(bufferOpcionMenu != 4);
    }

    return output;
}

/**
 * @fn int cliente_publicacion_CalcularCantidadDeAvisosPorCliente(Publicacion*, int, Publicacion, int*)
 * @brief Funcion que cuenta la cantidad de avisos que tiene un solo Cliente
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param elemento: Un elemento de tipo Publicacion
 * @param pResultado: El puntero a int donde se guardaran la cantidad de avisos
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_CalcularCantidadDeAvisosPorCliente(Publicacion *puArray, int lenPublicacion, Publicacion elemento, int *pResultado)
{
    int output = -1;
    int contadorDeAvisos = 0;

    if(puArray != NULL  && pResultado != NULL && lenPublicacion > 0 && elemento.isEmpty == FALSE)
    {
        for(int x = 0; x < lenPublicacion; x++)
        {
            if(puArray[x].idCliente == elemento.idCliente)
            {
                contadorDeAvisos++;
            }
        }
        *pResultado = contadorDeAvisos;
        output = 0;
    }
    return output;
}

/**
 * @fn int cliente_publicacion_CalcularClientesConMasAvisos(Publicacion*, int, Cliente*, int, int*, int*)
 * @brief Funcion que calcula de entre todos los Clientes, aquel que tiene mas avisos
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @param bufferIndex: El puntero a int que guarda el Indice del cliente con mas avisos
 * @param contadorAvisos: El puntero a int que guarda el valor total de avisos del cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_CalcularClientesConMasAvisos(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente, int *bufferIndex, int *contadorAvisos)
{
    int output = -1;
    int bufferContador = 0;
    int bufferMax = bufferContador;
    int bufferClienteID;
    int bufferClienteIndex;

    if(puArray != NULL && paArray != NULL && bufferIndex!= NULL && contadorAvisos != NULL && lenPublicacion > 0 && lenCliente > 0)
    {
        for(int x = 0; x < lenPublicacion; x++)
        {
            if(!(cliente_publicacion_CalcularCantidadDeAvisosPorCliente(puArray, lenPublicacion, puArray[x], &bufferContador)))
            {
                if(bufferMax < bufferContador || x == 0)
                {
                    bufferMax = bufferContador;
                    bufferClienteID = puArray[x].idCliente;
                }
            }
        }
        if(!(cliente_FindById(paArray, lenCliente, bufferClienteID, &bufferClienteIndex)))
        {
            *bufferIndex = bufferClienteIndex;
            *contadorAvisos = bufferMax;
            output = 0;
        }
    }
    return output;
}

/**
 * @fn int cliente_publicacion_CalcularCantidadDeAvisosPausados(Publicacion*, int, int*)
 * @brief Funcion que calcula la cantidad de avisos pausados
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param bufferContador: El puntero a int que devuele la cantitad total de avisos pausados
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_CalcularCantidadDeAvisosPausados(Publicacion *puArray, int lenPublicacion, int *bufferContador)
{
    int output = -1;
    int bufferContadorAvisosPausados = 0;

    for(int x = 0; x< lenPublicacion; x++)
    {
        if(puArray[x].isEmpty == FALSE && puArray[x].estado == NO_ACTIVA)
        {
            bufferContadorAvisosPausados++;
            output = 0;
        }
    }
    *bufferContador = bufferContadorAvisosPausados;
    return output;
}

/**
 * @fn int cliente_publicacion_CalcularRubroConMasAvisos(Publicacion*, int)
 * @brief
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @return
 */
int cliente_publicacion_CalcularRubroConMasAvisos(Publicacion *puArray, int lenPublicacion, char *msg, int *pContador)
{
    int output = -1;
    int avisos[5] = {0};
    int bufferMax = 0;
    char bufferStrAvisos[5][20] = {"CLASIFICADOS", "OBITUARIOS", "DEPORTES", "POLICIALES", "EMPLEOS"};

    if(puArray != NULL && msg != NULL && pContador != NULL && lenPublicacion >0)
    {
        for(int x = 0; x <lenPublicacion; x++)
        {
            if(puArray[x].isEmpty == FALSE)
            {
                if(puArray[x].numeroRubro == 0)
                {
                    avisos[0] +=1;
                }
                else if(puArray[x].numeroRubro == 1)
                {
                    avisos[1] +=1;
                }
                else if(puArray[x].numeroRubro == 2)
                {
                    avisos[2] +=1;
                }
                else if(puArray[x].numeroRubro == 3)
                {
                    avisos[3] +=1;
                }
                else if(puArray[x].numeroRubro == 4)
                {
                    avisos[4] +=1;
                }
            }
        }
        for(int x = 0; x < 5; x++)
        {
            if(bufferMax < avisos[x] || x == 0)
            {
                bufferMax = avisos[x];
                sprintf(msg, bufferStrAvisos[x]);
            }
        }
        *pContador = bufferMax;
        output = 0;
    }
    return output;
}

/**
 * @fn int cliente_publicacion_Informes(Publicacion*, int, Cliente*, int)
 * @brief Funcion que muestra un menu de Informes
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_publicacion_Informes(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente, Rubro *ruArray, int lenRubro)
{
    int output = -1;
    int flagGeneroInforme = 0;
    int bufferOpcionInformes;
    int bufferTotalAvisos;
    int bufferClienteConMasAvisosIndex;
    int bufferRubroConMasAvisos;
    if (puArray != NULL && paArray != NULL && lenPublicacion > 0 && lenCliente > 0)
    {
        do
        {
            if (!(menu_Informes(&bufferOpcionInformes)))
            {
                switch (bufferOpcionInformes)
                {
                case 1:
                    if(!(cliente_publicacion_CalcularClientesConMasAvisos(puArray, lenPublicacion, paArray, lenCliente, &bufferClienteConMasAvisosIndex, &bufferTotalAvisos)))
                    {
                        printf("\nEL CLIENTE CON MAS AVISOS ES %s %s CON UN TOTAL DE %d\n", paArray[bufferClienteConMasAvisosIndex].name, paArray[bufferClienteConMasAvisosIndex].lastName, bufferTotalAvisos);
                        output = 0;
                        flagGeneroInforme = 1;
                    }
                    break;
                case 2:
                    if(!(cliente_publicacion_CalcularCantidadDeAvisosPausados(puArray, SIZE_ARRAY_PUBLICACION, &bufferTotalAvisos))
                            && bufferTotalAvisos > 0)
                    {
                        printf("\nCANTITAD TOTAL DE AVISOS PAUSADOS: %d\n", bufferTotalAvisos);
                        output = 0;
                    }
                    else
                    {
                        printf("\nNO EXISTEN AVISOS PAUSADOS, TODOS ESTAN ACTIVOS\n");
                        output = 0;
                    }
                    flagGeneroInforme = 1;
                    break;
                case 3:
                    if(!(rubro_GenerarRubros(ruArray, lenRubro, puArray))
                            && !(rubro_CalcularRubroConMasAvisos(ruArray, lenRubro, puArray, lenPublicacion, &bufferRubroConMasAvisos)))
                    {
                        if(bufferRubroConMasAvisos == -1)
                        {
                            printf("\nNO EXISTE RUBRO CON MAS AVISOS\n");
                        }
                        else
                        {
                            printf("\nEL RUBRO CON MAS AVISOS ES: %d\n", bufferRubroConMasAvisos);
                        }
                        output = 0;
                    }
                    flagGeneroInforme = 1;
                    break;
                case 4:
                    if(flagGeneroInforme == 0)
                    {
                        output = 1;
                    }
                    printf("VOLVIENDO AL MENU PRINCIPAL\n");
                    break;
                default:
                    printf("OPCION INVALIDA\n");
                }
            }
        } while (bufferOpcionInformes != 4);
    }
    return output;
}

