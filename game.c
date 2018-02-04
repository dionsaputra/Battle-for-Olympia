#include "boolean.h"
#include "point.h"
#include "unit.h"
#include "petak.h"
#include "player.h"
#include "peta.h"
#include "kata.h"
#include "jam.h"
#include "game.h"
#include "stackt.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mesinkata.h"

void start_game(boolean *new_game){
	printf("\n");
	printf("    ____        __  __  __        ______              ____  __                      _       \n");
	printf("   / __ )____ _/ /_/ /_/ /__     / ____/___  _____   / __ \\/ /_  ______ ___  ____  (_)___ _ \n");
	printf("  / __  / __ `/ __/ __/ / _ \\   / /_  / __ \\/ ___/  / / / / / / / / __ `__ \\/ __ \\/ / __ `/ \n");
	printf(" / /_/ / /_/ / /_/ /_/ /  __/  / __/ / /_/ / /     / /_/ / / /_/ / / / / / / /_/ / / /_/ /  \n");
	printf("/_____/\\__,_/\\__/\\__/_/\\___/  /_/    \\____/_/      \\____/_/\\__, /_/ /_/ /_/ .___/_/\\__,_/   \n");
	printf("                                                          /____/         /_/                \n");
	printf("\n");
	printf("START\n");
	printf("1. New Game\n");
	printf("2. Load Game\n");
	printf("\n");
	char start_option;
	for (;;)
	{
		printf("Your input: ");
		scanf("%c",&start_option);
		if (start_option == '1')
		{
			*new_game = true;
			break;
		} else if (start_option == '2')
		{
			*new_game = false;
			break;
		}
		printf("Invalid input. Try again.\n");
		scanf("%c",&start_option);
	}
	printf("\n");
}

void do_new_game(peta *M, player *p1, player *p2){
	boolean valid_peta;
	int input_nbaris, input_nkolom;
	do {
		printf("Length of map row : "); scanf("%d",&input_nbaris);
		printf("\n");
		printf("Length of map column : "); scanf("%d",&input_nkolom);
		printf("\n");
		if (input_nbaris < 8 || input_nkolom < 8 || input_nbaris > MAX_BARIS_peta || input_nkolom > MAX_KOLOM_peta){
			valid_peta = false;
		} else {
			valid_peta = true;
		}
		if (!valid_peta){
			printf("The minimum map area is 8x8 and maximum map area is %dx%d\n",MAX_BARIS_peta,MAX_KOLOM_peta);
			printf("\n");
		}
	} while (!valid_peta);
	init_peta(M, input_nbaris, input_nkolom, p1, p2);
}

void display_command(){
	printf("Available Command\n");
	printf("1.  MOVE\n");
	printf("2.  UNDO\n");
	printf("3.  CHANGE_UNIT\n");
	printf("4.  RECRUIT\n");
	printf("5.  ATTACK\n");
	printf("6.  MAP\n");
	printf("7.  INFO\n");
	printf("8.  END_TURN\n");
	printf("9.  SAVE\n");
	printf("10. EXIT\n");
	printf("11. DISPLAY_COMMAND\n");
	printf("12. NEXT_UNIT\n");
	printf("\n");
}

int command_code(Kata str){
	Kata Kmap = BuildKata("MAP");
	Kata Kinfo = BuildKata("INFO");
	Kata Kmove = BuildKata("MOVE");
	Kata Kundo = BuildKata("UNDO");
	Kata Ksave = BuildKata("SAVE");
	Kata Kexit = BuildKata("EXIT");
	Kata Kattack = BuildKata("ATTACK");
	Kata Krecruit = BuildKata("RECRUIT");
	Kata Kend_turn = BuildKata("END_TURN");
	Kata Knext_unit = BuildKata("NEXT_UNIT");
	Kata Kchange_unit = BuildKata("CHANGE_UNIT");
	Kata Kdisplay_command = BuildKata("DISPLAY_COMMAND");
	
	int code;
	if (isSamaKata(str,Kmove)){
		code = 1;
	} else if (isSamaKata(str,Kundo)){
		code = 2;
	} else if (isSamaKata(str,Kchange_unit)){
		code = 3;
	} else if (isSamaKata(str,Krecruit)){
		code = 4;
	} else if (isSamaKata(str,Kattack)){
		code = 5;
	} else if (isSamaKata(str,Kmap)){
		code = 6;
	} else if (isSamaKata(str,Kinfo)){
		code = 7;
	} else if (isSamaKata(str,Kend_turn)){
		code = 8;
	} else if (isSamaKata(str,Ksave)){
		code = 9;
	} else if (isSamaKata(str,Kexit)){
		code = 10;
	} else if (isSamaKata(str,Kdisplay_command)){
		code = 11;
	} else if (isSamaKata(str,Knext_unit)) { 
		code = 12;
	} else {
		code = 0;
	}
	return code;
}

boolean isAdaMusuh(POINT P_Select, POINT P2, peta M){
	//Cek Horizontalnya (doang)
	boolean ada = false;

	if (Ordinat(P_Select) == Ordinat(P2)){
		if (Absis(P_Select) > Absis(P2)){
			for (int i = Absis(P2) + 1; i < Absis(P_Select); ++i){
				if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 1) && (pemilik(unit_petak(petak(M,i,Ordinat(P2)))) == 2))
					ada = true;
				else if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 2) && (pemilik(unit_petak(petak(M,i,Ordinat(P2)))) == 1))
					ada = true;
			}
		}
		else if (Absis(P_Select) < Absis(P2)){
			for (int i = Absis(P_Select) + 1; i < Absis(P2); ++i){
				if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 1) && (pemilik(unit_petak(petak(M,i,Ordinat(P2)))) == 2))
					ada = true;
				else if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 2) && (pemilik(unit_petak(petak(M,i,Ordinat(P2)))) == 1))
					ada = true;
			}
		}
	}

	//Cek Vertikalnya (doang)
	else if (Absis(P_Select) == Absis(P2)){
		if (Ordinat(P_Select) > Ordinat(P2)){
			for (int i = Ordinat(P2) + 1; i < Ordinat(P_Select); ++i){
				if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 1) && (pemilik(unit_petak(petak(M,Absis(P2),i))) == 2))
					ada = true;
				else if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 2) && (pemilik(unit_petak(petak(M,Absis(P2),i))) == 1))
					ada = true;
			}
		}
		else if (Ordinat(P_Select) < Ordinat(P2)){
			for (int i = Ordinat(P_Select) + 1; i < Ordinat(P2); ++i){
				if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 1) && (pemilik(unit_petak(petak(M,Absis(P2),i))) == 2))
					ada = true;
				else if ((pemilik(unit_petak(petak(M,Absis(P_Select),Ordinat(P_Select)))) == 2) && (pemilik(unit_petak(petak(M,Absis(P2),i))) == 1))
					ada = true;
			}
		}
	}
	return ada;	
}

void MOVE(player *P, peta *M, player *q, Stack *S){ 
	POINT loc = (*P).selected.lokasi;
	unit slc = (*P).selected; //unit yang sedang dipilih
	state X;
	PrevPos(X) = loc; 
	/***************************	TULIS PETA 	*****************************/
	printf("\n");
	printf("  ");
	for (int i=0; i<NKolEff(*M); i++){
		for (int j=0; j<4; j++){
			if (i<10 && j==1){
				printf("%d",i);
			} else if (i>=10 && j == 1){
				printf("%d",i);
			} else {
				printf(" ");
			}
		}				
	}
	printf("\n");
	for (int i=0; i<NBrsEff(*M); i++){
		printf("  ");
		for (int j=0; j<4*NKolEff(*M); j++){
			printf("*");
		}
		printf("*");
		for (int j=0; j<4; j++){
			if (j==2){
				printf("%d",i);
				if (i<10){
					printf(" ");
				}
			} else {
				printf("  ");
			}
			for (int k=0; k<NKolEff(*M); k++){
				POINT Current = MakePOINT(i,k);
				for (int l=0; l<4; l++){
					if (j!=0){
						if (l == 0){
							printf("*");
						} else if (l == 2){
							if (j==1){
								if (milik_petak(petak(*M,i,k)) == 1){
										print_red(jenis_petak(petak(*M,i,k)));	
									} else if (milik_petak(petak(*M,i,k)) == 2) {
										print_cyan(jenis_petak(petak(*M,i,k)));
									} else {
										printf("%c",jenis_petak(petak(*M,i,k)));
									}
							} else if (j==2){
								if (isequal_unit(unit_petak(petak(*M,i,k)),empty_unit(MakePOINT(i,k))) && (manhattan_dist(Current, loc) <= move_point(slc)) && 
									(isAdaMusuh(loc, MakePOINT(i,k), *M) == 0) && (Absis(loc) == i || Ordinat(loc) == k)){
									print_yellow('#');
								} 
								else if (isequal_unit(unit_petak(petak(*M,i,k)),empty_unit(MakePOINT(i,k)))){
									printf(" ");
								}
								else {
									if (isequal_unit(unit_petak(petak(*M,i,k)),selected(*P))){
										print_green(simbol(unit_petak(petak(*M,i,k))));
									} else if (pemilik(unit_petak(petak(*M,i,k))) == 1){
										print_red(simbol(unit_petak(petak(*M,i,k))));	
									} else if (pemilik(unit_petak(petak(*M,i,k))) == 2){
										print_cyan(simbol(unit_petak(petak(*M,i,k))));
									} else {
										printf("ERROR"); //Error
									}
								}
							} else {
								printf(" ");
							}
						} else {
							printf(" ");
						}
					} else {
						printf(" ");
					}
				}	
				if (k == NKolEff(*M) - 1 && j!=0){
					printf("*");
				}
			}
			printf("\n");
		}
	}
	printf("  ");
	for (int i=0; i<4*NKolEff(*M)+1; i++) printf("*");
	printf("\n");
/******************************************	AKHIR TULIS PETA ***************************/
	int x,y; 
	boolean moved = false;
	if (move_point(slc) <= 0){
		printf("Movement point = 0. Your selected unit can't move\n");
	} else {
		do{
			printf("Please enter cell's coordinate x y: ");
			scanf("%d %d",&x,&y);
			if (manhattan_dist(MakePOINT(x,y),loc) > move_point(slc) || !isequal_unit(unit_petak(petak(*M,x,y)),empty_unit(MakePOINT(x,y))) || 
				isAdaMusuh(loc, MakePOINT(x,y), *M) || !(Absis(loc) == x || Ordinat(loc) == y)) {
				printf("Sorry. You can't move there\n");
			} else {
				unit temp = selected(*P);
				swap_unit(&unit_petak(petak(*M,x,y)), &unit_petak(petak(*M,Absis(loc), Ordinat(loc))));
				if (jenis_petak(petak(*M,x,y)) == 'V'){
					MP(X) = move_point(unit_petak(petak(*M,x,y))); // Buat Undo
					move_point(unit_petak(petak(*M,x,y))) = 0;
					Take(X) = false;
					if (milik_petak(petak(*M,x,y)) == simbol_player(*q)){
						DelP_listpetak (&list_petak(*q), petak(*M,x,y));
						income(*q) -= INCOME_INC;
						InsVFirst_listpetak (&list_petak(*P), petak(*M,x,y));
						Take(X) = true;
					}
					printf("This village has been seized.\n");
					milik_petak(petak(*M,x,y)) = simbol_player(*P);
					income(*P) += INCOME_INC;			
				} else {
					Take(X) = false;
					MP(X) = move_point(unit_petak(petak(*M,x,y))); // Menyimpan Movement point sebelumnya
					move_point(unit_petak(petak(*M,x,y))) -= manhattan_dist(loc,MakePOINT(x,y));				
				}

				printf("Your selected unit has been moved to (%d,%d)\n",x,y);
				// Searching unit di list
				NextPos(X) = MakePOINT(x,y);
				selected(*P) = unit_petak(petak(*M,x,y));
				add_unit slc_in_list = Search_listunit(list_unit(*P),temp);
				Info_unit(slc_in_list) = selected(*P);
				WSelect(X) = slc_in_list;
				moved = true;
				Push(S, X); // Push ke stack of state setiap unit bergerak;
			}
	} while (moved == false);		
	}
}

void receive_command(int *code){
	char str_command[100];
	for (int i=0; i<100; i++)str_command[i] = '\0';
	do{
		printf("Your input : "); scanf("%s",str_command);
		Kata lucknut = BuildKata(str_command);
		*code = command_code(lucknut);
		if (*code == 0){
			printf("Command %s is not available\n",str_command);
			printf("\n");
		}
	} while (*code == 0);
}

void call_SAVE(peta *M, int TURN, long time_start, player p1, player p2) //incomplete
{
	FILE *fp;
	fp = fopen("save_game.txt", "w");
	if (fp == NULL){
		printf("Save game failed, please try again later\n");
	} else {
		fprintf(fp,"%d %d\n", NBrsEff(*M), NKolEff(*M)); // Besar Map
		fprintf(fp,"%d\n", TURN);					  // Turn siapa		
		//save data player p1
		add_unit unit_p1 = First_unit(list_unit(p1));
		int cnt = 0;
		while (unit_p1 != Nil){
			cnt++;
			unit_p1 = Next_unit(unit_p1);
		}
	}

	/* NOTE: Hal2 yg perlu disimpen
			Besar map !!DONE!!
			Turn siapa !!DONE!!
			State petak (ingat bahwa letak village perlu disave karena random)
			State Player 1 dan 2 (gold, income, upkeep, warna)
			State semua unit
		// Kalo ada yang perlu ditambahin ketik disini yaa!!
	*/

	long time_end = time(NULL);
	JAM tstart = DetikToJAM(time_start);
	JAM tend = DetikToJAM(time_end);
	long durasi = Durasi(tstart, tend);
	if (durasi < 120)
	{
		printf("Your game have been saved, you have played for %ld seconds this session\n", (durasi));
	} else
	{
		printf("Your game have been saved, you have played for %ld minutes this session\n", (durasi/60));
	}

}

void call_EXIT(peta *M, int TURN, long time_start, boolean game_over, player p1, player p2)
{
	char savegame;
	printf("Would you like to save the game? (y/n)\n");
	scanf("%c",&savegame);
	do {
		scanf("%c",&savegame);
		if (savegame != 'y' && savegame != 'n'){
			printf("Tidak valid");
		}
	} while (savegame != 'y' && savegame != 'n');

    if (savegame == ('y'))
    {
        call_SAVE(M, TURN, time_start, p1, p2);
    } else if (savegame == ('n'))
    {
    }
	printf("Exiting the game...\n");
	game_over = true;
	exit('\n');
}

void do_recruit(player *P, POINT loc_new, peta *M){
	printf("List of recruits\n");
	int cnt = 1;
	if (gold(*P) >= H_ARCHER){
		printf("%d. Archer | Health: %d | ATK: %d | ATK_type: %c | Price: %dG\n", cnt,MH_ARCHER,ATK_ARCHER,TS_ARCHER,H_ARCHER);
		cnt++;
	} 
	if (gold(*P) >= H_SWORDSMAN){
		printf("%d. Swordsman | Health: %d | ATK: %d | ATK_type: %c | Price: %dG\n", cnt,MH_SWORDSMAN,ATK_SWORDSMAN,TS_SWORDSMAN,H_SWORDSMAN);
		cnt++;
	} 
	if (gold(*P) >= H_WHITEMAGE) { // gold(P) >= H_WHITEMAGE
		printf("%d. Whitemage | Health: %d | ATK: %d | ATK_type: %c | Price: %dG\n", cnt,MH_WHITEMAGE,ATK_WHITEMAGE,TS_WHITEMAGE,H_WHITEMAGE);
		cnt++;
	}
	
	int no_rec;
	do {
		printf("Enter the ID of unit that you want to recruit\n");
		scanf("%d",&no_rec);
		if (no_rec < 1 || no_rec > 3){
			printf("Invalid input\n");
		}	
	} while (no_rec < 1 || no_rec > 3);					
		
	unit new_u;
	if (no_rec == 1){
		gold(*P) = gold(*P) - H_ARCHER;
		new_u = unit_petak(petak(*M,Absis(loc_new),Ordinat(loc_new)));
		assign_unit(&new_u,'A',simbol_player(*P));

		printf("You have recruited an archer\n");
	} else if (no_rec == 2){
		gold(*P) = gold(*P) - H_SWORDSMAN;
		new_u = unit_petak(petak(*M,Absis(loc_new),Ordinat(loc_new)));
		assign_unit(&new_u,'S',simbol_player(*P));
		printf("You have recruited a swordsman\n");
	} else {
		gold(*P) = gold(*P) - H_WHITEMAGE;
		new_u = unit_petak(petak(*M,Absis(loc_new),Ordinat(loc_new)));
		assign_unit(&new_u,'W',simbol_player(*P));

		printf("You have recruited a whitemage\n");
	}		
	move_point(new_u) = 0;
	InsVLast_listunit(&list_unit(*P),new_u);
	assign_petak(&(petak(*M,Absis(loc_new),Ordinat(loc_new))),'C',simbol_player(*P),new_u);
	upkeep(*P) += UP_KEEP_DEC;
}	

void recruit(player *P, peta *M, Stack *S){
	int id_p = simbol_player(*P);
	petak pt;
	if (id_p == 1){
		pt = petak(*M,NBrsEff(*M)-2,1);	
	} else {
		pt = petak(*M,1,NKolEff(*M)-2);	
	}

	if (simbol(unit_petak(pt)) == 'K' && pemilik(unit_petak(pt)) == id_p){
		petak l = petak(*M,Absis(left(lokasi_petak(pt))),Ordinat(left(lokasi_petak(pt))));
		petak r = petak(*M,Absis(right(lokasi_petak(pt))),Ordinat(right(lokasi_petak(pt))));
		petak u = petak(*M,Absis(up(lokasi_petak(pt))),Ordinat(up(lokasi_petak(pt))));
		petak d = petak(*M,Absis(down(lokasi_petak(pt))),Ordinat(down(lokasi_petak(pt))));

		boolean b1 = simbol(unit_petak(l)) == ' ';
		boolean b2 = simbol(unit_petak(r)) == ' ';
		boolean b3 = simbol(unit_petak(u)) == ' ';
		boolean b4 = simbol(unit_petak(d)) == ' ';

		if (b1 || b2 || b3 || b4){
			int x = Absis(lokasi_petak(pt));
			int y = Ordinat(lokasi_petak(pt));
			int x1, y1;
			
			do{
				printf(">> Enter coordinate x y of your castle\n");
				printf("<< ");
				scanf("%d %d",&x1,&y1);
				if (abs(x-x1) + abs(y-y1) != 1){
					printf(">> This cell is not your castle\n");
				} else {
					POINT slc = MakePOINT(x1,y1);
					if (isequal_point(lokasi_petak(l),slc) && b1){
						do_recruit(P,slc,M);
					} else if (isequal_point(lokasi_petak(r),slc) && b2){
						do_recruit(P,slc,M);
					} else if (isequal_point(lokasi_petak(u),slc) && b3){
						do_recruit(P,slc,M);
					} else if (isequal_point(lokasi_petak(d),slc) && b4){
						do_recruit(P,slc,M);
					} else {
						printf(">> Your selected castle is occupied\n");						
					}	
					CreateEmptyStack(S);
				}				
			} while (abs(x-x1) + abs(y-y1) != 1);

		} else {
			printf(">> Recruit failed. Your castles are full\n");
		}

	} else {
		printf(">> Recruit failed. Your king is not in tower\n");
	}
}

void infopetak(peta M)
{
    int X, Y;
    petak p;
    unit u;

    printf("Enter the coordinate of the cell: ");scanf(" %d %d",&X,&Y);
    while (!(0<=X && X<=NBrsEff(M)-1 && 0<=Y && Y<=NKolEff(M)-1)){
    	printf("Your coordinate is out of bounds\n");
	    printf("Enter the coordinate of the cell: ");scanf(" %d %d",&X,&Y);
    }
    p=petak(M,X,Y);
    printf("== Cell Info ==\n");
    if(jenis_petak(p)=='V')
    {
        printf("Village\n");
    }
    else if(jenis_petak(p)=='C')
    {
        printf("Castle\n");
    }
    else if(jenis_petak(p)=='T')
    {
        printf("Tower\n");
    }
    else
    {
        printf("Empty Land\n");
    }
    if (jenis_petak(p)!=' '){
    printf("Owned by Player %d\n", milik_petak(p));
    printf("\n");}

    printf("== Unit Info ==\n");
    u=unit_petak(p);


    if(simbol(u)=='K')
    {
        printf("King\n");
    }
    else if(simbol(u)=='A')
    {
        printf("Archer\n");
    }
    else if(simbol(u)=='S')
    {
        printf("Swordsman\n");
    }
    else if(simbol(u)==' ')
    {
        printf("No Unit\n");
    }
    else
    {
        printf("White Mage\n");
    }

    if(simbol(u)!=' '){
    	printf("Owned by Player %d\n", pemilik(u));
    	printf("Health %d/%d | ATK %d | DEF %c\n",health(u),max_health(u),attack(u),tipe_serang(u));
    }
}

void do_command(int code, player *p, player *q, peta *M, int turn, long time_start, boolean *game_over,Queue *Q, Stack *S){
	switch (code) {
		case 1 :  MOVE(p,M,q,S); break;
		case 2 :  UNDO(p,M,q,S); break;
		case 3 :  change_unit(p); CreateEmptyStack(S); break;
		case 4 :  recruit(p,M,S); break;
		case 5 :  COMMAND_ATTACK(p,q,M, game_over); CreateEmptyStack(S); break;
		case 6 :  display_peta(*M,*p); break;
		case 7 :  infopetak(*M); break;
		case 8 :  NextTurnQueue(Q,p,q,M,S); break;
		case 9 :  call_SAVE(M, turn, time_start,*p,*q); break;
		case 10 : call_EXIT(M, turn, time_start, *game_over,*p,*q); break;
		case 11 : display_command(); break;
		case 12 : next_unit(p); break;
		default : 
			printf("ERROR\n"); 
			printf("\n"); 
			break;
	}
}

void UNDO(player *P, peta *M, player *q, Stack *S){
	state X;

	if (IsEmptyStack(*S)){
		printf("You cannot UNDO anymore, you haven't done anything.\n");
	}
	else {
		Pop(S,&X);
		swap_unit(&unit_petak(petak(*M,Absis(PrevPos(X)),Ordinat(PrevPos(X)))), &unit_petak(petak(*M,Absis(NextPos(X)), Ordinat(NextPos(X)))));
		if (jenis_petak(petak(*M, Absis(NextPos(X)),Ordinat(NextPos(X)))) == 'V'){
			DelP_listpetak (&list_petak(*P), petak(*M,Absis(NextPos(X)),Ordinat(NextPos(X))));
			if (Take(X) == true){
				milik_petak(petak(*M,Absis(NextPos(X)),Ordinat(NextPos(X)))) = simbol_player(*q);
				income(*q) += INCOME_INC;
				InsVFirst_listpetak (&list_petak(*q), petak(*M,Absis(NextPos(X)),Ordinat(NextPos(X))));
			} else {
				milik_petak(petak(*M,Absis(NextPos(X)),Ordinat(NextPos(X)))) = 0;
			}
			income(*P) -= INCOME_INC;
		}
		move_point(unit_petak(petak(*M,Absis(PrevPos(X)),Ordinat(PrevPos(X))))) = MP(X);				
		Info_unit(WSelect(X)) = unit_petak(petak(*M,Absis(PrevPos(X)),Ordinat(PrevPos(X))));
		selected(*P) = Info_unit(WSelect(X));
		printf("Your last move has been canceled.\n");
	}
}

void white_heal(player *P, peta *M){
	add_unit A = First_unit(list_unit(*P));

	while (A != Nil){
		if (simbol(Info_unit(A)) == 'W')
			healing(Info_unit(A), P, M);
		A = Next_unit(A);
	}
}

void healing(unit W, player *P, peta *M){
	unit l = unit_petak(petak(*M,Absis(left(lokasi_unit(W))),Ordinat(left(lokasi_unit(W)))));
    unit r = unit_petak(petak(*M,Absis(right(lokasi_unit(W))),Ordinat(right(lokasi_unit(W)))));
    unit u = unit_petak(petak(*M,Absis(up(lokasi_unit(W))),Ordinat(up(lokasi_unit(W)))));
    unit d = unit_petak(petak(*M,Absis(down(lokasi_unit(W))),Ordinat(down(lokasi_unit(W)))));

    boolean bl,br,bd,bu;

    bl = false; br = false; bd = false; bu = false;

    if (pemilik(W) == pemilik(l)) bl = true;
    if (pemilik(W) == pemilik(r)) br = true;
    if (pemilik(W) == pemilik(d)) bd = true;
    if (pemilik(W) == pemilik(u)) bu = true;

    if (!bl && !br && !bd && !bu)
    	printf("No unit is adjacent to your White Mage (%d,%d), so it's not healing anyone.\n", Absis(lokasi_unit(W)), Ordinat(lokasi_unit(W)));

    add_unit u_in_list;

    if (bl){
    	u_in_list = Search_listunit(list_unit(*P), l);
    	health(l) += 10;
    	if (health(l) > max_health(l))
    		health(l) = max_health(l);
    	unit_petak(petak(*M,Absis(left(lokasi_unit(W))),Ordinat(left(lokasi_unit(W))))) = l;
    	Info_unit(u_in_list) = l;
    	printf("Your ");
        printUnitName(l);
        printf("(%d,%d) health is restored by 10.\n", Absis(lokasi_unit(l)), Ordinat(lokasi_unit(l)));
    }

    if (br){
    	u_in_list = Search_listunit(list_unit(*P), r);
    	health(r) += 10;
    	if (health(r) > max_health(r))
    		health(r) = max_health(r);
    	unit_petak(petak(*M,Absis(right(lokasi_unit(W))),Ordinat(right(lokasi_unit(W))))) = r;
    	Info_unit(u_in_list) = r;
    	printf("Your ");
        printUnitName(r);
        printf("(%d,%d) health is restored by 10.\n", Absis(lokasi_unit(r)), Ordinat(lokasi_unit(r)));
    }

    if (bd){
    	u_in_list = Search_listunit(list_unit(*P), d);
    	health(d) += 10;
    	if (health(d) > max_health(d))
    		health(d) = max_health(d);
    	unit_petak(petak(*M,Absis(down(lokasi_unit(W))),Ordinat(down(lokasi_unit(W))))) = d;
    	Info_unit(u_in_list) = d;
    	printf("Your ");
        printUnitName(d);
        printf("(%d,%d) health is restored by 10.\n", Absis(lokasi_unit(d)), Ordinat(lokasi_unit(d)));
    }

    if (bu){
    	u_in_list = Search_listunit(list_unit(*P), u);
    	health(u) += 8;
    	if (health(u) > max_health(u))
    		health(u) = max_health(u);
    	unit_petak(petak(*M,Absis(up(lokasi_unit(W))),Ordinat(up(lokasi_unit(W))))) = u;
    	Info_unit(u_in_list) = u;
    	printf("Your ");
        printUnitName(u);
        printf("(%d,%d) health is restored by 10.\n", Absis(lokasi_unit(u)), Ordinat(lokasi_unit(u)));
    }
}

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
