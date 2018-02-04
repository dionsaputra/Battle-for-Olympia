#include<stdio.h>
#include "queue.h"

int main(){
    Queue Q;
    CreateEmpty(&Q,10);

    for(int i=0;i<10;i++){
        printf("add %d\n", i);
        Add(&Q,i);
    }

    int X;
    for(int i=0;i<10;i++){
        Del(&Q,&X);
        printf("deleted front element  = %d\n", X);
    }
}