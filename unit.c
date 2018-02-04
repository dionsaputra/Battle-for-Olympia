#include "unit.h"
#include "boolean.h"
#include "point.h"

unit empty_unit(POINT lokasi_u){
	unit u;
	
	max_health(u) = 0;
	health(u) = 0;
	attack(u) = 0;
	max_move_point(u) = 0;
	tipe_serang(u) = ' ';
	harga(u) = 0;	
	move_point(u) = 0;
	kesempatan_serang(u) = false;
	lokasi_unit(u) = lokasi_u;
	simbol(u) = ' ';
	pemilik(u) = 0;

	return u;
}

void assign_unit(unit *u, char tipe_unit, int pemilik_unit){
	kesempatan_serang(*u) = true;
	simbol(*u) = tipe_unit;
	pemilik(*u) = pemilik_unit;

	if (tipe_unit == 'K'){
		max_health(*u) = MH_KING;
		health(*u) = MH_KING;
		attack(*u) = ATK_KING;
		max_move_point(*u) = MM_KING;
		tipe_serang(*u) = TS_KING;
		harga(*u) = H_KING;	
	} else if (tipe_unit == 'A'){
		max_health(*u) = MH_ARCHER;
		health(*u) = MH_ARCHER;
		attack(*u) = ATK_ARCHER;
		max_move_point(*u) = MM_ARCHER;
		tipe_serang(*u) = TS_ARCHER;
		harga(*u) = H_ARCHER;
	} else if (tipe_unit == 'S'){
		max_health(*u) = MH_SWORDSMAN;
		health(*u) = MH_SWORDSMAN;
		attack(*u) = ATK_SWORDSMAN;
		max_move_point(*u) = MM_SWORDSMAN;
		tipe_serang(*u) = TS_SWORDSMAN;
		harga(*u) = H_SWORDSMAN;
	} else {
		max_health(*u) = MH_WHITEMAGE;
		health(*u) = MH_WHITEMAGE;
		attack(*u) = ATK_WHITEMAGE;
		max_move_point(*u) = MM_WHITEMAGE;
		tipe_serang(*u) = TS_WHITEMAGE;
		harga(*u) = H_WHITEMAGE;
	}
	move_point(*u) = max_move_point(*u);
}

boolean isequal_unit(unit u1, unit u2){
	boolean b1 = health(u1) == health(u2);
	boolean b2 = move_point(u1) == move_point(u2);
	boolean b3 = kesempatan_serang(u1) == kesempatan_serang(u2);
	boolean b4 = isequal_point(lokasi_unit(u1),lokasi_unit(u2));
	boolean b5 = simbol(u1) == simbol(u2);
	return (b1 && b2 && b3 && b4 && b5);
}

void swap_unit(unit *u1, unit *u2){
	unit temp = *u1;
	*u1 = *u2;
	*u2 = temp;

	/* SAD */
	lokasi_unit(temp) = lokasi_unit(*u2);
	lokasi_unit(*u2) = lokasi_unit(*u1);
	lokasi_unit(*u1) = lokasi_unit(temp);
}

void copy_unit(unit u_src, unit *u_dest){
	max_health(*u_dest) = max_health(u_src);
	health(*u_dest) = health(u_src);
	attack(*u_dest) = attack(u_src);
	max_move_point(*u_dest) = max_move_point(u_src);
	move_point(*u_dest) = move_point(u_src);
	tipe_serang(*u_dest) = tipe_serang(u_src);
	kesempatan_serang(*u_dest) = kesempatan_serang(u_src);
	lokasi_unit(*u_dest) = lokasi_unit(u_src);
	harga(*u_dest) = harga(u_src);
	simbol(*u_dest) = simbol(u_src);
	pemilik(*u_dest) = pemilik(u_src);
}