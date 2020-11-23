
#ifndef CLIENTE_VENTA_H_
#define CLIENTE_VENTA_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utn.h"
#include"Cliente.h"
#include"Venta.h"

int cliente_venta_print(void* cliente, void* venta, int id_venta);
int cliente_venta_isEstado(void* cliente, void* venta, int estado);
#endif /* CLIENTE_VENTA_H_ */
