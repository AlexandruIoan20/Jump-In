#include "utilizatori.h"
#include "../structures/structures.h"
#include "../global/global.h"
#include <iostream>
#include <fstream>
using namespace std;

utilizator get_utilizatori() {

}

void add_utilizator(char username[101]) {
  ofstream fout("utilizatori.txt", ios::app);
  if(!fout.is_open()) {
    cerr << "Eroare la deschiderea fisierului cu utilizatori" << '\n';
    return;
  }

  fout << username << '\n';

  for(int i = 0; i < NUMAR_NIVELE; i++)
    fout << "nivel: " << i << " timp: 00: 00: 00" << '\n';

  fout << '\n';
  fout.close();
}



