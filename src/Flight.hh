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
    string instancia;

public:

    Flight(string file);
    Flight();
    ~Flight();
    void writeFile();
    int totalFee(int idxCurrent, int idxPrevious, int time);
    int bestFlight(int idxPrevious, int currentTime);
    void addTime(int whichRunway, int idxCurrent, int idxPrevious);
    void showInputs();
    int swapLine(int f, vector<pair<vector<int>, int>> &runwaysTemp);
    int opt2(int totalFee, vector<pair<vector<int>, int>> &runwaysTemp);
    void reinsertionMove(vector<pair<vector<int>, int>> &runway, int idxfirst, int idxsecond, int howRunway);
    int reinsertion(int totalFee, vector<pair<vector<int>, int>> &runwaysTemp);
    int throughRunways(int totalFee, vector<pair<vector<int>, int>> &vetor);
    void vnd();
    void bestRunway ();
    int calculateTotalPenalty(vector<pair<vector<int>, int>> runwaysTemp);
};
