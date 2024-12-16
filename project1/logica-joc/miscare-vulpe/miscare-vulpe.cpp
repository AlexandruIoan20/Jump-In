#include "miscare-vulpe.h"

#include <iostream>
#include "../../structures/structures.h"
#include "../../global/global.h"
#include "../../utils/utils.h"
#include "../../miscari/miscari.h"
using namespace std;

bool verificare_miscare_vulpe(int xnou, int ynou) {
    return inmat(xnou, ynou) && matrice_joc[xnou][ynou].val == 0;
}

void miscare_valoare_negativa(vulpe &vulp, int directie) { // Functie apelata cand la pozitia din vectorul de directii exista -1
    int xnou = vulp.x1 + dx[directie];
    int ynou = vulp.y1 + dy[directie];

    if (!verificare_miscare_vulpe(xnou, ynou)) {
        cerr << "Vulpea este oprita de un obstacol si nu poate sa se miste";
        return;
    }

    matrice_joc[vulp.x2][vulp.y2].val = 0;
    vulp.x2 = vulp.x1;
    vulp.y2 = vulp.y1;

    matrice_joc[xnou][ynou].val = VALOARE_VULPE;
    vulp.x1 = xnou;
    vulp.y1 = ynou;
}

void miscare_valoare_pozitiva (vulpe &vulp, int directie) {
    cout << "Test valoare pozitiva" << '\n'; // Functie apelata cand la pozitia din vectorul de directii exista 1
    int xnou = vulp.x2 + dx[directie];
    int ynou = vulp.y2 + dy[directie];

    if (!verificare_miscare_vulpe(xnou, ynou)) {
        cerr << "Vulpea este oprita de un obstacol si nu poate sa se miste";
        return;
    }

    // Campul x1 devine null
    matrice_joc[vulp.x1][vulp.y1].val = 0;
    vulp.x1 = vulp.x2;
    vulp.y1 = vulp.y2;

    // Pe urmatorul camp este recunoscuta vulpea
    matrice_joc[xnou][ynou].val = VALOARE_VULPE;
    vulp.x2 = xnou;
    vulp.y2 = ynou;
}

void miscare_vulpe(vulpe &vulp, int directie) {
    if ((vulp.orientare == 'O' && (directie == 0 || directie == 2)) ||
        (vulp.orientare == 'V' && (directie == 1 || directie == 3))) {
        cout << "Miscarea vulpii pe acea directie nu este posibila" << '\n';
        return;
        }

    int x1 = vulp.x1, x2 = vulp.x2, y1 = vulp.y1, y2 = vulp.y2;

    // Miscarea vulpii pe orizontala
    if (directie < 0 || directie > 3) {
        cout << "Directia introdusa nu este valida" << '\n';
        return;
    }

    if (directie == 0 || directie == 3) miscare_valoare_negativa(vulp, directie);
    else if (directie == 1 || directie == 2) miscare_valoare_pozitiva(vulp, directie);

    inregistrare_miscare_vulpe(vulp, x1, x2, y1, y2);
    cout << '\n';
}