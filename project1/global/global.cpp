#include "global.h"
#include <iostream>
using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

const int VALOARE_GAURA = -1;
const int VALOARE_IEPURE = 1;
const int VALOARE_VULPE = 2;
const int VALOARE_CIUPERCA = 3;

int NUMAR_IEPURI = 3;
int NUMAR_VULPI = 2;
int NUMAR_CIUPERCI = 2;

const int N = 5;

iepure iepuri[11];
vulpe vulpi[11];
ciuperca ciuperci[11];

camp matrice_joc[5][5];