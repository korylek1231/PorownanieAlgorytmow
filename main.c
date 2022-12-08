#include <stdio.h>
#include "time.h"
#include "stdlib.h"

/* POROWNANIE ALGORYTMU BABELKOWEGO Z ALGORYTMEM PRZEZ WSTAWIENIE */

void swap(int i, int j, int tab[]){
    int temp;
    temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
} //funkcja zamieniania miejscami

void SortowaniePrzezWstawianie(int *array, int wielkosc)
{
    int j,temp,i;
    for(j = wielkosc - 2; j >= 0; j--)
    {
        temp = array[j]; //ten element bedzie wstawiony w odpowiednie miejsce
        i = j + 1;
        while((i < wielkosc) && (temp > array[i])) //przesowanie elementow wiekszych od temp
        {
            array[i - 1] = array[i]; //przesuwanie elementow
            i++;
        }
        array[i - 1] = temp; //wstawienie temp w odpowiednie miejsce
    }
}

void SortowanieBabelkowe(int tab[], int size){
    for( int i = 0; i < size; i++ )
    {
        for( int j = 0; j < size-i-1; j++ ) //dzieki pomniejszaniu o i algorytm wykonuje mniej petli
        {
            if(tab[j] > tab[j+1] ) //sprawdzanie czy kolejny element jest mniejszy od poprzedniego
                swap( j, j + 1 ,tab); //zamiana elementow miejscami

        }
    }
}

int main() {
    int iloscciagow = 6;
    int dlugoscciagu = 10;
    int ciag[dlugoscciagu];
    int ciag2[dlugoscciagu];
    unsigned long long a;
    srand(time(NULL));

    FILE *array;
    FILE *bubble;
    FILE *selection;
    array = fopen("wygenerowaneciagi.txt", "a");
    bubble = fopen("sortowanieBabelkowe.txt","a");
    selection = fopen("sortowaniePrzezWstawianie.txt","a"); //otwarcie plikow

    for(int i = 0; i < iloscciagow; i++){
        for(int j = 0; j < dlugoscciagu; j++){
            ciag[j] = rand()%100;
            fprintf(array, "%d ", ciag[j]);
        }
        fprintf(array, "%s", "\n");
    } //generowanie ciagow do pliku

    fclose(array);
    array = fopen("wygenerowaneciagi.txt", "r"); //otwarcie pliku z danymi

    for(int k =0 ; k < iloscciagow; k++) {

        for (int j = 0; j < dlugoscciagu; j++) {
            fscanf(array, "%d", &ciag[j]);
             ciag2[j] = ciag[j];
        } //wczytanie ciagu z pliku

        SortowanieBabelkowe(ciag,dlugoscciagu); //sortowanie babelkowe
        SortowaniePrzezWstawianie(ciag2,dlugoscciagu); //sortowanie przez wstawianie

        for(int i = 0; i < dlugoscciagu; i++){
            fprintf(bubble, "%d ", ciag[i]);
            fprintf(selection, "%d ", ciag2[i]); //zapis posortowanego ciagu do pliku
        }

        fprintf(bubble, "%s", "\n");
        fprintf(selection, "%s", "\n"); //znak nowej lini

        for(int i = 0; i < 2; i++){
            a = ftell(array);
        }
        fseek(array, a+1,0);
        a += ftell(array); //przesowanie znacznika na poczatek lini kolejnego ciagu

    }
    fclose(bubble);
    fclose(selection);
    fclose(array); //zamkniecie plikow
    return 0;
}
