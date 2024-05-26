//fike berisi print ke file dan melakukan read
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>


void list_print_to_file(struct list **head){
    FILE *data_csv;

    struct list *write = *head;
    data_csv = fopen("data.csv", "w");

    if(data_csv == NULL){
        printf("Error");
        exit(1);
    }
    while(write != NULL){
        fprintf(data_csv," %s, %d, %s, %s, %ld, %s, %d, %s, %ld, %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", write->unit.Pemilik, write->unit.No_Unit, write->unit.Status, write->unit.Penghuni, 
        write->unit.Harga_Jual, write->unit.tipe_Sewa, write->unit.Harga_Sewa
        , write->detail.sertifikat, write->detail.lantai, write->detail.jumlah_kamar, 
        write->detail.jumlah_WC, write->detail.panjang_garasi, write->detail.lebar_garasi, 
        write->detail.panjang_rumah, write->detail.lebar_rumah, write->unit.tanggal_beli, write->unit.bulan_beli, write->unit.tahun_beli, 
        write->unit.tgl_start_sewa, write->unit.bln_start_sewa, write->unit.thn_start_sewa, write->unit.tgl_end_sewa, write->unit.bln_end_sewa, write->unit.thn_end_sewa);
        write = write->link; 
    }
    
    fclose(data_csv);
    return;
    
}

void read_list_file(struct list **head, struct data temporary, struct rumah spek){
    FILE *data_csv;
    char line[1000];
    int count = 0;
    struct list *file = *head;

    data_csv = fopen("data.csv", "r");
    if (data_csv == NULL) {
        fclose(data_csv);
        return;
    }

    while (fgets(line, sizeof(line), data_csv) != NULL) {
        count++;
    }

    fseek(data_csv, 0, SEEK_SET);

    while (fgets(line, sizeof(line), data_csv) != NULL) {
        sscanf(line," %25[^,], %d, %15[^,], %25[^,], %ld, %9[^,], %d, %5[^,], %ld, %d, %d, %f, %f, %f, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d", temporary.Pemilik, &temporary.No_Unit, temporary.Status, 
        temporary.Penghuni, &temporary.Harga_Jual, temporary.tipe_Sewa, &temporary.Harga_Sewa
        , spek.sertifikat, &spek.lantai, &spek.jumlah_kamar, &spek.jumlah_WC, &spek.panjang_garasi, 
        &spek.lebar_garasi, &spek.panjang_rumah, &spek.lebar_rumah, &temporary.tanggal_beli, &temporary.bulan_beli, &temporary.tahun_beli, 
        &temporary.tgl_start_sewa, &temporary.bln_start_sewa, &temporary.thn_start_sewa, &temporary.tgl_end_sewa, &temporary.bln_end_sewa, &temporary.thn_end_sewa);
        linked_list_add(head, temporary, spek);
    }

    fclose(data_csv);
}


void queue_print_to_file(struct queue **start){
    FILE *data_queue_csv;

    struct queue *write = *start;
    data_queue_csv = fopen("data_queue.csv", "w");

    if(data_queue_csv == NULL){
        printf("Error");
        exit(1);
    }

    while(write != NULL){
        fprintf(data_queue_csv,"%s\n", write->nama);
        write = write->link; 
    }
    
    fclose(data_queue_csv);
    return;
}


void read_queue_file(struct queue **start, struct queue **end){
    FILE *data_queue_csv;
    char nama[25];
    char line[1000];
    int count = 0;
    struct queue *file = *start;

    data_queue_csv = fopen("data_queue.csv", "r");
    if (data_queue_csv == NULL) {
        fclose(data_queue_csv);
        return;
        
    }

    while (fgets(line, sizeof(line), data_queue_csv) != NULL) {
        count++;
    }

    fseek(data_queue_csv, 0, SEEK_SET);

    while (fgets(line, sizeof(line), data_queue_csv) != NULL) {
        sscanf(line," %25[^\n]", nama);
        queue_add(start, end, nama);
    }

    fclose(data_queue_csv);
    
}