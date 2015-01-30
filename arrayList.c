#include <stdlib.h>
#include "arrayList.h"

/*
 * Increases the dimension of the Array List.
 * *size is the number of elements in the list.
 * *dimension is the number of elements allocated for the list: it will be doubled
 *  after the function call. In case of 0, it is set to 2.
 * 
 * Returns 0 on success.
 * Returns -1 if memory allocation fails.
 */
int ALIncreaseAndCopy(AList *list, int size, int *dimension) {
    int i;
    int returnValue=-1;
 
    AList nuovoVettore=NULL;
    
    if(*dimension==0) *dimension=1;
    nuovoVettore=(AList)malloc(2*(*dimension)*sizeof(int));
    if(nuovoVettore!=NULL){
        *dimension*=2;
        for(i=0;i<size;i++){
            nuovoVettore[i]=(*list)[i];
        }
        free(*list);
        *list=nuovoVettore;
        returnValue=0;
    }
    return returnValue;
}

/*
 * Inserts the new key at the beginning of the list.
 * *size is the number of elements in the list.
 * *dimension is the number of elements allocated for the list: it could be increased
 *      to store the new element.
 * 
 * Returns 0 on success.
 * Returns -1 if memory allocation fails.
 */
int ALInsertAtBeginning(AList *list, int *size, int *dimension, int key) {
    int returnValue=-1;
    int i;
    int r=0;
    
    if(*size==*dimension){
        r=ALIncreaseAndCopy(list,*size,dimension);
    }
    if(r==0){
        for(i=*size;i>0;i--){
            (*list)[i]=(*list)[i-1];
        }
        (*list)[0]=key;
        (*size)++;
        returnValue=0;
    }
    return returnValue;
}

/*
 * Inserts the new key at the end of the list.
 * *size is the number of elements in the list.
 * *dimension is the number of elements allocated for the list: it could be increased
 *      to store the new element.
 * 
 * Returns 0 on success.
 * Returns -1 if memory allocation fails.
 */
int ALInsertAtEnd(AList *list, int *size, int *dimension, int key) {
    int returnValue=-1;
    int r=0;
    int i;

        if(*size==*dimension){
            r=ALIncreaseAndCopy(list,*size,dimension);
        }
        if(r==0){
            (*list)[*size]=key;
            (*size)++;
            returnValue=0;
        }
    
    return returnValue;
}

/*
 * Inserts the new key at the specified positon of the list.
 * Position is zero-based, meaning that the first element is at position 0,
 * analogous to what happens in arrays.
 * *size is the number of elements in the list.
 * *dimension is the number of elements allocated for the list: it could be increased
 *      to store the new element.
 * 
 * Returns 0 on success.
 * Returns -1 if memory allocation fails.
 */
int ALInsertAtPosition(AList *list, int *size, int *dimension, int key, int position) {
    int returnValue=-1;
    int i;
    int r=0;
    
        if(*size==*dimension && position>=0){
            r=ALIncreaseAndCopy(list,*size,dimension);
        }
        if(((r==0) && (position>=0) && (position<*dimension))){
            for(i=((*dimension)-1);i>position;i--){
                (*list)[i]=(*list)[i-1];
            }
            (*list)[i]=key;
            (*size)++;
            returnValue=0;
        }
    
    return returnValue;
}

/*
 * Gives the key at the specified position. * 
 * 
 * Returns 0 on success.
 * Returns -1 if there is no key at the specified position
 */ 
int ALGetKey(AList list, int size, int position, int *key) {
    int returnValue=-1;
    int dimension =0;

    if(position<size && position>=0 && size>0){
        *key=list[position];
        returnValue=0;
    }
 
    return returnValue;
}

/*
 * Gives the position of the first element, starting from startPosition, that
 * has the specified key.
 * 
 * Returns 0 on success.
 * Returns -1 if not found. 
 */ 
int ALFindKey(AList list, int size, int key, int startPosition, int *position) {
    
    int trovato=0; //se=0, nessun elemento trovato; se=1 elemento trovato.
    int returnValue=-1;
    int i=startPosition;
    
    
    while(i<size && trovato==0){
        if(list[i]==key){
            *position=i;
            trovato=1;
            returnValue=0;
        }
        i++;
    }
    
    return returnValue;
}

/*
 * Removes the first element of the list.
 * *size is the number of elements in the list.
 * The dimension of the list is not reduced.
 * 
 * Returns 0 on success.
 * Returns -1 in case of empty list.
 */
int ALRemoveFirst(AList list, int *size) {
    int i=0;
    int returnValue=-1;
    if(*size>0){
        for(i=0;i<*size;i++){
            list[i]=list[i+1];
        }
        returnValue=0;
        (*size)--;
    }
    
    return returnValue;
}

/*
 * Remove the last element of the list.
 * *size is the number of elements in the list.
 * The dimension of the list is not reduced.
 * 
 * Returns 0 on success.
 * Returns -1 in case of empty list.
 */
int ALRemoveLast(AList list, int *size) {
    int i=0;
    int returnValue=-1;
    
    if(*size>0){
        (*size)--;
        returnValue=0;
    }
    
    return returnValue;
}

/*
 * Remove the element at the specified position.
 * Position is zero-based, meaning that the first element is at position 0,
 * analogous to what happens in arrays.
 * 
 * *size is the number of elements in the list.
 * The dimension of the list is not reduced.
 * 
 * Returns 0 on success.
 * Returns -1 in case it does not exist any element at the specified position
 */
int ALRemoveAtPosition(AList list, int *size, int position) {
    int returnValue=-1;
    int i;
    
    if(position < *size && *size>0){
        for(i=position;i<(*size)-1;i++){
            list[i]=list[i+1];
        }
        (*size)--;
        returnValue=0;   
    }
    
    return returnValue;
}

/*
 * Empties the list.
 * 
 * *size is the number of elements in the list: it is set to 0.
 * *dimension is the number of elements allocated for the list: it is set to 0.
 * 
 * Returns 0 on success.
 * Return -1 in case of emtpy list. 
 */
int ALEmptyList(AList *list, int *size, int *dimension) {
    
    int returnValue=-1;
    
    if(*size>0){
        free(*list);
        *dimension=0;
        *size=0;
        returnValue=0;
    }
    return returnValue;
}


/*
 * Reduces the dimension of the list to its size.
 * 
 * Returns 0 on success.
 * Return -1 if memory allocation fails. 
 */
int ALShrink(AList *list, int *size, int *dimension) {

    AList nuovo;
    int i;
    int returnValue=-1;
    nuovo=(AList)malloc((*size)*sizeof(int));
    if(*size<*dimension && nuovo!=NULL){
         for(i=0;i<(*size);i++){
             nuovo[i]=(*list)[i];
         }
         free(*list);
         *list=nuovo;
         *dimension=*size;
         returnValue=0;
    }
   
    return returnValue;
}
