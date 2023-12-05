#include <stdio.h>
#include <stdlib.h>

/* Eine globale Variable, die initialisiert wird */
int globalVar1 = 42;

/* Eine globale Variable, die nicht initialisiert wird */
int globalVar2;

// gloale Konstante
const int globalKonstVar = 100;



void funktionBeispiel() {
    /* Eine lokale Variable in einer Funktion */
    int lokalVar1 = 10;


    /* Eine lokale, static-Variable */
    static int statischVar = 20;

    printf("Lokale Variable in der Funktion: %p\n", (void*)&lokalVar1);
    printf("Statische lokale Variable in der Funktion: %p\n", (void*)&statischVar);
}

int main() {
    /* Adressen der globalen Variablen ausgeben */
    printf("Global initialisierte Variable: %p\n", (void*)&globalVar1);
    printf("Global nicht initialisierte Variable: %p\n", (void*)&globalVar2);
    printf("Globale Konstante Variable: %p\n", (void*)&globalKonstVar);

    /* Adressen des dynamisch allozierten Speichers ausgeben */
    int *dynamicMemory = (int *)malloc(sizeof(int));
    printf("Dynamisch alloziierter Speicher: %p\n", (void*)dynamicMemory);
    free(dynamicMemory); // Speicher freigeben

    /* Adressen einer Funktion und einer Funktion aus der Standardbibliothek ausgeben */
    printf("Adresse der Hauptfunktion: %p\n", (void*)main);
    printf("Adresse der printf-Funktion: %p\n", (void*)printf);

    /* Die Funktion aufrufen, um lokale Variablen in ihr zu erstellen und deren Adressen auszugeben */
    funktionBeispiel();

    return 0;
}

// Ausgabe:
/*
Global initialisierte Variable: 0x55c3dfc3a038
Global nicht initialisierte Variable: 0x55c3dfc3a044
Globale Konstante Variable: 0x55c3dfc38008
Dynamisch alloziierter Speicher: 0x55c3e08856b0
Adresse der Hauptfunktion: 0x55c3dfc37187
Adresse der printf-Funktion: 0x7fb24f886cf0
Lokale Variable in der Funktion: 0x7ffff9ea436c
Statische lokale Variable in der Funktion: 0x55c3dfc3a03c
 */