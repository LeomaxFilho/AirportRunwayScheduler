#include "Flight.hh"
#include <chrono>


int main(int argc, char *argv[]) {

    std::string file(argv[1]);
    Flight flights(file);

    auto startGuloso = chrono::high_resolution_clock::now();
    flights.bestRunway();
    auto endGuloso = chrono::high_resolution_clock::now();
    
    // Tempo do Guloso 
    auto durationGuloso = chrono::duration_cast<chrono::microseconds>(endGuloso - startGuloso);
    cout << "Tempo de Execucao Guloso: " << (durationGuloso.count() / 1000.0) << " milisegundos\n";
     
    auto startVND = chrono::high_resolution_clock::now();
    flights.vnd();
    auto endVND = chrono::high_resolution_clock::now();

    // Tempo do VND
    auto durationVND = chrono::duration_cast<chrono::microseconds>(endVND - startVND);
    cout << "Tempo de Execucao VND: " << (durationVND.count() / 1000.0) << " milisegundos\n";

    return 0;
}
