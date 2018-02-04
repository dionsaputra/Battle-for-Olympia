#include <stdio.h>
#include "point.h"

int main(){
    POINT P;
    BacaPOINT(&P);
    printf("P     : ");tulis_point(P);printf("\n");
    printf("right : ");tulis_point(right(P));printf("\n");
    printf("left  : ");tulis_point(left(P));printf("\n");
    printf("up    : ");tulis_point(up(P));printf("\n");
    printf("down  : ");tulis_point(down(P));printf("\n");


}