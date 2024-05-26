//Topik: Proyek PAS
//Group 15
//Izzan Nawa Syarif (2306266956)
//Muhammad Rafli (2306250730)
//Versi 2.0
//22/05/2024

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

struct date{
    int da_day;
    int da_mon;
    int da_year;
};

struct data{
    int No_Unit;
    char Pemilik[25];
    char Penghuni[25];
    char Status[15];
    long int Harga_Jual;
    long int Harga_Sewa;
    char tipe_Sewa[9];
    int tanggal_beli;
    int bulan_beli;
    int tahun_beli;
    int tgl_start_sewa;
    int bln_start_sewa;
    int thn_start_sewa;
    int tgl_end_sewa;
    int bln_end_sewa;
    int thn_end_sewa;
};

struct rumah{
    float lebar_rumah;
    float panjang_rumah;
    int jumlah_kamar;
    int jumlah_WC;
    float panjang_garasi;
    float lebar_garasi;
    int lantai;
    char sertifikat[5];
};

struct list{
    struct rumah detail;
    struct data unit;
    struct list *link;
};

struct queue{
    char nama[25];
    struct queue *link;
};

struct akun{
    char akun[25];
    char password[25];
    struct akun *link;
};

//header file
//system cls & getchar di menu.h
#include "menu.h"
#include "edit.h"
#include "hitungan.h"
#include "print_data.h"
#include "search.h"
#include "input_data.h"
#include "case_main.h"
#include "file.h"
#include "akun.h"


int main(){
    struct date dt;
    struct list *head = NULL;
    struct queue *start = NULL;
    struct queue *end = NULL;
    struct data temporary;
    struct rumah spek;
    struct akun *database = NULL;

    //read file saat startup, jika tidak ada akan lanjut keprogram
    read_akun_file(&database);
    read_list_file(&head, temporary, spek);
    read_queue_file(&start, &end);

    int login = 2;
    int limit = 0;
    int pilihan;
    while(1){
        while(login != 1){
            cls();
            akun();
            int pilihan_akun;
            scanf("%d", &pilihan_akun);
            switch(pilihan_akun){
                case 1:
                    login = case_akun_1(&database);//login ke program
                    break;
                case 2:
                    case_akun_2(&database);//membuat akun baru
                    print_akun_file(&database);//menulis akun ke file
                    break;
                case 3:
                    tentang_program();
                    get();
                    get();
                    break;
                case 0://exit program
                    return 0;
                default:
                    printf("Input Salah\n");
                    break;
            }   
        }
        menu(&dt);
        scanf("%d", &pilihan);
        switch(pilihan){
            case 1://Menambah Unit
                while(limit != -1){
                    limit = case_1(&head, temporary, spek);//fungsi tambah unit dengan linkedlist
                }
                limit = 0;
                list_print_to_file(&head);//print semua data list ke file
                break;
            case 2://Melihat Unit dalam bentuk tabel
                while(limit != -1){
                    limit = case_2(&head);
                }
                limit = 0;
                break;
            case 3://Edit Unit
                while(limit != -1){
                    limit = case_3(&head);
                }
                limit = 0;
                list_print_to_file(&head);
                break;
            case 4:
                while(limit != -1){
                    limit = case_4(&start, &end);//menambah data queue
                }
                limit = 0;
                queue_print_to_file(&start);//print data queue 
                break;
            case 5://memindahkan data queue ke linked list
                while(limit != -1){
                        limit = case_5(&start, &end, &head, temporary, &dt);
                    }
                limit = 0;
                queue_print_to_file(&start);//print ulang queue setelah perubahan data
                list_print_to_file(&head);//print ulang linked list setelah perubahan data
                break;
            case 6://searching data sesuai nama pemilik, nama penghuni dan no unit
                while(limit != -1){
                    limit = case_6(&head);
                }
                limit = 0;
                break;
            case 7://menghapus data dengan input nomor data
                while(limit != -1){
                    limit = case_7(&head);
                }
                list_print_to_file(&head);
                limit = 0;
                break;
            case 8://sorting data linked list sesuai urutan no unit dan nama pemilik
                while(limit != -1){
                    limit = case_8(&head);
                }
                list_print_to_file(&head);
                limit = 0;
                break;
            case 9://menampilkan summary data
                while(limit != -1){
                    limit = case_9(&head);
                }
                limit = 0;
                break;
            case 0: //kembali ke menu login untuk keluar program
                login = 2;
                break;
            default:
                break;
        }
    }
    return 0;
}
