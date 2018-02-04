#include <stdio.h>
#include "jam.h"

int main()
{
    JAM J, J1;
    int H, M, S;
    long js;
    printf("masukkan h m s\n");
    BacaJAM(&J); //mengecek fungsi dan prosedur isJAMValid, MakeJAM, BacaJAM
    TulisJAM(J); //mengecek prosedur tulisJAM
    printf("\n");
    printf("kalau dalam detik?\n");
    printf("%ld", JAMToDetik(J)); //mengecek fungsi JAMToDetik
    printf("\n");
    js = JAMToDetik(J);
    J1 = (DetikToJAM(js)); //mengecek fungsi detikToJAM
    printf("ubah lagi ke jam?\n");
    TulisJAM(J1);
    printf("\n");
    printf("is j and j1 equal?\n");
    if (JEQ(J, J1))
    {
        printf("equal");
    } else printf("not equal");
    printf("\n");
    if (JNEQ(J, J1))
    {
        printf("not equal");
    } else printf("not not equal");
    printf("\n");
   if (JLT(J,J1))
   {
       printf("less than");
   } else printf("not less than");
    printf("\n");
    printf("next detik\n");
    TulisJAM(NextDetik(J));
    printf("\n");
    printf("next 2 detik\n");
    TulisJAM(NextNDetik(J,2));
    printf("\n");
    printf("prev detik\n");
    TulisJAM(PrevDetik(J));
    printf("\n");
    printf("prev 2 detik\n");
    TulisJAM(PrevNDetik(J,2));
    printf("\n");
    printf("cek durasi, harusnya hasilnya 2\n");
    printf("%ld",Durasi(J,NextNDetik(J,2)));
}