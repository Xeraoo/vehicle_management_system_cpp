#include "Motorcycle.h"

// Constructor: Initializes a Motorcycle object with owner details, color, brand, quality, mileage, engine capacity, and fuel type
Motorcycle::Motorcycle(const string& owner, int r, int g, int b, const string& brand, bool quality, int mileage, int capacity, int fuel)
    : MotorVehicle(owner, r, g, b, brand, quality, mileage, capacity, fuel) // Using initializer list to initialize the base class MotorVehicle
{
    this->kind = "Motorcycle"; // Setting the kind attribute specifically for motorcycles
}

// Method to print motorcycle details
void Motorcycle::printVehicle() {
    cout << "Kind: " << this->kind 
         << ", Brand: " << this->brand 
         << ", Owner: " << this->owner 
         << ", Colour: [" << this->rgb[0] << "," << this->rgb[1] << "," << this->rgb[2] << "]" 
         << ", Mileage: " << this->mileage 
         << ", Capacity: " << this->capacity 
         << ", Fuel: " << this->fuel 
         << endl;
}
