#ifndef PROJEKT_FACTORY_H
#define PROJEKT_FACTORY_H

#include "Car.h"
#include "Motorcycle.h"
#include "Bike.h"
#include "Sprayer.h"
#include <iostream>
#include <string>
#include <vector>

constexpr int FACTORY_SIZE {10}; // Constant value for the array size of vehicles.

class Factory {
private:
    Vehicle* vehicles[FACTORY_SIZE]{}; // Array to store pointers to vehicles.

public:
    std::string brand; // Brand of the factory.
    int capacity{}; // Capacity of the factory.
    bool quality{}; // Quality indicator of the vehicles.

    // Constructor with parameters to initialize brand, capacity, and quality.
    Factory(std::string &brand, int capacity, bool quality);
    // Default constructor initializes brand as an empty string.
    Factory();
    
    // Retrieve a vehicle from the factory by its index.
    Vehicle* getVehicle(int vehicleNumber);

    // Print the brand of the factory.
    void printFactory() const;
    // Create a vehicle of a specified type.
    void createVehicle(int kindOfVehicle, int doors, int r, int g, int b, bool basket);
    // List all vehicles in the factory and return the count.
    int listVehicles();
    // Sell a vehicle and change its owner.
    Vehicle* saleVehicle(int vehicleNumber, std::string &newOwner);
};

#endif //PROJEKT_FACTORY_H
