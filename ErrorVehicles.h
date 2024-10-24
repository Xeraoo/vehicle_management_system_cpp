#ifndef PROJECT_ERRORVEHICLES_H
#define PROJECT_ERRORVEHICLES_H

#include <iostream>
#include <string>
#include <exception>

// Base exception class for vehicle-related errors.
struct VehicleError : public std::exception {
    std::string warning;

    // Constructor to initialize the warning message.
    explicit VehicleError(std::string warn) : warning(std::move(warn)) {}
};

// Exception for the case when no vehicles exist.
struct NoVehicleError : public VehicleError {
    explicit NoVehicleError() 
        : VehicleError("There is no vehicle in all factories! You should create one before you take any action.") {}
};

// Exception for the case when a bike is incorrectly chosen.
struct BikeError : public VehicleError {
    explicit BikeError() 
        : VehicleError("You should choose a motor vehicle, NOT a bike.") {}
};

// Base exception class for fuel-related errors.
struct FuelError : public VehicleError {
    explicit FuelError(std::string warn) : VehicleError(std::move(warn)) {}
};

// Exception for low fuel situations.
struct LowFuelError : public FuelError {
    float maxDistance; // Maximum distance that can be traveled with the remaining fuel.

    explicit LowFuelError(float maxD) 
        : FuelError("There is not enough fuel for such a long distance."), maxDistance(maxD) {}
};

// Exception for the case when there is no fuel.
struct NoFuelError : public FuelError {
    explicit NoFuelError() 
        : FuelError("There is no fuel!") {}
};

#endif // PROJECT_ERRORVEHICLES_H
