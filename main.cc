#include "Flight.hh"

int greedy(int numberOfFlights, int numberOfRunways, Flight flights, std::vector<std::vector<int>> wakeTurbulence,
std::vector<std::queue<int>>& runways){
        
    std::vector<int> time(2);
    for (int i = 0; i < 2; i++)
        time[i] = 0;

    for (int i = 0; i < numberOfFlights; i++)
    {

        
    }
    
        

}




int main(int argc, const char** argv) {

    int numberOfFlights = 6;
    int numberOfRunways = 2;
    Flight flights(numberOfFlights, numberOfRunways);
    std::vector<std::queue<int>> runways (numberOfRunways);



    return 0;
}
