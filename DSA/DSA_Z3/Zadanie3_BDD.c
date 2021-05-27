//Marcel Valent
//DSA_Zadanie_3-Binarne_rozhodovacie_diagramy
//LS 2020/2021
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//Definovanie struktur ktore budeme pouzivat v projekte
typedef struct node {
    struct node* pravy;
    struct node* lavy;
    char data;
} NODE;
typedef struct bdd {
    int pocet_premennych;
    int uzly;
    NODE* hlavicka;
}BDD;

//pomocne funkcie
void binary(int cislo, int bites, char* pomocnepole) {
    for (int i = bites; i > 0; i--) {
        pomocnepole[i - 1] = cislo % 2;
        cislo /= 2;
    }
}

// BDD
BDD* BDD_create(char* bfunkcia) {
    int mocnina = 2;
    int n = 1;
    BDD* temp;
    temp = (BDD*)malloc(sizeof(BDD));
    temp->hlavicka = malloc(sizeof(NODE));
    temp->hlavicka->lavy = NULL;
    temp->hlavicka->pravy = NULL;
    temp->hlavicka->data = 5;
    while ((mocnina) <= strlen(bfunkcia)) {//while cyklus na zistenie poctu premennych
        if ((mocnina) == strlen(bfunkcia)) {
            temp->pocet_premennych = n;
            break;
        }
        n++;
        mocnina = 2 * mocnina;
    }
    if ((mocnina) > strlen(bfunkcia)) {//pripad kedy sa neda vytvorit BDD 
        printf("Zo vstupu sa nedá vytvori BDD.\n");
        return NULL;
    }
    char* binarka = malloc(sizeof(char) * temp->pocet_premennych);//alokovanie pomocneho pola
    for (int i = 0; i < strlen(bfunkcia); i++) {
        binary(i, temp->pocet_premennych, binarka);// prevedenie vektora na 1 a 0 za  pomocie funkcie binary,nasledne pomocne pole binarka pouzivame na vytvaranie BDD 
        NODE* temporary = temp->hlavicka;
        for (int k = 0; k < temp->pocet_premennych; k++) {//cyklus na vytvaranie BDD 
            if (binarka[k] == 0) {
                if (temporary->lavy == NULL) {
                    temporary->lavy = malloc(sizeof(NODE));
                    temporary->lavy->pravy = NULL;
                    temporary->lavy->lavy = NULL;
                    temporary->lavy->data = 5;
                }
                temporary = temporary->lavy;
            }
            if (binarka[k] == 1) {
                if (temporary->pravy == NULL) {
                    temporary->pravy = malloc(sizeof(NODE));
                    temporary->pravy->pravy = NULL;
                    temporary->pravy->lavy = NULL;
                    temporary->pravy->data = 5;
                }
                temporary = temporary->pravy;
            }
        }
        temporary->data = bfunkcia[i];
    }
    free(binarka);
    return temp;// funkcia vracia vytvoreny BDD
}
char BDD_use(BDD* bdd, char* vstupy) {
    //osetrenie ci sme dostali platny pointer na koren BDD, a ci dlzka vstupu sa rovna poctu premennych ulozenemu v BDD
    if (bdd->hlavicka == NULL) {
        return -1;
    }
    if (strlen(vstupy) != bdd->pocet_premennych) {
        return -1;
    }
    //prehladavanie BDDD
    NODE* temp = bdd->hlavicka;
    for (int i = 0; i < bdd->pocet_premennych; i++) {
        if (vstupy[i] == '0') {
            temp = temp->lavy;
        }
        if (vstupy[i] == '1') {
            temp = temp->pravy;
        }
    }
    return temp->data;//navrati hodnotu daneho listu 
}

//testovaè
//pomocna funkcia na uvolnovanie vytvoreneho BDD
void BDD_free(NODE* koren) {
    if (koren == NULL) {
        return;
    }
    BDD_free(koren->lavy);
    BDD_free(koren->pravy);
    free(koren);
}
//tato pomocna funkcia sluzi na randomne vygenerovanie vektora Booleovskej funkcie, podla ktorej sa vytvori BDD
char* testhelp1(int pocetpremennych) {
    int i = 0;
    int x = pow(2, pocetpremennych);
    char* funkcia = malloc(x * sizeof(char)); //alokovanie miesta pre vysledny vektor
    //nahodne generovanie 1 a 0 a ich ukladanie
    for (i ; i < x; ++i) {
        funkcia[i] = ((rand() % 2) + '0');
    }
    funkcia[i] = '\0';//na koniec vlozime znak ukoncenia stringu a tym sa z pola charov stane plnohodnotny string (aby sme mohli pouzit strlen)
    return funkcia;
}
// táto pomocná funkcia testovaèu slúži na randomné vygenerovanie hodnot premennych Booleovskej funkcie, ktoré budeme kontrolovat 
char* testhelp2(int pocetpremennych) {
    int i = 0;
    char* testovanafunkcia = malloc((pocetpremennych) * sizeof(char));//alokovanie miesta pre vysledne hodnoty premennych
    //nahodne generovanie 1 a 0 a ich ukladanie
    for (i = 0; i < pocetpremennych; ++i) {
        testovanafunkcia[i] = ((rand() % 2)+'0');
    }
    testovanafunkcia[i] = '\0';//na koniec vlozime znak ukoncenia stringu a tym sa z pola charov stane plnohodnotny string (aby sme mohli pouzit strlen)
    return testovanafunkcia;
}
//samotný testovaè v ktorom využijeme pomocné funkcie testhelp1 a testhelp 2
void test(int numofVars, int numofTries) {
    double time_all = 0;
    double average_time = 0;
    printf("Please wait :)\n");
    if(numofVars>0 && numofTries>0){
        for (int k = 0; k < numofTries; k++) {
            clock_t begin = clock();
            BDD* strom = BDD_create(testhelp1(numofVars));//testovanie vytvarania stromu
            BDD_use(strom,testhelp2(numofVars));
            BDD_free(strom->hlavicka);
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //vypocet casu kolko trval dany strom
            time_all = time_all + time_spent;//celkovy cas
            time_spent = 0;
        }
        average_time = (time_all / numofTries);//priemerny cas
        printf("\nPriemerny cas BDD je: %.3lf sekund", average_time);
        printf("\nTestovanie BDD o %d premennych s poctom opakovani %d trvalo: %.3lf sekund.\n\n", numofVars, numofTries, time_all);
        return;
    }
    else {
        printf("\nPocet premennych a pocet opakovani musi byt vacsi ako 0.\n");
    }
}

int main() {
    //For testing: launch args are (numOfVars,numOfTries)
    test(13, 2000);
    return 0;
}