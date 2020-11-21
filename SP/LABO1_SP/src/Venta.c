#include"Venta.h"

Venta* venta_new(void)
{
    return (Venta*)malloc(sizeof(Venta));
}

int venta_delete(Venta* this)
{
    int output = -1;
    if(this != NULL)
    {
        free(this);
        output = 0;
    }
    return output;
}

Venta* venta_newParam(int id_venta, int id_cliente, char* nombre_archivo, int cantidad_afiches, int zona)
{
    Venta* this = venta_new();
    if(this != NULL)
    {
        if(!(venta_setId_cliente(this, id_cliente))
            && !(venta_setId_venta(this, id_venta))
            && !(venta_setCantidad_afiches(this, cantidad_afiches))
            && !(venta_setNombre_archivo(this, nombre_archivo))
            && !(venta_setZona(this, zona))
            && !(venta_setEstado(this, A_COBRAR)))
        {
            return this;
        }
    }
    return NULL;
}

Venta* venta_newParamTXT(char* id_venta, char* id_cliente, char* nombre_archivo, char* cantidad_afiches, char* zona
                            ,char* estado)
{
    Venta* this = venta_new();
    if(this != NULL)
    {
        if(!(venta_setId_clienteTXT(this, id_cliente))
            && !(venta_setId_ventaTXT(this, id_venta))
            && !(venta_setCantidad_afichesTXT(this, cantidad_afiches))
            && !(venta_setNombre_archivo(this, nombre_archivo))
            && !(venta_setZonaTXT(this, zona))
            && !(venta_setEstadoTXT(this, estado)))
        {

            return this;
        }
    }
    return NULL;
}

int venta_getId_cliente(Venta* this)
{
    return this->id_cliente;
}

int venta_setId_cliente(Venta* this, int id_cliente)
{
    int output = -1;
    if(this != NULL  && venta_isValidId_cliente(id_cliente))
    {
        this->id_cliente = id_cliente;
        output = 0;
    }
     return output;
}

int venta_setId_clienteTXT(Venta* this, char* id_cliente)
{
    int output = -1;
    int bufferId_cliente;
    if(this != NULL  && venta_isValidId_clienteTXT(id_cliente))
    {
        bufferId_cliente = atoi(id_cliente);
        this->id_cliente = bufferId_cliente;
        output = 0;
    }
     return output;
}

int venta_isValidId_cliente(int id_cliente)
{
    return 1;
}

int venta_isValidId_clienteTXT(char* id_cliente)
{
    return 1;
}

int venta_getId_venta(Venta* this)
{
    return this->id_venta;
}

int venta_setId_venta(Venta* this, int id_venta)
{
    int output = -1;
    if(this != NULL  && venta_isValidId_venta(id_venta))
    {
        this->id_venta = id_venta;
        output = 0;
    }
     return output;
}

int venta_setId_ventaTXT(Venta* this, char* id_venta)
{
    int output = -1;
    int bufferId_venta;
    if(this != NULL  && venta_isValidId_ventaTXT(id_venta))
    {
        bufferId_venta = atoi(id_venta);
        this->id_venta = bufferId_venta;
        output = 0;
    }
     return output;
}

int venta_isValidId_venta(int id_venta)
{
    return 1;
}

int venta_isValidId_ventaTXT(char* id_venta)
{
    return 1;
}

int venta_getCantidad_afiches(Venta* this)
{
    return this->cantidad_afiches;
}

int venta_setCantidad_afiches(Venta* this, int cantidad_afiches)
{
    int output = -1;
    if(this != NULL  && venta_isValidCantidad_afiches(cantidad_afiches))
    {
        this->cantidad_afiches = cantidad_afiches;
        output = 0;
    }
     return output;
}

int venta_setCantidad_afichesTXT(Venta* this, char* cantidad_afiches)
{
    int output = -1;
    int bufferCantidad_afiches;
    if(this != NULL  && venta_isValidCantidad_afichesTXT(cantidad_afiches))
    {
        bufferCantidad_afiches = atoi(cantidad_afiches);
        this->cantidad_afiches = bufferCantidad_afiches;
        output = 0;
    }
     return output;
}

int venta_isValidCantidad_afiches(int cantidad_afiches)
{
    return 1;
}

int venta_isValidCantidad_afichesTXT(char* cantidad_afiches)
{
    return 1;
}

char* venta_getNombre_archivo(Venta* this)
{
    return this->nombre_archivo;
}

int venta_setNombre_archivo(Venta* this, char* nombre_archivo)
{
    int output = -1;
    if(this != NULL && venta_isValidNombre_archivo(nombre_archivo))
    {
        strncpy(this->nombre_archivo,nombre_archivo,(int)sizeof(this->nombre_archivo));
        output = 0;
    }
    return output;
}

int venta_isValidNombre_archivo(char* nombre_archivo)
{
    return 1;
}

int venta_getZona(Venta* this)
{
    return this->zona;
}

int venta_setZona(Venta* this, int zona)
{
    int output = -1;
    if(this != NULL  && venta_isValidZona(zona))
    {
        this->zona = zona;
        output = 0;
    }
     return output;
}

int venta_setZonaTXT(Venta* this, char* zona)
{
    int output = -1;
    int bufferZona;
    if(this != NULL  && venta_isValidZonaTXT(zona))
    {
        bufferZona = atoi(zona);
        this->zona = bufferZona;
        output = 0;
    }
     return output;
}

int venta_isValidZona(int zona)
{
    int output = 0;
    if(zona >= 0 && zona <= 2)
    {
        output = 1;
    }
    return output;
}

int venta_isValidZonaTXT(char* zona)
{
    int output = 0;
    int bufferZona;
    if(zona != NULL && utn_isNumeric(zona))
    {
        bufferZona = atoi(zona);
        if(bufferZona >= 0 && bufferZona <= 2)
        {
            output = 1;
        }
    }
    return output;
}


int venta_setEstadoTXT(Venta* this, char* estado)
{
    int output = -1;
    int bufferEstado;
    if(estado != NULL && utn_isNumeric(estado))
    {
        bufferEstado = atoi(estado);
        if(bufferEstado == 0 || bufferEstado == 1)
        {
            output = 0;
        }
    }
    return output;
}

int venta_setEstado(Venta* this, int estado)
{
    int output = -1;
    if(this != NULL)
    {
        this->estado = estado;
        output = 0;
    }
    return output;
}
int venta_getEstado(Venta* this)
{
    return this->estado;
}

int venta_isValidEstado(int estado)
{
    int output = 0;
    if(estado == A_COBRAR || estado == COBRADO)
    {
        output = 1;
    }
    return output;
}

int venta_print(void* pElement)
{
    int output = -1;
    Venta* aux;
    aux = (Venta*)pElement;
    char bufferZona[SIZE_FILE_NAME] = "CABA";
    char bufferEstado[SIZE_FILE_NAME] = "A COBRAR";
    if(aux != NULL)
    {
        printf("%d - \t%d - \t%s - \t%d -", venta_getId_venta(aux), venta_getId_cliente(aux)
                , venta_getNombre_archivo(aux)
                , venta_getCantidad_afiches(aux));
        if(venta_getZona(aux) == 1)
        {
            sprintf(bufferZona, "ZONA SUR");
        }
        else if(venta_getZona(aux) == 2)
        {
            sprintf(bufferZona, "ZONA OESTE");
        }
        printf("\t%s -", bufferZona);

        if(venta_getEstado(aux) == 1)
        {
            sprintf(bufferEstado, "COBRADO");
        }
        printf("\t%s\n", bufferEstado);
        output = 0;
    }
    return output;
}

int venta_findMaxId(void* pElement, int indice, int *id)
{
    int output = -1;
    Venta* aux;
    aux = (Venta*)pElement;
    if(aux != NULL && indice >= 0 && id != NULL)
    {

        if(venta_getId_venta(aux) > *id || indice == 0)
        {
            *id = venta_getId_venta(aux);
        }
        output = 0;
    }
    return output;
}
