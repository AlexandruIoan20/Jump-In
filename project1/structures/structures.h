//
// Created by ialex on 14.12.2024.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

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

#endif //STRUCTURES_H
