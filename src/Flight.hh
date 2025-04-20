#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <queue>
#include <utility>
#include <cstdlib>
#include <ctime>
//#include <windows.h>

using namespace std;

class Flight
{
private:
    int numberOfFlights;
    int numberOfRunWays;
    int totalFeeToPay;
    vector<pair<vector<int>, int>> runways; 
    vector<bool> haveFlown;
    vector<int> departureTime;
    vector<int> timeToFlight;
    vector<int> fee ;
    vector<vector<int>> wakeTurbulence;

public:

    Flight(string file);
    Flight();
    ~Flight();
    int totalFee(int idxCurrent, int idxPrevious, int time);
    int bestFlight(int idxPrevious, int currentTime);
    void addTime(int whichRunway, int idxCurrent, int idxPrevious);
    void showInputs();
    int swapLine(int f, vector<pair<vector<int>, int>> &runwaysTemp);
    int opt2(int totalFee, vector<pair<vector<int>, int>> &runwaysTemp);
    void reinsertionMove(vector<pair<vector<int>, int>> &runway, int idxfirst, int idxsecond, int howRunway);
    int reinsertion(int totalFee, vector<pair<vector<int>, int>> &runwaysTemp);
    void vnd();
    void bestRunway ();
    int calculateTotalPenalty(vector<pair<vector<int>, int>> runwaysTemp);
    

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
                    if (fee[i] < fee[bestFlight])
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

// Tirar o calculo da multa total desta funcao
void Flight::bestRunway() {
    // Limpa as pistas antes de alocar os voos
    for (int i = 0; i < numberOfRunWays; ++i) {
        runways[i].first.clear();
        runways[i].second = 0; // Reinicializa o tempo da pista
    }

    haveFlown.assign(numberOfFlights, false); // Reinicializa o vetor haveFlown

    // Aloca os voos para as pistas
    for (int i = 0; i < numberOfFlights; ++i) {
        int whichRunway = 0;
        for (int j = 0; j < numberOfRunWays; ++j) {
            if (runways[j].second < runways[whichRunway].second) {
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

        // Atualiza o tempo da pista
        runways[whichRunway].second = startTime + timeToFlight[bestIdx];

        haveFlown[bestIdx] = true;
    }

    // Exibe a alocação dos voos nas pistas
    cout << "\nAlocacao dos voos nas pistas:" << endl;
    for (int i = 0; i < numberOfRunWays; ++i) {
        cout << "Pista " << i << ": ";
        for (int flightIdx : runways[i].first) {
            cout << flightIdx << " ";
        }
        cout << endl;
    }
    totalFeeToPay = calculateTotalPenalty(runways);
    cout << "Multa total: " << totalFeeToPay << endl;
}

int Flight::calculateTotalPenalty(vector<pair<vector<int>, int>> runwaysTemp) {
    int totalPenalty = 0;
    for (int i = 0; i < numberOfRunWays; ++i) {
        int currentTime = 0;
        int previousFlight = -1;
        for (int flightIdx : runwaysTemp[i].first) {
            // Calcula o tempo de inicio do voo
            int startTime = currentTime;
            if (previousFlight != -1) {
                startTime += wakeTurbulence[previousFlight][flightIdx];
            }
            if (startTime < departureTime[flightIdx]) {
                startTime = departureTime[flightIdx];
            }

            // Calcula a multa e adiciona à penalidade total
            totalPenalty += (startTime - departureTime[flightIdx]) * fee[flightIdx];

            // Atualiza o tempo atual da pista
            currentTime = startTime + timeToFlight[flightIdx];
            previousFlight = flightIdx;
        }
    }
    return totalPenalty;
}

int Flight::swapLine(int totalFee, vector<pair<vector<int>, int>> &runway){

    int totalFee0 = totalFee;
    int totalFeeSwap;
    vector<pair<vector<int>, int>> runwaysTemp = runway;
    vector<pair<vector<int>, int>> bestRunway = runwaysTemp;
    int TEMP;

    for (int i = 0; i < numberOfRunWays; i++)
    {
        for (int j = 0; j < runwaysTemp[i].first.size(); j++)
        {
            for (int k = j + 1; k < runwaysTemp[i].first.size(); k++)
            {
                TEMP = runwaysTemp[i].first[j];
                runwaysTemp[i].first[j] = runwaysTemp[i].first[k];
                runwaysTemp[i].first[k] = TEMP;

                totalFeeSwap = calculateTotalPenalty(runwaysTemp);
                if (totalFeeSwap < totalFee0)
                {
                    totalFee0 = totalFeeSwap;
                    bestRunway[i].first = runwaysTemp[i].first;
                }
                runwaysTemp[i].first = runway[i].first;
            }
        }
    }
    runway = bestRunway;
    return totalFee0;
}

int Flight::opt2(int totalFee, vector<pair<vector<int>, int>> &runwaysTemp){
    
    int totalFee1;
    int totalFee2 = totalFee;
    
    vector<pair<vector<int>, int>> runwaysTemp2 = runwaysTemp;
    vector<pair<vector<int>, int>> bestRunway = runwaysTemp2;

    // Implementar o SWAP entre os voos das pistas
    for (int i= 0; i< numberOfRunWays; i++){
        if(runwaysTemp[i].first.size() < 4)
            continue;

        for (int j = 0; j< runwaysTemp[i].first.size(); j++){
            for (int k = j + 4 ; k <= runwaysTemp[i].first.size(); k++){
                
                reverse(runwaysTemp2[i].first.begin() + j, runwaysTemp2[i].first.begin() + k );
                
                totalFee1 = calculateTotalPenalty(runwaysTemp2);
            
                if(totalFee1 < totalFee2)
                {
                    totalFee2 = totalFee1;
                    bestRunway[i].first = runwaysTemp2[i].first;
                }
                runwaysTemp2[i].first = runwaysTemp[i].first;
            }
        }
    }

    // Retorna a melhor solucao e o valor da multa
    runwaysTemp = bestRunway;
    return totalFee2;    
}

void Flight::reinsertionMove(vector<pair<vector<int>, int>> &runway, int idxfirst, int idxsecond, int howRunway)
{
    
    int TEMP = runway[howRunway].first[idxsecond];
    int TEMP2;

    runway[howRunway].first[idxsecond] = runway[howRunway].first[idxfirst];

    for (int i = idxsecond - 1; i >= idxfirst; i--)
    {
        TEMP2 = runway[howRunway].first[i];
        runway[howRunway].first[i] = TEMP;
        TEMP = TEMP2;
    }
}

int Flight::reinsertion(int totalFee, vector<pair<vector<int>, int>> &runwaysTemp){

    
    int totalFee1;
    int totalFee2 = totalFee;
    int temp;

    vector<pair<vector<int>, int>> runwaysTemp0 = runwaysTemp;
    vector<pair<vector<int>, int>> bestRunway = runwaysTemp0;

    for (int i = 0; i < numberOfRunWays; i++)
    {
        for (int j = 0; j < runwaysTemp0[i].first.size(); j++)
        {
            
            for (int k = j + 2; k < runwaysTemp0[i].first.size(); k++)
            {

                reinsertionMove(runwaysTemp0, j, k, i);

                totalFee1 = calculateTotalPenalty(runwaysTemp0);
                if(totalFee1 < totalFee2)
                {
                    totalFee2 = totalFee1;

                    bestRunway[i].first = runwaysTemp0[i].first;
                }
                runwaysTemp0[i].first = runwaysTemp[i].first;
            }
        }
    }
    // Retorna a melhor solucao e o valor da multa
    runwaysTemp = bestRunway;
    return totalFee2;    
}

void Flight::vnd(){

    // Euristica Construtiva
    bestRunway();

    int totalFee = totalFeeToPay;
    int totalFee1;
    int k=1;
    int cont=0;
    vector<pair<vector<int>, int>> runwaysTemp = runways; 

    int qtdNbh[3] = {0,0,0};
    
    while(k <= 3){
        switch(k){
         case 1:
            totalFee1 = swapLine(totalFee, runwaysTemp);
            ++qtdNbh[0];
            break;
        case 2:
            totalFee1 = opt2(totalFee, runwaysTemp);
            ++qtdNbh[1];
            break;
        case 3:
            totalFee1 = reinsertion(totalFee, runwaysTemp);
            ++qtdNbh[2];
            break;
        default: break;
        }

        if (totalFee1 < totalFee){
            totalFee = totalFee1; // Atualiza valor da solucao calculada
            runways = runwaysTemp; // Atualiza representacao da solucao
            k = 1;
        }else{
            k++;
        }
        cont++;
    }
    
    
    cout << "\nPista depois do VND" << endl;
    cout << "Alocacao dos voos nas pistas:" << endl;
    for (int i = 0; i < numberOfRunWays; ++i) {
        cout << "Pista " << i << ": ";
        for (int flightIdx : runways[i].first) {
            cout << flightIdx << " ";
        }
        cout << endl;
    }

    cout << "Valor total multa anterior (GULOSO): " << totalFeeToPay<< endl;
    cout << "Valor total multa nova (VND): " << totalFee << endl;

    cout << "\n\n----------------------------------------------\n";
    cout << "Movimentos de vizinhanca" << endl;
    for(int i=0; i<3; i++){
        switch (i+1)
        {
        case 1:
            cout << "SWAP - " << qtdNbh[i] << endl;
            break;
        case 2:
            cout << "OPT2 - " << qtdNbh[i] << endl;
            break;

        case 3:
            cout << "REINSERTION - " << qtdNbh[i] << endl;
            break;
        default:
            break;
        }
    }

    cout << "Repeticoes no While - " << cont << endl;
}



