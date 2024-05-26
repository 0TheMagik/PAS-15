//file berisi menu dan data tanggal
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

enum color {BLUE, GREEN, RED, YELLOW};

void backgroundcolor(int color){
	system("cls");
	
	switch (color){
		case (BLUE):
			system("color 90");
			break;
		case (GREEN):
			system("color A0");
			break;
		case (RED):
			system("color 4f");
			break;
		case (YELLOW):
			system("color E0");
			break;		
	}
}

//fungsi waktu dari sistem;
void date(struct date *dt){
    time_t now = time NULL;
    struct tm *local = localtime(&now);

    dt->da_day = local->tm_mday;
    dt->da_mon = local->tm_mon + 1;
    dt->da_year = local->tm_year + 1900;
}

void menu(struct date *dt){
	backgroundcolor(GREEN);
        date(dt);
        printf("|=============================================|\n");
        printf("|                  Tangggal                   |\n");
        printf("|                 %-2d/%-2d/%-4d                  |\n", dt->da_day, dt->da_mon, dt->da_year);
		printf("===============================================\n");
		printf("|                                             |\n");
        printf("|                    MENU                     |\n");
        printf("|                                             |\n");
        printf("|=============================================|\n");
        printf("| 1.| Tambah Unit                             |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 2.| Tampilkan Semua Unit                    |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 3.| Edit Unit                               |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 4.| Tambah Pembeli/Penyewa ke Antrean       |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 5.| Pindahkan Pembeli/Penyewa ke Unit       |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 6.| Search Unit                             |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 7.| Hapus Data                              |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 8.| Sort Data                               |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 9.| Summary Perumahan                       |\n");
        printf("|---|-----------------------------------------|\n");
        printf("| 0.| Log out                                 |\n");
        printf("|=============================================|\n");
        printf("| Masukkan pilihan : ");
}

void search_menu(){
backgroundcolor(GREEN);
	printf("|==============================================|\n");
    printf("|              Pilih Metode Search             |\n");
    printf("|==============================================|\n");
    printf("| 1.| Search Berdasarkan Nomor Unit            |\n");
    printf("|---|------------------------------------------|\n");
    printf("| 2.| Search Berdasarkan Pemilik               |\n");
    printf("|---|------------------------------------------|\n");
    printf("| 3.| Search Berdasarkan Penghuni              |\n");
    printf("|---|------------------------------------------|\n");
    printf("| 0.| Kembali                                  |\n");
    printf("|==============================================|\n");
    printf("| Masukkan Pilihan :  ");
}

void sort_menu(){
    backgroundcolor(GREEN);
	printf("|==============================================|\n");
    printf("|                   Sorting                    |\n");
    printf("|==============================================|\n");
    printf("| 1.| Sorting berdasarkan Nama Pemilik         |\n");
    printf("|---|------------------------------------------|\n");
    printf("| 2.| Sorting Berdasarkan No Unit              |\n");
    printf("|---|------------------------------------------|\n");
    printf("| 0.| Kembali                                  |\n");
    printf("|==============================================|\n");
    printf("| Masukkan Pilihan : ");
}

void menu_edit(){
	
	printf("|========================================================================|\n");
	printf("|                             Edit Data                                  |\n");
	printf("|========================================================================|\n");
    printf("| 1.| Edit Nama Pemilik               | 8. | Edit Jumlah Lantai          |\n");
    printf("|---|---------------------------------|----|-----------------------------|\n");
    printf("| 2.| Edit Tipe Sertifikat            | 9. | Edit Jumlah Kamar           |\n");
    printf("|---|---------------------------------|----|-----------------------------|\n");
    printf("| 3.| Edit Status Unit                | 10.| Edit Jumlah WC              |\n");
    printf("|---|---------------------------------|----|-----------------------------|\n");
    printf("| 4.| Edit Nama Penghuni              | 11.| Edit Luas Garasi            |\n");
    printf("|---|---------------------------------|----|-----------------------------|\n");
    printf("| 5.| Edit Tipe Sewa                  | 12.| Edit Luas Rumah             |\n");
    printf("|---|---------------------------------|----|-----------------------------|\n");
    printf("| 6.| Edit Harga Sewa                 | 13.| Edit Tanggal Sewa           |\n");
    printf("|---|---------------------------------|----|-----------------------------|\n");
    printf("| 7.| Edit Harga Jual/Beli                                               |\n");
    printf("|========================================================================|\n");
    printf("|\tMasukkan Pilihan : ");
}

//getchar di deklarasikan pada fungsi
void get(){
    getchar();
}

//system("cls") di deklarasikan pada fungsi
void cls(){
    system("cls");
}