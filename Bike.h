//
// Created by Xeraoo.
// 

#ifndef BIKE_H
#define BIKE_H

#include "Vehicle.h"
#include <string>
#include <iostream>

using namespace std;

// Bike class inherits from the Vehicle class.
class Bike : public Vehicle {
public:
    // Constructor for the Bike class with default values for parameters.
    explicit Bike(const string &owner = "factory", int r = -1, int g = -1, int b = -1, 
                  const string &brand = " ", bool quality = false, int capacity = -1, bool basket = false);

    // Override the printVehicle method to display bike details.
    void printVehicle() override;

protected:
    bool basket; // Option to select whether the bike has a basket, which can hold a specified capacity.
};

#endif //BIKE_H
