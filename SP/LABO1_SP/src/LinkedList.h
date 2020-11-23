/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

typedef int (*pFunc)            (void*);
typedef int (*pFuncSort)        (void*,void*);
typedef int (*pReduce)          (void*,float*);
typedef int (*pReduceInt)       (void*,void*,int*);
typedef int (*pFind)            (void*,int);
typedef int (*pFuncCmpStr)      (void*,char*);
typedef int (*pCalcMaxInt)      (void*,int,int*);
typedef int (*pDosEntidades)    (void*,void*);
typedef int (*pDosByInt)        (void*,void*,int);
typedef int (*pFuncDobleSort)   (void*,void*,void*,void*);


//Publicas
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
int ll_sort2(LinkedList* this, int (*pFunc)(void* ,void*));
int ll_sort3(LinkedList* this, LinkedList* this2, int (*pFuncDobleSort)(void* ,void*, void*, void*));

/*              FUNCIONES EXTRAS              */

int ll_map(LinkedList* this, int (*pCriterio)(void*)); // lista
int ll_mapStr(LinkedList* this, char* str, int (*pFuncCmpStr)(void*,char*));
int ll_filter(LinkedList* this, int (*pCriterio)(void*));
int ll_findByInt(LinkedList* this, int (*pFind)(void*,int), int number);
void* ll_findAndReturnElement(LinkedList* this, int (*pFind)(void*,int), int number);
int ll_mapInt(LinkedList* this, int (*pCalcMaxInt)(void*,int,int*), int *pResultado);
int ll_mapDosEntidades(LinkedList* usuarios, LinkedList* posts, int(*pDos)(void*, void*));

int ll_reduceInt(LinkedList* this, void*, int(*pDosByInt)(void*,void*,int), int*);
int ll_mapDosEntidadesByInt(LinkedList*, LinkedList*, int(*pDosByInt)(void*,void*,int), int);
LinkedList* ll_filterToNewListByInt(LinkedList* this, LinkedList* this2, int(*pDosByInt)(void*,void*,int), int);



/*int ll_map(LinkedList* this, int (*pFunc)(void*)); // lista
int ll_filter(LinkedList* this, int (*pFunc)(void*));
int ll_filter2(LinkedList* this, int (*pFuncCmpStr)(void*, char*))
LinkedList* ll_filterToNewListByStr(LinkedList* this, int (*pFunc)(void*, char*), char* str);
int ll_reduceFloat(LinkedList* this, int (*pCriterio)(void*, float*), float*);
int ll_findByInt(LinkedList* this, int(*pFind)(void*, int), int number, int *pResultado);
int ll_mapInt(LinkedList* this, int (*pCalcMaxInt)(void*, int, int*), int *pResultado);*/
