#include "peta.h"
#include <time.h>
#include <math.h>
#include "pcolor.h"

void empty_peta(peta *M, int NB, int NK){
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
	for (int i=0; i<NB; i++){
		for (int j=0; j<NK; j++){
			petak(*M,i,j) = empty_petak(MakePOINT(i,j));
		}
	}
}

void bangun_kerajaan(peta *M)
{	
	//menentukan letak tower p1 dan p2
	POINT lokasi_p1 = MakePOINT(NBrsEff(*M) - 2, 1);
	POINT lokasi_p2 = MakePOINT(1, NKolEff(*M) - 2);
	//membuat unit kosong untuk diisikan ke tower
	unit dummy_unit_p1 = empty_unit(lokasi_p1);
	unit dummy_unit_p2 = empty_unit(lokasi_p2);
	//absis dan ordinat tower p1 dan p2
	int xt1 = Absis(lokasi_p1), yt1 = Ordinat(lokasi_p1);
	int xt2 = Absis(lokasi_p2), yt2 = Ordinat(lokasi_p2);
	//mengisikan T dan dummy unit di petak tower
	assign_petak(&(petak(*M,xt1,yt1)),'T',1,dummy_unit_p1);
	assign_petak(&(petak(*M,xt2,yt2)),'T',2,dummy_unit_p2);	
	
	//membangun castle kiri tower p1
	int xcl1 = Absis(left(lokasi_p1)), ycl1 = Ordinat(left(lokasi_p1));
	unit dummy_xcl1 = empty_unit(left(lokasi_p1));
	assign_petak(&(petak(*M,xcl1,ycl1)),'C',1,dummy_xcl1);
	//membangun castle kanan tower p1
	int xcr1 = Absis(right(lokasi_p1)), ycr1 = Ordinat(right(lokasi_p1));
	unit dummy_xcr1 = empty_unit(right(lokasi_p1));
	assign_petak(&(petak(*M,xcr1,ycr1)),'C',1,dummy_xcr1);
	//membangun castle atas tower p1
	int xcu1 = Absis(up(lokasi_p1)), ycu1 = Ordinat(up(lokasi_p1));
	unit dummy_xcu1 = empty_unit(up(lokasi_p1));
	assign_petak(&(petak(*M,xcu1,ycu1)),'C',1,dummy_xcu1);
	//membangun castle bawah tower p1
	int xcd1 = Absis(down(lokasi_p1)), ycd1 = Ordinat(down(lokasi_p1));
	unit dummy_xcd1 = empty_unit(down(lokasi_p1));
	assign_petak(&(petak(*M,xcd1,ycd1)),'C',1,dummy_xcd1);

	//membangun castle kiri tower p2
	int xcl2 = Absis(left(lokasi_p2)), ycl2 = Ordinat(left(lokasi_p2));
	unit dummy_xcl2 = empty_unit(left(lokasi_p2));
	assign_petak(&(petak(*M,xcl2,ycl2)),'C',2,dummy_xcl2);
	//membangun castle kanan tower p2
	int xcr2 = Absis(right(lokasi_p2)), ycr2 = Ordinat(right(lokasi_p2));
	unit dummy_xcr2 = empty_unit(right(lokasi_p2));
	assign_petak(&(petak(*M,xcr2,ycr2)),'C',2,dummy_xcr2);
	//membangun castle atas tower p2
	int xcu2 = Absis(up(lokasi_p2)), ycu2 = Ordinat(up(lokasi_p2));
	unit dummy_xcu2 = empty_unit(up(lokasi_p2));
	assign_petak(&(petak(*M,xcu2,ycu2)),'C',2,dummy_xcu2);
	//membangun castle bawah tower p2
	int xcd2 = Absis(down(lokasi_p2)), ycd2 = Ordinat(down(lokasi_p2));
	unit dummy_xcd2 = empty_unit(down(lokasi_p2));
	assign_petak(&(petak(*M,xcd2,ycd2)),'C',2,dummy_xcd2);
}

void taruh_king(peta *M, player *p1, player *p2){
	POINT lokasi_p1 = MakePOINT(NBrsEff(*M) - 2, 1);
	POINT lokasi_p2 = MakePOINT(1, NKolEff(*M) - 2);
	
	int xk1 = Absis(lokasi_p1), yk1 = Ordinat(lokasi_p1);
	int xk2 = Absis(lokasi_p2), yk2 = Ordinat(lokasi_p2);
	//claim posisi untuk king
	unit king_p1 = unit_petak(petak(*M,xk1,yk1));
	unit king_p2 = unit_petak(petak(*M,xk2,yk2));
	//memberi unit di petak dengan properti king
	assign_unit(&king_p1,'K',1);
	assign_unit(&king_p2,'K',2);
	//menjadikan king sebagai selected unit
	selected(*p1) = king_p1;
	selected(*p2) = king_p2;
	//menambahkan ke list player
	InsVFirst_listunit(&list_unit(*p1),king_p1);
	InsVFirst_listunit(&list_unit(*p2),king_p2);
	//menambahkan ke peta
	assign_petak(&(petak(*M,xk1,yk1)),'T',1,king_p1);
	assign_petak(&(petak(*M,xk2,yk2)),'T',2,king_p2);
}

void init_peta(peta *M, int NBrsEff, int NKolEff, player *p1, player *p2){
	empty_peta(M, NBrsEff, NKolEff);
	init_player(p1,'R',1);
	init_player(p2,'C',2);
	bangun_kerajaan(M);
	taruh_king(M,p1,p2);
	PasangDesa(NBrsEff*NKolEff/20, M);
}

void display_peta(peta M, player p){
	//tulis angka horizontal
	printf("\n");
	printf("  ");
	for (int i=0; i<NKolEff(M); i++){
		for (int j=0; j<4; j++){
			if (i<10){
				if (j==2){
					printf("%d",i);						
				} else {
					printf(" ");
				}
			} else {
				if (j==2){
					printf("%d",i);
				} else if (j<3){
					printf(" ");
				}
			}
		}				
	}
	printf("\n");
	for (int i=0; i<NBrsEff(M); i++){
		printf("  ");
		for (int j=0; j<4*NKolEff(M); j++){
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
			for (int k=0; k<NKolEff(M); k++){
				for (int l=0; l<4; l++){
					if (j!=0){
						if (l == 0){
							printf("*");
						} else if (l == 2){
							if (j==1){
								if (isequal_petak(petak(M,i,k),empty_petak(MakePOINT(i,k)))){
									printf(" ");
								} else {
									if (milik_petak(petak(M,i,k)) == 1){
										print_red(jenis_petak(petak(M,i,k)));	
									} else if (milik_petak(petak(M,i,k)) == 2) {
										print_cyan(jenis_petak(petak(M,i,k)));
									} else {
										printf("%c",jenis_petak(petak(M,i,k)));
									}
								}
							} else if (j==2){
								if (isequal_unit(unit_petak(petak(M,i,k)),empty_unit(MakePOINT(i,k)))){
									printf(" ");
								} else {
									if (isequal_unit(unit_petak(petak(M,i,k)),selected(p))){
										print_green(simbol(unit_petak(petak(M,i,k))));
									} else if (pemilik(unit_petak(petak(M,i,k))) == 1){
										print_red(simbol(unit_petak(petak(M,i,k))));	
									} else if (pemilik(unit_petak(petak(M,i,k))) == 2){
										print_cyan(simbol(unit_petak(petak(M,i,k))));
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
				if (k == NKolEff(M) - 1 && j!=0){
					printf("*");
				}
			}
			printf("\n");
		}
	}
	printf("  ");
	for (int i=0; i<4*NKolEff(M)+1; i++) printf("*");
	printf("\n");
}

int RNGbatas(int min, int maks){
//menghasilkan Random Number dari min sampai maks dengan sebelumnya ada srand
    int r;

    r=rand()%(maks-min+1)+min;

    return r;
}

void PasangDesa(int jumlah_village, peta *M){
//MASIH FULL RANDOM, KLO MAU PK BATAS GANTI RNG DAN X Y NYA :) //done, mantap '-'b
//Sudah diedit, random buat setengah peta, dan random buat setengahnya lagi
    int i = 0;
    int x = NBrsEff(*M)-1;
    int y = NKolEff(*M)-1;
    int A,B;

    srand(time(NULL));//Untuk seed rand()

    while (i<=jumlah_village)
    {   
        if (i <= jumlah_village/2){
            //Random untuk bagian kiri peta
            A=RNGbatas(0,x/2);
            B=RNGbatas(0,y/2);
        }
        else {
            //Random untuk bagian kanan peta
            A=RNGbatas(x/2 + 1, x);
            B=RNGbatas(y/2 + 1, y);
        }
        //random location, jika petak kosong, tanam village
        POINT Random_location = MakePOINT(A,B);
        if (isequal_petak(petak(*M,Absis(Random_location),Ordinat(Random_location)),empty_petak(Random_location)))
        {
            assign_petak(&(petak(*M,Absis(Random_location),Ordinat(Random_location))), 'V', 0, empty_unit(Random_location));
            i++;
        }
    }
}


int manhattan_dist(POINT x1, POINT x2){
	return (abs(Absis(x1) - Absis(x2)) + abs(Ordinat(x1) - Ordinat(x2)));
}