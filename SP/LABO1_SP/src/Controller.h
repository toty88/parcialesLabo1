#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utn.h"
#include"menu.h"
#include"LinkedList.h"
#include"parser.h"
#include"Cliente_Venta.h"


int controller_loadClientesFromText(char*, LinkedList*);
int controller_saveClientesAsText(char* path , LinkedList* pArrayListClientes);
int controller_addCliente(LinkedList* pArrayListClientes);
//int controller_removeCliente(LinkedList* pArrayListClientes);

int controller_loadVentasFromText(char* path, LinkedList* pArrayListVentas);
int controller_venderAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListClientes);
int controller_modificarVentas(LinkedList* pArrayListVentas, LinkedList* pArrayListClientes);
int controller_cobrarVentas(LinkedList* pArrayListVentas, LinkedList* pArrayListClientes);
int controller_saveVentasAsText(char* path , LinkedList* pArrayListVentas);

int controller_generarInformes(LinkedList* pArrayListVentas, LinkedList* pArrayClientes);

#endif /* CONTROLLER_H_ */
