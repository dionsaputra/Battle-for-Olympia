#include "player.h"
#include "boolean.h"
#include "unit.h"
#include "petak.h"
#include <stdio.h>
#include <stdlib.h>

/******************		LIST UNIT 	******************************/
boolean IsEmpty_listunit(listunit L){
	return First_unit(L) == Nil;
}

void CreateEmpty_listunit(listunit *L){
	First_unit(*L) = Nil;
}

add_unit Alokasi_listunit(unit X){
	add_unit P = (add_unit) malloc(sizeof(unitlist));
	if (P!=Nil){
		Info_unit(P) = X;
		Next_unit(P) = Nil;
	}
	return P;
}

add_unit address_king(listunit L){
	add_unit P = First_unit(L);
	boolean bfound = false;
	while (P!= Nil && !bfound){
		if(simbol(Info_unit(P)) == 'K')
			bfound = true;
		else
			P = Next_unit(P);
	}
	return P;
}

void Dealokasi_listunit(add_unit *P){
	free (*P);
}

add_unit Search_listunit(listunit L, unit X){
	add_unit P = First_unit(L);
	boolean bFound = false;
	while (P!=Nil && !bFound){
		if (isequal_unit(X,Info_unit(P))){
			bFound = true; 
		} else {
			P = Next_unit(P);
		}
	}
	return P;
}

void InsVFirst_listunit (listunit *L, unit X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan Alokasi_listunit sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika Alokasi_listunit berhasil */
{
	add_unit P = Alokasi_listunit(X);
	if (P!=Nil){
		Next_unit(P) = First_unit(*L);
		First_unit(*L) = P;
	}
}
void InsVLast_listunit (listunit *L, unit X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan Alokasi_listunit sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika Alokasi_listunit berhasil. Jika Alokasi_listunit gagal: I.S.= F.S. */
{
	add_unit P = Alokasi_listunit(X);
	if (P!=Nil) {
		InsertLast_listunit(L,P);
	}
}
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst_listunit (listunit *L, unit *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
{
	add_unit P = First_unit(*L);
	First_unit(*L) = Next_unit(First_unit(*L));
	Next_unit(P) = Nil;
	*X = Info_unit(P);
	Dealokasi_listunit(&P);
}
/*      dan alamat elemen pertama di-Dealokasi_listunit */
void DelVLast_listunit (listunit *L, unit *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-Dealokasi_listunit */
{
	add_unit Last = First_unit(*L);
	add_unit PrecLast = Nil;
	while (Next_unit(Last) != Nil){
		PrecLast = Last;
		Last = Next_unit(Last);
	}
	*X = Info_unit(Last);
	if (PrecLast == Nil){
		First_unit(*L) = Nil;
	} else {
		Next_unit(PrecLast) = Nil;
	}
}

void InsertFirst_listunit (listunit *L, add_unit P)
/* I.S. Sembarang, P sudah diAlokasi_listunit  */
/* F.S. Menambahkan elemen ber-add_unit P sebagai elemen pertama */
{
	Next_unit(P) = First_unit(*L);
	First_unit(*L) = P;	
}

void InsertAfter_listunit (listunit *L, add_unit P, add_unit Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah diAlokasi_listunit  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next_unit(P) = Next_unit(Prec);
	Next_unit(Prec) = P;
}

void InsertLast_listunit (listunit *L, add_unit P)
/* I.S. Sembarang, P sudah diAlokasi_listunit  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	if (IsEmpty_listunit(*L)){
		InsertFirst_listunit(L,P); 
	} else {
		add_unit Last = First_unit(*L);
		while (Next_unit(Last) != Nil) {
			Last = Next_unit(Last);
		}
		InsertAfter_listunit(L,P,Last);
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst_listunit (listunit *L, add_unit *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P = First_unit(*L);
	First_unit(*L) = Next_unit(First_unit(*L));
	Next_unit(*P) = Nil;
}

void DelP_listunit (listunit *L, unit X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beradd_unit P, dengan Info_unit(P)=X  */
/* Maka P dihapus dari list dan di-Dealokasi_listunit */
/* Jika tidak ada elemen list dengan Info_unit(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	if (!IsEmpty_listunit(*L)){
		add_unit P = Search_listunit(*L,X);
		if (P!=Nil){
			if (P==First_unit(*L)){
				DelFirst_listunit(L,&P);
			} else {
				add_unit Prec = First_unit(*L);
				while (Next_unit(Prec) != P) {
					Prec = Next_unit(Prec);
				}
				DelAfter_listunit(L,&P,Prec);
			}
		}
	}
}

void DelLast_listunit (listunit *L, add_unit *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
	add_unit Last = First_unit(*L);
	add_unit PrecLast = Nil;
	while (Next_unit(Last) != Nil){
		PrecLast = Last;
		Last = Next_unit(Last);
	}	
	*P = Last;
	if (PrecLast == Nil) {
		First_unit(*L) = Nil;
	} else {
		Next_unit(PrecLast) = Nil;
	}
}

void DelAfter_listunit (listunit *L, add_unit *Pdel, add_unit Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next_unit(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel = Next_unit(Prec);
	Next_unit(Prec) = Next_unit(Next_unit(Prec));
	Next_unit(*Pdel) = Nil;
}

/************************	LIST PETAK	******************************/

/************************	LIST PETAK	******************************/
boolean IsEmpty_listpetak(listpetak L){
	return First_petak(L) == Nil;
}

void CreateEmpty_listpetak(listpetak *L){
	First_petak(*L) = Nil;
}

add_petak Alokasi_listpetak(petak X){
	add_petak P = (add_petak) malloc(sizeof(petaklist));
	if (P!=Nil){
		Info_petak(P) = X;
		Next_petak(P) = Nil;
	}
	return P;
}

void Dealokasi_listpetak(add_petak *P){
	free (*P);
}

add_petak Search_listpetak(listpetak L, petak X){
	add_petak P = First_petak(L);
	boolean bFound = false;
	while (P!=Nil && !bFound){
		if (isequal_petak(X,Info_petak(P))){
			bFound = true; 
		} else {
			P = Next_petak(P);
		}
	}
	return P;
}

void InsVFirst_listpetak (listpetak *L, petak X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	add_petak P = Alokasi_listpetak(X);
	if (P!=Nil){
		Next_petak(P) = First_petak(*L);
		First_petak(*L) = P;
	}
}
void InsVLast_listpetak (listpetak *L, petak X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	add_petak P = Alokasi_listpetak(X);
	if (P!=Nil) {
		InsertLast_listpetak(L,P);
	}
}
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst_listpetak (listpetak *L, petak *X)
/* I.S. listpetak L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
{
	add_petak P = First_petak(*L);
	First_petak(*L) = Next_petak(First_petak(*L));
	Next_petak(P) = Nil;
	*X = Info_petak(P);
	Dealokasi_listpetak(&P);
}
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast_listpetak (listpetak *L, petak *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	add_petak Last = First_petak(*L);
	add_petak PrecLast = Nil;
	while (Next_petak(Last) != Nil){
		PrecLast = Last;
		Last = Next_petak(Last);
	}
	*X = Info_petak(Last);
	if (PrecLast == Nil){
		First_petak(*L) = Nil;
	} else {
		Next_petak(PrecLast) = Nil;
	}
}

void InsertFirst_listpetak (listpetak *L, add_petak P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-add_petak P sebagai elemen pertama */
{
	Next_petak(P) = First_petak(*L);
	First_petak(*L) = P;	
}

void InsertAfter_listpetak (listpetak *L, add_petak P, add_petak Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next_petak(P) = Next_petak(Prec);
	Next_petak(Prec) = P;
}

void InsertLast_listpetak (listpetak *L, add_petak P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	if (IsEmpty_listpetak(*L)){
		InsertFirst_listpetak(L,P); 
	} else {
		add_petak Last = First_petak(*L);
		while (Next_petak(Last) != Nil) {
			Last = Next_petak(Last);
		}
		InsertAfter_listpetak(L,P,Last);
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst_listpetak (listpetak *L, add_petak *P)
/* I.S. listpetak tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P = First_petak(*L);
	First_petak(*L) = Next_petak(First_petak(*L));
	Next_petak(*P) = Nil;
}

void DelP_listpetak (listpetak *L, petak X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beradd_petak P, dengan Info_petak(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info_petak(P)=X, maka list tetap */
/* listpetak mungkin menjadi kosong karena penghapusan */
{
	if (!IsEmpty_listpetak(*L)){
		add_petak P = Search_listpetak(*L,X);
		if (P!=Nil){
			if (P==First_petak(*L)){
				DelFirst_listpetak(L,&P);
			} else {
				add_petak Prec = First_petak(*L);
				while (Next_petak(Prec) != P) {
					Prec = Next_petak(Prec);
				}
				DelAfter_listpetak(L,&P,Prec);
			}
		}
	}
}

void DelLast_listpetak (listpetak *L, add_petak *P)
/* I.S. listpetak tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
	add_petak Last = First_petak(*L);
	add_petak PrecLast = Nil;
	while (Next_petak(Last) != Nil){
		PrecLast = Last;
		Last = Next_petak(Last);
	}	
	*P = Last;
	if (PrecLast == Nil) {
		First_petak(*L) = Nil;
	} else {
		Next_petak(PrecLast) = Nil;
	}
}

void DelAfter_listpetak (listpetak *L, add_petak *Pdel, add_petak Prec)
/* I.S. listpetak tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next_petak(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel = Next_petak(Prec);
	Next_petak(Prec) = Next_petak(Next_petak(Prec));
	Next_petak(*Pdel) = Nil;
}

// PLAYER

#define INIT_GOLD 100

void init_player(player *p, char wrn, int smb){
// setting awal player
	gold(*p) = INIT_GOLD;
	income(*p) = 0;
	upkeep(*p) = 0;
	CreateEmpty_listunit(&list_unit(*p));
	CreateEmpty_listpetak(&list_petak(*p));
	warna(*p) = wrn;
	simbol_player(*p) = smb;
}

void change_unit(player *P){
	// tampilkan seluruh unit
	printf("List of Units \n");
	//cetak info king
	add_unit CU = First_unit(list_unit(*P));
	int cnt = 1;
	while (CU != Nil){
		printf("%d. ", cnt);
		switch (simbol(Info_unit(CU))){
			case 'K' : printf("King "); break;
			case 'A' : printf("Archer "); break;
			case 'S' : printf("Swordsman "); break;
			case 'W' : printf("White Mage "); break;
			default  : printf("No unit found");
		}
		tulis_point(lokasi_unit(Info_unit(CU)));
		printf(" | Health: %d | ATK: %d | Move_pts: %d | ATK_type: ",health(Info_unit(CU)),attack(Info_unit(CU)),move_point(Info_unit(CU)));
		switch (tipe_serang(Info_unit(CU))){
			case 'M' : printf("Melee"); break;
			case 'R' : printf("Range"); break;
			default  : printf("No unit found");
		}
		printf(" | ATK_chance: ");
		if(kesempatan_serang(Info_unit(CU))){
			printf("Yes ");
		} else {
			printf("No ");
		}
		printf(" | Price: %d\n",harga(Info_unit(CU)));
		CU = Next_unit(CU);
		cnt++;
	}

	printf("Enter the number of unit you want to select : ");
	int num_slc;
	do {
		scanf("%d",&num_slc);
		if (num_slc < 1 || num_slc >= cnt){
			printf("Invalid input. Try again\n");
		}
	} while (num_slc < 1 || num_slc >= cnt);

	// searching unit bernomor num_slc
	add_unit CUU = First_unit(list_unit(*P));
	int cnt1 = 1;
	while (cnt1 < num_slc){
		CUU = Next_unit(CUU);
		cnt1 = cnt1 + 1;
	}
	// mengganti unit yang dipilih P menjadi CU
	selected(*P) = Info_unit(CUU);
	printf("You have select ");
	switch (simbol(Info_unit(CUU))){
		case 'K' : printf("King ");
		case 'A' : printf("Archer "); break;
		case 'S' : printf("Swordsman "); break;
		case 'W' : printf("White Mage "); break;
		default  : printf("No unit found");
	}
	tulis_point(lokasi_unit(Info_unit(CUU)));	
	printf("\n");
}

void next_unit(player *p){
	add_unit P = First_unit(list_unit(*p));

	while (P != Nil && (kesempatan_serang(Info_unit(P)) != true || move_point(Info_unit(P)) > 0)){
		P = Next_unit(P);
	}

	if (P != Nil){
		printf("Your selected unit has been changed to %c (%d,%d)\n",simbol(Info_unit(P)), Absis(lokasi_unit(Info_unit(P))), Ordinat(lokasi_unit(Info_unit(P))));
		selected(*p) = Info_unit(P);
	}
	else // HABIS
		printf("You don't have any unit left that able to move\n");
}

void display_player_info(player p){
	int x = Absis(lokasi_unit(selected(p)));
	int y = Ordinat(lokasi_unit(selected(p)));
	int m = move_point(selected(p));
	printf("Player %d turn\n",simbol_player(p));
	printf("Cash: %dG| Income: %dG| Upkeep: %dG\n", gold(p),income(p),upkeep(p));
	switch(simbol(selected(p))){
		case 'K' : printf("King"); break;
		case 'A' : printf("Archer"); break;
		case 'S' : printf("Swordsman"); break;
		case 'W' : printf("White Mage"); break;
		default : printf("ERROR"); break;
	}
	printf(" (%d,%d) | Movement Points: %d | Can attack: ",x,y,m);
	if (kesempatan_serang(selected(p))){
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	printf("\n");
}