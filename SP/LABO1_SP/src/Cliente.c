#include"Cliente.h"

/*      CONSTRUCTOR & DESTRUCTOR      */

Cliente* cliente_new(void)
{
    return (Cliente*)malloc(sizeof(Cliente));
}

int cliente_delete(Cliente* this)
{
    int output = -1;
    if(this != NULL)
    {
        free(this);
        output = 0;
    }
    return output;
}

Cliente* cliente_newParam(int id, char* nombre, char* apellido, char* cuit)
{
    Cliente* this = cliente_new();
    if(this != NULL)
    {
        if(!(cliente_setId(this, id))
            && !(cliente_setNombre(this, nombre))
            && !(cliente_setApellido(this, apellido))
            && !(cliente_setCuit(this, cuit)))
        {
            return this;
        }
    }
    return NULL;
}

Cliente* cliente_newParamTXT(char* id, char* nombre, char* apellido, char* cuit)
{
    Cliente* this = cliente_new();
    if(this != NULL)
    {
        if(!(cliente_setIdTXT(this, id))
            && !(cliente_setNombre(this, nombre))
            && !(cliente_setApellido(this, apellido))
            && !(cliente_setCuit(this, cuit)))
        {
            return this;
        }
    }
    return NULL;
}

/*      SETTERS      */

int cliente_setCuit(Cliente* this, char* cuit)
{
    int output = -1;
    if(this != NULL && cliente_isValidCuitTXT(cuit))
    {
        strncpy(this->cuit,cuit,(int)sizeof(this->cuit));
        output = 0;
    }
    return output;
}

int cliente_setApellido(Cliente* this, char* apellido)
{
    int output = -1;
    if(this != NULL && cliente_isValidApellido(apellido))
    {
        strncpy(this->apellido,apellido,(int)sizeof(this->apellido));
        output = 0;
    }
    return output;
}

int cliente_setId(Cliente* this, int id)
{
    int output = -1;
    if(this != NULL  && cliente_isValidId(id))
    {
        this->id = id;
        output = 0;
    }
     return output;
}

int cliente_setIdTXT(Cliente* this, char* id)
{
    int output = -1;
    int bufferId;
    if(this != NULL  && cliente_isValidIdTXT(id))
    {
        bufferId = atoi(id);
        this->id = bufferId;
        output = 0;
    }
     return output;
}

int cliente_setNombre(Cliente* this, char* nombre)
{
    int output = -1;
    if(this != NULL && cliente_isValidNombre(nombre))
    {
        strncpy(this->nombre,nombre,(int)sizeof(this->nombre));
        output = 0;
    }
    return output;
}

/*      GETTERS      */

char* cliente_getCuit(Cliente* this)
{
    return this->cuit;
}

char* cliente_getApellido(Cliente* this)
{
    return this->apellido;
}

int cliente_getId(Cliente* this)
{
    return this->id;
}

char* cliente_getNombre(Cliente* this)
{
    return this->nombre;
}

/*      IS_VALID     */

int cliente_isValidCuitTXT(char* cuit)
{
    int output = 0;
    int contador = 0;
    if(cuit != NULL && utn_isNumeric(cuit))
    {
        for(int x = 0; cuit[x] != '\0'; x++)
        {
            contador++;
        }
        if(contador == 11)
        {
            output = 1;
        }
    }
    return output;
}

int cliente_isValidApellido(char* apellido)
{
    int output = 1;
    if(apellido !=NULL){
        for(int x = 0; apellido[x] !='\0'; x++){
            if((apellido[x] < 'A' || apellido[x] > 'z') && (apellido[x] > 'Z' || apellido[x] < 'a') && apellido[x] != ' ' && apellido[x] != '-'){
                output = 0;
                break;
            }
        }
    }
    return output;
}

int cliente_isValidId(int id)
{
    int output = 0;
    if(id > 0)
    {
        output = 1;
    }
    return output;
}

int cliente_isValidIdTXT(char* id)
{
    int output = 0;
    int bufferID;
    if(id !=NULL && utn_isIntNumber(id))
    {
        bufferID = atoi(id);
        if(bufferID > 0)
        {
            output = 1;
        }
    }
    return output;
}

int cliente_isValidNombre(char* nombre)
{
    int output = 1;
    if(nombre !=NULL){
        for(int x = 0; nombre[x] !='\0'; x++){
            if((nombre[x] < 'A' || nombre[x] > 'z') && (nombre[x] > 'Z' || nombre[x] < 'a') && nombre[x] != ' ' && nombre[x] != '-'){
                output = 0;
                break;
            }
        }
    }
    return output;
}

/* FUNCIONES EXTRAS  */

int cliente_print(void* pElement)
{
    int output = -1;
    Cliente* aux;
    aux = (Cliente*)pElement;
    if(aux != NULL)
    {
        printf("%5d %20s %20s %25s\n"
                ,cliente_getId(aux)
                ,cliente_getNombre(aux)
                ,cliente_getApellido(aux)
                ,cliente_getCuit(aux));
        output = 0;
    }
    return output;
}

int cliente_printConAfiche(void* pElement, int afiches)
{
    int output = -1;
    Cliente* aux;
    aux = (Cliente*)pElement;
    if(aux != NULL)
    {
        printf("%5d %20s %20s %25s %19d \n"
                                            ,cliente_getId(aux)
                                            ,cliente_getNombre(aux)
                                            ,cliente_getApellido(aux)
                                            ,cliente_getCuit(aux)
                                            ,afiches);
        output = 0;
    }
    return output;
}

int cliente_findMaxId(void* pElement, int indice, int *id)
{
    int output = -1;
    Cliente* aux;
    aux = (Cliente*)pElement;
    if(aux != NULL && id != NULL)
    {

        if(cliente_getId(aux) > *id || indice == 0)
        {
            *id = cliente_getId(aux);
        }
        output = 0;
    }
    return output;
}

int cliente_DoesClientExist(void* pElement, char* cuit)
{

    int output = 0;
    Cliente* aux = NULL;
    aux = (Cliente*)pElement;
    if (aux != NULL && cuit != NULL)
    {
        if(strncmp(cliente_getCuit(aux),cuit, SIZE_CUIT) == 0)
        {
            output = 1;
        }
    }
    return output;
}

int cliente_DoesIdExist(void* pElement, int id)
{
   int output = 1;
   Cliente* aux = NULL;
   aux = (Cliente*)pElement;
   if(aux != NULL && id >0)
   {
       if(cliente_getId(aux) == id)
       {
           output = 0;
       }
   }
   return output;
}
















