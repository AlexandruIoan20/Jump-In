#include "structures/structures.h"
#include "global/global.h"
#include "afis/afis.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

vector<pair<int, int>> COORDONATE_GAURI;

void citesteProvocareDinFisier(const string& numeFisier) {
    ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        cout << "Eroare! Nu am putut deschide fisierul: " << numeFisier << endl;
        return;
    }

    /// Citirea valorilor pentru matricea de joc
    int liepuri = 0;
    int lvulpi = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fisier >> matrice_joc[i][j].val;

            /// Setăm valorile implicite pentru câmpurile `este_gaura` și `este_ocupat`
            if (matrice_joc[i][j].val == -1) {
                matrice_joc[i][j].este_gaura = true;
                matrice_joc[i][j].este_ocupat = false;
            }

            if (matrice_joc[i][j].val == VALOARE_IEPURE) {
                iepuri[liepuri].x = i;
                iepuri[liepuri].y = j;

                liepuri++;
            } else if (matrice_joc[i][j].val == VALOARE_VULPE) {
                // todo
            }
        }
    }
    fisier.close();
}

/// Funcție pentru a începe jocul
void incepere_joc() {
    int nrProvocare;
    cout << "Selecteaza una dintre provocari:" << endl;
    cout << "1) Provocare 1" << endl;
    cout << "2) Provocare 2" << endl;
    cout << "3) Provocare 3" << endl;
    cin >> nrProvocare;

    string numeFisier;
    switch (nrProvocare) {
        case 1:
            cout << "Ai selectat Provocare 1." << endl;
        numeFisier = "Provocare1.txt";
        citesteProvocareDinFisier(numeFisier);
        break;
        case 2:
            cout << "Ai selectat Provocare 2." << endl;
        numeFisier = "Provocare2.txt";
        citesteProvocareDinFisier(numeFisier);
        break;
        case 3:
            cout << "Ai selectat Provocare 3." << endl;
        numeFisier = "Provocare3.txt";
        citesteProvocareDinFisier(numeFisier);
        break;
        default:
            cout << "Optiune invalida. Te rog selecteaza un numar intre 1 si 3." << endl;
    }
}

void asezare_piese () {
    // to do
    // pe baza unui anumit input obiectul trebuie asezat in matrice ( in functie de coordonate ).
        // trebuie actualizate si coordonatele din matrice si coordonatele din structura
}

bool conditie_final_joc () {
    for (int i = 0; i < NUMAR_IEPURI; i++)
        if (iepuri[i].ingame) return false;

    return true;
}

bool inmat(int x, int y) {
    return (x >= 0 && x <= N - 1 && y >= 0 && y <= N - 1);
}

void plasare_iepure(int x, int y, iepure iep) {
    if(matrice_joc[x][y].val != VALOARE_IEPURE){
        cerr << "Eroare la adaugarea unui iepure. Acest loc este deja ocupat";
        return;
    }

    iep.x = x;
    iep.y = y;
    matrice_joc[x][y].val = VALOARE_IEPURE;
}

void plasare_vulpe (int x, int y, char orientare, vulpe vulp) {
    int x1,y1;
    x1=x, y1=y;
    if(orientare=='O')
        y1++;
    if(orientare=='V')
        x1++;
    if(matrice_joc[x][y].este_ocupat && matrice_joc[x1][y1].este_ocupat){
        cerr << "Eroare la adaugarea unei vulpi. Acest loc este deja ocupat.";
        return;
    }
    vulp.x1=x;
    vulp.y1=y;
    vulp.x2=x1;
    vulp.y2=y1;
    matrice_joc[x][y].este_ocupat = true;
    matrice_joc[x][y].val = VALOARE_VULPE;
    matrice_joc[x1][y1].este_ocupat = true;
    matrice_joc[x1][y1].val = VALOARE_VULPE;
}

void plasare_ciuperca(int x, int y, ciuperca ciup) {
    if (matrice_joc[x][y].este_ocupat) {
        cerr << "Eroare la adaugarea unei ciuperci. Acest loc este deja ocupat.";
        return;
    }
    ciup.x=x;
    ciup.y=y;
    matrice_joc[x][y].este_ocupat = true;
    matrice_joc[x][y].val = VALOARE_CIUPERCA;
}

void hardcoding_exemplu_youtube_obiecte () {
    // Hardcoding pentru testare de joc
    matrice_joc[0][3].val = matrice_joc[2][4].val = matrice_joc[4][1].val = VALOARE_IEPURE;
    iepuri[0].x = 0;
    iepuri[0].y = 3;
    iepuri[1].x = 2;
    iepuri[1].y = 4;
    iepuri[2].x = 4;
    iepuri[2].y = 1;

    matrice_joc[1][3].val = matrice_joc[4][2].val = VALOARE_CIUPERCA;

    matrice_joc[0][1].val = matrice_joc[1][1].val = VALOARE_VULPE;
    vulpi[0].orientare = 'V';
    vulpi[0].x1 = 0;
    vulpi[0].y1 = 1;
    vulpi[0].x2 = 1;
    vulpi[0].y2 = 1;

    matrice_joc[3][3].val = matrice_joc[3][4].val = VALOARE_VULPE;
    vulpi[1].orientare = 'O';
    vulpi[1].x1 = 3;
    vulpi[1].y1 = 3;
    vulpi[1].x2 = 3;
    vulpi[1].y2 = 4;
}

void initializare_matrice () {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) {
            matrice_joc[i][j].este_gaura = false;
            matrice_joc[i][j].este_ocupat = false;
        }

    // Setam coordonatele la care sunt gauri
    COORDONATE_GAURI.push_back({ 0, 0});
    COORDONATE_GAURI.push_back({ 0, N - 1 });
    COORDONATE_GAURI.push_back({ N - 1, 0 });
    COORDONATE_GAURI.push_back({ N - 1, N - 1 });

    // Initializam valorile din matrice cu VALOARE_GAURA acolo unde sunt gauri iar proprietatea este_gaura devine adevarata
    for (int i = 0; i < COORDONATE_GAURI.size(); i++) {
        matrice_joc[COORDONATE_GAURI[i].first][COORDONATE_GAURI[i].second].este_gaura = true;
        matrice_joc[COORDONATE_GAURI[i].first][COORDONATE_GAURI[i].second].val = VALOARE_GAURA;
    }
    if(N % 2 == 1) {
        matrice_joc[(N - 1) / 2][(N - 1) / 2].este_gaura = true;
        matrice_joc[(N - 1) / 2][(N - 1) / 2].val = -1;
    }

    // Iepurii sunt in joc
    for (int i = 0; i < NUMAR_IEPURI; i++) iepuri[i].ingame = 1;

    hardcoding_exemplu_youtube_obiecte();
}

// Miscare
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
    iep.x = xnou;
    iep.y = ynou;

    matrice_joc[iep.x][iep.y].val = VALOARE_IEPURE;
    verificare_iepure_in_gaura(iep);

    afisare_matrice();
    cout << '\n';
}

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

    // Miscarea vulpii pe orizontala
    if (directie == 0 || directie == 3) miscare_valoare_negativa(vulp, directie);
    else if (directie == 1 || directie == 2) miscare_valoare_pozitiva(vulp, directie);
    else {
        cout << "Directia introdusa nu este valida" << '\n';
        return;
    }

    afisare_matrice();
    cout << '\n';
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
        saritura_iepure(iepuri[nr_iepure - 1], directie - 1);
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
        miscare_vulpe(vulpi[nr_vulpe -1], directie - 1);
    }

    if (strcmp(comanda, "0") == 0) {
        return;
    }
}

int main()
{
    afisare_matrice();
    cout << "Mapa de joc este urmatoarea: " << '\n';
    initializare_matrice();
    afisare_matrice();
    cout << '\n';

    cout << "Informatii utile pentru joc: " << '\n';
    cout << "Cu -1 sunt notate gaurile, cu 0 campurile libere, cu 1 iepurii, cu 2 vulpile si cu 3 ciupercile" << '\n';
    cout << "Atat vulpile cat si iepurii sunt numerotati de la stanga la dreapta de sus in jos" << '\n';

    while (!conditie_final_joc()) joc();

    if (conditie_final_joc()) cout << "Felicitari! Toti iepurii au intrat in gauri.";
    return 0;
}