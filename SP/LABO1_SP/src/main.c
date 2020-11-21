
#include <stdio.h>
#include <stdlib.h>
#include"menu.h"
#include"LinkedList.h"
#include"Controller.h"
#include"Cliente.h"
#include"Venta.h"

int main(void)
{
        int mainMenuOption;
        int bufferResultado;
        LinkedList *listaClientes = ll_newLinkedList();
        LinkedList *listaVentas = ll_newLinkedList();
        if(listaClientes != NULL
                && listaVentas != NULL
                && !(controller_loadClientesFromText("clientes.txt", listaClientes))
                && !(controller_loadVentasFromText("ventas.txt", listaVentas)))

        {
            do
            {
                if (!(menu_Main(&mainMenuOption)))
                {
                    switch (mainMenuOption)
                    {
                    case 1:
                        bufferResultado = controller_addCliente(listaClientes);
                        if(bufferResultado == 0)
                        {
                            printf("\n >>>>> CLIENTES AGREGADO CON EXITO <<<<<\n");
                        }
                        else if(bufferResultado == -3)
                        {
                            printf("\n >>>>> CLIENTE NO AGREGADO, CLIENTE YA EXISTENTE <<<<<\n");
                        }
                        else if(bufferResultado == -2)
                        {
                            printf("\n >>>>> CLIENTE NO AGREGADO, ERORR EN CUIT <<<<<\n");
                        }
                        break;
                    case 2:
                        if(!(controller_venderAfiches(listaVentas, listaClientes)))
                        {
                            printf("\n >>>>> VENTA REALIZADA CON EXITO <<<<<\n");
                        }
                        break;
                    case 3:
                        if(!(controller_ListVentas(listaVentas)))
                        {
                            printf("\n >>>>> CLIENTES LISTADOS CON EXITO <<<<<\n");
                        }

                        break;
                    case 4:

                        break;
                    case 5:

                        break;
                    case 6:
                        printf("\n >>>>> HA SALIDO, HASTA LUEGO <<<<<\n");
                        break;
                    default:
                        printf("\n >>>>> OPCION INVALIDA, VUELVA A INTENTAR <<<<<\n");
                    }
                }
            }
            while (mainMenuOption != 6);
        }
        return 0;
}

