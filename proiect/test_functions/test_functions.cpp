#include <iostream>
#include <iomanip>
#include "test_functions.h"
using namespace std;

void afisare_iepuri() {
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
    cout << "VULPI: " << '\n';
    for (int i = 0; i < NUMAR_VULPI; i++) {
        cout << "vulpi[" << i  << "].orientare: " << vulpi[i].orientare << '\n';
        cout << "vulpi[" << i  << "].x1: " << vulpi[i].x1 <<  " vulpi[" << i  << "].y1: " << vulpi[i].y1 << '\n';
        cout << "vulpi[" << i  << "].x2: " << vulpi[i].x2 <<  " vulpi[" << i  << "].y2: " << vulpi[i].y2 << '\n';
        cout << '\n';
    }

    cout << '\n';
}