#ifndef CLIENTE_PUBLICACION_H_
#define CLIENTE_PUBLICACION_H_
#include<stdio.h>
#include"menu.h"
#include"utn.h"
#include"cliente.h"
#include"publicacion.h"
#define SIZE_ARRAY_RUBROS 100

typedef struct{

    int rubro;
    int isEmpty;
}Rubro;

int rubro_Init(Rubro*, int);
int rubro_ExisteRubro(Rubro*, int, int);
int rubro_GenerarRubros(Rubro*, int, Publicacion*);
int rubro_CalcularRubroConMasAvisos(Rubro* ,int, Publicacion*, int, int*);

int cliente_publicacion_CreatePublicidad(Publicacion*, int, Cliente*, int);
int cliente_publicacion_PrintPublicacionesConIdCliente(Publicacion*, int, Cliente*, int, int);
int cliente_publicacion_PrintPublicacionesActivasConIdCliente(Publicacion*, int, Cliente*, int, int);
int cliente_publicacion_PrintPublicacionesActivasClientes(Publicacion*, int, Cliente*, int);
int cliente_publicacion_RemoveClienteConPublicaciones(Publicacion*, int, Cliente*, int);
int cliente_publicacion_PausarReanudarPublicacion(Publicacion*, int, Cliente*, int, char*, int);


int cliente_publicacion_CalcularCantidadDeAvisosPorCliente(Publicacion*, int, Publicacion, int*);
int cliente_publicacion_CalcularClientesConMasAvisos(Publicacion*, int, Cliente*, int, int*, int*);
int cliente_publicacion_CalcularCantidadDeAvisosPausados(Publicacion*, int, int*);
int cliente_publicacion_CalcularRubroConMasAvisos(Publicacion*, int, char*, int*);
int cliente_publicacion_Informes(Publicacion*, int, Cliente*, int, Rubro*, int);

#endif /* CLIENTE_PUBLICACION_H_ */
