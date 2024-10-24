#include "MotorVehicle.h"

MotorVehicle::MotorVehicle(const string& owner, int r, int g, int b, const string& brand, bool quality, int mileage, int capacity, int fuel)
    : Vehicle(owner, r, g, b, brand, quality, capacity), mileage(mileage), fuel(fuel)
{}

void MotorVehicle::printVehicle() {
    cout << "Kind: " << this->kind << ", Brand: " << this->brand << ", Owner: " << this->owner 
         << ", Colour: [" << this->rgb[0] << "," << this->rgb[1] << "," << this->rgb[2] << "]"
         << ", Mileage: " << this->mileage << ", Capacity: " << this->capacity 
         << ", Fuel: " << this->fuel << endl;
}

void MotorVehicle::driveMotorVehicle(float distance) {

    // Zmienne dla obliczeń są traktowane jako float, ponieważ wartości pośrednie są małe
    float fuelLose = static_cast<float>(capacity) / 50 * distance / 100;
    float fuelCheck = static_cast<float>(fuel) - fuelLose;  // Sprawdzanie potrzebnego paliwa
    float maxDistance = static_cast<float>(fuel) / (static_cast<float>(capacity) / 50) * 100;  // Maksymalny dystans

    if (fuel == 0) {
        throw NoFuelError();  // Brak paliwa
    }
    if (fuelCheck < 0) {
        distance = maxDistance;  // Zmniejszenie dystansu do możliwego maksimum
        mileage += static_cast<int>(distance);
        fuel = 0;
        throw LowFuelError(distance);  // Niewystarczająca ilość paliwa
    }

    // Aktualizacja przebiegu i paliwa przy odpowiedniej ilości paliwa
    mileage += static_cast<int>(distance);
    fuel -= static_cast<int>(fuelLose);
}
