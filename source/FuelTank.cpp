#include "FuelTank.h"
using namespace std;

FuelTank::FuelTank(double _c, double _f, bool _b) : capacity(_c), fuel_quantity(_f), broken(_b){}

void FuelTank::setCapacity(double amount) {
    double total = fuel_quantity + amount;
    if (total > capacity) {
        fuel_quantity = capacity;
    } else
        fuel_quantity = total;
}

double FuelTank::getCapacity() const {
    return capacity;
}

double FuelTank::getFuelQuantity() const {
    return fuel_quantity;
}

void FuelTank::setFuelQuantity(double amount) {
    fuel_quantity = amount;
}

void FuelTank::addFuelQuantity(double amount) {
    if ((fuel_quantity + amount) > capacity)
        fuel_quantity = capacity;
    else
        fuel_quantity += amount;
}

bool FuelTank::getValve() {
    return val.statused();
}

void FuelTank::openValve() {
    val.open_valve();
    
}

void FuelTank::closeValve() {
    val.close_valve();
    cout << "Simulation stopped.";
}

bool FuelTank::isBroken() const {
    return !broken;
}

void FuelTank::breakTank() {
    broken = true;
}

void FuelTank::repairTank() {
    broken = false;
}

void FuelTank::print() {
    cout << "Capacity: " << capacity << ", Fuel Quantity: " << fuel_quantity << ", Broken: " << (broken ? "Yes" : "No")
         << ", Valve Statement: " << (val.statused() ? "Yes" : "No") << endl;
}

bool FuelTank::operator==(const FuelTank& other) const {
    return (capacity == other.capacity) && (fuel_quantity == other.fuel_quantity) && (broken == other.broken);
}

void FuelTank::giveBackFuel(double quantity) {
    double amount = fuel_quantity + quantity;
    if (amount > capacity) {
        fuel_quantity = capacity;
    } else
        fuel_quantity = amount;
}
