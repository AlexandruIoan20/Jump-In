#include "utils.h"

#include "../global/global.h"
#include <iostream>
using namespace std;

bool inmat(int x, int y) {
    return (x >= 0 && x <= N - 1 && y >= 0 && y <= N - 1);
}