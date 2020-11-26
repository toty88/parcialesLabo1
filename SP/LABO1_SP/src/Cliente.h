#ifndef CLIENTE_H_
#define CLIENTE_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utn.h"
#define SIZE_STR 60
#define SIZE_CUIT 12
typedef struct
{
    int id;
    char nombre[SIZE_STR];
    char apellido[SIZE_STR];
    char cuit[SIZE_CUIT];

}Cliente;

Cliente* cliente_new(void);
Cliente* cliente_newParam(int id, char* nombre, char* apellido, char* cuit);
Cliente* cliente_newParamTXT(char* id, char* nombre, char* apellido, char* cuit);
int cliente_delete(Cliente* this);
int cliente_setId(Cliente* this, int id);
int cliente_setIdTXT(Cliente* this, char* id);
int cliente_setNombre(Cliente* this, char* nombre);
int cliente_setApellido(Cliente* this, char* apellido);
int cliente_setCuit(Cliente* this, char* cuit);
int cliente_getId(Cliente* this);
char* cliente_getNombre(Cliente* this);
char* cliente_getApellido(Cliente* this);
char* cliente_getCuit(Cliente* this);
int cliente_isValidId(int id);
int cliente_isValidIdTXT(char* id);
int cliente_isValidNombre(char* nombre);
int cliente_isValidApellido(char* apellido);
int cliente_isValidCuitTXT(char* cuit);

int cliente_print(void*);
int cliente_printConAfiche(void*, int);
int cliente_findMaxId(void* pElement, int indice, int *id);
int cliente_DoesClientExist(void* pElement, char* cuit);
int cliente_DoesIdExist(void* pElement, int id);
#endif /* CLIENTE_H_ */
