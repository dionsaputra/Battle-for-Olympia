#include <stdio.h>
#include <stdlib.h>
#include "PlayerTurn.h"
#include "player.h"
#include "peta.h"
#include "stackt.h"
#include "game.h"

/*pakai dengan menggunakan & ex.NextTurnQueue(&Q)*/

void CreateTurnQueue12(Queue *Q)
{
    CreateEmpty(Q,2);
    Add(Q,1);
    Add(Q,2);
}


void CreateTurnQueue21(Queue *Q)
{
    CreateEmpty(Q,2);
    Add(Q,2);
    Add(Q,1);
}

void NextTurnQueue(Queue *Q, player *p, player *q, peta *M, Stack *S)
{
    int A;
    Del(Q,&A);
    Add(Q,A);
    gold(*p)=gold(*p)+income(*p)-upkeep(*p);
    add_unit P = First_unit(list_unit(*p));
    while (P != Nil){
        move_point(Info_unit(P)) = max_move_point(Info_unit(P)); 
        kesempatan_serang(Info_unit(P)) = true;
        kesempatan_serang(unit_petak(petak(*M, Absis(lokasi_unit(Info_unit(P))),Ordinat(lokasi_unit(Info_unit(P)))))) = true;
        P = Next_unit(P);
    }
    for (int i=0; i<NBrsEff(*M); i++){
        for (int j=0; j<NBrsEff(*M); j++){
            if (pemilik(unit_petak(petak(*M,i,j))) == simbol_player(*p)){
                move_point(unit_petak(petak(*M,i,j))) = max_move_point(unit_petak(petak(*M,i,j)));
            }
        }
    }
    move_point(selected(*p)) = max_move_point(selected(*p));
    selected(*p) = Info_unit(address_king(list_unit(*p)));
    kesempatan_serang(selected(*p)) = true;
    white_heal(q, M);
    CreateEmptyStack(S);
}
