//file fungsi-fungsi untuk melakukan edit data, dengan mengakses langsung node
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

void edit_pemilik(struct list **head){
    struct list *current = *head;

    printf("\tNama Pemilik : ");
    scanf(" %[^\n]", current->unit.Pemilik);
    
}

void edit_sertifikat(struct list **head){
    struct list *current = *head;
    int pilihan;
    printf("\tTipe Sertifikat : \n");
    printf("\t1. SHM\n");
    printf("\t2. HGB\n");
    printf("\tPilihan : ");
    scanf("%d", &pilihan);
    switch(pilihan){
        case 1:
            strcpy(current->detail.sertifikat, "SHM");
            break;
        case 2: 
            strcpy(current->detail.sertifikat, "HGB");
            break;
        default:
            printf("input salah");
            break;
    }
}

void edit_status_unit(struct list **head){
    struct list *current = *head;
    int pilihan;
    printf("\tStatus Unit\n");
    printf("\t1. Dijual\n");
    printf("\t2. Terjual\n");
    printf("\t3. Disewakan\n");
    printf("\t4. Disewa\n");
    printf("\ttPilihan : ");
    scanf("%d", &pilihan);
    switch(pilihan){
        case 1: 
            strcpy(current->unit.Status, "Dijual");
            break;
        case 2:
            strcpy(current->unit.Status, "Terjual");
            break;
        case 3:
            strcpy(current->unit.Status, "Disewakan");
            break;
        case 4:
            strcpy(current->unit.Status, "Disewa");
            break;
        default:
            printf("input salah\n");
            break;
    }
}

void edit_penghuni(struct list **head){
    struct list *current = *head;

    printf("\tNama Penghuni : ");
    scanf(" %[^\n]", current->unit.Penghuni);
}

void edit_tipesewa(struct list **head){
    struct list *current = *head;
    int pilihan;
    printf("\tTipe Sewa\n");
    printf("\t1. Bulanan\n");
    printf("\t2. Tahunan\n");
    printf("\t3. Tidak Disewakan");
    printf("\tPilihan : ");
    switch(pilihan){
        case 1:
            strcpy(current->unit.tipe_Sewa, "Bulanan");
            break;
        case 2:
            strcpy(current->unit.tipe_Sewa, "Tahunan");
            break;
        case 3:
            strcpy(current->unit.tipe_Sewa, "-");
        default:
            printf("\tinput salah");
            break;
    }
}

void edit_hargajual(struct list **head){
    struct list *current = *head;
    
    printf("\tHarga Jual/Beli : ");
    scanf("%ld", &current->unit.Harga_Jual);
}

void edit_hargasewa(struct list **head){
    struct list *current = *head;

    printf("\tHarga Sewa : ");
    scanf("%ld", &current->unit.Harga_Sewa);
}

void edit_jumlahlantai(struct list **head){
    struct list *current = *head;

    printf("\tJumlah Lantai : ");
    scanf("%d", &current->detail.lantai);
}

void edit_Jumlahkamar(struct list **head){
    struct list *current = *head;

    printf("\tJumlah Kamar : ");
    scanf("%d", &current->detail.jumlah_kamar);
}

void edit_JumlahWC(struct list **head){
    struct list *current = *head;

    printf("\tJumlah WC : ");
    scanf("%d", &current->detail.jumlah_WC);
}

void edit_luasgarasi(struct list **head){
    struct list *current = *head;

    printf("\tLuas Garasi\n");
    printf("\tPanjang Garasi : ");
    scanf("%f", &current->detail.panjang_garasi);
    printf("\tLebar Garasi   : ");
    scanf("%f", &current->detail.lebar_garasi);
    printf("\tLuas Garasi : %.2f", current->detail.panjang_garasi * current->detail.lebar_garasi);
}


void edit_luasrumah(struct list **head){
    struct list *current = *head;

    printf("\tLuas Rumah\n");
    printf("\tPanjang Rumah : ");
    scanf("%f", &current->detail.panjang_rumah);
    printf("\tLebar Rumah   : ");
    scanf("%f", &current->detail.lebar_rumah);
    printf("\tLuas Rumah : %.2f", current->detail.panjang_rumah * current->detail.lebar_rumah);
    
}
