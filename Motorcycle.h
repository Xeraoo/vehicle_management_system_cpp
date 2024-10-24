#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "MotorVehicle.h"
#include <string>
using namespace std;

class Motorcycle : public MotorVehicle {
public:
    explicit Motorcycle(const string &owner="factory", int r = -1, int g=-1, int b=-1, const string &brand= " ",  bool quality=false, int mileage=0, int capacity=-1, int fuel=10);

    void printVehicle() override;
};

#endif //MOTORCYCLE_H
