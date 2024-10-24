#include "Sprayer.h"

void Sprayer::paintOver(Vehicle* ptrToVehicle, const int* rgbNew) {
    for(int i = 0; i < 3; ++i) {
        ptrToVehicle->rgb[i] = rgbNew[i];
    }
}
