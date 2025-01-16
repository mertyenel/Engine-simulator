#include "KomutAta.h"
using namespace std;

int main() {
    string inputFileName;   
    string outputFileName;
    cout << "Enter the input file name and output file name(first one is input): ";
    cin >> inputFileName >> outputFileName; 
    freopen(outputFileName.c_str(), "w", stdout); 

    srand(time(NULL));
    KomutAta komut_ata;
    komut_ata.komut_calistir(inputFileName); 
    return 0;
}
