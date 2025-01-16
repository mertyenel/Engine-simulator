#include "KomutAta.h"
#include <fstream>
using namespace std;
 KomutAta::KomutAta() : engine(Engine::getInstance(5.5)) {}  

   void KomutAta::komut_calistir(const std::string& input_file) {
    std::ifstream inputFile(input_file);
    std::string yorumSatiri;

        while (inputFile >> yorumSatiri) {
            if (yorumSatiri == "stop_simulation") {  //! if input line is this comment, system is stopped 
                int i=1;
                engine.message();
                list<FuelTank>& tanks = engine.getConnectedTanks();

                for (list<FuelTank>::iterator it= tanks.begin(); it != tanks.end(); ++it) {
                      cout<<"Tank "<< i;
                      cout<<" simulation stopped";
                      cout<<endl;
                      cout<<"Valve "<< i;
                      it->closeValve();
                      cout<<endl;
                      i++;
                }
                break;  
            } 
            else if (yorumSatiri == "start_engine") {  //! engine is starting to work
                engine.startEngine();
                
            } 
            else if (yorumSatiri == "stop_engine") {  
                engine.stopEngine();
            }
            /**
             * @brief this comment makes if there is a enough fuel in the internal tank, it transfers specified amount to be been a minimum fuel  tank
            */
            else if (yorumSatiri == "give_back_fuel") { 
             if(engine.getStatus()){
                    engine.yakitTuket(1);
               }
            double quantity;
            inputFile >> quantity;
             if(engine.getInternalTank()>= quantity){
             engine.setInternalTank(engine.getInternalTank() - quantity);
             engine.minFuelTank().addFuelQuantity(quantity);
             }
            }
            //! this section adds a fueltank in the system
            else if (yorumSatiri == "add_fuel_tank") { 
                double capacity;
                inputFile >> capacity;  
                FuelTank newTank(capacity,0.0);
                fuelTanks.push_back(newTank);
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            } 
            /**
             * @brief to list whole fuel tanks. Actually i couldn't know which one is true but i did just beginning position or state
             * It only shows the unmodified version. If you want to see the modified version, you should look at the connectedtanks section.
            */
            else if (yorumSatiri == "list_fuel_tanks") {
             cout<<"------Initial list------- "<<endl<<"If you want to see change, you can take a look connected list"<<endl;

            list<FuelTank>::iterator it = fuelTanks.begin(); 
                for(it = fuelTanks.begin(); it != fuelTanks.end(); ++it){
                    it->print();
                }
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
                cout<<"----------------------------"<<endl;
            } 
            else if (yorumSatiri == "remove_fuel_tank") { 
                int tank_id;
                inputFile >> tank_id;
             if (tank_id >= 0 && tank_id < fuelTanks.size()) {
                list<FuelTank>::iterator it = fuelTanks.begin();
                advance(it, tank_id-1);
                if (it != fuelTanks.end()) {
                list<FuelTank>::iterator next_it = next(it); 
                fuelTanks.erase(it);
                it = next_it; 
                }
              }
              if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            }
            //! if you connect a tank with the engine. there is a different option to use fuel. But you have to be carefully, if its valve is close, you can't use it.
            else if (yorumSatiri == "connect_fuel_tank_to_engine") {  
                int tank_id;
                inputFile >> tank_id;
                list<FuelTank>::iterator it = fuelTanks.begin(); 
                advance(it,tank_id-1);
                engine.connectTank(*it);
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            } 
            else if (yorumSatiri == "disconnect_fuel_tank_from_engine") {
                int tank_id;
                inputFile >> tank_id;
                list<FuelTank>::iterator it = fuelTanks.begin(); 
                advance(it,tank_id-1);
                engine.disconnectTank(*it);
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            }
             //! if you open the valve, engine starts to consume fuel to be chosen connectedtank
            else if (yorumSatiri == "open_valve") { 
                int tank_id;
                inputFile >> tank_id;
                engine.open_valve(tank_id);
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            } 
            //! to quit consume fuel section
            else if (yorumSatiri == "close_valve") { 
                int tank_id;
                inputFile >> tank_id;
                engine.close_valve(tank_id);
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            }
            else if (yorumSatiri == "break_fuel_tank") { 
                int tank_id;
                inputFile >> tank_id;
                list<FuelTank>::iterator it = fuelTanks.begin(); 
                advance(it,tank_id-1);
                it->breakTank();
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            }
            else if (yorumSatiri == "repair_fuel_tank") { 
                int tank_id;
                inputFile >> tank_id;
                list<FuelTank>::iterator it = fuelTanks.begin(); 
                advance(it,tank_id-1);
                it->repairTank();
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            } 
            //! it shows how many tanks are there in the system
            else if (yorumSatiri == "print_fuel_tank_count") { 
            int counter=0;
            list<FuelTank>::iterator it = fuelTanks.begin(); 
                for(it = fuelTanks.begin(); it != fuelTanks.end(); ++it){
                    counter++;
                }
                cout<<"Fuel Tank Count = "<< counter <<endl;
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            } 
            //! Most efficient section is this section. It allows you to see information about my fuel consumption and the status of my tanks.
            else if (yorumSatiri == "list_connected_tanks") { 
                list<FuelTank>& tanks = engine.getConnectedTanks();
                for (list<FuelTank>::iterator it = tanks.begin(); it != tanks.end(); ++it) {
                    it->print();
                }
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            } 
            //!name of comment line give you a hint what to do this actually.
            else if (yorumSatiri == "print_total_fuel_quantity") {  
            if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            double totalFuel = engine.totalFuel();
            cout << "Total Fuel Quantity in Connected Tanks: " << totalFuel << endl;
            }
            //!This command represents the total fuel used in the system.
            else if (yorumSatiri == "print_total_consumed_fuel_quantity") {
            if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
             double totalConsumedFuel = 0.0;
             totalConsumedFuel= engine.getConsumedAmount();
             cout << "Total Consumed Fuel Quantity: " << totalConsumedFuel << endl;
            }

            else if (yorumSatiri == "print_tank_info") { 
                int tank_id;
                inputFile >> tank_id;
                list<FuelTank>::iterator it = fuelTanks.begin(); 
                advance(it,tank_id-1);
                it->print();                
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            } 
            //!command used to add fuel to the tank
            else if (yorumSatiri == "fill_tank") { 
                int tank_id;
                double fuel_quantity;
                inputFile >> tank_id;
                inputFile >> fuel_quantity;
                list<FuelTank>::iterator it = fuelTanks.begin(); 
                advance(it,tank_id-1);
                it->setCapacity(fuel_quantity);
                if(engine.getStatus()){
                    engine.yakitTuket(1);
                }
            
            } 
            /**
             * @brief The standby command allows as much fuel as it consumes per second while it is running.
             *  At the same time, it is designed to test some conditions in the system and take action accordingly because there are a lot of details in the system.
            */

            else if (yorumSatiri == "wait"){ 
                int seconds;
                inputFile >> seconds;
                if(engine.getStatus() && (engine.getFuelPerSec()*seconds) < engine.totalFuel()){
                    engine.yakitTuket(seconds);
                }
                else{
                 cout<<"Insufficient fuel for waiting time.. Engine continue to work without waiting !!"<<endl;
                 continue;
                }
            } 
        }
        inputFile.close();

    }