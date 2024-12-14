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

#endif //STRUCTURES_H
