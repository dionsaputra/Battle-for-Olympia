/* File: point.h */
/* Tanggal: 28 Agustus 2016 */
/* *** Definisi ABSTRACT DATA TYPE POINT *** */

#ifndef POINT_H
#define POINT_H

#include "boolean.h"
#include "point.h"
#include <math.h>

typedef struct { 
	int X; /* absis   */
	int Y; /* ordinat */
} POINT;

/* *** Notasi Akses: Selektor POINT *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y
        
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y);
/* Membentuk sebuah POINT dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPOINT (POINT * P); 
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */

boolean isequal_point(POINT P1, POINT P2);
/* true jika P1 dan P2 point yang sama */

void tulis_point(POINT X);
/* Menuliskan point X */

POINT left(POINT P);
/* Mengembalikan point yang berada di sebelah kiri point p dalam representasi peta game */

POINT right(POINT P);
/* Mengembalikan point yang berada di sebelah kiri point p dalam representasi peta game */

POINT up(POINT P);
/* Mengembalikan point yang berada di sebelah kiri point p dalam representasi peta game */

POINT down(POINT P);
/* Mengembalikan point yang berada di sebelah kiri point p dalam representasi peta game */

#endif