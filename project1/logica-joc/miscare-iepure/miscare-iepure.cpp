#include "miscare-iepure.h"

#include "../../global/global.h"
#include "../../structures/structures.h"
#include "../../utils/utils.h"
#include "../../miscari/miscari.h"
#include <iostream>
using namespace std;

void verificare_iepure_in_gaura(iepure &iep) {
    if (matrice_joc[iep.x][iep.y].este_gaura && !matrice_joc[iep.x][iep.y].este_ocupat) {
        iep.ingame = false;
        matrice_joc[iep.x][iep.y].este_ocupat = true;
        matrice_joc[iep.x][iep.y].val = -1;

        cout << "Felicitari, un iepure a intrat in gaura." << '\n';
    }
}

void saritura_iepure(iepure &iep, int directie) {
    // Daca sunt doi iepuri unul langa altul ( afara din matrice | iepure iepure )
    // si pe cel din dreapta il mutam in stanga, va iesi de tot din matrice
    if (iep.ingame == false) {
        cout << "Acel iepure a fost deja introdus intr-o gaura";
        return;
    }

    int xnou = iep.x + dx[directie], ynou = iep.y + dy[directie];
    if (!inmat(xnou, ynou)) {
        cerr << "Iepurele nu poate sari deoarece va iesi de pe teren." << '\n';
        return;
    }

    if (matrice_joc[xnou][ynou].val == 0 || matrice_joc[xnou][ynou].val == VALOARE_GAURA && matrice_joc[xnou][ynou].este_ocupat == false) {
        cerr << "Iepurele nu poate avansa deoarece nu are peste ce sari.";
        return;
    }

    while(
        inmat(xnou, ynou) && matrice_joc[xnou][ynou].val != 0
        ) {
        if (matrice_joc[xnou][ynou].val == VALOARE_GAURA && !matrice_joc[xnou][ynou].este_ocupat) break;
        xnou = xnou + dx[directie];
        ynou = ynou + dy[directie];
        }

    if (!inmat(xnou, ynou)) {
        cerr << "Iepurele iese din matrice" << '\n';
        return;
    }

    matrice_joc[iep.x][iep.y].val = 0;
    inregistrare_miscare_iepure(iep, iep.x, iep.y);

    iep.x = xnou;
    iep.y = ynou;

    matrice_joc[iep.x][iep.y].val = VALOARE_IEPURE;
    verificare_iepure_in_gaura(iep);

    cout << '\n';
}


