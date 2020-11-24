#include"Cliente_Venta.h"

int cliente_venta_print(void* cliente, void* venta, int id_venta)
{
    int output = -1;
    Cliente* auxCliente = (Cliente*)cliente;
    Venta* auxVenta = (Venta*)venta;
    if(auxCliente != NULL && auxVenta != NULL && id_venta > 0)
    {
        if(venta_getId_venta(auxVenta) == id_venta && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
        {
            cliente_print(auxCliente);
            venta_print(auxVenta);
            output = 0;
        }
    }
    return output;
}

int cliente_venta_isEstado(void* cliente, void* venta, int estado)
{
    int output = 0;
    Cliente* auxCliente = (Cliente*)cliente;
    Venta* auxVenta = (Venta*)venta;
    if(auxCliente != NULL && auxVenta != NULL && (estado == 0 || estado == 1))
    {
        if(venta_getEstado(auxVenta) == estado && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
        {
            output = 1;
        }
    }
    return output;
}

int cliente_venta_TotalAfichesPorCliente(void* cliente, void* venta, int* pResultado)
{
    int output = 0;
    Cliente* auxCliente = (Cliente*)cliente;
    Venta* auxVenta = (Venta*)venta;
    if(auxCliente != NULL && auxVenta != NULL && pResultado != NULL)
    {
        if(cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
        {
            *pResultado += venta_getCantidad_afiches(auxVenta);
            output = 0;
        }
    }
    return output;
}

int cliente_venta_VentaConMasAfichesVendidos(void* cliente, void* venta, int* pResultado)
{
    int output = -1;
    Cliente* auxCliente = (Cliente*)cliente;
    Venta* auxVenta = (Venta*)venta;
    if(auxCliente != NULL && auxVenta != NULL)
    {
        if(venta_getEstado(auxVenta) == COBRADO && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
        {
            *pResultado = venta_getCantidad_afiches(auxVenta);
            output = 0;
        }
    }
    return output;
}
