#include "structures/structures.h"
#include "global/global.h"
#include "afis/afis.h"
#include "logica-joc/miscare-vulpe/miscare-vulpe.h"
#include "logica-joc/miscare-iepure/miscare-iepure.h"
#include "miscari/miscari.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

bool conditie_final_joc () {
    for (int i = 0; i < NUMAR_IEPURI; i++)
        if (iepuri[i].ingame) return false;

    return true;
}

void joc() {
    cout << "Comenzi: " << '\n';
    cout << "Tastati 'iepuri' pentru a afisa coorodonatele iepurilor: " << '\n';
    cout <<  "Tastati 'vulpi' pentru a afisa coordonatele vulpilor: " << '\n';
    cout << "Alege un tip de animal pe care doresti sa il muti. Tasteaza 'mvulpe' sau 'miepure': " << '\n';
    cout <<  "! -  Poti tasta mereu 0 si vei ajunge inapoi la meniul principal" << '\n';

    char comanda[10];
    cin >> comanda;

    if (strcmp(comanda, "iepuri") == 0) afisare_iepuri();
    if (strcmp(comanda, "vulpi") == 0) afisare_vulpi();
    if (strcmp(comanda, "miscari") == 0) afisare_miscari();
    if (strcmp(comanda, "undo") == 0) {
        undo();
        afisare_matrice();
        cout << '\n';
        afisare_miscari();
    }

    if (strcmp(comanda, "miepure") == 0) {
        cout << "Alege numarul iepurelui pe care doresti sa il muti: " << '\n';
        int nr_iepure;
        cin >> nr_iepure;

        if (nr_iepure == 0) return;

        if (!(nr_iepure >= 1 && nr_iepure <= NUMAR_IEPURI)) {
            cerr << "Nu exista acel iepure";
            return;
        }

        if (iepuri[nr_iepure - 1].ingame == false) {
            cerr << "Acest iepure a fost deja introdus intr-o gaura" << '\n';
            return;
        }

        cout << "Perfect, esti pe drumul cel bun. Alege acum o directie in care doresti sa muti iepurele.: " << '\n';
        cout << "1 - Sus" << '\n';
        cout << "2 - Dreapta" << '\n';
        cout << "3 - Jos" << '\n';
        cout << "4 - Stanga" << '\n';

        int directie;
        cin >> directie;
        if (directie == 0) return;
        saritura_iepure(iepuri[nr_iepure - 1], directie - 1, nr_iepure - 1);
        afisare_matrice();
    }

    if (strcmp(comanda, "mvulpe") == 0) {
        cout << "Selecteaza numarul vulpii pe care doresti sa o muti: " << '\n';
        int nr_vulpe;
        cin >> nr_vulpe;
        if (!(nr_vulpe >= 1 && nr_vulpe <= NUMAR_VULPI)) {
            cout << "Acea vulpe nu exista";
            return;
        }
        cout << "Perfect, esti pe drumul cel bun. Alege acum o directie in care doresti sa muti vulpea.: " << '\n';
        cout << "1 - Sus" << '\n';
        cout << "2 - Dreapta" << '\n';
        cout << "3 - Jos" << '\n';
        cout << "4 - Stanga" << '\n';

        int directie;
        cin >> directie;
        if (directie == 0) return;
        miscare_vulpe(vulpi[nr_vulpe - 1], directie - 1, nr_vulpe - 1);
        afisare_matrice();
    }

    if (strcmp(comanda, "0") == 0) {
        return;
    }
}

int main()
{
    cout << "Selecteaza nivelul dorit (1 - 15): " << '\n';
    int nivel;
    cin >> nivel;

    while (nivel < 1 || nivel > NUMAR_NIVELE) {
        cout << "Introdu un nivel valid: " << '\n';
        cin >> nivel;
    }
    cout << "Mapa de joc este urmatoarea: " << '\n';
    initializare_matrice(nivel);
    afisare_matrice();
    cout << '\n';

    cout << "Informatii utile pentru joc: " << '\n';
    cout << "Cu -1 sunt notate gaurile, cu 0 campurile libere, cu 1 iepurii, cu 2 vulpile si cu 3 ciupercile" << '\n';
    cout << "Atat vulpile cat si iepurii sunt numerotati de la stanga la dreapta de sus in jos" << '\n';

    while (!conditie_final_joc()) joc();

    if (conditie_final_joc()) cout << "Felicitari! Toti iepurii au intrat in gauri.";
    return 0;
}