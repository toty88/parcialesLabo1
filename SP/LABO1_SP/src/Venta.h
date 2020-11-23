/*
 * Venta.h
 *
 *  Created on: Nov 21, 2020
 *      Author: toty
 */

#ifndef VENTA_H_
#define VENTA_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utn.h"
#define SIZE_FILE_NAME 60
#define COBRADO 1
#define A_COBRAR 0

typedef struct
{
    int id_cliente;
    int id_venta;
    int cantidad_afiches;
    char nombre_archivo[SIZE_FILE_NAME];
    int zona;
    int estado;

}Venta;

/*      CONSTRUCTORES Y DESTRUCTOR     */
Venta* venta_new(void);
Venta* venta_newParam(int id_venta, int id_cliente, char* nombre_archivo, int cantidad_afiches, int zona);
Venta* venta_newParamTXT(char* id_venta, char* id_cliente, char* nombre_archivo, char* cantidad_afiches, char* zona,char* estado);
int venta_delete(Venta* this);

/*      SETTERS     */
int venta_setEstado(Venta* this, int);
int venta_setEstadoTXT(Venta* this, char*);
int venta_setId_cliente(Venta* this, int id_cliente);
int venta_setId_clienteTXT(Venta* this, char* id_cliente);
int venta_setId_venta(Venta* this, int id_venta);
int venta_setId_ventaTXT(Venta* this, char* id_venta);
int venta_setCantidad_afiches(Venta* this, int cantidad_afiches);
int venta_setCantidad_afichesTXT(Venta* this, char* cantidad_afiches);
int venta_setNombre_archivo(Venta* this, char* nombre_archivo);
int venta_setZona(Venta* this, int zona);
int venta_setZonaTXT(Venta* this, char* zona);


/*      GETTERS     */
int venta_getEstado(Venta* this);
int venta_getId_cliente(Venta* this);
int venta_getId_venta(Venta* this);
int venta_getCantidad_afiches(Venta* this);
char* venta_getNombre_archivo(Venta* this);
int venta_getZona(Venta* this);

/*      IS_VALID     */
int venta_isValidId_cliente(int id_cliente);
int venta_isValidId_clienteTXT(char* id_cliente);
int venta_isValidEstadoTXT(char* zona);
int venta_isValidId_venta(int id_venta);
int venta_isValidId_ventaTXT(char* id_venta);
int venta_isValidCantidad_afiches(int cantidad_afiches);
int venta_isValidCantidad_afichesTXT(char* cantidad_afiches);
int venta_isValidNombre_archivo(char* nombre_archivo);
int venta_isValidZona(int zona);
int venta_isValidZonaTXT(char* zona);
int venta_isValidEstado(int estado);


/*      FUNCIONES EXTRAS     */
int venta_print(void*);
int venta_printAcobrar(void*);
int venta_findMaxId(void* pElement, int indice, int *id);
int venta_findVentaById(void* pElement, int id);

#endif /* VENTA_H_ */
