#include "boolean.h"
#include "unit.h"
#include "player.h"
#include "petak.h"
#include "peta.h"
#include <math.h>
#include "stdio.h"
#include <stdlib.h>

boolean MEC_canAttack(unit A, unit B){
    boolean b1 = pemilik(A) == 1 && pemilik(B) == 2;
    boolean b2 = pemilik(A) == 2 && pemilik(B) == 1;
    return ((b1||b2) && (manhattan_dist(lokasi_unit(A),lokasi_unit(B)) == 1));
}

boolean MEC_canRetaliates(unit X, unit Y){
    return ((tipe_serang(X)==tipe_serang(Y)) || simbol(Y)=='K') && (health(Y)>0);
}

void MEC_attack(unit *X, unit *Y){
    int chance = rand() % 100;
    int chance2 = rand() % 100;
    
    if (chance <= 20){
        health(*Y) -= attack(*X);
        if(MEC_canRetaliates(*X,*Y) && chance2 <= 20)
            health(*X) -= attack(*Y);
        else if (MEC_canRetaliates(*X,*Y) && chance2 > 20)
            printf("Your enemy attempted to fight back, but it missed!\n");
    }

    else if(chance > 20)
            printf("You missed!\n");
    
    kesempatan_serang(*X) = false;
    move_point(*X) = 0;
}

void printUnitName(unit U){
    if(simbol(U) == 'A'){
        printf("Archer");
    }else
    if(simbol(U) == 'K'){
        printf("King");
    }else
    if(simbol(U) == 'S'){
        printf("Swordsman");
    }else
    if(simbol(U) == 'W'){
        printf("White Mage");
    }
}

void COMMAND_ATTACK(player *one, player *two, peta *m, boolean *game_over){

    if (kesempatan_serang(selected(*one))){
        unit l = unit_petak(petak(*m,Absis(left(lokasi_unit(selected(*one)))),Ordinat(left(lokasi_unit(selected(*one))))));
        unit r = unit_petak(petak(*m,Absis(right(lokasi_unit(selected(*one)))),Ordinat(right(lokasi_unit(selected(*one))))));
        unit u = unit_petak(petak(*m,Absis(up(lokasi_unit(selected(*one)))),Ordinat(up(lokasi_unit(selected(*one))))));
        unit d = unit_petak(petak(*m,Absis(down(lokasi_unit(selected(*one)))),Ordinat(down(lokasi_unit(selected(*one))))));

        int cntUnit = 0;
        int cntUnit2 = 0;

        if (MEC_canAttack(selected(*one),l)) cntUnit2++;
        if (MEC_canAttack(selected(*one),r)) cntUnit2++;
        if (MEC_canAttack(selected(*one),u)) cntUnit2++;
        if (MEC_canAttack(selected(*one),d)) cntUnit2++;

        if (cntUnit2==0){
            printf("No unit to atttack\n");
            return;
        }

        unit uAttack[5];

        printf("Enemy you can attack:\n");
        if (MEC_canAttack(selected(*one),l)){
            //printf("health %d",health(l));
            printf("%d. ",++cntUnit);
            uAttack[cntUnit] = l;
            printUnitName(l);
            printf(" (%d,%d) | Health ", lokasi_unit(l).X, lokasi_unit(l).Y);
            printf("%d/%d\n", health(l), max_health(l));
        }

        if (MEC_canAttack(selected(*one),r)){
            //printf("health %d",health(r));
            printf("%d. ",++cntUnit);
            uAttack[cntUnit] = r;
            printUnitName(r);
            printf(" (%d,%d) | Health ", lokasi_unit(r).X, lokasi_unit(r).Y);
            printf("%d/%d\n", health(r), max_health(r));
        }

        if (MEC_canAttack(selected(*one),u)){
            //printf("health %d",health(u));
            printf("%d. ",++cntUnit);
            uAttack[cntUnit] = u;
            printUnitName(u);
            printf(" (%d,%d) | Health ", lokasi_unit(u).X, lokasi_unit(u).Y);
            printf("%d/%d\n", health(u), max_health(u));
        }

        if (MEC_canAttack(selected(*one),d)){
            //printf("health %d",health(d));
            printf("%d. ",++cntUnit);
            uAttack[cntUnit] = d;
            printUnitName(d);
            printf(" (%d,%d) | Health ", lokasi_unit(d).X, lokasi_unit(d).Y);
            printf("%d/%d\n", health(d), max_health(d));
        }

        printf("Select enemy you want to attack: ");
        int unitYangAkanDiserang;
        scanf("%d", &unitYangAkanDiserang);

        //printf("123456%d", unitYangAkanDiserang);
        unit serang = uAttack[unitYangAkanDiserang];
        
        unit temp1 = selected(*one);
        unit temp2 = serang;
       //printf("%d", health(serang));
        MEC_attack(&selected(*one), &serang);
       //printf("%d",health(serang));

        int xxx = lokasi_unit(serang).X;
        int yyy = lokasi_unit(serang).Y;
        int xxx2 = lokasi_unit(selected(*one)).X;
        int yyy2 = lokasi_unit(selected(*one)).Y;

        // unit_petak(petak(*m,xxx,yyy)) = selected(*one);
        // unit_petak(petak(*m,xxx2,yyy2)) = serang;
        if (health(serang) < health(temp2)){
            printf("Enemy\'s ");
            printUnitName(serang);
            printf(" is damaged by %d.\n",attack(selected(*one)));
        }

        if(health(serang)<=0){
            printf("Enemy\'s ");
            printUnitName(serang);
            printf(" is dead.\n");
            // HAPUS AKU

        }

        if (((tipe_serang(selected(*one)) == tipe_serang(serang) || (simbol(serang)=='K')) && health(serang) > 0)){
            
            if(health(selected(*one)) < health(temp1)){
                printf("Enemy\'s ");
                printUnitName(serang);
                printf(" retaliates.\n");
                printf("Your ");
                printUnitName(selected(*one));
                printf(" is damaged by %d.\n", attack(serang));
            }
            if(health(selected(*one)) <=0){
                printf("Your's ");
                printUnitName(selected(*one));
                printf(" is dead :(\n");
                // HAPUS AKU
            }
        }

        // Update info unit player yang menyerang.
        add_unit slc_in_list_1 = Search_listunit(list_unit(*one),temp1);
        if (health(selected(*one)) > 0){
            Info_unit(slc_in_list_1) = selected(*one);
            unit_petak(petak(*m,xxx2,yyy2)) = selected(*one);
        }
        else { //ded
            DelP_listunit(&list_unit(*one), Info_unit(slc_in_list_1));
            unit_petak(petak(*m,xxx2,yyy2)) = empty_unit(MakePOINT(xxx2,yyy2));
        }
        // Update info unit player yang diserang
        add_unit slc_in_list_2 = Search_listunit(list_unit(*two),temp2);
        // Penanganan khusus apabila yang diserang adalah King 
        if (simbol(serang) == 'K'){
            if (health(serang) > 0){
                selected(*two) = serang;
            } else { // ded
                printf("Congratulations! Player %d has won the game!\n", simbol_player(*one));
                *game_over = true;
            }
        }

        if (health(serang) > 0){
            Info_unit(slc_in_list_2) = serang;
            unit_petak(petak(*m,xxx,yyy)) = serang;
        }
        else { //ded
            DelP_listunit(&list_unit(*two), Info_unit(slc_in_list_2));
            unit_petak(petak(*m,xxx,yyy)) = empty_unit(MakePOINT(xxx,yyy));   
        }
    } else {
        printf("This unit cannot attack anymore.\n");
    }
}