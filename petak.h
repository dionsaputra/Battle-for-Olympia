#ifndef PETAK_H
#define PETAK_H

#include "point.h"
#include "unit.h"

typedef struct{
	char jenis;
	int milik;
	unit u;
	int income; //Ada untuk villages
} petak;

#define lokasi_petak(p) (p).u.lokasi
#define jenis_petak(p) (p).jenis
#define milik_petak(p) (p).milik
#define unit_petak(p) (p).u
#define income_petak(p) (p).income


boolean isequal_petak(petak p1, petak p2); 
//Mengecek kesamaan petak

petak empty_petak(POINT lokasi_p);
//Mengembalikan petak yang belum berisi bangunan, unit, dan pemilik

void assign_petak(petak *p, char jenis_p, int milik_p, unit unit_p);
//Mengisi petak *p yang sudah memiliki lokasi dengan jenis, milik, dan unitnya

#endif
