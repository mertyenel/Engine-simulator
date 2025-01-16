#ifndef KOMUTATA_H
#define KOMUTATA_H
#include "Engine.h"      // Engine sınıfının bildirimini içeren başlık dosyası
#include "FuelTank.h"    // FuelTank sınıfının bildirimini içeren başlık dosyası
class KomutAta {
private:
    Engine& engine;
    std::list<FuelTank> fuelTanks;

public:
    KomutAta();

    void komut_calistir(const std::string& input_file);
};

#endif // KOMUTATA_H
