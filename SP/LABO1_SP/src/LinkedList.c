#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

static Node* getNode(LinkedList *this, int nodeIndex);
static int addNode(LinkedList *this, int nodeIndex, void *pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */

LinkedList* ll_newLinkedList(void)
{
    LinkedList *this = (LinkedList*) malloc(sizeof(LinkedList));
    if (this != NULL)
    {
        this->pFirstNode = NULL;
        this->size = 0;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */

int ll_len(LinkedList *this)
{
    int returnAux = -1;
    if (this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pNode) Si funciono correctamente
 *
 */

static Node* getNode(LinkedList *this, int nodeIndex)
{
    Node *nodeToReturn = NULL;
    if (this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        nodeToReturn = this->pFirstNode;
        for (int x = 0; x < nodeIndex; x++)
        {
            nodeToReturn = nodeToReturn->pNextNode;
        }
    }
    return nodeToReturn;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */

Node* test_getNode(LinkedList *this, int nodeIndex) {

    return getNode(this, nodeIndex);

}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */

static int addNode(LinkedList *this, int nodeIndex, void *pElement)
{
    int output = -1;
    Node *newNode = NULL;
    Node *prevNode = NULL;
    if (this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        newNode = (Node*) malloc(sizeof(Node));
        if (newNode != NULL)
        {
            if (nodeIndex == 0)
            { // quiero agregar un nodo en la primer posicion
                newNode->pNextNode = this->pFirstNode;
                this->pFirstNode = newNode;
                newNode->pElement = pElement;
                this->size++;
                output = 0;
            }
            else
            { // en el medio
                prevNode = getNode(this, (nodeIndex-1));
                if(prevNode != NULL)
                {
                    newNode->pNextNode = prevNode->pNextNode;
                    prevNode->pNextNode = newNode;
                    newNode->pElement = pElement;
                    this->size++;
                    output = 0;
                }
            }
        }
    }
    return output;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */

int test_addNode(LinkedList *this, int nodeIndex, void *pElement) {

    return addNode(this, nodeIndex, pElement);

}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */

int ll_add(LinkedList *this, void *pElement)
{
    int output = -1;
    if (this != NULL)
    {
        if (!addNode(this, ll_len(this), pElement))
        {
            output = 0;
        }
    }
    return output;
}

/**
 * @fn void ll_get*(LinkedList*, int)
 * @brief Devuelve un puntero a la direccion de memoria donde se encuentra un elemento de tipo Empleado
 * @param this La LinkedList
 * @param index El indice donde se encuentra el elemento de tipo Empleado
 */

void* ll_get(LinkedList *this, int index)
{
    void *returnAux = NULL;
    Node *aux = NULL;
    if (this != NULL && index >= 0 && index < ll_len(this))
    {
        aux = getNode(this, index);
        if (aux != NULL)
        {
            returnAux = aux->pElement;
        }
    }
    return returnAux;
}

/** \brief Modifica un elemento de la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */

int ll_set(LinkedList *this, int index, void *pElement)
{
    int output = -1;
    Node *aux;
    if (this != NULL && index >= 0 && index < ll_len(this))
    {
        aux = getNode(this, index);
        if (aux != NULL)
        {
            aux->pElement = pElement;
            output = 0;
        }
    }
    return output;
}

/** \brief Elimina un Nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */

int ll_remove(LinkedList *this, int index)
{
    int output = -1;
    Node *pNodeToRemove = NULL;
    Node *pPrevNode = NULL;
    if (this != NULL && index >= 0 && index < ll_len(this))
    {
        pNodeToRemove = getNode(this, index);
        if (pNodeToRemove != NULL)
        {
            if (index == 0)
            {
                this->pFirstNode = pNodeToRemove->pNextNode;
            }
            else
            {
                pPrevNode = getNode(this, (index-1));
                if (pPrevNode != NULL)
                {
                    pPrevNode->pNextNode = pNodeToRemove->pNextNode;
                }
            }
            //free(pNodeToRemove->pElement);
            free(pNodeToRemove);
            pNodeToRemove = NULL;
            this->size--;
            output = 0;
        }
    }
    return output;
}

/** \brief Elimina todos los elementos de la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */

int ll_clear(LinkedList *this)
{
    int output = -1;
    int len;
    if (this != NULL)
    {
        len = ll_len(this);
        if (len > 0)
        {
            for (int x = len -1; x >= 0; x--)
            {
                if(!(ll_remove(this, x)))
                {
                    output = 0;
                }
            }
        }
    }
    return output;
}

/** \brief Elimina todos los elementos de la lista y la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si funciono correctamente
 *
 */

int ll_deleteLinkedList(LinkedList *this)
{
    int output = -1;
    if (this != NULL && !(ll_clear(this)))
    {
        this = NULL;
        output = 0;
    }
    return output;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 (indice del elemento) Si funciono correctamente
 *
 */

int ll_indexOf(LinkedList *this, void *pElement)
{
    int output = -1;
    void* temp;
    int len;
    if (this != NULL)
    {
        len = ll_len(this);
        for (int x = 0; x < len; x++)
        {
            temp = ll_get(this, x);
            if (temp == pElement)
            {
                output = x;
                break;
            }
        }
    }
    return output;
}

/** \brief Indica si la lista esta o no vacia
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 0) Si la lista NO esta vacia
 ( 1) Si la lista esta vacia
 *
 */

int ll_isEmpty(LinkedList *this)
{
    int output = -1;
    if (this != NULL)
    {
        output = 0;
        if (ll_len(this) <= 0)
        {
            output = 1;
        }
    }
    return output;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 ( 0) Si funciono correctamente
 *
 */

int ll_push(LinkedList *this, int index, void *pElement)
{
    int output = -1;
    if (this != NULL && index >= 0 && index <= ll_len(this))
    {
        if (!(addNode(this, index, pElement)))
        {
            output = 0;
        }
    }
    return output;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
 (pElement) Si funciono correctamente
 *
 */

void* ll_pop(LinkedList *this, int index)
{
    Node *aux = NULL;
    void* output = NULL;
    if (this != NULL && index >= 0 && index < ll_len(this))
    {
        aux = getNode(this, index);
        if (aux != NULL)
        {
            output = aux->pElement;
            ll_remove(this, index);
        }
    }
    return output;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
 ( 1) Si contiene el elemento
 ( 0) si No contiene el elemento
 */

int ll_contains(LinkedList *this, void *pElement)
{
    int output = -1;
    if (this != NULL)
    {
        output = 0;
        if (ll_indexOf(this, pElement) >= 0)
        {
            output = 1;
        }
    }
    return output;
}
/** \brief  Determina si todos los elementos de la lista (this2)
 estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
 ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
 ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
 */
int ll_containsAll(LinkedList *this, LinkedList *this2)
{
    int output = -1;
    void* auxElement;
    int len = ll_len(this2);
    if(this != NULL && this2 != NULL)
    {
        output = 1;
        for(int x = 0; x < len; x++)
        {
            auxElement = ll_get(this2, x);
            if(!ll_contains(this, auxElement))
            {
                output = 0;
                break;
            }
        }
    }
    return output;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 o (si el indice from es menor a 0 o mayor al len de la lista)
 o (si el indice to es menor o igual a from o mayor al len de la lista)
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_subList(LinkedList *this, int from, int to) {
    LinkedList *cloneArray = NULL;
    Node* pNodeToAdd = NULL;
    if(this != NULL && from >=0 && to <= ll_len(this))
    {
        cloneArray = (LinkedList*)malloc(sizeof(LinkedList));
        if(cloneArray != NULL)
        {
            for(int x = 0; x < to; x++)
            {
                pNodeToAdd = getNode(this, from);
                if(pNodeToAdd != NULL)
                {
                    addNode(cloneArray, x, pNodeToAdd->pElement);
                    from++;
                }
            }
        }
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
 (puntero a la nueva lista) Si ok
 */
LinkedList* ll_clone(LinkedList *this) {
    LinkedList *cloneArray = NULL;
    if(this != NULL)
    {
        cloneArray = (LinkedList*)malloc(sizeof(LinkedList));
        if(cloneArray != NULL)
        {
            cloneArray = this;
        }
    }
    return cloneArray;
}

/**
 * @fn int swapNodes(Node*, Node*, Node*)
 * @brief Intercambia el nodo actual con el siguiente
 * @param prevCurrent el nodo anterior al actual
 * @param current el nodo actual
 * @param next el nodo   siguiente
 * @return int Retorna (-1) si algun nodo es NULL (0) si el intercambio fue correcto
 */
int swapNodes(Node* prevCurrent, Node* current, Node* next)
{
    int output = -1;
    if(prevCurrent != NULL && current != NULL && next != NULL)
    {
        current->pNextNode = next->pNextNode;
        prevCurrent->pNextNode = next;
        next->pNextNode = current;
        output = 0;
    }
    return output;
}

int ll_map(LinkedList* this, pFunc pCriterio)
{
    int output = -1;
    void* aux;
    if(this != NULL && pCriterio != NULL)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            aux = ll_get(this, x);
            if(!(pCriterio(aux)))
            {
                output = 0;
            }
        }
    }
    return output;
}

int ll_mapStr(LinkedList* this, char* str, pFuncCmpStr pCriterio)
{
    {
        int output = -1;
        void* aux;
        if(this != NULL && pCriterio != NULL)
        {
            for(int x = 0; x < ll_len(this); x++)
            {
                aux = ll_get(this, x);
                if((pCriterio(aux, str)))
                {
                    output = 0;
                    break;
                }
            }
        }
        return output;
    }
}

int ll_mapDosEntidades(LinkedList* this, LinkedList* this2, pDosEntidades pCriterio)
{
    int output = -1;
    void* auxThis;
    void* auxThis2;
    if(this != NULL && this2 != NULL && pCriterio != NULL)
    {
        for(int x = 0; x < ll_len(auxThis); x++)
        {
            auxThis = ll_get(this, x);
            for(int j = 0; j < ll_len(auxThis2); j++)
            {
                auxThis2 = ll_get(this2, j);
                if(!(pCriterio(auxThis, auxThis2)))
                {
                    output = 0;
                }
            }
        }
    }
    return output;
}

int ll_mapDosEntidadesByInt(LinkedList* this, LinkedList* this2, pDosByInt pCriterio, int number)
{
    int output = -1;
    void* auxThis;
    void* auxThis2;
    if(this != NULL && this2 != NULL && pCriterio != NULL && number > 0)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            auxThis = ll_get(this, x);
            for(int j = 0; j < ll_len(this2); j++)
            {
                auxThis2 = ll_get(this2, j);
                if(!(pCriterio(auxThis, auxThis2, number)))
                {
                    output = 0;
                    break;
                }
            }
        }
    }
    return output;
}

int ll_mapInt(LinkedList* this, pCalcMaxInt pCriterio, int *pResultado)
{
    int output = -1;
    void* aux;
    if(this != NULL && pCriterio != NULL)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            aux = ll_get(this, x);
            if(!(pCriterio(aux, x, pResultado)))
            {
                output = 0;
            }
        }
    }
    return output;
}

int ll_findByInt(LinkedList* this, pFind pCriterio, int number)
{
    {
        int output = -1;
        void* aux;
        if(this != NULL && pCriterio != NULL)
        {
            for(int x = 0; x < ll_len(this); x++)
            {
                aux = ll_get(this, x);
                if((pCriterio(aux, number)))
                {
                    output = 0;
                    break;
                }
            }
        }
        return output;
    }
}

void* ll_findAndReturnElement(LinkedList* this, pFind pCriterio, int number)
{
    void* pElement;
    if(this != NULL && pCriterio != NULL && number > 0)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            pElement = ll_get(this, x);
            if(!(pCriterio(pElement, number)))
            {
                break;
            }
        }
    }
    return pElement;
}

int ll_filter(LinkedList* this, pFunc pCriterio)
{
    int output = -1;
    void* aux;
    if(this != NULL && pCriterio != NULL)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            aux = ll_get(this, x);
            if(aux != NULL)
            {
                if(!(pCriterio(aux)))
                {
                    ll_pop(this, x);
                    x--;
                    output = 0;
                }
            }
        }
    }
    return output;
}

void* ll_filterByInt(LinkedList* this, LinkedList* this2, pReduceInt pCriterio, int* pResultado, int* pResultado2)
{
    void* aux1;
    void* aux2;
    int bufferMax;
    int bufferAcumulador = 0;
    void* aux3;
    if(this != NULL && this2 != NULL && pCriterio != NULL && pResultado != NULL)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            aux1 = ll_get(this, x);
            for(int j = 0; j < ll_len(this2); j++)
            {
                aux2 = ll_get(this2, j);
                if(!(pCriterio(aux2, aux1, &bufferAcumulador)))
                {
                    if(bufferMax < bufferAcumulador || x == 0)
                    {
                        bufferMax = bufferAcumulador;
                        *pResultado = bufferMax;
                        aux3 = aux1;
                        *pResultado2 = 0;
                    }
                    else if(bufferMax == bufferAcumulador)
                    {
                       *pResultado2 = 1;
                    }
                }
            }
        }
    }
    return aux3;
}

LinkedList* ll_filterToNewListByInt(LinkedList* this, LinkedList* this2, pDosByInt pCriterio, int number)
{
    void* aux1;
    void* aux2;
    LinkedList* this3;
    if(this != NULL && this2 != NULL && pCriterio != NULL && number >= 0)
    {
        this3 = ll_newLinkedList();
        if(this3 != NULL)
        {
            for(int x = 0; x < ll_len(this); x++)
            {
                aux1 = ll_get(this, x);
                for(int j = 0; j < ll_len(this2); j++)
                {
                    aux2 = ll_get(this2, j);
                    if(pCriterio(aux1, aux2, number))
                    {
                        ll_add(this3, aux1);
                        break;
                    }
                }
            }
        }
    }
    return this3;
}

int ll_reduceInt(LinkedList* this, void* aux2, pDosByInt pCriterio, int* pResultado, int number)
{
    int output = -1;
    void* aux;
    int counter = 0;
    if(this != NULL && pCriterio != NULL)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            aux = ll_get(this, x);
            if(aux != NULL)
            {
                 if(pCriterio(aux2,aux, number))
                 {
                     counter++;
                     output = 0;
                 }
            }
        }
        if(counter > 0)
        {
            *pResultado = counter;
        }
    }
    return output;
}

int ll_reduceIntMinMax(LinkedList* this, void* aux2, pReduceInt pCriterio, int* pResultado)
{
    int output = -1;
    void* aux;
    int counter = 0;
    if(this != NULL && pCriterio != NULL)
    {
        for(int x = 0; x < ll_len(this); x++)
        {
            aux = ll_get(this, x);
            if(aux != NULL)
            {
                 if(!(pCriterio(aux2,aux, &counter)))
                 {
                     output = 0;
                 }
            }
        }
        if(counter > 0)
        {
            *pResultado = counter;
        }
    }
    return output;
}

int ll_sort2(LinkedList* this, pFuncSort pCriterio)
{
    int output = -1;
    void* actual;
    void* siguiente;
    int len;
    int flagSort = 1;

    if(this != NULL)
    {
        len = ll_len(this);
        while(flagSort == 1)
        {
            flagSort = 0;
            for(int x = 0; x < len-1; x++)
            {
                actual = ll_get(this, x);
                siguiente = ll_get(this, x+1);
                if(pCriterio(actual, siguiente) == 1)
                {
                    if(!(ll_set(this, x, siguiente)) && !(ll_set(this, x+1, actual)))
                    {
                        flagSort = 1;
                        output = 0;
                    }
                }
            }
        }
    }
    return output;
}

int ll_sort3(LinkedList* this, LinkedList* this2, pFuncDobleSort pCriterio)
{
    int output = -1;
    void* uActual;
    void* uNext;
    void* mActual;
    void* mNext;
    int lenUsuarios;
    int lenMensajes;
    int uFlagSort = 1;

    if(this != NULL && this2 != NULL)
    {
        lenUsuarios = ll_len(this);
        lenMensajes = ll_len(this2);
        while(uFlagSort)
        {
            uFlagSort = 0;
            for(int x = 0; x <lenUsuarios-1; x++)
            {
                uActual = ll_get(this, x);
                uNext = ll_get(this, x+1);

                for(int j = 0; j < lenMensajes-1; j++)
                {
                    mActual = ll_get(this2, j);
                    mNext = ll_get(this2, j+1);

                    if(!(pCriterio(uActual, uNext, mActual, mNext)))
                    {
                        if(!(ll_set(this, x, uNext)) && !(ll_set(this, x+1, uActual)))
                        {
                            output = 0;
                            uFlagSort = 1;
                        }
                    }
                    else if(pCriterio(uActual, uNext, mActual, mNext) == 1)
                    {
                        if(!(ll_set(this, x, uNext)) && !(ll_set(this, x+1, uActual))
                                && !(ll_set(this2, j, mNext)) && !(ll_set(this2, j+1, mActual)))
                        {
                            output = 0;
                            uFlagSort = 1;
                        }
                    }
                }
            }
        }
    }
    return output;
}



/*int ll_sort(LinkedList *this, pFuncSort pCriterio, int order)
{
    int output = -1;
    void* current;
    void* next;
    int len;
    int flagSort = 1;
    if(this != NULL && pCriterio != NULL && order > -1 && order < 2)
    {
        len = ll_len(this);
        while(flagSort)
        {
            flagSort = 0;
            for(int x = 0; x < len-1; x++)
            {
                current = ll_get(this, x);
                next = ll_get(this, x+1);
                if((order == 1 && (pCriterio(current, next)) == 1) || (order == 0 && (pCriterio(current, next)) == -1))
                {

                    if(!(ll_set(this, x, next)) && !(ll_set(this, x+1, current)))
                    {
                        flagSort = 1;
                        output = 0;
                    }
                }
            }
        }
    }
    return output;
}*/



