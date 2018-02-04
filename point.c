#include <stdio.h>
#include "point.h"
#include <math.h>
#include "boolean.h"

POINT MakePOINT (int X, int Y){
	POINT P;
	Absis(P) = X;
	Ordinat(P) = Y;
	return P;
}

void BacaPOINT (POINT * P){
	int x,y;
	scanf("%d %d", &x, &y);
	*P = MakePOINT(x,y);
} 

boolean isequal_point(POINT P1, POINT P2){
	return (Absis(P1) == Absis(P2) && Ordinat(P1) == Ordinat(P2));
}

void tulis_point (POINT X){
	printf("(%d,%d)",Absis(X),Ordinat(X));
}

POINT left(POINT P){
	int xp = Absis(P), yp = Ordinat(P);
	return MakePOINT(xp,yp-1);
}

POINT right(POINT P){
	int xp = Absis(P), yp = Ordinat(P);
	return MakePOINT(xp,yp+1);
}

POINT up(POINT P){
	int xp = Absis(P), yp = Ordinat(P);
	return MakePOINT(xp-1,yp);
}

POINT down(POINT P){
	int xp = Absis(P), yp = Ordinat(P);
	return MakePOINT(xp+1,yp);
}

