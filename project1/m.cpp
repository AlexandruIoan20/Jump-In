#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

struct camp {
    bool este_gaura;
    bool este_ocupat;
    int val;
};

struct vulpe {
    char orientare; // V - vertical,  O - Orizontal
    int x1, y1, x2, y2; // valori constante stabilite mai sus
};

struct ciuperca {
    int x, y;
};

struct iepure {
    bool ingame;
    int x, y;
};

struct coordonate {
    int x, y;
};

struct miscare {
    char obiect;
    int index_iepure;
    int index_vulpe;
    coordonate coordonate_vechi;
    coordonate coordonate_vechi2;
    coordonate coordonate_noi;
    coordonate coordonate_noi2;
};

struct scor_nivel {
    int numar_nivel;
    int secunde;
};

struct utilizator {
    char nume[51];
    scor_nivel scoruri[12];
};

utilizator utilizatori[101];
int numar_utilizatori = 0;

const int VALOARE_GAURA = -1;
const int VALOARE_IEPURE = 1;
const int VALOARE_VULPE = 2;
const int VALOARE_CIUPERCA = 3;
const int VALOARE_CAMP_GOL = 0;

const int NUMAR_NIVELE=12;
int NUMAR_IEPURI = 0;
int NUMAR_VULPI = 0;
int NUMAR_CIUPERCI = 0;

const int N = 5;

iepure iepuri[11];
vulpe vulpi[11];
ciuperca ciuperci[11];

camp matrice_joc[5][5];
miscare miscari[101];

int numar_miscari = 0;

void initializare_matrice(int numar_nivel) {
    string nume_fisier = "../nivele/nivel" + to_string(numar_nivel) + ".txt";
    ifstream fin(nume_fisier);

    cout << "nume fisier:" << nume_fisier << '\n';

    int valoare;
    for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++) {
           fin >> valoare;
           matrice_joc[i][j].val = valoare;

           matrice_joc[i][j].este_gaura = false;
           if(valoare == VALOARE_GAURA) {
               matrice_joc[i][j].este_gaura = true;
               matrice_joc[i][j].este_ocupat = false;
          }

          if(valoare == VALOARE_IEPURE) {
            iepuri[NUMAR_IEPURI].x = i;
            iepuri[NUMAR_IEPURI].y = j;
            iepuri[NUMAR_IEPURI].ingame = true;
            NUMAR_IEPURI++;
          }

          if(valoare == VALOARE_CIUPERCA) {
                ciuperci[NUMAR_CIUPERCI].x = i;
                ciuperci[NUMAR_CIUPERCI].y = j;
                NUMAR_CIUPERCI++;
          }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if(matrice_joc[i][j].val == VALOARE_VULPE) {
                int x1 = i + dx[1];
                int y1 = j + dy[1];

                int x2 = i + dx[2];
                int y2 = j + dy[2];

                if (matrice_joc[x1][y1].val == VALOARE_VULPE || matrice_joc[x2][y2].val == VALOARE_VULPE) {
                    vulpi[NUMAR_VULPI].x1 = i;
                    vulpi[NUMAR_VULPI].y1 = j;
                    if (matrice_joc[x1][y1].val == VALOARE_VULPE) {
                        vulpi[NUMAR_VULPI].x2 = x1;
                        vulpi[NUMAR_VULPI].y2 = y1;
                        vulpi[NUMAR_VULPI].orientare = 'O';
                    } else if (matrice_joc[x2][y2].val == VALOARE_VULPE) {
                        vulpi[NUMAR_VULPI].x2 = x2;
                        vulpi[NUMAR_VULPI].y2 = y2;
                        vulpi[NUMAR_VULPI].orientare = 'V';
                    }

                    NUMAR_VULPI++;
                }
            }
        }

    fin.close();
}

bool inmat(int x, int y) {
    return (x >= 0 && x <= N - 1 && y >= 0 && y <= N - 1);
}

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

void verificare_iepure_in_gaura(iepure &iep) {
    if (matrice_joc[iep.x][iep.y].este_gaura && !matrice_joc[iep.x][iep.y].este_ocupat) {
        iep.ingame = false;
        matrice_joc[iep.x][iep.y].este_ocupat = true;
        matrice_joc[iep.x][iep.y].val = -1;

        cout << "Felicitari, un iepure a intrat in gaura." << '\n';
    }
}

void saritura_iepure(iepure &iep, int directie, int index) {
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
        // pozitia veche xnou, ynou
        //(stanga+lat*xnou,sus+lat*ynou,"spatiu.bmp");
        xnou = xnou + dx[directie];
        ynou = ynou + dy[directie];
        // pozitia noua xnou, ynou
        //readimagefile(stanga+lat*xnou,sus+lat*ynou,"iepure.bmp");
        }

    if (!inmat(xnou, ynou)) {
        cerr << "Iepurele iese din matrice" << '\n';
        return;
    }

    matrice_joc[iep.x][iep.y].val = 0;
    inregistrare_miscare_iepure(iep, iep.x, iep.y, index);

    iep.x = xnou;
    iep.y = ynou;

    matrice_joc[iep.x][iep.y].val = VALOARE_IEPURE;
    verificare_iepure_in_gaura(iep);

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

void miscare_vulpe(vulpe &vulp, int directie, int index) {
    if ((vulp.orientare == 'O' && (directie == 0 || directie == 2)) ||
        (vulp.orientare == 'V' && (directie == 1 || directie == 3))) {
        cout << "Miscarea vulpii pe acea directie nu este posibila" << '\n';
        return;
        }

    int x1 = vulp.x1, x2 = vulp.x2, y1 = vulp.y1, y2 = vulp.y2;

    if (directie < 0 || directie > 3) {
        cout << "Directia introdusa nu este valida" << '\n';
        return;
    }

    if (directie == 0 || directie == 3) miscare_valoare_negativa(vulp, directie);
    else if (directie == 1 || directie == 2) miscare_valoare_pozitiva(vulp, directie);

    inregistrare_miscare_vulpe(vulp, x1, x2, y1, y2, index);
    cout << '\n';
}

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

void afisare_miscare(miscare m) {
    cout << "obiect: " << m.obiect << '\n';
    cout << "index_iepure: " << m.index_iepure << '\n';
    cout << "index_vulpe: " << m.index_vulpe << '\n';
    cout << "coordonate_vechi: (" << m.coordonate_vechi.x << ", " << m.coordonate_vechi.y << ")\n";
    cout << "coordonate_vechi2: (" << m.coordonate_vechi2.x << ", " << m.coordonate_vechi2.y << ")\n";
    cout << "coordonate_noi: (" << m.coordonate_noi.x << ", " << m.coordonate_noi.y << ")\n";
    cout << "coordonate_noi2: (" << m.coordonate_noi2.x << ", " << m.coordonate_noi2.y << ")\n";
    cout << '\n';
}

void afisare_miscari() {
    if (numar_miscari == -1) {
        cout << "Momentan nu au fost facute miscari." << '\n';
        return;
    }

    cout << "Miscarile executate pana acum sunt: " << '\n';

    for (int i = 0; i < numar_miscari; i++) afisare_miscare(miscari[i]);
}

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

int main() {
    for (int i = 0; i < numar_utilizatori; i++) {
        cout << "Nume utilizator: " << utilizatori[i].nume << '\n';
    }
    // Utilizator
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