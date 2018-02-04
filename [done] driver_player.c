include "player.h"
#include <stdio.h>

int main(){
	player P1;
	unit nganu;

	// Driver List Unit
	boolean b = IsEmpty_list(list_unit(P1));
	CreateEmpty_listunit(&list_unit(P1));
	printf("%d\n", address_king(list_unit(P1)));
	Dealokasi_listunit(&P1);
	InsVFirst_listunit(&list_unit(P1), nganu);
	InsVLast_listunit(&list_unit(P1), nganu);
	DelVFirst_listunit(&list_unit(P1), nganu);
	DelVLast_listunit(&list_unit(P1), nganu);


	init_player(&P1, 'R', 1);
	change_unit(&P1);
	next_unit(&P1);
	display_player_info(P1);



	return 0;
}