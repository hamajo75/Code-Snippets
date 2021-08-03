#include <stdio.h>
#include <iostream>
#include <string.h>

#include <stdlib.h>

double values[] = { 88., 56., 100., 2., 25. };

int cmpfunc (const void* a, const void* b) {
   return ( *(double*)a - *(double*)b );
}

int main () {
   int n;

   printf("Before sorting the list is: \n");
   for( n = 0 ; n < 5; n++ ) {
      printf("%f ", values[n]);
   }

   qsort(values, 5, sizeof(double), cmpfunc);

   printf("\nAfter sorting the list is: \n");
   for( n = 0 ; n < 5; n++ ) {   
      printf("%f ", values[n]);
   }
  
   return(0);
}

