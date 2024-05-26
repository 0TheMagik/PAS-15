#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//memutuskan looping atau tidak
int search_loop(){
    char konfirmasi[2];
    printf("\t\nSearch Kembali ? Y/N: ");
    scanf(" %s", konfirmasi);
    if(strcasecmp("y", konfirmasi) == 0){
        return 0;
    }
    else if(strcasecmp("n", konfirmasi) == 0){
        return -1;
    }
    else{
        printf("\tInput salah");
        return search_loop();
    }
}

//searching unit
int search_Unit(struct list **head){
    struct list *data_search = *head;
    int i;
    int jumlah = traverse_no_output(head);
    int search;
    int IPL[jumlah];
    biaya_perawatan(head, IPL);

    printf("\tMasukkan No Unit Yang dicari: ");
    scanf("%d", &search);

    printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("| %-3s| %-25s| %-9s| %-15s| %-25s| %-15s| %-10s| %-12s| %-17s| %-21s| %-23s| %-10s|\n", "No","Nama Pemilik", "No Unit", "Status", "Penghuni", "Harga Jual", "Tipe Sewa", "Harga Sewa", 
    "Tanggal Terjual", "Tanggal Mulai Sewa", "Tanggal Selesai Sewa", "Biaya IPL");
    printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	
    for(i = 1; i <= jumlah; i++){
        if(search == data_search->unit.No_Unit){
            printf("| %-3d| %-25s| %-9d| %-15s| %-25s| %-15ld| %-10s| %-12ld| %-2d/%-2d/%-11d| %-2d/%-2d/%-15d| %-2d/%-2d/%-17d| %-10d|\n", 
                1, data_search->unit.Pemilik, data_search->unit.No_Unit, data_search->unit.Status, 
                data_search->unit.Penghuni, data_search->unit.Harga_Jual, data_search->unit.tipe_Sewa, 
                data_search->unit.Harga_Sewa, data_search->unit.tanggal_beli, data_search->unit.bulan_beli, data_search->unit.tahun_beli, 
                data_search->unit.tgl_start_sewa, data_search->unit.bln_start_sewa, data_search->unit.thn_start_sewa, data_search->unit.tgl_end_sewa, data_search->unit.bln_end_sewa, data_search->unit.thn_end_sewa, IPL[i]);
        printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
			return i;
        }
        else{
            if(data_search->link == NULL){
                printf("\t\ndata tidak ada");
                return -1;
            }
        }
        data_search = data_search->link;
    }
}

//go to list untuk menuju node yang diinginkan
void go_to_list(struct list **head, int retrive, int number) {
    struct list *current = *head;
    int count = 0;
    while (current != NULL && count != retrive) {
        current = current->link;
        count++;
    }
    if (current != NULL) {
        int IPL = biaya_perawatan_satuan(&current);
        printf("| %-25s| %-9d| %-15s| %-25s| %-15ld| %-10s| %-12ld| %-2d/%-2d/%-11d| %-2d/%-2d/%-15d| %-2d/%-2d/%-17d| %-15d|\n", 
                current->unit.Pemilik, current->unit.No_Unit, current->unit.Status, 
                current->unit.Penghuni, current->unit.Harga_Jual, current->unit.tipe_Sewa, 
                current->unit.Harga_Sewa, current->unit.tanggal_beli, current->unit.bulan_beli, current->unit.tahun_beli, 
                current->unit.tgl_start_sewa, current->unit.bln_start_sewa, current->unit.thn_start_sewa, current->unit.tgl_end_sewa, current->unit.bln_end_sewa, current->unit.thn_end_sewa, IPL);
    }
}

// mengubah case huruf untuk searching string
void string_to_lower(const char* src, char* dest, int size) {
    int i;
    for ( i = 0; i < size; i++) {
        dest[i] = tolower(src[i]);
    }
    dest[size - 1] = '\0'; // Ensure null-termination
}

//searching nama pemilik
int search_pemilik(struct list **head) {
    struct list *data_search = *head;
    int jumlah = traverse_no_output(head);
    int number = 0;

    if (jumlah == 0){
        return 0;
    }
    
    char search[25];
    char search_lower[25];
    char hold[jumlah][25];
    char hold_lower[jumlah][25];
    #pragma omp parallel firstprivate (data_search)//daerah parallel dengan data_search private
    {
        #pragma omp single//mengakses linked list dengan omp single untuk memasukan data string ke array
        for (int i = 0; i < jumlah; i++) {
            strncpy(hold[i], data_search->unit.Pemilik, 25);
            data_search = data_search->link;
        }

        #pragma omp for//parallel denagn omp for untuk melakukan lower case nama
        for (int i = 0; i < jumlah; i++) {
            string_to_lower(hold[i], hold_lower[i], 25);
        }

        #pragma omp single//melakukan input nama yang dicari
        {
            printf("\tMasukkan Nama Pemilik yang dicari: ");
            scanf(" %[^\n]", search);
            string_to_lower(search, search_lower, 25);
            printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
            printf("| %-25s| %-9s| %-15s| %-25s| %-15s| %-10s| %-12s| %-17s| %-21s| %-23s| %-15s|\n", "Nama Pemilik", "No Unit", "Status", "Penghuni", "Harga Jual", "Tipe Sewa", "Harga Sewa", 
            "Tanggal Terjual", "Tanggal Mulai Sewa", "Tanggal Selesai Sewa", "Biaya IPL");
            printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        }
    
        #pragma omp for reduction(+: number)//parallel dengan for reduction number
        for (int i = 0; i < jumlah; i++) {
            if (strstr(hold_lower[i], search_lower) != NULL) {
                int retrive = i;
                #pragma omp critical//go_to_list dan number++ menggunakan omp critical untuk mencegah race condition
                {
                    go_to_list(head, retrive, number);
                    number++;
                }
            }
        }
    }
    return search_loop();
}

//prinsip sama seperti search penghuni
int search_penghuni(struct list **head) {
    struct list *data_search = *head;
    int jumlah = traverse_no_output(head);
    int number = 0;

    if (jumlah == 0){
        return 0;
    }
    
    char search[25];
    char search_lower[25];
    char hold[jumlah][25];
    char hold_lower[jumlah][25];
    #pragma omp parallel firstprivate (data_search)
    {
        #pragma omp single
        for (int i = 0; i < jumlah; i++) {
            strncpy(hold[i], data_search->unit.Penghuni, 25);
            data_search = data_search->link;
        }

        #pragma omp for
        for (int i = 0; i < jumlah; i++) {
            string_to_lower(hold[i], hold_lower[i], 25);
        }

        #pragma omp single
        {
            printf("\tMasukkan Nama Penghuni yang dicari: ");
            scanf(" %[^\n]", search);
            string_to_lower(search, search_lower, 25);
            printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
            printf("| %-25s| %-9s| %-15s| %-25s| %-15s| %-10s| %-12s| %-17s| %-21s| %-23s| %-15s|\n", "Nama Pemilik", "No Unit", "Status", "Penghuni", "Harga Jual", "Tipe Sewa", "Harga Sewa", 
            "Tanggal Terjual", "Tanggal Mulai Sewa", "Tanggal Selesai Sewa", "Biaya IPL");
            printf("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        }
    
        #pragma omp for reduction(+: number)
        for (int i = 0; i < jumlah; i++) {
            if (strstr(hold_lower[i], search_lower) != NULL) {
                int retrive = i ; // Adjust indexing since i starts from 0
                #pragma omp critical
                {
                    go_to_list(head, retrive, number);
                    number++;
                }                
            }
        }
    }
    return search_loop();
    
}