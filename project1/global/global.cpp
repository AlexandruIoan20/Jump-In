#include "global.h"
#include "../utils/utils.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <queue>
using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

const int VALOARE_GAURA = -1;
const int VALOARE_IEPURE = 1;
const int VALOARE_VULPE = 2;
const int VALOARE_CIUPERCA = 3;

int NUMAR_IEPURI = 0;
int NUMAR_VULPI = 0;
int NUMAR_CIUPERCI = 0;

const int N = 5;

iepure iepuri[11];
vulpe vulpi[11];
ciuperca ciuperci[11];

camp matrice_joc[5][5];

void initializare_matrice(int numar_nivel) {
    string nume_fisier = "../nivele/nivel" + to_string(numar_nivel) + ".txt";
    ifstream fin(nume_fisier);

    cout << "nume fisier:" << nume_fisier << '\n';
    queue <int> q;

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

          if(valoare == VALOARE_VULPE) {
                bool este_x2 = false;
                for(int k = 1; k < 4 && !este_x2; k += 2) {
                    int xnou = i + dx[k];
                    int ynou = j + dy[k];
                    if(inmat(xnou, ynou) && matrice_joc[xnou][ynou].val == VALOARE_VULPE) este_x2 = true;
                }

                if(!este_x2) {
                    q.push(NUMAR_VULPI);
                    vulpi[NUMAR_VULPI].x1 = i;
                    vulpi[NUMAR_VULPI].y1 = j;
                    NUMAR_VULPI++;
                } else {
                    vulpi[q.front()].x2 = i;
                    vulpi[q.front()].y2 = j;
                    q.pop();
                }
          }

          if(valoare == VALOARE_CIUPERCA) {
                ciuperci[NUMAR_CIUPERCI].x = i;
                ciuperci[NUMAR_CIUPERCI].y = j;
                NUMAR_CIUPERCI++;
          }
    }

    fin.close();
}