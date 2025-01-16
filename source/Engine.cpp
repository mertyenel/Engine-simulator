#include "Engine.h"

Engine* Engine::INSTANCE = nullptr;

Engine::Engine(double fuel_per_sec) : fuel_per_second(fuel_per_sec), consumedAmount(0.0), status(false),
                                      internalTank(55.0, 55.0, false) {}

Engine& Engine::getInstance(double fuel_per_sec) {
    if (INSTANCE == nullptr) {
        INSTANCE = new Engine(fuel_per_sec);
    }
    return *INSTANCE;
}

void Engine::startEngine() {
    if (internalTank.isBroken() && !connectedTanks.empty()) {
        status = true;
    } else {
        status = false;
    }
}

void Engine::stopEngine() {
    status = false;
}

void Engine::message() {
    std::cout << "Engine: Simulation stopped" << std::endl;
}

double Engine::getFuelPerSec() {
    return fuel_per_second;
}

double Engine::getInternalTank() {
    return internalTank.getFuelQuantity();
}

double Engine::getInternalTankCapacity() {
    return internalTank.getCapacity();
}

void Engine::setInternalTank(double amount) {
    internalTank.setFuelQuantity(amount);
}

bool Engine::getStatus() {
    return status;
}

double Engine::getConsumedAmount() {
    return consumedAmount;
}

std::list<FuelTank>& Engine::getConnectedTanks() {
    return connectedTanks;
}

void Engine::yakitTuket(int time) {
    int random_number = rand() % connectedTanks.size() + 1;
    std::list<FuelTank>::iterator it = connectedTanks.begin();
    std::advance(it, random_number - 1);
    while (time > 0) {
        if ((internalTank.getFuelQuantity() - fuel_per_second) >= 20) {
            internalTank.setFuelQuantity(internalTank.getFuelQuantity() - fuel_per_second);
            consumedAmount += fuel_per_second;
        } else {
            while ((it->getFuelQuantity() < fuel_per_second) || !it->getValve()) {
                random_number = rand() % connectedTanks.size() + 1;
                it = connectedTanks.begin();
                std::advance(it, random_number - 1);
            }
            it->setFuelQuantity(it->getFuelQuantity() - fuel_per_second);
            consumedAmount += fuel_per_second;
        }
        time--;
    }
}

bool Engine::isConnectedToTank() {
    return !connectedTanks.empty();
}

void Engine::open_valve(int tank_index) {
    if (status && !connectedTanks.empty()) {
        if (tank_index > 0 && tank_index <= connectedTanks.size()) {
            std::list<FuelTank>::iterator it = connectedTanks.begin();
            std::advance(it, tank_index - 1);
            it->openValve();
        }
    }
 }
 void Engine::close_valve(int tank_index) {
        if (status && !connectedTanks.empty()) {
            if (tank_index > 0 && tank_index <= connectedTanks.size()) {
                std::list<FuelTank>::iterator it = connectedTanks.begin();
                advance(it, tank_index-1);
                it->closeValve();
            }
        }
    }

    void Engine::connectTank(const FuelTank& tank) {
        connectedTanks.push_back(tank);
    }
    void Engine::disconnectTank(const FuelTank& tank) {
        std::list<FuelTank>::iterator it = connectedTanks.begin(); 
        for(it = connectedTanks.begin(); it != connectedTanks.end(); ++it){
                if (*it == tank){
                connectedTanks.erase(it);
                break;
                }
        } 
    }

    FuelTank& Engine::minFuelTank(){
        std::list<FuelTank>::iterator it=connectedTanks.begin();
        FuelTank& minTank = *it;
        double totalFuel = it->getFuelQuantity();
        for(it=connectedTanks.begin(); it!=connectedTanks.end(); it++){
            if(totalFuel <=  it->getFuelQuantity()){
                totalFuel = it->getFuelQuantity();
                minTank = *it;
            }
        }
        return minTank;
    }
    
    double Engine::totalFuel(){
        double totalFuel = 0.0;
        totalFuel += getInternalTank();
         for (std::list<FuelTank>::const_iterator it = connectedTanks.begin(); it != connectedTanks.end(); ++it) {
            totalFuel += it->getFuelQuantity(); 
             }
        return totalFuel;
    }

