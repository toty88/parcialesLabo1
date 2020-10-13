#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"informes.h"


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

/**
 * @fn int informes_CalcularClientesConMasAvisos(Publicacion*, int, Cliente*, int, int*, int*)
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
int informes_CalcularClientesConMasAvisos(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente, int *bufferIndex, int *contadorAvisos)
{
    int output = -1;
    int bufferContador = 0;
    int bufferMax;

    if(puArray != NULL && paArray != NULL && bufferIndex!= NULL && contadorAvisos != NULL && lenPublicacion > 0 && lenCliente > 0)
    {
        for(int x = 0; x < lenCliente; x++)
        {
            if(paArray[x].isEmpty == FALSE)
            {
                for(int j = 0; j < lenPublicacion; j++)
                {
                    if(puArray[j].isEmpty == FALSE && paArray[x].id == puArray[j].idCliente)
                    {
                        bufferContador++;
                    }
                }
                if(bufferMax < bufferContador || x == 0)
                {
                    bufferMax = bufferContador;
                    *bufferIndex = x;
                    *contadorAvisos = bufferMax;
                    output = 0;
                }
                else if(bufferMax == bufferContador)
                {
                    output = 1;
                }
                bufferContador = 0;
            }
        }
    }
    return output;
}

/**
 * @fn int informes_CalcularCantidadDeAvisosPausados(Publicacion*, int, int*)
 * @brief Funcion que calcula la cantidad de avisos pausados
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param bufferContador: El puntero a int que devuele la cantitad total de avisos pausados
 * @return (-1) Error (0) todo OK
 */
int informes_CalcularCantidadDeAvisosPausados(Publicacion *puArray, int lenPublicacion, int *bufferContador)
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
 * @fn int informes_GenerarInformes(Publicacion*, int, Cliente*, int)
 * @brief Funcion que muestra un menu de Informes
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param paArray: El puntero al array de tipo Cliente
 * @param lenCliente: La longitud del array de tipo Cliente
 * @return (-1) Error (0) todo OK
 */
int informes_GenerarInformes(Publicacion *puArray, int lenPublicacion, Cliente *paArray, int lenCliente, Rubro *ruArray, int lenRubro)
{
    int output = -1;
    int flagGeneroInforme = 0;
    int bufferResultado;
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
                    bufferResultado = (informes_CalcularClientesConMasAvisos(puArray, lenPublicacion, paArray, lenCliente, &bufferClienteConMasAvisosIndex, &bufferTotalAvisos));
                    if(bufferResultado == 1)
                    {

                            printf("\nEXISTEN VARIOS CLIENTES CON LA MISMA CANTIDAD DE AVISOS\n");
                    }
                    else if(bufferResultado == 0)
                    {
                        printf("\nEL CLIENTE CON MAS AVISOS ES %s %s CON UN TOTAL DE %d\n", paArray[bufferClienteConMasAvisosIndex].name, paArray[bufferClienteConMasAvisosIndex].lastName, bufferTotalAvisos);
                    }
                    else
                    {
                        printf("\nERROR AL LISTAR CLIENTE CON MAS AVISOS\n");
                    }
                        output = 0;
                        flagGeneroInforme = 1;
                    break;
                case 2:
                    if(!(informes_CalcularCantidadDeAvisosPausados(puArray, SIZE_ARRAY_PUBLICACION, &bufferTotalAvisos))
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
                            printf("\nEXISTEN VARIOS RUBROS CON LA MISMA CANTIDAD DE AVISOS\n");
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


