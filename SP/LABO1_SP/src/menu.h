#ifndef MENU_H_
#define MENU_H_

#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include"utn.h"

/* ######################## MENUES GENERALES ############################*/

int menu_Main(int*);
int menu_ModifyVenta(int*);
int menu_VenderAfiches(int*);
int menu_CobrarVenta(int *pResultado);
int menu_generarInformes(int *pResultado);
//int menu_SortEmployee(int*);

/* ######################## HEADERS LISTAS #############################*/

int printColumn(void);



#endif /* MENU_H_ */
