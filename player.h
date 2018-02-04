#ifndef PLAYER_H
#define PLAYER_H

#include "boolean.h"
#include "point.h"
#include "unit.h"
#include "petak.h"
#include <stdlib.h>
#include <stdio.h>

/***********************	LIST OF UNIT 	**************************/
#define Nil NULL

typedef struct t_unitlist *add_unit;
typedef struct t_unitlist {
	unit info_unit;
	add_unit next_unit;
} unitlist;
typedef struct {
	add_unit First_unit;
} listunit;

#define Info_unit(CU) (CU)->info_unit
#define Next_unit(CU) (CU)->next_unit
#define First_unit(L) (L).First_unit

boolean IsEmpty_listunit(listunit L);

void CreateEmpty_listunit(listunit *L);

add_unit Alokasi_listunit(unit X);

add_unit address_king(listunit L);

void Dealokasi_listunit(add_unit *P);

add_unit Search_listunit(listunit L, unit X);

void InsVFirst_listunit (listunit *L, unit X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast_listunit (listunit *L, unit X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst_listunit (listunit *L, unit *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info_unit disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast_listunit (listunit *L, unit *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info_unit disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst_listunit (listunit *L, add_unit P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-add_unit P sebagai elemen pertama */
void InsertAfter_listunit (listunit *L, add_unit P, add_unit Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLast_listunit (listunit *L, add_unit P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst_listunit (listunit *L, add_unit *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP_listunit (listunit *L, unit X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beradd_unit P, dengan Info_unit(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info_unit(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelLast_listunit (listunit *L, add_unit *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void DelAfter_listunit (listunit *L, add_unit *Pdel, add_unit Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next_unit(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/***********************	LIST OF PETAK 	**************************/

typedef struct t_petaklist *add_petak;
typedef struct t_petaklist {
	petak info_petak;
	add_petak next_petak;
} petaklist;
typedef struct {
	add_petak First_petak;
} listpetak;

#define Info_petak(P) (P)->info_petak
#define Next_petak(P) (P)->next_petak
#define First_petak(L) (L).First_petak

boolean IsEmpty_listpetak(listpetak L);

void CreateEmpty_listpetak(listpetak *L);

add_petak Alokasi_listpetak(petak X);

void Dealokasi_listpetak(add_petak *P);

add_petak Search_listpetak(listpetak L, petak X);

void InsVFirst_listpetak (listpetak *L, petak X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void InsVLast_listpetak (listpetak *L, petak X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst_listpetak (listpetak *L, petak *X);
/* I.S. listpetak L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info_petak disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void DelVLast_listpetak (listpetak *L, petak *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info_petak disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst_listpetak (listpetak *L, add_petak P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-add_petak P sebagai elemen pertama */
void InsertAfter_listpetak (listpetak *L, add_petak P, add_petak Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLast_listpetak (listpetak *L, add_petak P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst_listpetak (listpetak *L, add_petak *P);
/* I.S. listpetak tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP_listpetak (listpetak *L, petak X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beradd_petak P, dengan Info_petak(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info_petak(P)=X, maka list tetap */
/* listpetak mungkin menjadi kosong karena penghapusan */
void DelLast_listpetak (listpetak *L, add_petak *P);
/* I.S. listpetak tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void DelAfter_listpetak (listpetak *L, add_petak *Pdel, add_petak Prec);
/* I.S. listpetak tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next_petak(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */


/***********************	PLAYER 	************************/
typedef struct {
	int gold;
	listunit list_unit;
	listpetak list_petak;
	int income;
	int upkeep;
	char warna;
	int simbol;
	unit selected;
	// berguna buat recruit karena nggak bisa akses peta dari player
	petak petak_khusus[6]; //petak[0] simpan tower, 4 lagi simpan castle 
	unit king_player; //berguna buat nyimpan info king
} player;

#define gold(P) (P).gold
#define list_unit(P) (P).list_unit
#define list_petak(P) (P).list_petak
#define income(P) (P).income
#define upkeep(P) (P).upkeep
#define warna(P) (P).warna
#define simbol_player(P) (P).simbol
#define selected(P) (P).selected
#define petak_khusus(P,i) (P).petak_khusus[i]
#define king_player(P) (P).king_player

void init_player(player *p, char wrn, int smb);
/*I.S. : Sembarang 
  F.S. : player p diinisiasi dengan warna wrn dan simbol smb */

void change_unit(player *p);

void next_unit(player *p);

void display_player_info(player p);
#endif