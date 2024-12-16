#ifndef MISCARE_VULPE_H
#define MISCARE_VULPE_H

#include "../../structures/structures.h"

bool verificare_miscare_vulpe(int xnou, int ynou);
void miscare_valoare_negativa(vulpe &vulp, int directie);
void miscare_valoare_pozitiva (vulpe &vulp, int directie);
void miscare_vulpe(vulpe &vulp, int directie, int index);

#endif //MISCARE_VULPE_H