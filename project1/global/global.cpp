#include "global.h"
#include <iostream>
#include <fstream>
using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

utilizator utilizatori[101];
int numar_utilizatori = 0;

const int VALOARE_GAURA = -1;
const int VALOARE_IEPURE = 1;
const int VALOARE_VULPE = 2;
const int VALOARE_CIUPERCA = 3;
const int VALOARE_CAMP_GOL = 0;

const int NUMAR_NIVELE=12;
int NUMAR_IEPURI = 0;
int NUMAR_VULPI = 0;
int NUMAR_CIUPERCI = 0;

const int N = 5;

iepure iepuri[11];
vulpe vulpi[11];
ciuperca ciuperci[11];

camp matrice_joc[5][5];
miscare miscari[101];

int numar_miscari = 0;

void initializare_matrice(int numar_nivel) {
    string nume_fisier = "../nivele/nivel" + to_string(numar_nivel) + ".txt";
    ifstream fin(nume_fisier);

    cout << "nume fisier:" << nume_fisier << '\n';

    int valoare;
    for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++) {
           fin >> valoare;
           matrice_joc[i][j].val = valoare;

           matrice_joc[i][j].este_gaura = false;
           if(valoare == VALOARE_GAURA) {
               matrice_joc[i][j].este_gaura = true;
               matrice_joc[i][j].este_ocupat = false;
          }

          if(valoare == VALOARE_IEPURE) {
            iepuri[NUMAR_IEPURI].x = i;
            iepuri[NUMAR_IEPURI].y = j;
            iepuri[NUMAR_IEPURI].ingame = true;
            NUMAR_IEPURI++;
          }

          if(valoare == VALOARE_CIUPERCA) {
                ciuperci[NUMAR_CIUPERCI].x = i;
                ciuperci[NUMAR_CIUPERCI].y = j;
                NUMAR_CIUPERCI++;
          }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if(matrice_joc[i][j].val == VALOARE_VULPE) {
                int x1 = i + dx[1];
                int y1 = j + dy[1];

                int x2 = i + dx[2];
                int y2 = j + dy[2];

                if (matrice_joc[x1][y1].val == VALOARE_VULPE || matrice_joc[x2][y2].val == VALOARE_VULPE) {
                    vulpi[NUMAR_VULPI].x1 = i;
                    vulpi[NUMAR_VULPI].y1 = j;
                    if (matrice_joc[x1][y1].val == VALOARE_VULPE) {
                        vulpi[NUMAR_VULPI].x2 = x1;
                        vulpi[NUMAR_VULPI].y2 = y1;
                        vulpi[NUMAR_VULPI].orientare = 'O';
                    } else if (matrice_joc[x2][y2].val == VALOARE_VULPE) {
                        vulpi[NUMAR_VULPI].x2 = x2;
                        vulpi[NUMAR_VULPI].y2 = y2;
                        vulpi[NUMAR_VULPI].orientare = 'V';
                    }

                    NUMAR_VULPI++;
                }
            }
        }

    fin.close();
}