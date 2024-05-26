#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//sorting dengan bubble sort pada linked list
void sort_list_nama(struct list **head) {
    int swap;
    struct list *current;
    struct data temp1;
    struct rumah temp2;

    if (*head == NULL) {
        printf("List Kosong\n");
        return;
    }

    do {
        swap = 0;
        current = *head;

        while (current->link != NULL) {
            struct list *next = current->link;
            if (strcmp(current->unit.Pemilik, next->unit.Pemilik) > 0) {
                temp1 = current->unit;
                temp2 = current->detail;
                current->unit = next->unit;
                current->detail = next->detail;
                next->unit = temp1;
                next->detail = temp2;
                swap = 1;
            }
            current = current->link;
        }
    } while (swap == 1);
}

//sorting dengan bubble sort pada linked list
void sort_list_Unit(struct list **head) {
    int swap;
    struct list *current;
    struct data temp1;
    struct rumah temp2;

    if (*head == NULL) {
        printf("List Kosong\n");
        return;
    }

    do {
        swap = 0;
        current = *head;

        while (current->link != NULL) {
            struct list *next = current->link;
            if (current->unit.No_Unit > next->unit.No_Unit) {
                temp1 = current->unit;
                temp2 = current->detail;
                current->unit = next->unit;
                current->detail = next->detail;
                next->unit = temp1;
                next->detail = temp2;
                swap = 1;
            }
            current = current->link;
        }
    } while (swap == 1);
}

//menambah linked list
void linked_list_add(struct list **head, struct data temporary, struct rumah spek){
    struct list *New_Node = (struct list*)malloc(sizeof(struct list));
    if(New_Node == NULL){
        printf("\n\talokasi memori gagal");
        exit(1);
    }

    New_Node->unit = temporary;
    New_Node->detail = spek;
    New_Node->link = NULL;

    if(*head == NULL){
        *head = New_Node;
    }
    else{
        struct list *tail = *head;
        while(tail->link != NULL){
            tail = tail->link;
        }
        tail->link = New_Node;
    }
}

//menambah node queue
void queue_add(struct queue **start, struct queue **end, char *temporary){
    
    struct queue *New_Node = (struct queue *)malloc(sizeof(struct queue));

    if(New_Node == NULL){
        printf("\n\talokasi memori gagal");
        exit(1);
    }

    strcpy(New_Node->nama, temporary);
    New_Node->link = NULL;

    if(*start == NULL){
        *start = New_Node;
    }
    else{
        (*end)->link = New_Node;
    }
    *end = New_Node;
}

//delete queue
void dequeue(struct queue **start, struct queue **end){
    if(*start == NULL){
        printf("\tTidak ada waiting list pembeli");
        return;
    }

    struct queue *hold = *start;
    *start = (*start)->link;
    free(hold);

    if(*start == NULL){
        *end = NULL;
    }
}

//traversing ke node tertentu
struct list* traverse_to(struct list **head, int count){
    struct list *current = *head;
    if(*head == NULL){
        printf("\n\tdata kosong");
        return NULL;
    }

    if(count == 1){
        return current;
    }
    else{
        while(count != 1){
            current = current->link;
            count--;
        }
        return current;
    }
}

//memindahkan isi sesuai queue ke list
int queue_to_list(struct queue **start, struct queue **end, struct list **head, struct data temporary, struct date *dt){
    int posisi, pilihan;
    struct list *pass = *head;
    print_data_queue(start);
    if(pass == NULL){
        printf("Queue Kosong\n");
    }
    printf("\tStatus Pelanggan\n");
    printf("\t1. Lanjut Proses Pembelian/Sewa\n");
    printf("\t2. Cancel (tidak jadi membeli)\n");
    printf("\t0. Kembali\n");
    printf("\tPilihan : ");
    scanf("%d", &pilihan);
    switch(pilihan){
        case 1:
            struct queue *hold = *start;
            if(hold == NULL){
                printf("Antrean Kosong, Tekan enter untuk kembali");
                get();
                get();
                return -1;
            }
            print_data_unit(head);
            posisi = search_Unit(&pass);
            if(posisi == -1){
                return posisi;
            }
            struct list *current = traverse_to(head, posisi);
            if(strcasecmp("Dijual", current->unit.Status) == 0){
                strcpy(current->unit.Pemilik, hold->nama);
                strcpy(current->unit.Status, "Terjual");
                current->unit.tanggal_beli = dt->da_day;
                current->unit.bulan_beli = dt->da_mon;
                current->unit.tahun_beli = dt->da_year;
            }
            else if(strcasecmp("Disewakan", current->unit.Status) == 0){
                strcpy(current->unit.Penghuni, hold->nama);
                strcpy(current->unit.Status, "Disewa");
                current->unit.tgl_start_sewa = dt->da_day;
                current->unit.bln_start_sewa = dt->da_mon;
                current->unit.thn_start_sewa = dt->da_year;
                printf("Tanggal Selesai Sewa Belum ditentukan, Silahkan ubah di menu edit\n");
            }
            else{
                printf("Tidak Tersedia\n");
                return -1;
            }
            *start = (*start)->link;
            free(hold);
            break;
            
        case 2:
            if(*start == NULL){
                printf("Antrean Kosong, Tekan enter untuk kembali");
                get();
                get();
                return -1;
            }
            dequeue(start, end);
            break;
        case 0:
            return -1;
        default:
            break;
    }
    return 0;
}

//menambah unit sebelum ke linked list
void tambah_unit(struct list **head, struct data temporary, struct rumah spek){
    strcpy(temporary.Pemilik, "Developer");
    strcpy(temporary.Status, "Dijual");
    strcpy(temporary.Penghuni, "None");
    strcpy(temporary.tipe_Sewa, "-");
    temporary.Harga_Sewa = 0;
    temporary.tanggal_beli = 0;
    temporary.bulan_beli = 0;
    temporary.tahun_beli = 0;
    temporary.tgl_start_sewa = 0;
    temporary.bln_start_sewa = 0;
    temporary.thn_start_sewa = 0;
    temporary.tgl_end_sewa = 0;
    temporary.bln_end_sewa = 0;
    temporary.thn_end_sewa = 0;
    linked_list_add(head, temporary, spek);
}

//mengecek no unit 
int cek_data_no_unit(struct list **head){
    struct list *cek = *head;
    int input;
    printf("\tMasukkan No Unit         : ");
    scanf("%d", &input);

    while(cek != NULL){
        if(cek == NULL){
            return input;
        }
        else if(input == cek->unit.No_Unit){
            printf("No unit sudah ada\n");
            return cek_data_no_unit(head);
        }
        else{
            cek = cek->link;
        }
    }
    return input;
    
}

//mengisi detail rumah sebelum ke linked list
struct rumah detail_unit(struct rumah spek){
    int pilih;
    printf("\tMasukkan Data Unit\n");
    printf("\tSertifikat Rumah: \n");
    printf("\t1. SHM\n");
    printf("\t2. HGB\n");
    printf("\tPilihan: ");
    scanf("%d", &pilih);
    switch(pilih){
        case 1:
            strcpy(spek.sertifikat, "SHM");
            break;
        case 2: 
            strcpy(spek.sertifikat, "HGB");
            break;
        default:
            printf("input salah");
            break;
    }
    printf("\tSertifikat Rumah      : %s\n", spek.sertifikat);
    printf("\tJumlah Lantai         : ");
    scanf("%d", &spek.lantai);
    printf("\tJumlah Kamar          : ");
    scanf("%d", &spek.jumlah_kamar);
    printf("\tJumlah WC             : ");
    scanf("%d", &spek.jumlah_WC);
    printf("\tPanjang Garasi        : ");
    scanf("%f", &spek.panjang_garasi);
    printf("\tLebar Garasi          : ");
    scanf("%f", &spek.lebar_garasi);
    float luas = spek.panjang_garasi * spek.lebar_garasi;
    printf("\tLuas Garasi           : %.2f\n", luas);
    printf("\tPanjang Tanah         : ");
    scanf("%f", &spek.panjang_rumah);
    printf("\tLebar Tanah           : ");
    scanf("%f", &spek.lebar_rumah);
    float luas_rumah = spek.panjang_rumah * spek.lebar_rumah;
    printf("\tLuas Tanah            : %.2f\n", luas_rumah);
    printf("\tMeyimpan data...");
	Sleep(5);
	printf("\n\tInput Data Selesai");
    printf("\n\tSilahkan tekan Enter");
    get();
    get();
    cls();
    return spek;
}

//menghapus node pada linked list
void hapus_list(struct list **head, int position){
    
    struct list *current = *head;
    struct list *previous = *head;
    

    if(*head == NULL){
        printf("Data Kosong");
    }
    //jika posisi 1 yang akan dihapus
    else if(position == 1){
        *head = current->link; 
        free(current);
        current = NULL;
    }

    else{
        while(position != 1){
            previous = current; 
            current = current->link; 
            position--;
        }
        previous->link = current->link; 
        free(current);
        current = NULL;
    }
}

//menambah isi queue
int queue_input(struct queue **start, struct queue **end){
    char nama[25];

    printf("\tMasukkan Nama Calon Pembeli : ");
    scanf(" %[^\n]", nama);

    queue_add(start, end, nama);
    
}