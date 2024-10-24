#ifndef SPRAYER_H
#define SPRAYER_H

#include "Vehicle.h"
#include <iostream>
#include <string>
#include <vector>

class Sprayer {
public:
    static void paintOver(Vehicle* ptrToVehicle, const int* rgbNew);
};

#endif // SPRAYER_H
