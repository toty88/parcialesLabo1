#include<stdio.h>
#include<stdlib.h>
#include"Cliente.h"
#include"Venta.h"
#include"LinkedList.h"
#define FALSE 0

int parser_ClientesFromText(FILE*, LinkedList*);
int parser_ClientesToText(FILE*, LinkedList*);
int parser_ClientesConTotalVentasToText(FILE*, void*, int);
int parser_VentasFromText(FILE*, LinkedList*);
int parser_VentasToText(FILE*, LinkedList*);
int parser_ProductoFromBinary(FILE*, LinkedList*);
int parser_ProductoToBinary(FILE*, LinkedList*);

