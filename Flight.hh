#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <utility>

#ifndef FLIGHT
#define FLIGHT

class Flight
{
private:
    int numberOfFlights;
    int numberOfRunWays;
    std::vector<std::pair<std::queue<int>, int>> runways = std::vector<std::pair<std::queue<int>, int>>(2);
    std::vector<bool> haveFlown = {0,0,0,0,0,0};
    std::vector<int> departureTime = {5, 25, 15, 40, 75, 50};
    std::vector<int> timeToFlight = {15, 25, 20, 30, 15, 25};
    std::vector<int> fee = {55, 90, 61, 120, 45, 50};
    std::vector<std::vector<int>> wakeTurbulence = {
        {0, 10, 15, 8, 21, 15},
        {10, 0, 10, 13, 15, 20},
        {17, 9, 0, 10, 14, 8},
        {11, 13, 12, 0, 10, 10},
        {5, 10, 15, 20, 0, 12},
        {5, 10, 15, 20, 28, 0}
    };
public:
    Flight(int numberOfFlights, int numberOfRunWays);
    ~Flight();
    int totalFee(int idxCurrent, int idxPrevious, int time);
    int bestFlight(int idxPrevious, int actualTime);
    int bestRunway (int actualTime);
    int addTime(int whichRunway, int idxCurrent, int idxPrevious);
};

/**
* TODO - Deve ser implementado um construtor para que seja possível adicionar o arquivo
* TODO - diretamente do arquivo de texte de **input**
*/ 
Flight::Flight(int numberOfFlights, int numberOfRunWays){
}

Flight::~Flight(){

}

int Flight::totalFee(int idxCurrent, int idxPrevious, int actualTime){
    int time = (actualTime + departureTime[idxCurrent] + wakeTurbulence[idxPrevious][idxCurrent] - timeToFlight[idxCurrent]);
    return time * fee[idxCurrent];
}

int Flight::bestFlight(int idxPrevious, int actualTime){

    int bestFlight = -1;
    for (int i = 0; i < numberOfFlights; ++i) {
        if (!haveFlown[i]) {
            bestFlight = i;
            break;
        }
    }
    if (bestFlight == -1)
    {
        return -1;
    }
    
    if (idxPrevious == -1)
    {

        for (int i = 0; i < numberOfFlights; i++)
        {
            if ((bestFlight != i) && (!haveFlown[i]))
            {
                if (departureTime[i] < departureTime[bestFlight])
                    bestFlight = i;
                if (departureTime[bestFlight] == departureTime[i])
                {
                    if (timeToFlight[i] < timeToFlight[bestFlight])
                    {
                        bestFlight = i;
                    }
                }
            }
        }
    }else{

        for (int i = 0; i < numberOfFlights; i++)
        {
            if (((i != idxPrevious) && (bestFlight != i))&& (!haveFlown[i]))
            {
                if ((totalFee(i, idxPrevious, actualTime) > totalFee(bestFlight, idxPrevious, actualTime)) )
                {
                    bestFlight = i;
                }
                if ((totalFee(i, idxPrevious, actualTime) == totalFee(bestFlight, idxPrevious, actualTime)))
                {
                    if (timeToFlight[i] < timeToFlight[bestFlight])
                    {
                        bestFlight = i;
                    }
                }
            }
        }
    }
    return bestFlight;
}

int Flight::addTime(int whichRunway, int idxCurrent, int idxPrevious){
    if (idxPrevious != -1)
    {
        if ((runways[whichRunway].second + wakeTurbulence[idxPrevious][idxCurrent])  < departureTime[idxCurrent])
        {
            runways[whichRunway].second = departureTime[idxCurrent] + timeToFlight[idxCurrent];
            return 1;
        }
        runways[whichRunway].second += wakeTurbulence[idxPrevious][idxCurrent] + timeToFlight[idxCurrent];
        return 1;
    }
    runways[whichRunway].second = departureTime[idxCurrent] + timeToFlight[idxCurrent];
    return 1;
}

int Flight::bestRunway (int actualTime){

    int bestIdx = 0;
    int whichRunway = 0;
    for (int i = 0; i < numberOfFlights; i++)
    {
        whichRunway = i % numberOfRunWays;
        if (runways[whichRunway].first.empty())
        {
            bestIdx = bestFlight(-1, 0);
            runways[whichRunway].first.push(bestIdx);
            addTime(whichRunway, bestIdx, -1);
            haveFlown[bestIdx] = true;
            continue;
        }
        bestIdx = bestFlight(runways[whichRunway].first.back(), runways[whichRunway].second);
        runways[whichRunway].first.push(bestIdx);
        addTime(whichRunway, bestIdx, runways[whichRunway].first.back());
        haveFlown[bestIdx] = true;
        continue;
    }

    return 1;
}


#endif !FLIGHT