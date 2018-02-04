#include "stackt.h"
#include <stdio.h>

int main(){
	Stack S;
	CreateEmptyStack(&S);

	printf("%Ini kudunya bener : %d\n",IsEmptyStack(S));
	printf("%Ini kudunya salah : %d\n",IsFullStack(S));

	state A;

	Push(&S, A);
	printf("%d\n", MP(InfoTop(S)));
	Pop(&S, &A);

	return 0;
}
