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
                "(3).  MODIFICAR VENTA\n"
                "(4).  COBRAR VENTA\n"
                "(5).  GENERAR INFORMES\n"
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

int menu_ModifyVenta(int *pResultado)
{
    int output = -1;
    int opcion;
    if(pResultado != NULL)
    {
        if(!(utn_getInt(
                      "\n######################################################\n"
                        "################### MENU MODIFICAR ###################\n"
                        "######################################################\n"
                        "(1). LISTAR VENTAS\n"
                        "(2). INGRESE ID DE VENTA\n"
                        "(3). MODIFICAR CANTIDAD DE AFICHES\n"
                        "(4). MODIFICAR NOMBRE DEL ARCHIVO\n"
                        "(5). MODIFICAR ZONA\n"
                        "(6). VOLVER MENU PRINCIPAL -------------> ","EROR, OPCION INVALIDA. REINTENTOS", &opcion, 3)))
        {
            *pResultado = opcion;
            output = 0;
            }
    }
    return output;
}

int menu_CobrarVenta(int *pResultado)
{
    int output = -1;
    int opcion;
    if(pResultado != NULL)
    {
        if(!(utn_getInt(
                      "\n######################################################\n"
                        "################# MENU COBRAR VENTA ##################\n"
                        "######################################################\n"
                        "(1). LISTAR VENTAS\n"
                        "(2). INGRESE ID DE VENTA\n"
                        "(3). CONFIRMAR COBRO\n"
                        "(4). VOLVER MENU PRINCIPAL -------------> ","EROR, OPCION INVALIDA. REINTENTOS", &opcion, 3)))
        {
            *pResultado = opcion;
            output = 0;
            }
    }
    return output;
}

int menu_generarInformes(int *pResultado)
{
    int output = -1;
    int opcion;
    if(pResultado != NULL)
    {
        if(!(utn_getInt(
                      "\n######################################################\n"
                        "################### MENU INFORMES ####################\n"
                        "######################################################\n"
                        "(1). GENERAR INFORME DE COBROS\n"
                        "(2). GENERAR INFORME DE DEUDAS\n"
                        "(3). GENERAR ESTADISTICAS\n"
                        "(4). VOLVER MENU PRINCIPAL -------------> ","EROR, OPCION INVALIDA. REINTENTOS", &opcion, 3)))
        {
            *pResultado = opcion;
            output = 0;
            }
    }
    return output;
}

/* ########################## PRINTS ##################################*/

int printColumnClientes(void){

    char sp = ' ';

    printf(
      "\n#########################################################################\n"
        "########################### LISTA DE CLIENTES ###########################\n"
        "#########################################################################\n");
    printf("# %1cID%15cNOMBRE%13cAPELLIDO%22cCUIT\n", sp, sp, sp, sp);
    printf("#########################################################################\n\n");
    return 0;
}

int printColumnVentas(void){

    char sp = ' ';

    printf(
      "\n##################################################################################################################\n"
        "############################################# LISTA DE VENTAS ####################################################\n"
        "##################################################################################################################\n");
    printf("# %1cID_VENTA%3cID_CLIENTE%5cCANT_AFICHES%12cZONA%10cESTADO%27cNOMBRE_ARCHIVO\n", sp, sp, sp, sp, sp, sp);
    printf("##################################################################################################################\n\n");
    return 0;
}







/*
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
