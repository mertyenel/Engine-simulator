#ifndef FUELTANK_H
#define FUELTANK_H
#include "valve.h"
#include <iostream>
#include <list>

class FuelTank {
private:
    double capacity;
    double fuel_quantity;
    bool broken;
    Valve val;

public:
    FuelTank(double _c = 0, double _f = 0, bool _b = false);

    void setCapacity(double amount);
    double getCapacity() const;
    double getFuelQuantity() const;
    void setFuelQuantity(double amount);
    void addFuelQuantity(double amount);
    bool getValve();
    void openValve();
    void closeValve();
    bool isBroken() const;
    void breakTank();
    void repairTank();
    void print();
    bool operator==(const FuelTank& other) const;
    void giveBackFuel(double quantity);
};

#endif // FUELTANK_H
