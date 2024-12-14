//
// Created by ialex on 14.12.2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H

#include "../structures/structures.h"

// Vectori de directie
extern const int dx[5];
extern const int dy[5];

// Valori in matrice dupa care sunt recunoscute fiecare obiecte
extern const int VALOARE_GAURA;
extern const int VALOARE_IEPURE;
extern const int VALOARE_VULPE;
extern const int VALOARE_CIUPERCA;

// Numarul de obiecte in functie de nivel
extern int NUMAR_IEPURI;
extern int NUMAR_VULPI;
extern int NUMAR_CIUPERCI;

// Tabla este o matrice patratica de dimensiune N x N
extern const int N; // maxim 5

extern iepure iepuri[11];
extern vulpe vulpi[11];
extern ciuperca ciuperci[11];

extern camp matrice_joc[5][5];

#endif //GLOBALS_H
