/*
 * menu.h
 *
 *  Created on: Oct 6, 2020
 *      Author: toty
 */

#ifndef MENU_H_
#define MENU_H_

#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include"utn.h"

/* ########################## MENUES ##################################*/
int menu_Principal(int*);
int menu_Modificar(int*);
int menu_Baja(int*);
int menu_Informes(int*);
/* ################ MENUES CLIENTES Y PUBLICACIONES ###################*/
int menu_ModificarPublicacion(int*);
int menu_ContratarPublicidad(int*);
int menu_PusarPublicacion(int*);
/* ########################## PRINTS ##################################*/
void printColumn(void);
void printColumnPublicacion(void);
void printColumnPublicacionesDeUnCliente(void);
void printColumnClientYpublicacionesActivas(void);


#endif /* MENU_H_ */
