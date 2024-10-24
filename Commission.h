#ifndef PROJECT_COMMISSION_H
#define PROJECT_COMMISSION_H

#include <iostream>
#include <string>
#include <vector>
#include "MotorVehicle.h"

// Class representing a vehicle commission.
class Commission {
public:
    // Constructor to initialize the commission with a sales price.
    explicit Commission(int salesPrice);
    
    // Vector to store vehicles purchased by the commission.
    std::vector<MotorVehicle*> square; 
    
    // Sales price with a margin.
    int salesPrice; 

    // Method to print the details of vehicles in the commission.
    bool printCommission();
    
    // Method to calculate the purchase price of a sold vehicle.
    static int purchasePrice(MotorVehicle* sold); 
    
    // Method to buy a vehicle from the commission.
    void buyFromCommission(int vehicleNumber, std::string newOwner);
    
    // Method to sell a vehicle to the commission.
    void sellToCommission(MotorVehicle* vehicle);
};

#endif // PROJECT_COMMISSION_H
