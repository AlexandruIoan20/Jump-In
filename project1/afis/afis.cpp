#include "afis.h"

#include <iostream>
#include <iomanip>
#include "../structures/structures.h"
#include "../global/global.h"
using namespace std;

void afisare_iepuri() {
    cout << "Numar iepuri: " << NUMAR_IEPURI << '\n';
    cout << "IEPURI: " << '\n';
    for (int i = 0; i < NUMAR_IEPURI; i++) {
        cout << "iepuri[" << i << "].ingame: " << iepuri[i].ingame << '\n';
        cout << "iepuri[" << i  << "].x: " << iepuri[i].x << '\n';
        cout << "iepuri[" << i  << "].y: " << iepuri[i].y << '\n';
        cout << '\n';
    }

    cout << '\n';
}

void afisare_vulpi() {
    cout << "Numar vulpi: " << NUMAR_VULPI << '\n';
    cout << "VULPI: " << '\n';
    for (int i = 0; i < NUMAR_VULPI; i++) {
        cout << "vulpi[" << i  << "].orientare: " << vulpi[i].orientare << '\n';
        cout << "vulpi[" << i  << "].x1: " << vulpi[i].x1 <<  " vulpi[" << i  << "].y1: " << vulpi[i].y1 << '\n';
        cout << "vulpi[" << i  << "].x2: " << vulpi[i].x2 <<  " vulpi[" << i  << "].y2: " << vulpi[i].y2 << '\n';
        cout << '\n';
    }

    cout << '\n';
}

void afisare_matrice() {
    cout << "    ";
    for (int j = 0; j < N; j++) {
        cout << setw(3) << j;
    }
    cout << '\n';

    cout << "   ";
    for (int j = 0; j < N; j++) {
        cout << "---";
    }
    cout << '\n';

    for (int i = 0; i < N; i++) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < N; j++) {
            cout << setw(3) << matrice_joc[i][j].val;
        }
        cout << '\n';
    }
}