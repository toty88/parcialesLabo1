
#ifndef CLIENTE_VENTA_H_
#define CLIENTE_VENTA_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utn.h"
#include"Cliente.h"
#include"Venta.h"

int cliente_venta_print(void*, void*, int);
int cliente_venta_isEstado(void*, void*, int);
int cliente_venta_TotalAfichesPorCliente(void*, void*, int*);
int cliente_venta_VentaConMasAfichesVendidos(void*, void*, int*);
#endif /* CLIENTE_VENTA_H_ */
