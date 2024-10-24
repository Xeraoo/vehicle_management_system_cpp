#include "Commission.h"

// Constructor to initialize the sales price.
Commission::Commission(int salesPrice) : salesPrice(salesPrice) {
}

// Method to print vehicles in the commission along with their purchase and sales prices.
bool Commission::printCommission() {
    bool notEmpty = false;  // Flag to check if the commission has vehicles.

    if (!square.empty()) {
        notEmpty = true;  // Set flag to true if there are vehicles.

        cout << "Here is the list of all vehicles in commission:" << endl;
        for (int i = 0; i < square.size(); i++) {
            cout << i << ". ";
            square[i]->printVehicle();  // Print vehicle details.
            cout << endl;

            // Calculate the purchase price and sales price.
            int purchasePriceValue = purchasePrice(square[i]);
            salesPrice = static_cast<int>(1.5 * purchasePriceValue); // Sales price with a margin.

            cout << "Purchase price: " << purchasePriceValue << endl;
            cout << "Sales price: " << salesPrice << endl;
            cout << endl;
        }
    } else {
        cout << "There is no vehicle in the commission yet" << endl;  // No vehicles available.
    }

    return notEmpty;  // Return if the commission has vehicles.
}

// Method to calculate the purchase price of a vehicle.
int Commission::purchasePrice(MotorVehicle* vehicles) {
    // Determine the purchase price based on capacity, mileage, and quality.
    int capacityPrice = (vehicles->capacity) * 10; // Price factor based on vehicle capacity.
    int mileagePrice = ((vehicles->quality) ? (vehicles->mileage) : (vehicles->mileage) * 2); // Mileage consideration.

    // Calculate purchase price considering capacity, mileage, and additional quality fee for luxury vehicles.
    int purchasePriceValue = capacityPrice - mileagePrice + (vehicles->quality) * 5000;

    return purchasePriceValue;  // Return the calculated purchase price.
}

// Method to add a vehicle to the commission.
void Commission::sellToCommission(MotorVehicle* mvehicle) {
    square.push_back(mvehicle); // Add a new vehicle to the commission.
    square[square.size() - 1]->owner = "Commission"; // Change the owner to 'Commission'.

    cout << "You sold your vehicle!" << endl; // Confirmation message.
}

// Method to buy a vehicle from the commission.
void Commission::buyFromCommission(int vehicleNumber, string newOwner) {
    if (!square.empty()) { // Check if there are vehicles in the commission.
        square[vehicleNumber]->owner = move(newOwner); // Change the owner to the new owner.
        square.erase(square.begin() + vehicleNumber); // Remove the sold vehicle from the commission.
        cout << "Now it is your vehicle!" << endl; // Confirmation message.
    } else {
        cout << "There is no vehicle to buy" << endl; // No vehicles available for purchase.
    }
}
