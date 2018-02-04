#include "unit.h"
#include "point.h"
#include <stdio.h>

int main(){
	unit u1 = empty_unit(MakePOINT(1,1));
	assign_unit(&u1,'W',1);
	unit u2 = empty_unit(MakePOINT(1,1));
	assign_unit(&u2,'K',1);
	printf("%d\n",isequal_unit(u1,u2));
	swap_unit(&u1, &u2);
	printf("%c\n", simbol(u1));
	printf("%c\n", simbol(u2));

	copy_unit(u1, &u2);
	printf("%c\n", simbol(u2));

	return 0;
}