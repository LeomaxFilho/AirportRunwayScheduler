/*
void Flight::bestRunway() {
    // Limpa as pistas antes de alocar os voos
    for (int i = 0; i < numberOfRunWays; ++i) {
        runways[i].first.clear(); // Limpa o vetor da pista
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
        runways[whichRunway].first.push_back(bestIdx); // Adiciona o voo ao vetor da pista
        
        // Verifica se a pista está vazia antes de passar o voo anterior para addTime
        int previousFlight = -1;
        if (!runways[whichRunway].first.empty()) {
            if (runways[whichRunway].first.size() > 1) {
                previousFlight = runways[whichRunway].first[runways[whichRunway].first.size() - 2];
            }
        }
        addTime(whichRunway, bestIdx, previousFlight);

        haveFlown[bestIdx] = true;
    }

    // Exibe a alocação dos voos nas pistas
    std::cout << "\nAlocacao dos voos nas pistas:" << std::endl;
    for (int i = 0; i < numberOfRunWays; ++i) {
        std::cout << "Pista " << i << ": ";
        for (int flightIdx : runways[i].first) {
            std::cout << flightIdx << " ";
        }
        cout << " tempo - " << runways[i].second;
        std::cout << std::endl;
    }
}*/


/*
// TODO adicionar o critério para usar a pista que esta livre primeiro sempre..
// TODO algo como olhar o tempo atual de cada uma delas e decidir qual delas é a melhor para o momento
void Flight::bestRunway (){

    int bestIdx = 0;
    int whichRunway = 0;

    for (int i = 0; i < numberOfFlights; i++)
    {
        for (int j = 0; j < numberOfRunWays; j++)
        {
            if (runways[j].second < runways[whichRunway].second)
            {
                whichRunway = j;
            }
        }
        bestIdx = bestFlight(runways[whichRunway].first.back(), runways[whichRunway].second);
        addTime(whichRunway, bestIdx, runways[whichRunway].first.back());
        haveFlown[bestIdx] = true;
    }
}*/
//#endif !FLIGHT

/**
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
 */