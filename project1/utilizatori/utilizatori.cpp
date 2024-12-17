#include "utilizatori.h"
#include "../structures/structures.h"
#include "../global/global.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

void get_utilizatori() {
  ifstream fin("utilizatori.txt", ios::app);
  if (!fin.is_open()) {
    cerr << "Eroare la deschiderea fisierului cu utilizatori" << '\n';
    return;
  }

  string linie;
  while (getline(fin, linie)) {
    cout << "linie: " << linie << '\n';
    if (linie.substr(0, 5) == "Nume:") {
      sscanf(linie.c_str(), "Nume: %50[^\n]", utilizatori[numar_utilizatori].nume);
      cout << "In functie: " << utilizatori[numar_utilizatori].nume << '\n';
    }
  }

  numar_utilizatori++;

  fin.close();
}

void add_utilizator(char username[101]) {
  ofstream fout("utilizatori.txt", ios::app);
  if(!fout.is_open()) {
    cerr << "Eroare la deschiderea fisierului cu utilizatori" << '\n';
    return;
  }

  fout << username << '\n';

  for(int i = 0; i < NUMAR_NIVELE; i++)
    fout << "nivel: " << i << " timp: 0" << '\n';

  fout << '\n';
  fout.close();
}



