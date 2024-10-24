#include "Vehicle.h"

Vehicle::Vehicle(const string& owner, int r, int g, int b, const string& brand, bool quality, int capacity) 
    : owner(owner), rgb{r, g, b}, brand(brand), quality(quality), capacity(capacity) {}

void Vehicle::bikeKind() const {
    if (kind == "Bike") {
        throw BikeError();
    }
} // Sprawdzenie, czy pojazd jest rowerem, i wyrzucenie wyjątku

bool Vehicle::bikeInList() {
    return kind != "Bike";
} // Sprawdzenie, czy pojazd nie jest rowerem

void Vehicle::printVehicle() {
    cout << "Kind: " << kind << " Brand: " << brand << ", Owner: " << owner
         << ", Colour: [" << rgb[0] << "," << rgb[1] << "," << rgb[2] << "], Capacity: "
         << capacity << endl;
} // Wypisywanie danych pojazdu
