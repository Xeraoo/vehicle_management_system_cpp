#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include "ErrorVehicles.h"

using namespace std;

class Vehicle {
public:
    string owner;
    int capacity;  // Samochód/motocykl - rozmiar bagażnika, rower - zależy od koszyka
    bool quality;
    int rgb[3];

    explicit Vehicle(const string& owner = "factory", int r = -1, int g = -1, int b = -1, const string& brand = " ", bool quality = false, int capacity = -1);

    void bikeKind() const;
    bool bikeInList();
    
    virtual void printVehicle();

protected:
    string brand;
    string kind;
};

#endif // VEHICLE_H
