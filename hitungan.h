#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>


int traverse_no_output(struct list **head){
    struct list *current = *head;
    int count = 0;
    if(current == NULL){
        return count;
    }

    while(current != NULL){
        count++;
        current = current->link;
    }

    return count;
}


//iuran biaya pengelolaan lingkungan (IPL);
//bervariasi untuk setiap perumahan
//tidak ditemukan aspek perhitungan IPL
//kami membuat IPL berdasarkan sertifikat dan harga jual
void biaya_perawatan(struct list **head, int *IPL){
    struct list *current = *head;
    struct list *save_cost = *head;
    int jumlah_unit = traverse_no_output(&current);
    int biaya[jumlah_unit];
    int i;
    #pragma omp parallel//region parallel start
    {
        #pragma omp single//melakukan akses linked list, maka menggunakan omp single
        {
            for(i = 0; i < jumlah_unit; i++){
                if(strcasecmp(save_cost->detail.sertifikat, "SHM") == 0){
                    IPL[i] =  save_cost->unit.Harga_Jual * 0.02 + 1000000; 
                    
                }
                else{
                    IPL[i] = save_cost->unit.Harga_Jual * 0.01 + 1000000;
                }
                save_cost = save_cost->link;
                
            }
        }
    }
}

//menghitung rumah yang sertifikat shm, rumah terjual
void count_summary(struct list **head, int *Rumah_shm, int *Rumah_terjual){
    struct list *current = *head;
    if(current == NULL){
        return;
    }

    while(current != NULL){
        if(strcasecmp(current->detail.sertifikat, "SHM") == 0){
            (*Rumah_shm)++;
        }
        if(strcasecmp(current->unit.Status, "Terjual") == 0 || strcasecmp(current->unit.Status, "Disewakan") == 0 || strcasecmp(current->unit.Status, "Disewa") == 0){
            (*Rumah_terjual)++;
        }
        current = current->link;
    }
    
}

//mencari ipl tertinggi dan ipl terendah
void high_low_IPL(struct list **head, int *IPL, int jumlah, int *IPL_high, int *IPL_low, int *total){
    int i;
    struct list *save_cost = *head;
    #pragma omp parallel
    {
        #pragma omp single//omp single karena melakukan akses linked list
        {
            for(i = 0; i < jumlah; i++){
                if(strcasecmp(save_cost->detail.sertifikat, "SHM") == 0){
                    IPL[i] =  save_cost->unit.Harga_Jual * 0.02 + 1000000; 
                    
                }
                else{
                    IPL[i] = save_cost->unit.Harga_Jual * 0.03 + 1000000;
                }
                save_cost = save_cost->link;
                
            }
        }
    }
    *IPL_high = IPL[0];
    *IPL_low = IPL[0];
    *total = 0;

    for(i = 1; i < jumlah; i++){
        if(IPL[i] > *IPL_high){
            *IPL_high = IPL[i];
        }
        if(IPL[i] < *IPL_low){
            *IPL_low = IPL[i];
        }
        *total += IPL[i];
    }
    
}