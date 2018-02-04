#include "stackt.h"
#include "boolean.h"

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]
/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack (Stack *S){
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */
	Top(*S) = 0;


}
/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S){
/* Mengirim true jika Stack kosong: lihat definisi di atas */
	return (Top(S) == 0);
}
boolean IsFullStack (Stack S){
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
	return (Top(S) == 20);
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, state X){
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
	Top(*S) += 1;
	InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, state* X){
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
	*X  = InfoTop (*S);
	Top(*S) -= 1;
}