/*
    Julia Zirinsky
    Description: A program that uses a heap-priority queue to simulate a landers
    descent
    Input: 2 separate files. a lander input file and a simulation file
    Output: The program must output the landers status maintaining the
    heap-priority queue order 
*/

#include <iostream>
#include "lander.h"

using namespace std;

int main()
{
    string landerFile, simFile;

    //priority queue of landers
    priorityQ<lander> pQueue;

    //prompt user for lander file
    cout << "Enter lander file: ";
    cin >> landerFile;

    //read lander info from file and populate the priority queue
    readLanderFile(landerFile, pQueue);

    //prompt user for simulation file
    cout << "Enter simulation file: ";
    cin >> simFile;

    //simulate using the provided simulation file.
    simulateLanding(simFile, pQueue);

    return 0;
}
