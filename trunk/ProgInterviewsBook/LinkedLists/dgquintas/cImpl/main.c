#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

int main(){

  List l;

  int *a,*b,*c;
  a=(int*)malloc(sizeof(int));
  b=(int*)malloc(sizeof(int));
  c=(int*)malloc(sizeof(int));

  *a = 1;
  *b = 2;
  *c = 3;
  
  list_init(&l, free);
  list_add(&l, a);
  list_add(&l, b);
  list_add(&l, c);

  int listSize = list_getSize(&l);

  printf("List size: %d\n", listSize);
  int i;
  for( i = 0; i < listSize; i++){
    printf("Element at index %d = %d\n", i, *((int*)list_get(&l, i)));
  }

  list_remove(&l, 1);

  listSize = list_getSize(&l);
  printf("List size: %d\n", listSize);
  for( i = 0; i < listSize; i++){
    printf("Element at index %d = %d\n", i, *((int*)list_get(&l, i)));
  }


  return 0;
}
