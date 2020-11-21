#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include"utn.h"

/* ########################## MENUES ##################################*/

/****************************************************
    Menu:
    (1).  CARGAR DATOS DESDE DATA.CSV (MODO TEXTO)
    (2).  IMPRIMIR ENVIOS
    (3).  CALCULAR COSTOS
    (4).  GENERAR ARCHIVO DE COSTOS PARA ZONA
    (5).  IMPRIMIR LISTA DE ZONAS
    (6).  SALIR
*****************************************************/
int menu_Main(int *pResultado)
{
    int output = -1;
    int opcion;
    if (pResultado != NULL)
    {
        if (!(utn_getInt(
              "\n######################################################\n"
                "#################### MENU MY_BOOK ####################\n"
                "######################################################\n"
                "(1).  AGREGAR CLIENTE\n"
                "(2).  VENDER AFICHES\n"
                "(3).  LISTAR VENTAS\n"
                "(4).  MODIFICAR VENTA\n"
                "(5).  COBRAR VENTA\n"
                "(6).  SALIR -------------> ","EROR, OPCION INVALIDA. REINTENTOS", &opcion, 3)))
        {
            *pResultado = opcion;
            output = 0;
        }
    }
    return output;
}

int menu_VenderAfiches(int *pResultado)
{
    int output = -1;
    int opcion;
    if(pResultado != NULL)
    {
        __fpurge(stdin);
        if(!(utn_getInt(
          "\n######################################################\n"
            "################# MENU VENDER AFICHE #################\n"
            "######################################################\n"
            "(1). LISTAR CLIENTES\n"
            "(2). INGRESAR ID CLIENTE\n"
            "(3). INGRESAR CANTIDAD DE AFICHES, NOMBRE DEL ARCHIVO Y ZONA\n"
            "(4). VOLVER MENU PRINCIPAL -------------> ","EROR, OPCION INVALIDA. REINTENTOS", &opcion, 3)))
        {
            *pResultado = opcion;
            output = 0;
        }
    }
    return output;
}

/* ########################## PRINTS ##################################*/

int printColumn(void){

    char sp = ' ';

    printf(
      "\n###########################################################################################################\n"
        "############################################ LISTA DE ENVIOS ##############################################\n"
        "###########################################################################################################\n");
    printf("# %1cID_PRODUCTO%6cPRODUCTO%2cID_CAMION%4cZONA_DESTINO%14cKM%3cTIPO_ENTREGA%10cCOSTO_ENVIO\n", sp, sp, sp, sp, sp, sp, sp);
    printf("###########################################################################################################\n\n");
    return 0;
}






/*int menu_ModifyEmployee(int *pResultado)
{
    int output = -1;
    int opcion;
    if(pResultado != NULL)
    {
        if(!(utn_getInt(
                      "\n######################################################\n"
                        "################### MENU MODIFICAR ###################\n"
                        "######################################################\n"
                        "(1). LISTAR CLIENTES\n"
                        "(2). INGRESE ID DE CLIENTE\n"
                        "(3). MODIFICAR NOMBRE\n"
                        "(4). MODIFICAR HORAS TRABAJADAS\n"
                        "(5). MODIFICAR SUELDO\n"
                        "(6). VOLVER MENU PRINCIPAL -------------> ","EROR, OPCION INVALIDA. REINTENTOS", &opcion, 3)))
        {
            *pResultado = opcion;
            output = 0;
            }
    }
    return output;
}



int menu_SortEmployee(int *pResultado)
{
    int output = -1;
    int opcion;
    if(pResultado != NULL)
    {
        if(!(utn_getInt(""
                      "\n######################################################\n"
                        "################# MENU ORDENAMIENTO ##################\n"
                        "######################################################\n"
                        "(1). ORDENAR EMPLEADOS POR ID\n"
                        "(2). ORDENAR EMPLEADOS POR NOMBRE\n"
                        "(3). ORDENAR EMPLEADOS POR SUELDO\n"
                        "(4). ORDENAR EMPLEADOS POR HORAS TRABJADAS\n"
                        "(5). VOLVER MENU PRINCIPAL -------------> ","EROR, OPCION INVALIDA. REINTENTOS", &opcion, 3)))
        {
            *pResultado = opcion;
            output = 0;
        }

    }
    return output;
}*/
