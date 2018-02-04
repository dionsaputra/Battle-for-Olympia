#include <stdio.h>
#include "peta.h"

void infopetak(peta M)
{
    int X, Y;
    petak p;
    unit u;

    printf("Enter the coordinate of the cell: ");scanf(" %d %d",&X,&Y);
    p=petak(M,X,Y);
    printf("== Cell Info ==\n");
    if(jenis_petak(p)=='V')
    {
        printf("Village\n");
    }
    else if(jenis_petak(p)=='C')
    {
        printf("Castle\n");
    }
    else if(jenis_petak(p)=='T')
    {
        printf("Tower\n");
    }
    else
    {
        printf("Empty Land\n");
    }
    if (jenis_petak(p)!=' '){
    printf("Owned by Player %d\n", milik_petak(p));
    printf("\n");}

    printf("== Unit Info ==\n");
    u=unit_petak(p);


    if(simbol(u)=='K')
    {
        printf("King\n");
    }
    else if(simbol(u)=='A')
    {
        printf("Archer\n");
    }
    else if(simbol(u)=='S')
    {
        printf("Swordsman\n");
    }
    else if(simbol(u)==' ');
    {
        printf("No Unit\n");
    }
    else
    {
        printf("White Mage\n");
    }

    if(simbol(u)!=' '){
    printf("Owned by Player %d\n", pemilik(u));
    printf("Health %d/%d | ATK %d | DEF %c\n",health(u),max_health(u),attack(u),tipe_serang(u))
    }
}
