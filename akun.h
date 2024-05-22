#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

//menu akun
void akun(){
	backgroundcolor(BLUE);
	printf("|====================================|\n");
	printf("|            Selamat Datang          |\n");
	printf("|====================================|\n");
    printf("| 1.| Login                          |\n");
    printf("|---|--------------------------------|\n");
    printf("| 2.| Buat akun                      |\n");
    printf("|---|--------------------------------|\n");
    printf("| 0.| Exit Program                   |\n");
    printf("|---|--------------------------------|\n");
    printf("| Masukkan Pilihan : ");
}
//linked list untuk akun
void linked_list_akun(struct akun **head, char *akun, char *password){
    struct akun *New_Node = (struct akun*)malloc(sizeof(struct akun));
    if(New_Node == NULL){
        printf("\n\talokasi memori gagal");
        exit(1);
    }

    strcpy(New_Node->akun, akun);
    strcpy(New_Node->password, password);
    New_Node->link = NULL;

    if(*head == NULL){
        *head = New_Node;
    }
    else{
        struct akun *tail = *head;
        while(tail->link != NULL){
            tail = tail->link;
        }
        tail->link = New_Node;
    }
}

//melakukan pengecekan untuk akun dan password
int cek_akun(struct akun **head, char *akun, char *password){
    struct akun *cek = *head;

    while(cek != NULL){
        if(strcmp(cek->akun, akun) == 0 && strcmp(cek->password, password) == 0){
            return 1;
        }
        cek = cek->link;
    }
    return 2;
}

//login akun dengan password dan username
int case_akun_1(struct akun **head){
    
    char akun[25];
    char password[25];
    printf("\tUsername : ");
    scanf(" %s", akun);
    printf("\tPassword : ");
    scanf(" %s", password);
    return cek_akun(head, akun, password);
}

//membuat akun baru
void case_akun_2(struct akun **head){
    char akun[25];
    char password[25];
    printf("\tUsername : ");
    scanf(" %s", akun);
    printf("\tPassword : ");
    scanf(" %s", password);
    linked_list_akun(head, akun, password);//dimasukkan ke file
    return;
}

//print akun dan password untuk disimpan kefile
void print_akun_file(struct akun **head){
    FILE *data_akun_csv;

    struct akun *write = *head;
    data_akun_csv = fopen("data_akun.csv", "w");

    if(data_akun_csv == NULL){
        printf("Error");
        exit(1);
    }
    while(write != NULL){
        fprintf(data_akun_csv, "%s,%s\n", write->akun, write->password);
        write = write->link; 
    }
    
    fclose(data_akun_csv);
    return;
}

//membaca file yang menyimpan akun
void read_akun_file(struct akun **head){
    FILE *data_akun_csv;
    char line[1000];
    char akun[25];
    char password[25];
    int count = 0;
    struct akun *file = *head;

    data_akun_csv = fopen("data_akun.csv", "r");
    if (data_akun_csv == NULL) {
        fclose(data_akun_csv);
        return;
    }

    while (fgets(line, sizeof(line), data_akun_csv) != NULL) {
        count++;
    }

    fseek(data_akun_csv, 0, SEEK_SET);

    while (fgets(line, sizeof(line), data_akun_csv) != NULL) {
        sscanf(line," %24[^,], %24[^\n]", akun, password);
        linked_list_akun(head, akun, password);
    }

    fclose(data_akun_csv);
}