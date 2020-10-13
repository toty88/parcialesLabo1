#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"cliente_publicacion.h"


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

