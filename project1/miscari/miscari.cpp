#include "miscari.h"
#include <iostream>

#include "../structures/structures.h"
#include "../global/global.h"
using namespace std;

void inregistrare_miscare_iepure (iepure iep, int x_vechi, int y_vechi) {
    miscari[numar_miscari].obiect = 'I';
    // miscari[numar_miscari].index_iepure =
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

void inregistrare_miscare_vulpe(vulpe vulp, int x_vechi1, int x_vechi2, int y_vechi1, int y_vechi2) {
  miscari[numar_miscari].obiect = 'V';

  // miscari[numar_miscari].index_vulpe =
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
