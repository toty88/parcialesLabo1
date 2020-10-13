#ifndef CLIENTE_PUBLICACION_H_
#define CLIENTE_PUBLICACION_H_
#include<stdio.h>
#include"menu.h"
#include"utn.h"
#include"cliente.h"
#include"publicacion.h"


int cliente_publicacion_CreatePublicidad(Publicacion*, int, Cliente*, int);
int cliente_publicacion_PrintPublicacionesConIdCliente(Publicacion*, int, Cliente*, int, int);
int cliente_publicacion_PrintPublicacionesActivasConIdCliente(Publicacion*, int, Cliente*, int, int);
int cliente_publicacion_PrintPublicacionesActivasClientes(Publicacion*, int, Cliente*, int);
int cliente_publicacion_RemoveClienteConPublicaciones(Publicacion*, int, Cliente*, int);
int cliente_publicacion_PausarReanudarPublicacion(Publicacion*, int, Cliente*, int, char*, int);
int cliente_publicacion_CalcularCantidadDeAvisosPorCliente(Publicacion*, int, Publicacion, int*);


#endif /* CLIENTE_PUBLICACION_H_ */
