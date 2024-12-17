//
// Created by ialex on 14.12.2024.
//

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../structures/structures.h"

extern const int dx[4];
extern const int dy[4];

extern utilizator utilizatori[101];
extern int numar_utilizatori;

extern const int VALOARE_GAURA;
extern const int VALOARE_IEPURE;
extern const int VALOARE_VULPE;
extern const int VALOARE_CIUPERCA;
extern const int VALOARE_CAMP_GOL;

extern const int NUMAR_NIVELE;
extern int NUMAR_IEPURI;
extern int NUMAR_VULPI;
extern int NUMAR_CIUPERCI;

extern const int N;

extern iepure iepuri[11];
extern vulpe vulpi[11];
extern ciuperca ciuperci[11];

extern miscare miscari[101];
extern int numar_miscari;

extern camp matrice_joc[5][5];
void initializare_matrice(int numar_nivel);

#endif //GLOBAL_H
