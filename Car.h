#ifndef PROJECT_CAR_H
#define PROJECT_CAR_H

#include <string>
#include <iostream>
#include "MotorVehicle.h"

using namespace std;

// Class representing a car, inheriting from the MotorVehicle class.
class Car : public MotorVehicle {
public:
    // Constructor for the Car class, initializing member variables with default values.
    explicit Car(const string &owner = "factory", int r = -1, int g = -1, 
                 int b = -1, const string &brand = " ", bool quality = false, 
                 int doors = 0, int mileage = 0, int capacity = -1, int fuel = 25);

    // Method to print details of the car, overrides the base class method.
    void printVehicle() override;

protected:
    int doors; // Number of doors in the car.
};

#endif // PROJECT_CAR_H
