#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//memutuskan melakukan loopingb atau tidak
int data_loop(){
    char konfirmasi[2];
    scanf(" %s", konfirmasi);
    if(strcasecmp("y", konfirmasi) == 0){
        return 0;
    }
    else if(strcasecmp("n", konfirmasi) == 0){
        return -1;
    }
    else{
        printf("\tInput salah");
        return data_loop();
    }
}

//melakukan print data dalam bentuk tabel
int print_data_unit(struct list **head){
	backgroundcolor(YELLOW);
    int count = 0;
    struct list *current = *head;
    int i;
    int jumlah = traverse_no_output(head);
    int IPL[jumlah];
    biaya_perawatan(head, IPL);

    if(current == NULL){
        printf("\nData Unit Kosong\n");
        return 0;
    }
	printf("|---------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("| %-3s| %-25s| %-9s| %-15s| %-25s| %-15s| %-10s| %-12s| %-10s|", "No", "Nama Pemilik", "No Unit", "Status", "Penghuni", "Harga Jual", "Tipe Sewa", "Harga Sewa", "Biaya IPL");
	printf("\n|---------------------------------------------------------------------------------------------------------------------------------------------|\n");
	
    for (int i = 0; i < jumlah; i++) {
        count++;
        printf("| %-3d| %-25s| %-9d| %-15s| %-25s| %-15ld| %-10s| %-12ld| %-10d|\n", 
                count, current->unit.Pemilik, current->unit.No_Unit, current->unit.Status, 
                current->unit.Penghuni, current->unit.Harga_Jual, current->unit.tipe_Sewa, 
                current->unit.Harga_Sewa, IPL[i]);
        	printf("|---------------------------------------------------------------------------------------------------------------------------------------------|\n");
        current = current->link;
    }
    printf("\n");
    return count;
}

//keluar dari print
int exit_print(){
    char konfirmasi[1];
    printf("\tUntuk Kembali Tekan Y: ");
    scanf("%s", konfirmasi);
    if(strcasecmp("y", konfirmasi) == 0){
        cls();
        return -1;
    }
    else{
        printf("\tinput salah\n");
        return exit_print();
    }
}

//print data queue dalam bentuk tabel
int print_data_queue(struct queue **start){
	backgroundcolor(YELLOW);
    int count = 0;
    struct queue *current = *start;

    if(current == NULL){
        printf("\nData Queue Kosong\n");
        return 0;
    }
	printf("|-------------------------------|\n");
    printf("| %-3s| %-25s|", "No", "Nama Pelanggan");
	printf("\n|-------------------------------|");
	
    while(current != NULL){
        count++;
        printf("\n| %-3d| %-25s|", count, current->nama);
        current = current->link;
    printf("\n|-------------------------------|");
    }
    printf("\n");
    return count;
}

//perhitungan biaya IPL untuk satuan
int biaya_perawatan_satuan(struct list **head){
    struct list *temp = *head;
    int biaya;
    if(strcasecmp(temp->detail.sertifikat, "SHM") == 0){
        biaya = temp->unit.Harga_Jual * 0.02 + 1000000;
    }
    else{
        biaya = temp->unit.Harga_Jual * 0.03 + 1000000;
    }
    return biaya;
}

//print detail rumah untu edit data
int print_list_detail(struct list **head){
	backgroundcolor(YELLOW);
    struct list *current = *head;
    char decision[2];
    int edit_unit, pilihan;
    int biaya = biaya_perawatan_satuan(head);
    printf("----------------------------------------------------------------------------------------------\n");
    printf("|                                     Data Unit %d                                            |\n", current->unit.No_Unit);
    printf("----------------------------------------------------------------------------------------------\n");
    printf("| Pemilik         : %-25s        Jumlah Lantai        : %-15d  |\n", current->unit.Pemilik, current->detail.lantai);
    printf("| Tipe Sertifikat : %-25s        Jumlah Kamar         : %-15d  |\n", current->detail.sertifikat, current->detail.jumlah_kamar);
    printf("| Status Unit     : %-25s        Jumlah WC            : %-15d  |\n", current->unit.Status, current->detail.jumlah_WC);
    printf("| Penghuni        : %-25s        Luas Garasi          : %-16.2f |\n", current->unit.Penghuni, current->detail.panjang_garasi*current->detail.lebar_garasi);
    printf("| Tipe Sewa       : %-25s        Luas Rumah           : %-16.2f |\n", current->unit.tipe_Sewa, current->detail.panjang_rumah*current->detail.lebar_rumah);
    printf("----------------------------------------------------------------------------------------------\n");
    printf("| Harga Sewa      : %-25ld       Tanggal Rumah Dibeli : %d/%d/%d         |\n", current->unit.Harga_Sewa, current->unit.tanggal_beli, current->unit.bulan_beli, current->unit.tahun_beli);
    printf("| Harga Beli/Jual : %-25ld       IPL Rumah            : Rp %-15d|\n", current->unit.Harga_Jual, biaya);
    printf("----------------------------------------------------------------------------------------------\n");
    printf("\tEdit Data Unit ? Y/N : ");
    edit_unit = data_loop();
    if(edit_unit == 0){
        menu_edit();
        scanf("%d", &pilihan);
        switch(pilihan){
            case 1:
                edit_pemilik(&current);
                break;
            case 2:
                edit_sertifikat(&current);
                break;
            case 3:
                edit_status_unit(&current);
                break;
            case 4:
                edit_penghuni(&current);
                break;
            case 5:
                edit_tipesewa(&current);
                break;
            case 6:
                edit_hargasewa(&current);
                break;
            case 7:
                edit_hargajual(&current);
                break;
            case 8:
                edit_jumlahlantai(&current);
                break;
            case 9:
                edit_Jumlahkamar(&current);
                break;
            case 10:
                edit_JumlahWC(&current);
                break;
            case 11:
                edit_luasgarasi(&current);
                break;
            case 12:
                edit_luasrumah(&current);
                break;
            default:
                printf("\tinput salah\n");
                break;
        }
    }
    else{
        return edit_unit;
    }
    
}