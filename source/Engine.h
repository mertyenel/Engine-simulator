#include "FuelTank.h"
class Engine {

private:
    const double fuel_per_second; 
    double consumedAmount;
    bool status; 
    FuelTank internalTank;
    std::list<FuelTank> connectedTanks;
    Valve valve;
    static Engine* INSTANCE;   
    Engine(double fuel_per_sec);
public: 
    static Engine& getInstance(double fuel_per_sec);
    void startEngine();
    void stopEngine();
    void message();
    double getFuelPerSec();
    double getInternalTank();
    double getInternalTankCapacity();
    void setInternalTank(double amount);
    bool getStatus();
    double getConsumedAmount();
    std::list<FuelTank>& getConnectedTanks(); 
    void yakitTuket(int time);
    bool isConnectedToTank();
    void open_valve(int tank_index);
    void close_valve(int tank_index);
    void connectTank(const FuelTank& tank);
    void disconnectTank(const FuelTank& tank);
    FuelTank &minFuelTank();
    double totalFuel();
};
