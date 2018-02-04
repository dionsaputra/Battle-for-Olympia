/* Nama: Dafi Ihsandiya Faraz
  NIM: 13516057 */
/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */


#include "mesinkar.h"
#include "mesinkata.h"
#include "kata.h"

boolean EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
{
	while ((CC == BLANK) && (CC != MARK))
	{
		ADV();
	}
}
void STARTKATA()
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
	START();
	IgnoreBlank();
	if (CC == MARK)
	{
		EndKata = true;
	} else
	{
		EndKata = false;
		SalinKata();
	}
}
void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
	IgnoreBlank();
	if (CC == MARK)
	{
		EndKata = true;
	} else
	{
		SalinKata();
	}
}
void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
	int i = 1;
	for (;;)
	{
		CKata.TabKata[i] = CC;
		if (i == NMax)
		{
			break;
		}
		ADV();
		if ((CC == MARK) || (CC == BLANK))
		{
			break;
		} else{
			i++;
		}
	}
	CKata.Length = i;
	IgnoreBlank();
}

Kata BuildKata(char* str){
  Kata ans;
  int i;
  ans.Length = len(str);
  for (i=0; i<len(str); i++){
  	ans.TabKata[i] = str[i];
  }
  ans.TabKata[i] = '\0';
  return ans;
}

boolean isSamaKata(Kata K1, Kata K2){
  if (K1.Length == K2.Length){
    int i=0;
    while (i<K1.Length && K1.TabKata[i] == K2.TabKata[i]){
      i++;
    }
    return K1.TabKata[i] == K2.TabKata[i];
  } else {
    return false;
  }
}