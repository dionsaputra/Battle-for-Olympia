#ifndef UNIT_H
#define UNIT_H

#include "point.h"
#include "boolean.h"
#include <stdlib.h>
/***********************	UNIT 	**************************/

typedef struct{
	int max_health;
	int health;
	int attack;
	int max_move_point;
	int move_point;
	char tipe_serang;
	boolean kesempatan_serang;
	POINT lokasi;
	int harga;
	char simbol;
	int pemilik; //menunjukkan pemilik unit, jika bernilai 1 maka milik player 1, jika bernilai 2 maka milik player 2, jika 0 maka ia adalah "empty unit"
} unit;
#define max_health(U) (U).max_health
#define health(U) (U).health
#define attack(U) (U).attack
#define max_move_point(U) (U).max_move_point
#define move_point(U) (U).move_point
#define tipe_serang(U) (U).tipe_serang
#define kesempatan_serang(U) (U).kesempatan_serang
#define lokasi_unit(U) (U).lokasi
#define harga(U) (U).harga
#define simbol(U) (U).simbol
#define pemilik(U) (U).pemilik

#define MH_KING 100
#define ATK_KING 10
#define MM_KING 5
#define TS_KING 'M'
#define H_KING -1

#define MH_ARCHER 50
#define ATK_ARCHER 15
#define MM_ARCHER 4
#define TS_ARCHER 'R'
#define H_ARCHER 10

#define MH_SWORDSMAN 75
#define ATK_SWORDSMAN 10
#define MM_SWORDSMAN 6
#define TS_SWORDSMAN 'M'
#define H_SWORDSMAN 15

#define MH_WHITEMAGE 50
#define ATK_WHITEMAGE 5
#define MM_WHITEMAGE 4
#define TS_WHITEMAGE 'M'
#define H_WHITEMAGE 20

unit empty_unit(POINT lokasi_u);
//Mengembalikan unit yang tipe dan kepemilikannya belum terdefinisi di lokasi_u

void assign_unit(unit *u, char tipe_unit, int pemilik_unit); 
//Mengisi unit *u dengan properti sesuai tipe dan pemiliknya.

boolean isequal_unit(unit u1, unit u2);
//Mengembalikan true apabila u1 = u2

void swap_unit(unit *u1, unit *u2);
//I.S : u1 dan u2 terdefinisi
//F.s : u1 menjadi u2, u2 menjadi u1
//Prosedur ini dimanfaatkan untuk command MOVE.

void copy_unit(unit u_src, unit *u_dest);


#endif