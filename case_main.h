#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//fungsi konfirmasi untuk menentukan akan looping atau tidak
int konfirmasi(){
    char decision[2];
    scanf(" %s", decision);
    if(strcasecmp("y", decision) == 0){
        return 0;
    }
    else if(strcasecmp("n", decision) == 0){
        return -1;
    }
    else{
        printf("\tInput salah");
        return search_loop();
    }
}

//case 1 untuk menambah unit
int case_1(struct list **head, struct data temporary, struct rumah spek){
    char konfirmasi[1];
    printf("\tTambah Unit? Y/N: ");
    scanf("%s", konfirmasi);
    if(strcasecmp("y", konfirmasi) == 0){

        print_data_unit(head);

        //melakukan pengecukan no unit dengan linked list apakah ada no unit yang sam
        temporary.No_Unit = cek_data_no_unit(head);

        printf("\tMasukkan Harga Jual Unit : ");
        scanf("%d", &temporary.Harga_Jual);
        spek = detail_unit(spek);

        tambah_unit(head,temporary, spek);
        cls();

        return 1;
    }
    else if(strcasecmp("N", konfirmasi) == 0){
        return -1;
    }
    else{
        printf("\tinput salah");
        return case_1(head, temporary, spek);
    }
}

//case 2 untuk melihat isi linked list dengan bentuk tabel
int case_2(struct list **head){
    int konfirmasi = 0;
    print_data_unit(head);
    konfirmasi = exit_print();
    return konfirmasi;
}

//case 3 untuk edit data unit
int case_3(struct list **head){
    int posisi;
    int run = 0, run1 = 0, run2 = 0;
    struct list *pass;

    while(run == 0){
        while(run1 == 0){
        print_data_unit(head);
        posisi = search_Unit(head);
        if(posisi == -1 ){
            printf("\tSearch Kembali1 ? Y/N : ");
            return konfirmasi();
        }
        pass = traverse_to(head, posisi);//melakukan traverse untuk menuju node yang diinginkan
        printf("\nSearch Kembali ? Y/N : ");
        run1 = konfirmasi();
        }
        run1 = 0;
        while(run2 == 0){
            run2 = print_list_detail(&pass);//passing node variabel pass untuk melakukan print deatil data
        }
        run2 = 0;
        printf("\tEdit Data Lain ? Y/N: ");
        run = konfirmasi();
    }
    
    return run;
}

//case 4 untuk mengisi queue
int case_4(struct queue **start, struct queue **end){
    int run;
    while(run == 0){
        print_data_queue(start);
        printf("\tIsi Queue ? Y/N : ");
        run = konfirmasi();
        if(run == -1){
            return run;
        }
        print_data_queue(start);
        queue_input(start, end);
        cls();
        print_data_queue(start);
    }
    return run;
}

//case 5 untuk memindahkan data dari queue ke linked list
int case_5(struct queue **start, struct queue **end, struct list **head, struct data temporary, struct date *dt){
    int run;
    run = queue_to_list(start, end, head, temporary, dt);
    if(run == -1){
        printf("\tTetap Disini ? Y/N : ");
        return konfirmasi();
    }
    printf("\n\tLanjut Memindahkan ? Y/N : ");
    return konfirmasi();
}

//case 6 untuk searching data pada linked list
int case_6(struct list **head){
    int konfirmasi = 0;
    int search;
    int pilihan;
    int limit;
    search_menu();
    scanf("%d", &pilihan);
    switch(pilihan){
        case 1:
            while(limit != -1){
                cls();
                search_Unit(head);
                limit = search_loop();    
            }
            limit = 0;
            break;
        case 2:
            while(limit != -1){
                cls();
                limit = search_pemilik(head);    
            }
            limit = 0;
            break;
        case 3:
            while(limit != -1){
                cls();
                limit = search_penghuni(head);    
            }
            limit = 0;
            break;
        case 0:
            return -1;
            break;
        default:
        	break;
        	
    }
    
}

//fungsi untuk menghapus node pada linked list

int case_7(struct list **head){
    int posisi;
    struct list *current = *head;
    int jumlah = print_data_unit(head);
    if(current == NULL){
        get();
        get();
        cls();
        return -1;
    }
    else{
        printf("\n\tNo Data yang akan Dihapus: ");
        scanf(" %d", &posisi);
        if(posisi > jumlah){
            printf("\tData Tidak Ada, Hapus Data Lain ? Y/N");
            return konfirmasi();
        }
        hapus_list(head, posisi);
        print_data_unit(head);
        printf("\n\tHapus Lagi ? Y/N : ");
        return konfirmasi();
    }
    
}

//case 8 untuk melakukan sorting, menggunakan buble sort
int case_8(struct list **head){
    int pilihan;
    struct list *pass = *head;
    sort_menu();
    scanf("%d", &pilihan);
    switch(pilihan){
        case 1:
            print_data_unit(head);
            printf("\tTekan Enter Untuk Sort");
            get();
            get();
            cls();
            sort_list_nama(&pass);
            print_data_unit(head);
            printf("\tSort lagi ? Y/N : ");
            return konfirmasi();
            break;
        case 2:
            print_data_unit(head);
            printf("\tTekan Enter Untuk Sort");
            get();
            get();
            cls();
            sort_list_Unit(&pass);
            print_data_unit(head);
            printf("\tSort lagi ? Y/N : ");
            return konfirmasi();
            break;
        case 0:
            return -1;
        default:
            printf("\tInput Salah\n");
            break;
    }
}

//case 9 untuk menampilkan data perumahan 
int case_9(struct list **head){
backgroundcolor(YELLOW);
    int jumlah = traverse_no_output(head);
    int IPL[jumlah];
    int IPL_total;
    int IPL_AVG = 0;
    int Rumah_shm = 0;
    int Rumah_hgb = 0;
    int Rumah_terjual = 0;
    int IPL_high, IPL_low ;
    biaya_perawatan(head, IPL);
    count_summary(head, &Rumah_shm, &Rumah_terjual);
    high_low_IPL(head, IPL, jumlah, &IPL_high, &IPL_low, &IPL_total);
    Rumah_hgb = jumlah - Rumah_shm;
    IPL_AVG = IPL_total / jumlah;
    printf("===============================================================\n");
    printf("|                        Data Perumahan                       |\n");
    printf("===============================================================\n");
    printf("| Jumlah Rumah         : %-37d|\n", jumlah);
    printf("| Jumlah Rumah SHM     : %-37d|\n", Rumah_shm);
    printf("| Jumlah Rumah HGB     : %-37d|\n", Rumah_hgb);
    printf("| Jumlah Rumah Terjual : %-37d|\n", Rumah_terjual);
    printf("==============================================================|\n");
    printf("| Total IPL       = %-42d|\n", IPL_total);
    printf("| Rata-Rata IPL   = %-42d|\n", IPL_AVG);
    printf("| IPL Tertinggi   = %-42d|\n", IPL_high);
    printf("| IPL Terendah    = %-42d|\n", IPL_low);
    printf("==============================================================|\n");
    printf("\tTetap Disini ? Y/N : ");
    return konfirmasi();
}