#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <utility>

using namespace std;

class Flight
{
private:
    int numberOfFlights;
    int numberOfRunWays;
    int totalFeeToPay;
    vector<pair<vector<int>, int>> runways; // Da pra melhorar essa estrutura
    vector<bool> haveFlown;
    vector<int> departureTime;
    vector<int> timeToFlight;
    vector<int> fee ;
    vector<vector<int>> wakeTurbulence;
    vector<int> flightPenalties;

public:

    Flight(string file);
    Flight();
    ~Flight();
    int totalFee(int idxCurrent, int idxPrevious, int time);
    int bestFlight(int idxPrevious, int currentTime);
    void bestRunway ();
    void addTime(int whichRunway, int idxCurrent, int idxPrevious);
    void showInputs();
    int averageWakeTurbulence(int idx);
    void totalPenality();
    void vnd();

};

Flight::Flight(){}

void Flight::showInputs(){
    cout << numberOfFlights << endl;
    cout<< numberOfRunWays << endl << endl;

    // Vetor de tempos de partida
    for(int i=0; i< numberOfFlights; i++){
        cout << departureTime[i] << " ";
    }
    cout << endl << endl;
    // Vetor de tempo de partida/chegada
    for(int i=0; i< numberOfFlights; i++){    
        cout << timeToFlight[i] << " ";
    }        

    cout << endl << endl;

    for(int i=0; i< numberOfFlights; i++){    
        cout << fee[i] << " ";
    }    

    cout << endl << endl;


    // Matriz de tempos
    for(int i=0; i< numberOfFlights; i++){
        for(int j=0; j<numberOfFlights; j++){
            cout << wakeTurbulence[i][j] << " ";
        }  
        cout << endl;
    }
}

Flight::Flight(string file){
    
    ifstream readFile(file);
    int temp;

    cout << file << endl;

    if(!readFile.is_open()){
        cout << "Erro ao abrir o arquivo: " <<  file << endl;
        exit(EXIT_FAILURE); 
    }
    
    readFile >> numberOfFlights;
    readFile >> numberOfRunWays;

    // Vetor de tempos de partida
    for(int i=0; i< numberOfFlights; i++){
        readFile >> temp;
        departureTime.push_back(temp);
    }
    // Vetor de tempo de partida/chegada
    for(int i=0; i< numberOfFlights; i++){
        readFile >> temp;
        timeToFlight.push_back(temp);
    }
    // Vetor de multa para cada voo
    for(int i=0; i< numberOfFlights; i++){
        readFile >> temp;
        fee.push_back(temp);
    }
    
    // Alterar o tamanho dos vetores dentro dos vetores
    wakeTurbulence.resize(numberOfFlights);
    for (int i = 0; i < numberOfFlights; ++i) {
        wakeTurbulence[i].resize(numberOfFlights);
    }

    // Inicializa o vetor runways com o tamanho correto
    runways.resize(numberOfRunWays);

    // Matriz de tempos
    for(int i=0; i <  numberOfFlights; i++){
        for(int j=0; j < numberOfFlights; j++){
            readFile >> temp;
            wakeTurbulence[i][j] = temp;  
        }  
    }

    readFile.close();
}

Flight::~Flight(){

}

int Flight:: averageWakeTurbulence(int idx){
    int averageOfWakeTurbulence;
    for (size_t i = 0; i < numberOfFlights; i++)
    {
        averageOfWakeTurbulence += wakeTurbulence[idx][i];
    }
    return averageOfWakeTurbulence / numberOfFlights;
}

int Flight::totalFee(int idxCurrent, int idxPrevious, int currentTime){
    int time = (currentTime + wakeTurbulence[idxPrevious][idxCurrent] - departureTime[idxCurrent]);
    return time * fee[idxCurrent];
}

int Flight::bestFlight(int idxPrevious, int currentTime){

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
            if ((bestFlight != i) && (!haveFlown[i]))
            {
                if (totalFee(i, idxPrevious, currentTime) > totalFee(bestFlight, idxPrevious, currentTime))
                {
                    bestFlight = i;
                }
                if ((totalFee(i, idxPrevious, currentTime) == totalFee(bestFlight, idxPrevious, currentTime)))
                {
                    if (totalFee(i, bestFlight, currentTime + wakeTurbulence[bestFlight][i] + timeToFlight[bestFlight]) > totalFee(bestFlight, i, currentTime 
                        + wakeTurbulence[i][bestFlight] + timeToFlight[i]))
                    {
                        bestFlight = i;
                    }
                }
            }
        }
    }
    return bestFlight;
}

void Flight::addTime(int whichRunway, int idxCurrent, int idxPrevious){
    if (idxPrevious != -1)
    {
        if ((runways[whichRunway].second + wakeTurbulence[idxPrevious][idxCurrent])  < departureTime[idxCurrent])
        {
            runways[whichRunway].second = departureTime[idxCurrent] + timeToFlight[idxCurrent];
            return;
        }
        runways[whichRunway].second += wakeTurbulence[idxPrevious][idxCurrent] + timeToFlight[idxCurrent];
        return;
    }
    runways[whichRunway].second = departureTime[idxCurrent] + timeToFlight[idxCurrent];
}

void Flight::bestRunway() {
    // Limpa as pistas antes de alocar os voos
    for (int i = 0; i < numberOfRunWays; ++i) {
        runways[i].first.clear();
        runways[i].second = 0; // Reinicializa o tempo da pista
    }

    haveFlown.assign(numberOfFlights, false); // Reinicializa o vetor haveFlown

    // Reinicializa o vetor flightPenalties
    flightPenalties.assign(numberOfFlights, 0);

    // Aloca os voos para as pistas
    for (int i = 0; i < numberOfFlights; ++i) {
        int whichRunway = 0;
        for (int j = 1; j < numberOfRunWays; ++j) {
             
            if (runways[whichRunway].first.empty() || runways[j].first.empty())
            {
                if (runways[j].second < runways[whichRunway].second)
                {
                    
                    whichRunway = j;
                }
            }
            else
            {
                if (runways[j].second + averageWakeTurbulence(runways[j].first.back()) < runways[whichRunway].second //calcula a media das turbulencias de esteiras do voo anterior
                + averageWakeTurbulence(runways[whichRunway].first.back()))                                         // para adicionar ao "tempo" da pista.
                {
                    whichRunway = j;
                }
        }

        int bestIdx = bestFlight(runways[whichRunway].first.empty() ? -1 : runways[whichRunway].first.back(), runways[whichRunway].second);
        runways[whichRunway].first.push_back(bestIdx);
        
        // Calcula o tempo de inicio do voo
        int startTime = runways[whichRunway].second;
        if (!runways[whichRunway].first.empty()) {
            if (runways[whichRunway].first.size() > 1) {
                startTime += wakeTurbulence[runways[whichRunway].first[runways[whichRunway].first.size() - 2]][bestIdx];
            }
        }
        if (startTime < departureTime[bestIdx]) {
            startTime = departureTime[bestIdx];
        }

        // Calcula a multa e armazena no vetor flightPenalties
        flightPenalties[bestIdx] = (startTime - departureTime[bestIdx]) * fee[bestIdx];

        // Atualiza o tempo da pista
        runways[whichRunway].second = startTime + timeToFlight[bestIdx];

        haveFlown[bestIdx] = true;
    }

    // Exibe a alocação dos voos nas pistas
    cout << "Alocação dos voos nas pistas:" << endl;
    for (int i = 0; i < numberOfRunWays; ++i) {
        cout << "Pista " << i << ": ";
        for (int flightIdx : runways[i].first) {
            cout << flightIdx << " ";
        }
        cout << endl;
    }

    // Exibe as multas de cada voo
    cout << "Multas de cada voo:" << endl;
    for (int i = 0; i < numberOfFlights; ++i) {
        cout << "Voo " << i << ": " << flightPenalties[i] << endl;
    }
    totalPenality();

}

void Flight::totalPenality(){

    totalFeeToPay = 0;
    
    for(int i= 0; i <numberOfFlights; i++)
        totalFeeToPay += flightPenalties[i];

    cout << "Valor total Multa: " << totalFeeToPay << endl; 
}

void Flight::vnd(){
    int k = 1;
    int f = totalFeeToPay;
    int f1;

    while(k <= 3){
        switch(k){
            case 1:
                //f1 = swap(f)
                break;             
            case 2:
                //f1 = 2opt(f)
                break;
            case 3:
                //f1 = reinsertion(f)
                break;
        }

        if(f > f1){
            k = 1;
            f = totalFeeToPay;


        }


    }


    
}
