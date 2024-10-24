#ifndef MOTORVEHICLE_H
#define MOTORVEHICLE_H

#include "ErrorVehicles.h"
#include "Vehicle.h"
#include <string>
#include <iostream>

using namespace std;

class MotorVehicle : public Vehicle {
public:
    int fuel;      // ilość paliwa w litrach
    int mileage;   // przebieg pojazdu

    explicit MotorVehicle(const string& owner = "factory", int r = -1, int g = -1, int b = -1, const string& brand = " ", bool quality = false, int mileage = 0, int capacity = -1, int fuel = 25);

    void printVehicle() override;
    void driveMotorVehicle(float distance);
};

#endif // MOTORVEHICLE_H
