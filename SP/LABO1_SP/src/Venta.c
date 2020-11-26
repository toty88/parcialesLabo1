#include"Venta.h"

/*      CONSTRUCTOR & DESTRUCTOR      */

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

/*      SETTERS      */

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

int venta_setEstadoTXT(Venta* this, char* estado)
{
    int output = -1;
    int bufferEstado;
    if(this != NULL && estado != NULL)
    {
        if(venta_isValidEstadoTXT(estado))
        {
            bufferEstado = atoi(estado);
            this->estado = bufferEstado;
            output = 0;
        }
    }
    return output;
}


/*      GETTERS      */

int venta_getId_cliente(Venta* this)
{
    return this->id_cliente;
}

int venta_getId_venta(Venta* this)
{
    return this->id_venta;
}

int venta_getCantidad_afiches(Venta* this)
{
    return this->cantidad_afiches;
}

char* venta_getNombre_archivo(Venta* this)
{
    return this->nombre_archivo;
}

int venta_getZona(Venta* this)
{
    return this->zona;
}

int venta_getEstado(Venta* this)
{
    return this->estado;
}


/*      IS_VALID     */

int venta_isValidId_cliente(int id_cliente)
{
    int output = 0;
    if(id_cliente > 0)
    {
        output = 1;
    }
    return output;
}

int venta_isValidId_clienteTXT(char* id_cliente)
{
    int output = 0;
    int bufferID;
    if(id_cliente !=NULL && utn_isIntNumber(id_cliente))
    {
        bufferID = atoi(id_cliente);
        if(bufferID > 0)
        {
            output = 1;
        }
    }
    return output;
}

int venta_isValidId_venta(int id_venta)
{
    {
        int output = 0;
        if(id_venta > 0)
        {
            output = 1;
        }
        return output;
    }
}

int venta_isValidId_ventaTXT(char* id_venta)
{
    int output = 0;
    int bufferID;
    if(id_venta !=NULL && utn_isIntNumber(id_venta))
    {
        bufferID = atoi(id_venta);
        if(bufferID > 0)
        {
            output = 1;
        }
    }
    return output;
}

int venta_isValidCantidad_afiches(int cantidad_afiches)
{
    {
        int output = 0;
        if(cantidad_afiches > 0)
        {
            output = 1;
        }
        return output;
    }
}

int venta_isValidCantidad_afichesTXT(char* cantidad_afiches)
{
    int output = 0;
    int bufferID;
    if(cantidad_afiches !=NULL && utn_isIntNumber(cantidad_afiches))
    {
        bufferID = atoi(cantidad_afiches);
        if(bufferID > 0)
        {
            output = 1;
        }
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

int venta_isValidEstadoTXT(char* estado)
{
    int output = 0;
    int bufferEstado;
    if(estado != NULL && utn_isNumeric(estado))
    {
        bufferEstado = atoi(estado);
        if(bufferEstado == A_COBRAR || bufferEstado == COBRADO)
        {
            output = 1;
        }
    }
    return output;
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

int venta_isValidNombre_archivo(char* nombre_archivo)
{
    int output = 0;
    char separador = '.';
    char* extencion;
    if(nombre_archivo != NULL)
    {
        extencion = strrchr(nombre_archivo, separador);
        if(extencion != NULL && strcmp(".tiff", extencion) == 0)
        {
            output = 1;
        }
    }
    return output;
}


/*      FUNCIONES EXTRAS     */

int venta_print(void* pElement)
{
    int output = -1;
    Venta* aux;
    int zona;
    aux = (Venta*)pElement;
    char bufferZona[SIZE_FILE_NAME] = "CABA";
    char bufferEstado[SIZE_FILE_NAME] = "COBRADO";
    if(aux != NULL)
    {
        printf("%10d %13d %16d", venta_getId_venta(aux), venta_getId_cliente(aux), venta_getCantidad_afiches(aux));
        zona = venta_getZona(aux);
        switch(zona)
        {
        case 0:
            sprintf(bufferZona, "CABA");
            break;
        case 1:
            sprintf(bufferZona, "SUR");
            break;
        case 2:
            sprintf(bufferZona, "OESTE");
            break;
        }
        printf("%16s", bufferZona);
        if(venta_getEstado(aux) == 0)
        {
            sprintf(bufferEstado, "A COBRAR");
        }
        printf("%16s %40s\n", bufferEstado, venta_getNombre_archivo(aux));
        output = 0;
    }
    return output;
}

int venta_printAcobrar(void* pElement)
{
    int output = -1;
    Venta* aux;
    aux = (Venta*)pElement;
    int zona;
    char bufferZona[SIZE_FILE_NAME];
    char bufferEstado[SIZE_FILE_NAME];
    if(aux != NULL)
    {
        if(venta_getEstado(aux) == A_COBRAR)
        {
            printf("%10d %13d %16d", venta_getId_venta(aux), venta_getId_cliente(aux), venta_getCantidad_afiches(aux));
            zona = venta_getZona(aux);
            switch(zona)
            {
            case 0:
                sprintf(bufferZona, "CABA");
                break;
            case 1:
                sprintf(bufferZona, "SUR");
                break;
            case 2:
                sprintf(bufferZona, "OESTE");
                break;
            }
            printf("%16s", bufferZona);
            sprintf(bufferEstado, "A COBRAR");
            printf("%16s %40s\n", bufferEstado, venta_getNombre_archivo(aux));
            output = 0;
        }
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

int venta_findVentaById(void* pElement, int id)
{

    int output = -1;
    Venta* aux = NULL;
    aux = (Venta*)pElement;
    if (aux != NULL && id > 0)
    {
        if(venta_getId_venta(aux) == id)
        {
            output = 0;
        }
    }
    return output;
}
