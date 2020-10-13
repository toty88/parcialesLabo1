#ifndef CLIENTE_H_
#define CLIENTE_H_

//#include<stdio.h>
#include"menu.h"
#include"utn.h"
#define SIZE_ARRAY_CLIENTES 100
#define SIZE_STR 51
#define FALSE 0
#define TRUE 1

typedef struct{

	int id;
	char name[SIZE_STR];
	char lastName[SIZE_STR];
	char cuit[SIZE_STR];
	int isEmpty;

}Cliente;

int cliente_Init(Cliente*, int);
int cliente_HardCodeo(Cliente*);
int cliente_FindFree(Cliente*, int, int*);
int cliente_FindById(Cliente*, int, int, int*);
int cliente_DoesIdExist(Cliente*, int, int);
int cliente_Create(Cliente*, int);
int cliente_PrintOne(Cliente);
int cliente_printAll(Cliente*, int);
int cliente_Modify(Cliente*, int);
int cliente_Reports(Cliente*, int);

int cliente_Sort(Cliente*, int, int);
//int getClientesAverageSalary(Cliente*, int, float*, float*);
//int getClientesAboveAverageSalary(Cliente*, int, int);


#endif /* CLIENTE_H_ */
