#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "publicacion.h"

/**
 * @fn int publicacion_HardCodeo(Publicacion*)
 * @brief Funcion que da valores iniciales a 5 publicaciones
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @return (-1) Error (0) todo OK
 */
int publicacion_HardCodeo(Publicacion *puArray) {
    int output = -1;
    int bufferID[5] =           {   1000, 1001,   1002,   1003,   1004    };
    int bufferClienteID[5] =    {   100,  101,    102,    103,    100     };
    int bufferRubro[5] =        {   4,    1,      2,      2,      4       };

    char bufferDescripcion[5][SIZE_AVISO] = {   "SE VENDEN ZAPATOS AL POR MAYOR",
                                                "ROBERTO... QUE EN PAZ DESCANCES",
                                                "GANO ARGENTINA",
                                                "13/10/2020 - TRES ASALTOS EN EL OBELISCO EL SABADO POR LA NOCHE",
                                                "SE BUSCAR BARTENDER CON EXPERIENCA" };
    if (puArray != NULL) {
        for (int x = 0; x < 5; x++) {
            strncpy(puArray[x].descripcionAviso, bufferDescripcion[x], SIZE_AVISO);
            puArray[x].numeroRubro = bufferRubro[x];
            puArray[x].id = bufferID[x];
            puArray[x].idCliente = bufferClienteID[x];
            puArray[x].isEmpty = FALSE;
            puArray[x].estado = ACTIVA;
        }
        output = 0;
    }
    return output;
}

/**
 * @fn int publicacion_Init(Publicacion*, int)
 * @brief Funcion que setea todos los campos isEmpty de cada elemento de tipo Publicacion en TRUE
 *
 * @param puArray: EL puntero al array de tipo Publicacion
 * @param len: La longitud del array de tipo Publicacion
 * @return (-1) Error (0) todo ok
 */
int publicacion_Init(Publicacion *puArray, int len) {
    int output = -1;
    if (puArray != NULL && len > 0) {
        for (int x = 0; x < len; x++) {
            puArray[x].isEmpty = TRUE;
        }
        output = 0;
    }
    return output;
}

/**
 * @fn int publicacion_FindById(Publicacion*, int, int, int*)
 * @brief Funcion que encuentra el indice de un elemento de tipo Publicacion en base al ID de publicacion
 *
 * @param puArray: EL puntero al array de tipo Publicacion
 * @param len: La longitud del array de tipo Publicacion
 * @param id: El ID de publicacion a comparar con los elementos del array
 * @param indexPosition: El puntero a int donde se guardara la posiscion del elemento, si se encuentra
 * @return (-1) Error (0) todo OK
 */
int publicacion_FindById(Publicacion *puArray, int len, int id, int *indexPosition) {

    int output = -1;
    if (puArray != NULL && indexPosition != NULL && len > 0 && id > 0) {
        for (int x = 0; x < len; x++) {
            if (puArray[x].id == id && puArray[x].isEmpty == FALSE) {
                *indexPosition = x;
                output = 0;
                break;
            }
        }
    }
    return output;
}

/**
 * @fn int publicacion_FindByClientId(Publicacion*, int, int, int*)
 * @brief Funcion que encuentra un indice de un elemento en base a un ID de cliente
 *
 * @param puArray: EL puntero al array de tipo Publicacion
 * @param len: La longitud del array de tipo Publicacion
 * @param id: El ID del cliente a comparar con los elementos del array
 * @param indexPosition: El puntero a int donde se guardara la posiscion del elemento, si se encuentra
 * @return (-1) Error (0) todo OK
 */
int publicacion_FindByClientId(Publicacion *puArray, int len, int id, int *indexPosition) {

    int output = -1;
    if (puArray != NULL && indexPosition != NULL && len > 0 && id > 0) {
        for (int x = 0; x < len; x++) {
            if (puArray[x].idCliente == id && puArray[x].isEmpty == FALSE) {
                *indexPosition = x;
                output = 0;
                break;
            }
        }
    }
    return output;
}

/**
 * @fn int publicacion_FindFree(Publicacion*, int, int*)
 * @brief Funcion que encuentra el primer indice libre dentro del array de tipo Publicacion
 *
 * @param puArray: EL puntero al array de tipo Publicacion
 * @param len: La longitud del array de tipo Publicacion
 * @param freeIndexPosition: EL puntero a int donde se guardara el indice libre
 * @return (-1) Error (0) todo OK
 */
int publicacion_FindFree(Publicacion *puArray, int len, int *freeIndexPosition) {
    int output = -1;
    if (puArray != NULL && freeIndexPosition != NULL && len > 0) {
        for (int x = 0; x < len; x++) {
            if (puArray[x].isEmpty == TRUE) {
                *freeIndexPosition = x;
                output = 0;
                break;
            }
        }
    }
    return output;
}

/**
 * @fn int publicacion_GenerateId(int*)
 * @brief Funcion privada que calcula un id de forma incremental
 *
 * @param PublicacionID: El puntero a int donde se guardara el ID generado
 * @return (-1) Error (0) todo OK
 */
static int publicacion_GenerateId(int *PublicacionID) {

    int output = -1;
    static int id = 1005;
    if (PublicacionID != NULL) {
        *PublicacionID = id++;
        output = 0;
    }
    return output;
}

/**
 * @fn int publicacion_Create(Publicacion*, int, int*)
 * @brief Funcion que pide los datos de una publicacion
 *
 * @param puArray: EL puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param bufferIndice: El puntero de tipo entero donde se guardara el indice del nuevo elemento
 * @return (-1) Error (0) todo OK
 */
int publicacion_Create(Publicacion *puArray, int lenPublicacion, int *bufferIndice)
{
    int output = -1;
    Publicacion bufferAux;
    int bufferIndex;

    if (puArray != NULL && lenPublicacion > 0&& !(publicacion_FindFree(puArray, lenPublicacion, &bufferIndex)))
    {
        if (!(utn_getIntConMinMax("\n(a). SELECCIONE RUBRO ENTRE [1:100] -------------> ", "Error, rubro incorrecto - reintentos",
                &bufferAux.numeroRubro, 1, 100, 3))
                && !(utn_getStringWithNumbersAndSymbols("(b). INGRESE DESCRIPCION DEL AVISO: ", "Error, reintentos",
                bufferAux.descripcionAviso, SIZE_AVISO, 3))
                && !(publicacion_GenerateId(&bufferAux.id)))
        {
            *bufferIndice = bufferIndex;
            puArray[bufferIndex] = bufferAux;
            puArray[bufferIndex].isEmpty = FALSE;
            puArray[bufferIndex].estado = ACTIVA;
            output = 0;
        }
    }
    return output;
}

/**
 * @fn int publicacion_Remove(Publicacion*, int, int)
 * @brief Funcion que setea el campo isEmpty en TRUE
 *
 * @param puArray: EL puntero al array de tipo Publicacion
 * @param lenPublicacion: La longitud del array de tipo Publicacion
 * @param bufferClienteID: El ID del cliente que sirve para comparar con el ID cliente dentro del array de tipo Publicacion
 * @return (-1) Error (0) todo OK
 */
int publicacion_Remove(Publicacion *puArray, int lenPublicacion, int bufferClienteID) {
    int output = -1;

    if(puArray != NULL && lenPublicacion > 0 && bufferClienteID >= 100)
    {
        for(int x = 0; x < lenPublicacion; x++)
        {
            if(puArray[x].idCliente == bufferClienteID)
            {
                puArray[x].isEmpty = TRUE;
                output = 0;
            }
        }
    }
    return output;
}

/**
 * @fn int publicacion_PrintOne(Publicacion)
 * @brief Funcion que muestra por pantalla un elemento de tipo Publicacion
 *
 * @param Publicacion: El elemento de tipo Publicacion
 * @return (-1) Error (0) todo OK
 */
int publicacion_PrintOne(Publicacion Publicacion) {
    int output = -1;
    char estado[10];
    if(Publicacion.isEmpty == FALSE){
        if(Publicacion.estado == ACTIVA)
        {
            sprintf(estado, "ACTIVA");
        }
        else
        {
            sprintf(estado, "PAUSADA");
        }
        printf("# %d %13d %12s %70s\n", Publicacion.id, Publicacion.numeroRubro, estado, Publicacion.descripcionAviso);

        output = 0;
    }
    return output;
}

/**
 * @fn int publicacion_printAll(Publicacion*, int)
 * @brief Funcion que imprime todos los elementos de un array de tipo Publicacion
 *
 * @param puArray: El puntero al array de tipo Publicacion
 * @param len: La longitud del array de tipo Publicacion
 * @return (-1) Error (0) todo OK
 */
int publicacion_printAll(Publicacion *puArray, int len) {
    int output = -1;
    if (puArray != NULL && len > 0) {
        printColumnPublicacion();
        for (int x = 0; x < len; x++) {
            publicacion_PrintOne(puArray[x]);
        }
        output = 0;
    }
    return output;
}





