#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct hero {           //HERO bilgilerinin tutuldugu struck
    char name[25];
    int HP;
    int DAMAGE;
    int XP;
    int X;
    int Y;
};

struct monster {       //MONSTER bilgilerinin tutuldugu struck olusturduk.
    char name[25];
    int HP;
    int DAMAGE;
    int X;
    int Y;
};
FILE *yaz;

void showmap(int satir, int sutun, char **matris) {  //harita yazdirma fonksiyonu
    printf("\t MAP STATUS\n");
    fprintf(yaz, "\t MAP STATUS\n");
    int i,j;
    for (i = 0; i < satir; i++) {
        for (j = 0; j < sutun; j++) {
            printf("%c\t", matris[i][j]);
            fprintf(yaz, "%c\t", matris[i][j]);
        }
        printf("\n\n");
        fprintf(yaz, "\n\n");
    }
}


int main(int argc, char *argv[]) {


    FILE *oku;
    oku = fopen(argv[1], "r");  //karakterlerin oldugu dosyayi actik
    char ch[100];
    int sum = 0, n_hero = 0, n_monster = 0; //toplam/hero/monster sayisi
    int livehero = 0;
    int livemonster = 0; // oyunun devam etmesi icin live>0
    while (!feof(oku)) { //dosya sonuna kadar oku
        sum++;
        fgets(ch, 100, oku);
        strtok(ch, ",");
        if (strcmp(ch, "HERO") == 0) {
            n_hero++; //kahraman sayisi
            livehero++;
        } else {
            n_monster++; //canavar sayisi
            livemonster++;
        }
    }
    fclose(oku);


    struct hero *kahramanlar;  //kahramanlar strucktini isaret eden pointer
    struct monster *canavarlar; //canavarlar structini isaret eden pointer

    kahramanlar = (struct hero *) malloc(n_hero * sizeof(struct hero)); //struck dizisi kadar dinamik bellek
    canavarlar = (struct monster *) malloc(n_monster * sizeof(struct monster));

    FILE *oku2; //char doyası okuma islemi
    oku2 = fopen(argv[1], "r");
    char ch2[100], *ch3;
    int sayac = 0, sayac1 = 0;

    while (!feof(oku)) { //strucklara karakter ozelliklerini girdik.
        fgets(ch2, 100, oku2);
        ch3 = strtok(ch2, ",");
        if (strcmp(ch3, "HERO") == 0) {   //kahramanlari strucklara yerlestirdik.
            ch3 = strtok(NULL, ",");
            strcpy(kahramanlar[sayac].name, ch3);
            ch3 = strtok(NULL, ",");
            kahramanlar[sayac].HP = atoi(ch3);
            ch3 = strtok(NULL, ",");
            kahramanlar[sayac].DAMAGE = atoi(ch3);
            kahramanlar[sayac].XP = 0;
            kahramanlar[sayac].X = 0;
            kahramanlar[sayac].Y = 0;
            sayac++;
        } else if (strcmp(ch3, "MONSTER") == 0) { //canavarlari strucklara yerlestirdik.
            ch3 = strtok(NULL, ",");
            strcpy(canavarlar[sayac1].name, ch3);
            ch3 = strtok(NULL, ",");
            canavarlar[sayac1].HP = atoi(ch3);
            ch3 = strtok(NULL, ",");
            canavarlar[sayac1].DAMAGE = atoi(ch3);
            canavarlar[sayac1].X = 0;
            canavarlar[sayac1].Y = 0;
            sayac1++;
        };
    }
    fclose(oku2);//dosya kapandi.


    yaz = fopen(argv[3], "w"); //dosya yazma islemi


    FILE *oku3;   //komut dosyası acıldı.
    oku3 = fopen(argv[2], "r");

    char **matris;
    char komut[100], *CP; //komut pointerim splitlemek icin.
    int satir, sutun;

    while (!feof(oku3)) {  //komutlarin uygulandigi kisim
        fgets(komut, 150, oku3);
        CP = strtok(komut, " ");
        if (strcmp(CP, "LOADMAP") == 0) {  //mallock yapisini kullanarak 2d dinamik dizi olusturduk.

            CP = strtok(NULL, " ");
            satir = atoi(CP);
            CP = strtok(NULL, " ");
            sutun = atoi(CP);
            matris = (char **) malloc(satir * sizeof(char *));
            int i,j;
            for (i = 0; i < satir; i++) {
                matris[i] = (char *) malloc(sutun * sizeof(char));
            }
            int k;
            for (j = 0; j < satir; j++) {   //matrisin icini '*' ile doldurduk.
                for (k = 0; k < sutun; k++) {
                    matris[j][k] = '*';
                }
            }

        } else if (strcmp(komut, "PUT") == 0) { //Karakterlimizi verilen kordinatlara yerlestirdik.

            CP = strtok(NULL, " ");

            if (strcmp(CP, "HERO") == 0) {
                    int i,j;
                for (i = 0; i < n_hero; i++) { //bolme islemlerini yapıp herolari yerlestirdik.
                    CP = strtok(NULL, " ");
                    char kiyasla[20];
                    strcpy(kiyasla, CP);
                    char name = CP[0];
                    CP = strtok(NULL, " ");
                    int x = atoi(CP);
                    CP = strtok(NULL, " ");
                    int y = atoi(CP);
                    matris[x][y] = name;
                    for (j = 0; j < n_hero; ++j) {
                        if (strcmp(kiyasla, kahramanlar[j].name) == 0) { //struck x ve y bilgisini guncelledik.
                            kahramanlar[j].X = x;
                            kahramanlar[j].Y = y;
                        }
                    }
                }

            } else if (strcmp(CP, "MONSTER") == 0) { //split islemlerini yapıp canavarlari yerlestirdik.
                    int i,j;
                for (i = 0; i < n_monster; i++) {
                    CP = strtok(NULL, " ");
                    char kiyasla[20];
                    strcpy(kiyasla, CP);
                    char name = CP[0];
                    CP = strtok(NULL, " ");
                    int x = atoi(CP);
                    CP = strtok(NULL, " ");
                    int y = atoi(CP);
                    matris[x][y] = name;

                    for (j = 0; j < n_monster; j++) {
                        if (strcmp(kiyasla, canavarlar[j].name) == 0) { //struck x ve y bilgisini guncelledik.
                            canavarlar[j].X = x;
                            canavarlar[j].Y = y;

                        }
                    }
                }
            }

        } else if (strcmp(komut, "SHOW") == 0) { //SHOW > MAP/HERO/MONSTER

            CP = strtok(NULL, " ");
            if (strcmp(CP, "MAP\n") == 0) {
                showmap(satir, sutun, matris);  //harita yazdirma fonksiyon cagrisi
            } else if (strcmp(CP, "HERO\n") == 0) {

                printf("\tHERO STATUS\n");
                fprintf(yaz, "\tHERO STATUS\n");
                int i;
                for (i = 0; i < n_hero; i++) {
                    printf("%s\tHP:\t%d XP:\t%d\n", kahramanlar[i].name, kahramanlar[i].HP, kahramanlar[i].XP);
                    fprintf(yaz, "%s\tHP:\t%d XP:\t%d\n", kahramanlar[i].name, kahramanlar[i].HP, kahramanlar[i].XP);
                }
                printf("\n");
                fprintf(yaz, "\n");
            } else if (strcmp(CP, "MONSTER\n") == 0) { //show monster info

                printf("\tMONSTER STATUS\n");
                fprintf(yaz, "\tMONSTER STATUS\n");
                int i;
                for (i = 0; i < n_monster; ++i) {
                    printf("%s\tHP:\t%d\n", canavarlar[i].name, canavarlar[i].HP);
                    fprintf(yaz, "%s\tHP:\t%d\n", canavarlar[i].name, canavarlar[i].HP);

                }

                printf("\n");
                fprintf(yaz, "\n");
            }

        } else if (strcmp(komut, "ATTACK") == 0) {
            CP = strtok(NULL, " ");

            if (strcmp(CP, "HERO\n") == 0) {   //ATTACK HERO
                printf(">HEROES ATTACKED\n\n");
                fprintf(yaz, ">HEROES ATTACKED\n\n");
                int i,j;
                for (i = 0; i < n_hero; i++) {
                    if (kahramanlar[i].HP != 0) { //CAN KONTROL
                        for (j = 0; j < n_monster; j++) {
                            if (canavarlar[j].HP != 0) {
                                int x1 = kahramanlar[i].X;
                                int y1 = kahramanlar[i].Y;
                                int x2 = canavarlar[j].X;
                                int y2 = canavarlar[j].Y;
                                int uzaklik = sqrt(
                                        pow((x1 - x2), 2) + pow((y1 - y2), 2)); //kordinattaki iki nokta arası mesafe
                                if (uzaklik <= 1.5) {
                                    int xdamage = kahramanlar[i].DAMAGE;      //islemler bu kisimda yapildi.
                                    int yhp = canavarlar[j].HP;
                                    int xxp = kahramanlar[i].XP;
                                    yhp = yhp - xdamage;
                                    if (yhp <= 0) {  //olenlerin kontrolu yapıldi.
                                        yhp = 0;
                                        xxp = xxp + 1;
                                        matris[canavarlar[j].X][canavarlar[j].Y] = '*';
                                        livemonster = livemonster - 1;
                                    }
                                    canavarlar[j].HP = yhp;  //canavarların can bilgisi guncellendi
                                    kahramanlar[i].XP = xxp; //kahramanların xp puanı eklendi.
                                }
                            }
                        }
                    }
                }
            } else if (strcmp(CP, "MONSTER\n") == 0) { //ATTACK MONSTER
                printf(">MONSTER ATTACKED\n\n");
                fprintf(yaz, ">MONSTER ATTACKED\n\n");
                int i,j;
                for (i = 0; i < n_monster; i++) {
                    if (canavarlar[i].HP != 0) { //CAN KONTROL
                        for (j = 0; j < n_hero; j++) {
                            if (kahramanlar[j].HP != 0) {
                                int x1 = canavarlar[i].X;
                                int y1 = canavarlar[i].Y;
                                int x2 = kahramanlar[j].X;
                                int y2 = kahramanlar[j].Y;
                                int uzaklik = sqrt(
                                        pow((x1 - x2), 2) + pow((y1 - y2), 2)); //kordinattaki iki nokta arası mesafe
                                if (uzaklik <= 1.5) {
                                    int xdamage = canavarlar[i].DAMAGE;      //islemler bu kisimda yapildi.
                                    int yhp = kahramanlar[j].HP;
                                    yhp = yhp - xdamage;
                                    if (yhp <= 0) {    //Live or dead kontrol
                                        yhp = 0;
                                        matris[kahramanlar[j].X][kahramanlar[j].Y] = '*';
                                        livehero = livehero - 1;
                                    }
                                    kahramanlar[j].HP = yhp;  //struct can bilgisi guncellendi.

                                }
                            }
                        }
                    }
                }
            }
        } else if (strcmp(komut, "MOVE") == 0) {//tasıma komutu
            printf("HEROES MOVED\n");
            fprintf(yaz, "HEROES MOVED\n");
            CP = strtok(NULL, " "); //hero
            int i = 0;
            if (strcmp(CP, "HERO") == 0) {
                CP = strtok(NULL, " ");
                while (CP != NULL) { //satır sonuna kadar oku
                    char nn[25];
                    strcpy(nn, CP); //isim
                    CP = strtok(NULL, " ");
                    int nx = atoi(CP); //x kordinati
                    CP = strtok(NULL, " ");
                    int ny = atoi(CP); //y kordinati
                    int j;
                    for (j = 0; j < n_hero; j++) {
                        if (strcmp(kahramanlar[j].name, nn) == 0) {
                            if (kahramanlar[j].HP != 0) {
                                if ((nx >= satir || ny >= sutun) == 0) {
                                    int silx = kahramanlar[j].X;
                                    int sily = kahramanlar[j].Y;
                                    if (matris[nx][ny] == '*') { //dolu bos kontrol
                                        matris[silx][sily] = '*';
                                        matris[nx][ny] = kahramanlar[j].name[0];
                                        kahramanlar[j].X = nx;
                                        kahramanlar[j].Y = ny;
                                    } else {
                                        printf("%s can't move. Place is occupied.\n\n", kahramanlar[j].name);
                                        fprintf(yaz, "%s can't move. Place is occupied.\n\n", kahramanlar[j].name);
                                    }
                                } else {
                                    printf("%s can't move. There is a wall.\n\n", kahramanlar[j].name);
                                    fprintf(yaz, "%s can't move. There is a wall.\n\n", kahramanlar[j].name);
                                }
                            } else {
                                printf("%s can't move. Dead.\n\n", kahramanlar[j].name);
                                fprintf(yaz, "%s can't move. Dead.\n\n", kahramanlar[j].name);
                            }
                        }
                    }
                    CP = strtok(NULL, " "); //satir sonuna geldiginde durur.
                    if (CP == NULL)
                        break;
                }
            }
        }
        if (livehero == 0 || livemonster == 0) { //oyun biter yada devam eder.live=0 ise durur.
            if (livehero == 0) {
                printf("All Hero dead.FINISH GAME\n");
                fprintf(yaz, "All Hero are dead.FINISH GAME\n\n");
                showmap(satir, sutun, matris);
                break;
            }
            if (livemonster == 0) {
                printf("All Monster dead.FINISH GAME\n");
                fprintf(yaz, "All Monster dead.FINISH GAME\n\n");
                showmap(satir, sutun, matris);
                break;
            }
        }
    }

    fclose(yaz); //output dosyasi kapatildi
    free(matris);//mallocklar serbest birakildi.
    free(kahramanlar);//strucklar free
    free(canavarlar);//strucklar free
    return 0;
};
