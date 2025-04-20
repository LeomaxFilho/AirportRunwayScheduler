#include "Flight.hh"

/*int greedy(int numberOfFlights, int numberOfRunways, Flight flights, std::vector<std::vector<int>> wakeTurbulence,
std::vector<std::queue<int>>& runways){
        
    std::vector<int> time(2);
    for (int i = 0; i < 2; i++)
        time[i] = 0;

    for (int i = 0; i < numberOfFlights; i++)
    {

        
    }
    
        

}*/


int main(int argc, char *argv[]) {

    //std::cout << "Nome da instancia chamada: " << argv[1] << std::endl;

    Flight flights("../inputs/n5m50A.txt");

    flights.showInputs();

    flights.vnd();

    return 0;
}
