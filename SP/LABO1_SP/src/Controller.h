#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utn.h"
#include"menu.h"
#include"LinkedList.h"
#include"parser.h"


int controller_loadClientesFromText(char*, LinkedList*);
int controller_ListClientes(LinkedList* pArrayListClientes);
int controller_addCliente(LinkedList* pArrayListClientes);
int controller_isClienteCuitValid(char* cuit);

int controller_loadVentasFromText(char* path, LinkedList* pArrayListVentas);
int controller_ListVentas(LinkedList* pArrayListVentas);
int controller_venderAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListClientes);

int controller_loadFromBinary(char* path , LinkedList* pArrayListProducto);
int controller_ListEntidades(LinkedList* pArrayListUsuarios, LinkedList* pArrayListMensajes);
int controller_FilterProducto(LinkedList* pArrayListProducto);
int controller_saveAsText(char* path , LinkedList* pArrayListProducto);
int controller_saveAsBinary(char* path , LinkedList* pArrayListProducto);

int controller_ListUsuarios(LinkedList* pArrayListUsuarios);
int controller_ListMensajes(LinkedList* pArrayListMensajes);

int controller_sortMensajes(LinkedList* pArrayListMensajes);
int controller_sortUsuarios(LinkedList* pArrayListUsuarios);

int controller_sortDoble(LinkedList* pArrayListUsuarios, LinkedList* pArrayListMensajes);
#endif /* CONTROLLER_H_ */
