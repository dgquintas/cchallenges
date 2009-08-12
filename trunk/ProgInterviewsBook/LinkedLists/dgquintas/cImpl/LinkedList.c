#include "LinkedList.h"

void list_init(List* const list, void (*destroy)(void* data)){
  list->head = NULL;
  list->tail = NULL;

  list->destroy = destroy;

  list->size = 0;

}
void* list_get(const List* const list, int i){
  if( i >= list->size ){
    return NULL;
  }
  else if( i == 0 ){ //head
    return list->head->data;
  }
  else{
    //traverse the list
    const ListElement* nextElement = list->head;
    int j;
    for(j = 0 ; j < i; j++){ 
      nextElement = nextElement->next;
      assert(nextElement != NULL);
    }
    return nextElement->data;
  }
}

int list_add(List* const list, void* data){
  ListElement* const newElem = (ListElement*)malloc( sizeof(ListElement) );
  if( newElem == NULL ){
    return -1;
  }

  //assign the new data to the new elem
  newElem->data = data;
  //new element will be the new tail => its *next -> NULL
  newElem->next = NULL;

  if( list->head == NULL ){ //no head => empty list
    assert( list->size == 0 );
    //new element will be both the new head and tail
    list->head = newElem;
    list->tail = newElem;
  }
  else{ //already some stuff in the list
    //gotta change the current list's tail element's next pointer
    //to the newly created element
    ListElement* const tail = list->tail;
    tail->next = newElem;

    //new element is the new tail
    list->tail = newElem;
  }
  
  list->size++;
  return 0;
}


int list_insert(List* const list, const int pos, void* data){
  if( pos >= list->size ){
    return -1;
  }

  ListElement* const newElem = (ListElement*)malloc( sizeof(ListElement) );
  if( newElem == NULL ){
    return -1;
  }
  //assign the new data to the new elem
  newElem->data = data;

  if( pos == 0 ){ //substitute head
    newElem->next = list->head;
    list->head = newElem;
  }
  else if( pos == list->size-1 ){ //this is just a normal add
    return list_add(list, data);
  }
  else{ //in the middle de los chichos
    ListElement* ithElem = list->head;
    int i;
    for( i = 1; i < pos; i++ ){
      ithElem = ithElem->next;
    }
    //insert now, *after* i-th element
    //element's next will be newElem's next
    newElem->next = ithElem->next;
    ithElem->next = newElem;
  }

  list->size++;
  return 0;

}

int list_remove(List* const list, const int pos){
  if( pos >= list->size ){
    return -1;
  }

  if( pos == 0 ){ //remove head
    ListElement* oldHead = list->head;
    list->head = oldHead->next;

    //destroy the former head's data
    list->destroy(oldHead->data);
    free(oldHead);
    oldHead = NULL;
  }
  else{
    ListElement* ithElem = list->head;

    int i;
    for( i = 1; i < pos; i++){
      ithElem = ithElem->next;
    }
    //remove element *after* ithElem
    ListElement* toRemove = ithElem->next;
    ithElem->next = toRemove->next;

    list->destroy(toRemove->data);
    free(toRemove);
    toRemove = NULL;

    if( pos == list->size-1 ){ //we've just removed the tail => new tail
      list->tail = ithElem;
    }
  }
  list->size--;
  return 0;
}

