/*
 * informes.h
 *
 *  Created on: Oct 13, 2020
 *      Author: toty
 */

#ifndef INFORMES_H_
#define INFORMES_H_

#include"cliente_publicacion.h"
#define SIZE_ARRAY_RUBROS 100

typedef struct{

    int rubro;
    int isEmpty;
}Rubro;

int rubro_Init(Rubro*, int);
int rubro_ExisteRubro(Rubro*, int, int);
int rubro_GenerarRubros(Rubro*, int, Publicacion*);
int rubro_CalcularRubroConMasAvisos(Rubro* ,int, Publicacion*, int, int*);
int informes_CalcularClientesConMasAvisos(Publicacion*, int, Cliente*, int, int*, int*);
int informes_CalcularCantidadDeAvisosPausados(Publicacion*, int, int*);
int informes_Informes(Publicacion*, int, Cliente*, int, Rubro*, int);

#endif /* INFORMES_H_ */
