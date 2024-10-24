//
// Created by Xeraoo.
// 

#include "Bike.h"

// Constructor for the Bike class, initializing the vehicle properties and specifying that the kind is "Bike".
Bike::Bike(const string &owner, int r, int g, int b, const string &brand, bool quality, int capacity, bool basket)
    : Vehicle(owner, r, g, b, brand, quality, capacity), basket(basket) {
    this->kind = "Bike";  // Set the type of vehicle to "Bike".
}

// Method to print details of the bike.
void Bike::printVehicle() {
    cout << "Kind: " << this->kind 
         << ", Brand: " << this->brand 
         << ", Owner: " << this->owner 
         << ", Colour: [" << this->rgb[0] << "," 
         << this->rgb[1] << "," << this->rgb[2] << "]" 
         << ", Basket: " << this->basket 
         << ", Capacity: " << this->capacity << endl;
}
