#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boolean.h"
#include "pcolor.h"
#include "peta.h"
#include "player.h"
#include "kata.h"
#include "jam.h"
#include "game.h"
#include "stackt.h"
#include "mesinkata.h"

int main(){
	
	peta main_peta;
	player p1,p2;
	Queue Q;
	Stack S; //dimanfaatkan untuk command undo

	boolean new_game;
	time_t time_start = time(NULL);
	start_game(&new_game);
	int turn;

	// Aksi ketika new game
	if (new_game){
		do_new_game(&main_peta,&p1,&p2);
		CreateTurnQueue12(&Q); //Pemain 1 mulai pertama
	} else {
		int x, y, t;
		FILE *fp;
		fp = fopen("save_game.txt", "r");
		fscanf(fp,"%d %d", &x, &y);
		fscanf(fp,"%d", &t);
		init_peta(&main_peta, x, y, &p1, &p2);
		turn = t;
	}

	display_command();
	int code;
	boolean game_over = false;
	do{
		if (InfoHead(Q) == 1){
			display_player_info(p1);
			receive_command(&code);
			do_command(code,&p1,&p2,&main_peta, turn, time_start,&game_over,&Q,&S);
		} else {
			display_player_info(p2);
			receive_command(&code);
			do_command(code,&p2,&p1,&main_peta, turn, time_start,&game_over,&Q,&S);
		}
	} while (!game_over);
}
	