#include "miscari.h"
#include <iostream>

#include "../structures/structures.h"
#include "../global/global.h"
#include "../afis/afis.h"
using namespace std;

void inregistrare_miscare_iepure (iepure iep, int x_vechi, int y_vechi, int index) {
    miscari[numar_miscari].obiect = 'I';
    miscari[numar_miscari].index_iepure = index;
    miscari[numar_miscari].index_vulpe = -1;

    miscari[numar_miscari].coordonate_vechi.x = x_vechi;
    miscari[numar_miscari].coordonate_vechi.y = y_vechi;

    miscari[numar_miscari].coordonate_vechi2.x = -1;
    miscari[numar_miscari].coordonate_vechi2.y = -1;

    miscari[numar_miscari].coordonate_noi.x = iep.x;
    miscari[numar_miscari].coordonate_noi.y = iep.y;

    miscari[numar_miscari].coordonate_noi2.x = -1;
    miscari[numar_miscari].coordonate_noi2.y = -1;

    numar_miscari++;
}

void inregistrare_miscare_vulpe(vulpe vulp, int x_vechi1, int x_vechi2, int y_vechi1, int y_vechi2, int index) {
  miscari[numar_miscari].obiect = 'V';

  miscari[numar_miscari].index_vulpe = index;
  miscari[numar_miscari].index_iepure = -1;

  miscari[numar_miscari].coordonate_vechi.x = x_vechi1;
  miscari[numar_miscari].coordonate_vechi.y = y_vechi1;

  miscari[numar_miscari].coordonate_vechi2.x = x_vechi2;
  miscari[numar_miscari].coordonate_vechi2.y = y_vechi2;

  miscari[numar_miscari].coordonate_noi.x = vulp.x1;
  miscari[numar_miscari].coordonate_noi.y = vulp.y1;

  miscari[numar_miscari].coordonate_noi2.x = vulp.x2;
  miscari[numar_miscari].coordonate_noi2.y = vulp.y2;

  numar_miscari++;
}

void undo() {
    // Se ia ultima miscare facuta de utilizator
    miscare miscare_curenta = miscari[numar_miscari - 1];
    numar_miscari--;

    if(miscare_curenta.index_iepure == 0 && miscare_curenta.index_vulpe == 0) return;

    // Daca ultima miscare a fost cu un iepure
    if(miscare_curenta.index_iepure != -1) {
         iepure iepure_curent = iepuri[miscare_curenta.index_iepure];

         if(matrice_joc[iepure_curent.x][iepure_curent.y].este_gaura) { // Cazul in care miscarea a reprezentat intrarea unui iepure intr-o gaura
             matrice_joc[iepure_curent.x][iepure_curent.y].este_ocupat = false;
             matrice_joc[iepure_curent.x][iepure_curent.y].val = VALOARE_GAURA;
             iepure_curent.ingame = true;
         } else matrice_joc[iepure_curent.x][iepure_curent.y].val = VALOARE_CAMP_GOL; // Cazul in care iepurele a ajuns pe alt camp gol

         // Iepurele se duce inapoi la coordonatele vechi
         iepure_curent.x = miscare_curenta.coordonate_vechi.x;
         iepure_curent.y = miscare_curenta.coordonate_vechi.y;

        // Actualizare in matrice a valorii pe coordonatele vechi a iepurelui
        matrice_joc[iepure_curent.x][iepure_curent.y].val = VALOARE_IEPURE;

         iepuri[miscare_curenta.index_iepure] = iepure_curent;
    }

    if(miscare_curenta.index_vulpe != -1) {
        vulpe vulpe_curenta = vulpi[miscare_curenta.index_vulpe];

        // Stergere din matricea de joc a valorilor pe care se afla vulpea
        matrice_joc[vulpe_curenta.x1][vulpe_curenta.y1].val = VALOARE_CAMP_GOL;
        matrice_joc[vulpe_curenta.x2][vulpe_curenta.y2].val = VALOARE_CAMP_GOL;

        // Actualizarea coorodonatelor vulpii cu cele vechi
        vulpe_curenta.x1 = miscare_curenta.coordonate_vechi.x;
        vulpe_curenta.y1 = miscare_curenta.coordonate_vechi.y;
        vulpe_curenta.x2 = miscare_curenta.coordonate_vechi2.x;
        vulpe_curenta.y2 = miscare_curenta.coordonate_vechi2.y;

        // Actualizarea matricei cu valorile pe coordonatele vechi ale vulpii
        matrice_joc[vulpe_curenta.x1][vulpe_curenta.y1].val = VALOARE_VULPE;
        matrice_joc[vulpe_curenta.x2][vulpe_curenta.y2].val = VALOARE_VULPE;

        // Introducerea inapoi in vector
        vulpi[miscare_curenta.index_vulpe] = vulpe_curenta;
    }
}
