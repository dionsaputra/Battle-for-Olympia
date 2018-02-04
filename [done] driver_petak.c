#include "petak.h"
#include <stdio.h>
#include "point.h"
#include "unit.h"

int main(){

	unit u1 = empty_unit(MakePOINT(1,1));
	assign_unit(&u1,'W',2);


	// Ngetes empty petak
	petak p1 = empty_petak(MakePOINT(1,1));
	
	printf("%d %d\n", Absis(lokasi_petak(p1)), Ordinat(lokasi_petak(p1)));
	printf("%c\n", jenis_petak(p1));
	printf("%d\n", milik_petak(p1));
	printf("%c\n", simbol(unit_petak(p1)));
	printf("%d\n", income_petak(p1));


	// Ngetes assign
	printf("\nASSIGN\n");
	assign_petak(&p1, 'V', 1, u1);

	printf("%d %d\n", Absis(lokasi_petak(p1)), Ordinat(lokasi_petak(p1)));
	printf("%c\n", jenis_petak(p1));
	printf("%d\n", milik_petak(p1));
	printf("%c\n", simbol(unit_petak(p1)));
	printf("%d\n", income_petak(p1));
	printf("CHECK\n");
	printf("%c\n",simbol(unit_petak(p1)));

	// Ngetes is equal petak
	petak p2 = empty_petak(MakePOINT(1,2));
	petak p3;
	assign_petak(&p3, 'V', 1, u1);

	printf("INI HARUSNYA SALAH : %d\n", isequal_petak(p1,p2));
	printf("INI HARUSNA BENER : %d\n", isequal_petak(p1,p3));

	return 0;
}	
