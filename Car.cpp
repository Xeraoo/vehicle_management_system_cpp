#include "Car.h"

// Constructor for the Car class, initializing member variables.
Car::Car(const string &owner, int r, int g, int b, const string &brand, bool quality, 
         int doors, int mileage, int capacity, int fuel)
    : MotorVehicle(owner, r, g, b, brand, quality, mileage, capacity, fuel), doors(doors) 
{
    this->kind = "Car"; // Set the type of vehicle to "Car".
}

// Method to print details of the car.
void Car::printVehicle() {
    cout << "Kind: " << this->kind 
         << ", Brand: " << this->brand 
         << ", Owner: " << this->owner 
         << ", Nr. of doors: " << this->doors 
         << ", Colour: [" << this->rgb[0] << "," << this->rgb[1] << "," << this->rgb[2] 
         << "], Mileage: " << this->mileage 
         << ", Capacity: " << this->capacity 
         << ", Fuel: " << this->fuel << endl; // Display the car's details.
}
