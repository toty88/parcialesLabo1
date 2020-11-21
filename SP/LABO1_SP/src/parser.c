#include"parser.h"

int parser_ClientesFromText(FILE* pFile , LinkedList* pArrayListClientes)
{
    int output = -1;
    int writtenValues;
    char bufferId[SIZE_STR];
    char bufferNombre[SIZE_STR];
    char bufferApellido[SIZE_STR];
    char bufferCuit[SIZE_STR];

    Cliente* aux;
    if(pFile != NULL && pArrayListClientes != NULL)
    {
        do
        {
            writtenValues = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", bufferId,bufferNombre,bufferApellido,bufferCuit);
            if(writtenValues == 4)
            {
                aux = cliente_newParamTXT(bufferId,bufferNombre,bufferApellido,bufferCuit);
                if(aux != NULL)
                {
                    if(!(ll_add(pArrayListClientes, aux)))
                    {
                        output = 0;
                    }
                    else
                    {
                        cliente_delete(aux);
                    }
                }
            }
        }
        while(!feof(pFile));
    }
    return output;
}


int parser_VentasFromText(FILE* pFile , LinkedList* pArrayListVentas)
{
    int output = 1;
    int writtenValues;
    char bufferIdVenta[SIZE_FILE_NAME];
    char bufferIdCliente[SIZE_FILE_NAME];
    char bufferCantAfiches[SIZE_FILE_NAME];
    char bufferNombreArchivo[SIZE_FILE_NAME];
    char bufferZona[SIZE_FILE_NAME];
    char bufferEstado[SIZE_FILE_NAME];

    Venta* aux;
    if(pFile != NULL && pArrayListVentas != NULL)
    {
        do
        {
            writtenValues = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", bufferIdVenta
                                                                            ,bufferIdCliente
                                                                            ,bufferCantAfiches
                                                                            ,bufferNombreArchivo
                                                                            ,bufferZona
                                                                            ,bufferEstado);
            if(writtenValues == 6)
            {
                aux = venta_newParamTXT(bufferIdVenta
                        ,bufferIdCliente
                        ,bufferCantAfiches
                        ,bufferNombreArchivo
                        ,bufferZona
                        ,bufferEstado);
                if(aux != NULL)
                {
                    if(!(ll_add(pArrayListVentas, aux)))
                    {
                        output = 0;
                    }
                    else
                    {
                        venta_delete(aux);
                    }
                }
            }
        }
        while(!feof(pFile));
    }
    return output;
}


/*
int parser_ProductoToText(FILE* pFile , LinkedList* pArrayListProducto)
{
    int output = -1;
    if(pFile != NULL && pArrayListProducto != NULL)
    {
        int len = ll_len(pArrayListProducto);
        Envio* aux;
        if(pFile != NULL)
        {
            fprintf(pFile, "id_producto,nombre_producto,id_camion,zona_destino,km_recorridos,tipo_entrega,costo_envio\n");
            for(int x = 0; x < len; x++)
            {
                aux = (Envio*)ll_get(pArrayListProducto, x);
                if(aux != NULL)
                {
                    fprintf(pFile, "%d,%s,%d,%s,%.2f,%d,%.2f\n",envio_getIdProducto(aux), envio_getNombreProducto(aux),
                                                                envio_getIdCamion(aux), envio_getZonaDestino(aux),
                                                                envio_getKilometrosRecorridos(aux),envio_getTipoEntrega(aux),
                                                                envio_getCostoEnvio(aux));
                }
                output = 0;
            }
        }
    }
    return output;
}

int parser_ProductoFromBinary(FILE* pFile , LinkedList* pArrayListProducto)
{
    int output = -1;
    int writtenValues;

    if(pFile != NULL && pArrayListProducto != NULL)
    {
        do
        {
            Envio* aux = envio_new();
            if(aux != NULL)
            {
                writtenValues = fread(aux, sizeof(Envio), 1, pFile);
                if(writtenValues == 1)
                {
                    if(!(ll_add(pArrayListProducto, aux)))
                    {
                        output = 0;
                    }
                }
                else
                {
                    envio_delete(aux);
                }
            }
        }
        while(!feof(pFile));
    }
    return output;
}

int parser_ProductoToBinary(FILE* pFile , LinkedList* pArrayListProducto)
{
    int output = -1;
    int writtenValues;
    if(pFile != NULL && pArrayListProducto != NULL)
    {
        Envio* aux;
        if(pFile != NULL)
        {
            for(int x = 0; x < ll_len(pArrayListProducto); x++)
            {
                aux = (Envio*)ll_get(pArrayListProducto, x);
                if(aux != NULL)
                {
                    writtenValues = fwrite(aux, sizeof(Envio),1,pFile);
                    if(writtenValues == 1)
                    {
                        output = 0;
                    }
                }
            }
        }
    }
    return output;
}

*/

