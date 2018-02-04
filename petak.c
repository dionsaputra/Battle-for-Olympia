#include "petak.h"
#include "unit.h"
#include "point.h"

#define income_p 12;

boolean isequal_petak(petak p1, petak p2){
	boolean b1 = isequal_unit(unit_petak(p1), unit_petak(p2));
	boolean b2 = jenis_petak(p1) == jenis_petak(p2);
	boolean b3 = milik_petak(p1) == milik_petak(p2);
	boolean b4 = income_petak(p1) == income_petak(p2);
	return (b1 && b2 && b3 && b4);
}

petak empty_petak(POINT lokasi_p){
	petak p;
	lokasi_petak(p) = lokasi_p;
	jenis_petak(p) = ' ';
	milik_petak(p) = 0;
	unit_petak(p) = empty_unit(lokasi_p);
	income_petak(p) = 0;
	return p;
}

void assign_petak(petak *p, char jenis_p, int milik_p, unit unit_p){
	jenis_petak(*p) = jenis_p;
	milik_petak(*p) = milik_p;
	unit_petak(*p) = unit_p;
	
	if (jenis_p == 'V'){
		income_petak(*p) = income_p;
	} else {
		income_petak(*p) = 0;
	}
}


