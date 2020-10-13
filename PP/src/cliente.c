#include "cliente.h"

#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/**
 * @fn int cliente_HardCodeo(Cliente*)
 * @brief Funcion que da valores iniciales a 5 clientes
 *
 * @param pArray: El puntero al array de tipo Cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_HardCodeo(Cliente *pArray) {
    int output = -1;
    int bufferID[5] =                   {   100,                  101,            102,            103,            104           };
    char bufferName[5][SIZE_STR] =      {   "EDGARDO HORACIO",    "ANGUS",        "BRIAN",        "RICARDO",      "BRUCE"       };
    char bufferLastName[5][SIZE_STR] =  {   "LORENZO",            "DICIKINSON",   "JHONSON",      "IORIO",        "DICIKINSON"  };
    char bufferCuit[5][SIZE_STR] =      {   "2336330972",          "2456787196",   "3689210751",   "2903221487",   "4107389873" };

    if (pArray != NULL) {
        for (int x = 0; x < 5; x++) {
            strncpy(pArray[x].name, bufferName[x], SIZE_STR);
            strncpy(pArray[x].lastName, bufferLastName[x], SIZE_STR);
            strncpy(pArray[x].cuit, bufferCuit[x], SIZE_STR);
            pArray[x].id = bufferID[x];
            pArray[x].isEmpty = FALSE;
        }
        output = 0;
    }
    return output;
}

/**
 * @fn int cliente_Init(Cliente*, int)
 * @brief Funcion que setea todos los campos isEmpty de cada elemento de tipo Cliente en TRUE
 *
 * @param pArray: EL puntero al array de tipo Cliente
 * @param len: La longitud del array de tipo Cliente
 * @return (-1) Error (0) todo ok
 */
int cliente_Init(Cliente *pArray, int len) {
    int output = -1;
    if (pArray != NULL && len > 0) {
        for (int x = 0; x < len; x++) {
            pArray[x].isEmpty = TRUE;
        }
        output = 0;
    }
    return output;
}

/**
 * @fn int cliente_FindById(Cliente*, int, int, int*)
 * @brief Funcion que encuentra el indice de un elemento de tipo Cliente en base al ID
 *
 * @param pArray: EL puntero al array de tipo Cliente
 * @param len: La longitud del array de tipo Cliente
 * @param id: El ID a comparar con los elementos del array
 * @param indexPosition: El puntero a int donde se guardara la posiscion del elemento, si se encuentra
 * @return (-1) Error (0) todo OK
 */
int cliente_FindById(Cliente *pArray, int len, int id, int *indexPosition) {

    int output = -1;
    if (pArray != NULL && indexPosition != NULL && len > 0 && id > 0) {
        for (int x = 0; x < len; x++) {
            if (pArray[x].id == id && pArray[x].isEmpty == FALSE) {
                *indexPosition = x;
                output = 0;
                break;
            }
        }
    }
    return output;
}

/**
 * @fn int cliente_DoesIdExist(Cliente*, int, int)
 * @brief Funcion que pregunta si existe un determinado ID dentro del array de tipo Cliente
 *
 * @param pArray: EL puntero al array de tipo Cliente
 * @param len: La longitud del array de tipo cliente
 * @param id: El ID a comparar
 * @return (0) No existe (1) Existe
 */
int cliente_DoesIdExist(Cliente *pArray, int len, int id) {

    int output = 0;
    if (pArray != NULL && len > 0 && id > 0) {
        for (int x = 0; x < len; x++) {
            if (pArray[x].id == id && pArray[x].isEmpty == FALSE) {
                output = 1;
                break;
            }
        }
    }
    return output;
}

/**
 * @fn int cliente_FindFree(Cliente*, int, int*)
 * @brief Funcion que encuentra el primer indice libre dentro del array de tipo Cliente
 *
 * @param pArray: EL puntero al array de tipo Cliente
 * @param len: La longitud del array de tipo cliente
 * @param freeIndexPosition: EL puntero a int donde se guardara el indice libre
 * @return (-1) Error (0) todo OK
 */
int cliente_FindFree(Cliente *pArray, int len, int *freeIndexPosition) {
    int output = -1;
    if (pArray != NULL && freeIndexPosition != NULL && len > 0) {
        for (int x = 0; x < len; x++) {
            if (pArray[x].isEmpty == TRUE) {
                *freeIndexPosition = x;
                output = 0;
                break;
            }
        }
    }
    return output;
}

/**
 * @fn int cliente_GenerateId(int*)
 * @brief Funcion privada que calcula un id de forma incremental
 *
 * @param ClienteID: El puntero a int donde se guardara el ID generado
 * @return (-1) Error (0) todo OK
 */
static int cliente_GenerateId(int *ClienteID) {

    int output = -1;
    static int id = 105;
    if (ClienteID != NULL) {
        *ClienteID = id++;
        output = 0;
    }
    return output;
}

/**
 * @fn int cliente_Create(Cliente*, int)
 * @brief Funcion que solicita los campos de un elemento de tipo Cliente
 *
 * @param pArray: EL puntero al array de tipo Cliente
 * @param len: La longitud del array de tipo cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_Create(Cliente *pArray, int len) {

    int output = -1;
    Cliente bufferAux;
    int bufferIndex;

    if (pArray != NULL && len > 0 && !(cliente_FindFree(pArray, len, &bufferIndex))) {
        if (!(utn_getString("(a). Ingrese nombre: ", "Error, reintentos", bufferAux.name, SIZE_STR, 3))
                && !(utn_getString("(b). Ingrese apellido: ", "Error, reintentos", bufferAux.lastName, SIZE_STR, 3))
                && !(utn_getStringWithNumbers("Ingrese CUIT: ", "Error,  reintentos", bufferAux.cuit, SIZE_STR, 3))
                && !(cliente_GenerateId(&bufferAux.id)))
        {

            pArray[bufferIndex] = bufferAux;
            pArray[bufferIndex].isEmpty = FALSE;

            output = 0;
        }
    }
    return output;
}

/**
 * @fn int cliente_Modify(Cliente*, int)
 * @brief Funcion que permite modificar campos de un elemento de tipo Cliente
 *
 * @param pArray: EL puntero al array de tipo Cliente
 * @param len: La longitud del array de tipo cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_Modify(Cliente *pArray, int len) {
    int output = -1;
    int opcionMenuModificaciones;
    int flag;
    int bufferID;
    int bufferIndex;
    Cliente bufferAux;

    if (pArray != NULL && len > 0) {
        do
        {
            if (!(menu_Modificar(&opcionMenuModificaciones)))
            {
                switch (opcionMenuModificaciones)
                {
                case 1:
                    if (!cliente_printAll(pArray, len))
                    {
                        output = 1;
                    }
                    break;
                case 2:
                    if (!(utn_getInt("\nINGRESE ID DEL CLIENTE: ","Error, reintentos", &bufferID, 3)))
                    {
                        if (cliente_FindById(pArray, len, bufferID, &bufferIndex))
                        {
                            printf("ID INVALIDO, VUELVA A LISTAR COMPLETAR O SALGA\n");
                        }
                        else
                        {
                            flag = 1;
                        }
                        output = 1;
                    }
                    break;
                case 3:
                    if (flag == 1)
                    {
                        if (!(utn_getString("\n(a). Ingrese nuevo nombre: ", "Error, reintentos", bufferAux.name,
                                SIZE_STR, 3)))
                        {
                            strncpy(pArray[bufferIndex].name, bufferAux.name, SIZE_STR);
                            output = 0;
                        }
                    }
                    else
                    {
                        printf("DEBE INGRESAR ID PRIMERO\n");
                        output = 1;
                    }
                    break;
                case 4:
                    if (flag == 1)
                    {
                        if (!(utn_getString("(b). Ingrese nuevo apellido: ","Error, reintentos", bufferAux.lastName,SIZE_STR, 3)))
                        {
                            strncpy(pArray[bufferIndex].lastName,bufferAux.lastName, SIZE_STR);
                            output = 0;
                        }
                    }
                    else
                    {
                        printf("DEBE INGRESAR ID PRIMERO\n");
                        output = 1;
                    }
                    break;
                case 5:
                    if (flag == 1)
                    {
                        if (!(utn_getString("(b). Ingrese nuevo cuit: ","Error, reintentos", bufferAux.cuit,SIZE_STR, 3)))
                        {
                            strncpy(pArray[bufferIndex].cuit,bufferAux.cuit, SIZE_STR);
                            output = 0;
                        }
                    }
                    else
                    {
                        printf("DEBE INGRESAR ID PRIMERO\n");
                        output = 1;
                    }
                    break;
                case 6:
                   printf("SALIENDO AL MENU PRINCIPAL\n");
                    break;
                default:
                    printf("ERROR, OPCION INVALIDA\n");
                }
            }
            printf("\nPresione una tecla para continuar");
            __fpurge(stdin);
            getchar();
            system("clear");
        } while (opcionMenuModificaciones != 6);
    }
    return output;
}

/**
 * @fn int cliente_PrintOne(Cliente)
 * @brief Funcion que muestra por pantalla un elemento de tipo Cliente
 *
 * @param Cliente: El elemento de tipo Cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_PrintOne(Cliente Cliente) {
    int output = -1;
    if(Cliente.isEmpty == FALSE){
        printf("# %d %15s %15s %12s\n", Cliente.id, Cliente.name,
                Cliente.lastName, Cliente.cuit);
        output = 0;
    }
    return output;
}

/**
 * @fn int cliente_printAll(Cliente*, int)
 * @brief Funcion que imprime todos los elementos de un array de tipo Cliente
 *
 * @param pArray: El puntero al array de tipo Cliente
 * @param len: La longitud del array de tipo cliente
 * @return (-1) Error (0) todo OK
 */
int cliente_printAll(Cliente *pArray, int len) {
    int output = -1;
    if (pArray != NULL && len > 0) {
        printColumn();
        for (int x = 0; x < len; x++) {
            cliente_PrintOne(pArray[x]);
        }
        output = 0;
    }
    return output;
}










/*
 * ################# POSIBLES FUNCIONES ##################
 */

//int cliente_Sort(Cliente *pArray, int len, int order) {
//    int output = -1;
//    int flag = 1;
//    Cliente bufferAux;
//    if (pArray != NULL && len > 0 && (order == 1 || order == 2)) {
//        do {
//            flag = 0;
//            for (int x = 0; x < (len-1); x++){
//
//                  if(
//                    ((order == 1) &&
//                    (strncmp(pArray[x].lastName, pArray[x+1].lastName, SIZE_STR) > 0 ||
//                    (strncmp(pArray[x].lastName, pArray[x+1].lastName, SIZE_STR) == 0 &&
//                    pArray[x].sector > pArray[x+1].sector)) )
//                    ||
//                    ((order == 2) &&
//                    (strncmp(pArray[x].lastName, pArray[x+1].lastName, SIZE_STR) < 0 ||
//                    (strncmp(pArray[x].lastName, pArray[x+1].lastName, SIZE_STR) == 0 &&
//                    pArray[x].sector < pArray[x+1].sector)) )
//
//                )
//                {
//
//                    bufferAux = pArray[x];
//                    pArray[x] = pArray[x + 1];
//                    pArray[x + 1] = bufferAux;
//                    flag = 1;
//                    output = 0;
//                }
//            }
//        } while (flag);
//    }
//
//    return output;
//}

//int cliente_Reports(Cliente *pArray, int len) {
//
//    int output = -1;
//    int order;
//
//    int opcionMenuInformes;
//
//    if (pArray != NULL && len > 0) {
//        do {
//            __fpurge(stdin);
//            if (!(menu_Baja(&opcionMenuInformes))) {
//                switch (opcionMenuInformes) {
//                case 1:
//                    if (cliente_printAll(pArray, len)) {
//                        printf("Error al listar elementos\n");
//                    }
//                    break;
//
//                case 2:
//                    if (!(utn_getInt(
//                            "\n(1). ORDENAR POR COMPLETAR DE FORMA ASCENDENTE"
//                            "\n(2). ORDENAR POR COMPLETAR DE FORMA DESCENDENTE: ",
//                            "ERROR, REINTENTOS", &order, 3)) && !(cliente_Sort(pArray, len, order)))
//                    {
//                        cliente_printAll(pArray, len);
//                        output = 0;
//                    }
//                    break;
//                case 3:
//                    printf("SALIENDO AL MENU PRINCIPAL\n");
//                    break;
//                default:
//                    printf("ERROR, OPCION INVALIDA\n");
//                }
//            }
//            printf("\nPresione una tecla para continuar");
//            __fpurge(stdin);
//            getchar();
//            system("clear");
//        } while (opcionMenuInformes != 3);
//    }
//    return output;
//}


// * @fn int getClientesAverageSalary(Cliente*, int, float*, float*)
// * @brief Funcion que calcula la suma total de los salarios y el salario promedio
// *
// * @param pArray: Array de elementos de tipo Empleado
// * @param len: La cantidad de elementos del array de tipo Empleado
// * @param pAverageSalary: El puntero a float donde se guardara el salario promedio calculado
// * @param pTotalSalarios: EL puntero a float donde se guardara la suma total de los salarios
// * @return (-1) Error (0) todo OK
// */
//int getClientesAverageSalary(Cliente *pArray, int len, float *pAverageSalary, float *pTotalSalarios) {
//
//    int output = -1;
//    float bufferTotalSalary = 0;
//    int bufferAmountOfActiveClientes = 0;
//    if (pArray != NULL && pAverageSalary != NULL && pTotalSalarios != NULL
//            && len > 0) {
//
//        for (int x = 0; x < len; x++) {
//            if (pArray[x].isEmpty == FALSE) {
//                bufferTotalSalary += pArray[x].salary;
//                bufferAmountOfActiveClientes++;
//            }
//        }
//        if (bufferAmountOfActiveClientes > 0) {
//            *pTotalSalarios = bufferTotalSalary;
//            *pAverageSalary = bufferTotalSalary / bufferAmountOfActiveClientes;
//            output = 0;
//        }else{
//            *pTotalSalarios = 0;
//            *pAverageSalary = 0;
//            output = 0;
//        }
//    }
//    return output;
//}
//
///**
// * @fn int getClientesAboveAverageSalary(Cliente*, int, int)
// * @brief Funcion que imprime los empleados que tengan salarios por encima del salario promedio
// *
// * @param pArray: Array de elementos de tipo Empleado
// * @param len: La cantidad de elementos del array de tipo Empleado
// * @param averageSalary: El salario promedio
// * @return (-1) Error (0) todo OK
// */
//int getClientesAboveAverageSalary(Cliente *pArray, int len, int averageSalary) {
//
//    int output = -1;
//    if (pArray != NULL && len > 0 && averageSalary > 0) {
//        printColumnAboveAverageSalary();
//        for (int x = 0; x < len; x++) {
//            if (pArray[x].isEmpty == FALSE && pArray[x].salary > averageSalary) {
//                cliente_PrintOne(pArray[x]);
//            }
//        }
//        output = 0;
//    }
//    return output;
//
//}

