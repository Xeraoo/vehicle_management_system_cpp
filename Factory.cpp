#include "Factory.h"

// Constructor to initialize the factory with a specific brand, capacity, and quality.
Factory::Factory(std::string &brand, int capacity, bool quality) 
    : brand(brand), capacity(capacity), quality(quality) {
    for (int i = 0; i < FACTORY_SIZE; i++) {
        vehicles[i] = nullptr; // Initialize vehicle array with nullptr.
    }
}

// Default constructor initializes the factory with an empty brand.
Factory::Factory() {
    brand = "";

    for (int i = 0; i < FACTORY_SIZE; i++) {
        vehicles[i] = nullptr; // Initialize vehicle array with nullptr.
    }
}

// Retrieve a vehicle from the factory's private array.
Vehicle *Factory::getVehicle(int vehicleNumber) {
    return vehicles[vehicleNumber];
}

// Print the brand of the factory.
void Factory::printFactory() const {
    std::cout << brand;
}

// Create a vehicle of a specified type with given attributes.
void Factory::createVehicle(int kindOfVehicle, int doors, int r, int g, int b, bool basket) {
    int i = 0;
    
    // Find the first available slot in the vehicle array.
    while (vehicles[i] != nullptr) {
        i++;
    }

    // Pointers for different vehicle types.
    Car *vehicle1;
    Motorcycle *vehicle2;
    Bike *vehicle3;

    switch (kindOfVehicle) {
        case 0:
            vehicle1 = new Car("factory", r, g, b, this->brand, false, doors, 0, capacity / 1, 25);
            vehicles[i] = vehicle1; // Assign the created car to the available slot.
            break;

        case 1:
            vehicle2 = new Motorcycle("factory", r, g, b, this->brand, false, 0, capacity / 2, 10);
            vehicles[i] = vehicle2; // Assign the created motorcycle to the available slot.
            break;

        case 2:
            vehicle3 = new Bike("factory", r, g, b, this->brand, false, capacity / 50 * basket, basket);
            vehicles[i] = vehicle3; // Assign the created bike to the available slot.
            break;

        default:
            std::cout << "Type one of the numbers above!" << std::endl; // Error message for invalid input.
    }
}

// List all vehicles in the factory and count their number.
int Factory::listVehicles() {
    int count = 0;

    for (int i = 0; i < FACTORY_SIZE; i++) {
        if (vehicles[i] != nullptr) { // Prevent printing empty slots.
            std::cout << i << ". ";
            vehicles[i]->printVehicle(); // Print vehicle details.
            std::cout << std::endl;
            count = i + 1; // Track the total number of vehicles.
        }
    }

    if (count == 0) {
        std::cout << "No vehicles in this factory" << std::endl; // Message for empty factory.
    }

    return count; // Return the number of vehicles.
}

// Sale a vehicle by changing its owner and removing it from the factory.
Vehicle* Factory::saleVehicle(int vehicleNumber, std::string &newOwner) {
    Vehicle *vehicle = vehicles[vehicleNumber];

    if (vehicles[vehicleNumber] != nullptr) { // Check if the vehicle exists.
        vehicle->owner = newOwner; // Change the owner's name.
        vehicles[vehicleNumber] = nullptr; // Remove the vehicle from the factory.
        std::cout << "Now it is your vehicle!" << std::endl;
    } else {
        std::cout << "There is no vehicle to sell" << std::endl; // Error message for no vehicle.
    }

    return vehicle; // Return the sold vehicle.
}
