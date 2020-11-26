#include"Cliente_Venta.h"

/**
 * @fn int cliente_venta_print(void*, void*, int)
 * @brief funcion que imprime una venta con los datos del cliente en base al id_venta recibido
 *
 * @param cliente el void* que sea caste a Cliente*
 * @param venta el void* que se castea a Venta*
 * @param id_venta el int que se utiliza para comparar
 * @return (-1) Error (0) Todo OK
 */
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

/**
 * @fn int cliente_venta_isEstado(void*, void*, int)
 * @brief funcion que devuelve si el estado de la venta es igual al estado recibido por parametro
 *
 *
 * @param cliente el void* que sea caste a Cliente*
 * @param venta el void* que se castea a Venta*
 * @param estado el int a comparar
 * @return (-1) Error (0) Todo OK
 */

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

/**
 * @fn int cliente_venta_TotalAfichesPorCliente(void*, void*, int*)
 * @brief funcion que devuelve por referencia la cantidad de afiches de una venta en base al id de cliente
 *
 *
 * @param cliente el void* que sea caste a Cliente*
 * @param venta el void* que se castea a Venta*
 * @param pResultado el int* donde se va sumando el total de afiches
 * @return (-1) Error (0) Todo OK
 */

int cliente_venta_TotalAfichesPorCliente(void* cliente, void* venta, int* pResultado, int estado)
{
    int output = 0;
    Cliente* auxCliente = (Cliente*)cliente;
    Venta* auxVenta = (Venta*)venta;
    if(auxCliente != NULL && auxVenta != NULL && pResultado != NULL && estado >= 0)
    {
        if(estado == 2 && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
        {
            *pResultado += venta_getCantidad_afiches(auxVenta);
            output = 0;
        }
        else
        {
            if(venta_getEstado(auxVenta) ==  estado && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
            {
                *pResultado += venta_getCantidad_afiches(auxVenta);
                output = 0;
            }
        }
    }
    return output;
}

/**
 * @fn int cliente_venta_VentaConMasAfichesVendidos(void*, void*, int*)
 * @brief funcion que evalua de acuerdo al estado COBRADO
 *
 * @param cliente el void* que sea caste a Cliente*
 * @param venta el void* que se castea a Venta*
 * @param pResultado
 * @return (-1) Error (0) Todo OK
 */
int cliente_venta_VentaConMasAfiches(void* cliente, void* venta, int* pResultado, int estado)
{
    int output = -1;
    Cliente* auxCliente = (Cliente*)cliente;
    Venta* auxVenta = (Venta*)venta;
    if(auxCliente != NULL && auxVenta != NULL && estado >= 0)
    {
        if(estado == 2 && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
        {
            *pResultado = venta_getCantidad_afiches(auxVenta);
            output = 0;
        }
        else
        {
            if(venta_getEstado(auxVenta) == estado && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
            {
                *pResultado = venta_getCantidad_afiches(auxVenta);
                output = 0;
            }
        }
    }
    return output;
}

/**
 * @fn int cliente_venta_printIdVentaCuitCliente(void*, void*, int)
 * @brief
 *
 * @param cliente el void* que sea caste a Cliente*
 * @param venta el void* que se castea a Venta*
 * @param id_venta
 * @return (-1) Error (0) Todo OK
 */
int cliente_venta_printIdVentaCuitCliente(void* cliente, void* venta, int id_venta)
{
    int output = -1;
    Cliente* auxCliente = (Cliente*)cliente;
    Venta* auxVenta = (Venta*)venta;
    if(auxCliente != NULL && auxVenta != NULL && id_venta > 0)
    {
        if(venta_getId_venta(auxVenta) == id_venta && cliente_getId(auxCliente) == venta_getId_cliente(auxVenta))
        {

            printColumnVentaConMasAfiches();
            printf("%11d %23s %23d\n\n", venta_getId_venta(auxVenta), cliente_getCuit(auxCliente), venta_getCantidad_afiches(auxVenta));
        }
    }
    return output;
}


/*  POSIBLES FUNCIONES FUTURAS */






