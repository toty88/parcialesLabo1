#ifndef __LINKEDLIST
#define __LINKEDLIST
struct Node
{
    void* pElement;
    struct Node* pNextNode;
}typedef Node;

struct LinkedList
{
    Node* pFirstNode;
    int size;
}typedef LinkedList;
#endif

typedef int (*pMap)             (void*);
typedef int (*pFind)            (void*,int);
typedef int (*pFuncCmpStr)      (void*,char*);
typedef int (*pDosEntidades)    (void*,void*);
typedef int (*pReduce)          (void*,float*);
typedef int (*pCalcMaxInt)      (void*,int,int*);
typedef int (*pDosByInt)        (void*,void*,int);
typedef int (*pReduceInt)       (void*,void*,int*,int);
typedef int (*pFuncDobleSort)   (void*,void*,void*,void*);

LinkedList* ll_newLinkedList(void);
int ll_len(LinkedList* this);
Node* test_getNode(LinkedList* this, int nodeIndex);
int test_addNode(LinkedList* this, int nodeIndex,void* pElement);
int ll_add(LinkedList* this, void* pElement);
void* ll_get(LinkedList* this, int index);
int ll_set(LinkedList* this, int index,void* pElement);
int ll_remove(LinkedList* this,int index);
int ll_clear(LinkedList* this);
int ll_deleteLinkedList(LinkedList* this);
int ll_indexOf(LinkedList* this, void* pElement);
int ll_isEmpty(LinkedList* this);
int ll_push(LinkedList* this, int index, void* pElement);
void* ll_pop(LinkedList* this,int index);
int ll_contains(LinkedList* this, void* pElement);
int ll_containsAll(LinkedList* this,LinkedList* this2);
LinkedList* ll_subList(LinkedList* this,int from,int to);
LinkedList* ll_clone(LinkedList* this);
//int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);



/*              FUNCIONES EXTRAS              */

int ll_mapInt(LinkedList*, pCalcMaxInt, int*);
int ll_sort3(LinkedList*, LinkedList*, pFuncDobleSort);
int ll_mapStr(LinkedList*, char*, int (*pFuncCmpStr)(void*,char*));

int ll_map(LinkedList*, pMap);
int ll_filter(LinkedList*, pMap);

int ll_sort2(LinkedList*, pDosEntidades);
int ll_mapDosEntidades(LinkedList*, LinkedList*, pDosEntidades);

int ll_findByInt(LinkedList*, pFind, int);
void* ll_findAndReturnElement(LinkedList* this, pFind, int*, int);

int ll_reduceInt(LinkedList*, void*, pDosByInt, int*, int);
int ll_mapDosEntidadesByInt(LinkedList*, LinkedList*, pDosByInt, int);
LinkedList* ll_filterToNewListByInt(LinkedList*, LinkedList*, pDosByInt, int);

int ll_reduceIntMinMax(LinkedList*, void*, pReduceInt, int*, int);
void* ll_filterByInt(LinkedList*, LinkedList*, pReduceInt, int*, int*, int);

/*
LinkedList* ll_filterToNewListByStr(LinkedList* this, int (*pFunc)(void*, char*), char* str);
int ll_reduceFloat(LinkedList* this, int (*pCriterio)(void*, float*), float*);
*/
