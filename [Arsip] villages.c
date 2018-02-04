#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "peta.h"
#include "point.h"
#include "petak.h"
#include "player.h"
#include "unit.h"


int RNGbatas(int min, int maks){
//menghasilkan Random Number dari min sampai maks dengan sebelumnya ada srand
    int r;

    r=rand()%(maks-min+1)+min;

    return r;
}


void PasangDesa(int jumlah_village, peta *M){
//MASIH FULL RANDOM, KLO MAU PK BATAS GANTI RNG DAN X Y NYA :) //done, mantap '-'b
//Sudah diedit, random buat setengah peta, dan random buat setengahnya lagi
    int i = 0;
    int x = NBrsEff(*M)-1;
    int y = NKolEff(*M)-1;
    int A,B;

    srand(time(NULL));//Untuk seed rand()

    while (i<=jumlah_village)
    {   
        if (i <= jumlah_village/2){
            //Random untuk bagian kiri peta
            A=RNGbatas(0,x/2);
            B=RNGbatas(0,y/2);
        }
        else {
            //Random untuk bagian kanan peta
            A=RNGbatas(x/2 + 1, x);
            B=RNGbatas(y/2 + 1, y);
        }
        POINT Random_location = MakePOINT(A,B);
        if (jenis_petak(*M,Absis(Random_location), Ordinat(Random_location)))//Tolong ini gmn //OTW
        {
            assign_petak(&(petak(*M,Absis(Random_location),Ordinat(Random_location))), 'V', 0, empty_unit(Random_location));
            i++;
        }
    }
}

