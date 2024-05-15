/*
    Julia Zirinsky
    Description: A program that uses a heap-priority queue to simulate a landers
    descent
    Input: 2 separate files. a lander input file and a simulation file
    Output: The program must output the landers status maintaining the
    heap-priority queu order 
*/

#ifndef LANDER_H
#define LANDER_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

class lander
{
public:
    lander(double = 0, double = 0, double = 0, double = 0, double = 0, int = 0);
    double get_velocity() const;
    double get_altitude() const;
    double get_fuel_amount() const;
    int get_id() const;
    double get_mass() const;
    char get_status() const;
    bool change_flow_rate(double);
    void simulate();
    bool operator>(const lander&) const;

private:
    double flow_rate;
    double velocity;
    double altitude;
    double fuel_amount;
    bool stillLanding;
    int id;
    int timesSimulated;
    double LANDER_MASS;
    double MAX_FUEL_CONSUMPTION_RATE;
    double MAX_THRUST;
};

//default constructor
lander::lander(double m, double mThrust, double mf, double a, double f, int id)
      : flow_rate(0), velocity(0), altitude(a), fuel_amount(f), stillLanding(true), id(id),
        timesSimulated(0), LANDER_MASS(m), MAX_FUEL_CONSUMPTION_RATE(mf), MAX_THRUST(mThrust) {}

//getter functions
double lander::get_velocity() const {return velocity;}
double lander::get_altitude() const {return altitude;}
double lander::get_fuel_amount() const {return fuel_amount;}
int lander::get_id() const {return id;}
double lander::get_mass() const {return LANDER_MASS;}
char lander::get_status() const
{
    if(stillLanding)
    {
        return 'a';  //airborne
    }
    else if(velocity <= -2)
    {
        return 'c';  //crashed
    }
    else
    {
        return 'l';  //landed
    }
}

//function to change the fuel flow within a valid range
bool lander::change_flow_rate(double r) 
{
    if(r >= 0 && r <= 1 && fuel_amount > 0)
    {
        flow_rate = r;
        return true;
    }

    return false;
}

//function to simulate lander's descent
void lander::simulate()
{
    const double NUM = 1.62;
    const double TIME = 1.0;

    if(stillLanding)
    {
        double v = TIME*((flow_rate*MAX_THRUST)/(LANDER_MASS+fuel_amount))-NUM;
        velocity += v;
        altitude += TIME*velocity;

        //check if landed
        if(altitude <= 0)
        {
            stillLanding = false;
            altitude = 0;
        }

        //update fuel amount based on fuel consumption rate
        fuel_amount -= TIME*MAX_FUEL_CONSUMPTION_RATE*fabs(v);

        if(fuel_amount < 0)
        {
            fuel_amount = 0;
        }

        timesSimulated++;
    }
}

//used to compare lander objects
bool lander::operator>(const lander &rhs) const
{
    if(timesSimulated != rhs.timesSimulated)
    {
        return timesSimulated < rhs.timesSimulated;
    }
    else if(altitude != rhs.altitude)
    {
        return altitude < rhs.altitude;
    }
    else if(fuel_amount != rhs.fuel_amount)
    {
        return fuel_amount < rhs.fuel_amount;
    }
    else if(LANDER_MASS != rhs.LANDER_MASS)
    {
        return LANDER_MASS > rhs.LANDER_MASS;
    }
    else{
        return id < rhs.id;
    }
}

template <class Type>
class priorityQ
{
public:
    priorityQ(int = 10);
    priorityQ(const priorityQ<Type> &);
    ~priorityQ();
    const priorityQ<Type> &operator=(const priorityQ<Type> &);
    void insert(const Type &);
    void deleteHighestPriority();
    Type getHighestPriority() const;
    bool isEmpty() const;
    void bubbleUp(int);
    void bubbleDown(int);
    int getSize() const;

private:
    int capacity;
    int items;
    Type *heapArray;
};

//default constructor
template <class Type>
priorityQ<Type>::priorityQ(int capacity) : capacity(capacity), items(0)
{
    heapArray = new Type[capacity + 1];
}

//copy constructor
template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type> &copy) 
{
    capacity = copy.capacity;
    items = copy.items;
    heapArray = new Type[capacity];

    for(int i = 0; i < items; i++)
    {
        heapArray[i] = copy.heapArray[i];
    }    
}

//destructor
template <class Type>
priorityQ<Type>::~priorityQ() 
{
    delete[] heapArray;
}

//deep copy assignment operator
template <class Type>
const priorityQ<Type> &priorityQ<Type>::operator=(const priorityQ<Type> &rhs) 
{
    //check for self-assignment
    if(this == &rhs)
    {
        return *this;
    }

    delete[] heapArray;

    capacity = rhs.capacity;
    items = rhs.items;
    heapArray = new Type[rhs.capacity + 1];

    for(int i = 0; i <= items; i++)
    {
        heapArray[i] = rhs.heapArray[i];
    }

    return *this;
}

template <class Type>
void priorityQ<Type>::insert(const Type &element)
{
    if(items == capacity)
    {
        //if array is full, double capacity
        Type *heapArray2 = new Type[capacity*2];

        for(int i = 0; i <= items; i++)
        {
            heapArray2[i] = heapArray[i];
        }

        delete[] heapArray;
        heapArray = heapArray2;
    }

    heapArray[items] = element;

    //bubbleup to maintain heap-properties
    bubbleUp(items++);
}

//function to delete element with the highest priority
template <class Type>
void priorityQ<Type>::deleteHighestPriority()
{
    if(!isEmpty())
    {
        //replace root with last element and bubbledown
        heapArray[0] = heapArray[items - 1];
        items--;
        bubbleDown(0);
    }

    return;
}

//function to get element with the highest priority
template <class Type>
Type priorityQ<Type>::getHighestPriority() const {return heapArray[0];}

//function to see if priority queue is empty
template <class Type>
bool priorityQ<Type>::isEmpty() const {return items == 0;}

//move an element up in the heap
template <class Type>
void priorityQ<Type>::bubbleUp(int index) 
{
    int parent = (index - 1) / 2;

    while(index > 0 && heapArray[index] > heapArray[parent])
    {
        //swap element with parent if it has a higher priority
        swap(heapArray[index], heapArray[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }

}

//move an element down in the heap
template <class Type>
void priorityQ<Type>::bubbleDown(int index) 
{
    do
    {
        int ltChild = 2 * index + 1;
        int rtChild = 2 * index + 2;
        int max;

        //find chid with highest priority
        if(rtChild < items && heapArray[rtChild] > heapArray[ltChild])
        {
            max = rtChild;
        }
        else
        {
            max = ltChild;
        }

        //swap with the higher priority child if needed
        if(max < items && heapArray[max] > heapArray[index])
        {
            swap(heapArray[index], heapArray[max]);
            index = max;
        }
        else
        {
            break;
        }
    } while (index < (items / 2));
}

//function to get the size of the priority Queue
template <class Type>
int priorityQ<Type>::getSize() const {return items;}

///////////////////////////////////////////////////////////
//////NON-MEMBER  HELPER FUNCTIONS/////////////////////////
///////////////////////////////////////////////////////////

//non-member helper function to check if a file is open
bool checkFileOpen(ifstream& file, const string& filename)
{
    if(!file.is_open())
    {
        cout << "Error: Unable to open the file '" << filename << "'.\n";
        return false;
    }

    return true;
}

//non-member helper template function to read lander info from file and populate a priorityQ
template <class Type>
void readLanderFile(const string& filename, priorityQ<Type> &pQueue)
{
    double m, mThrust, mf, a, f;
    int id;

    ifstream lFile(filename);
    checkFileOpen(lFile, filename);

    while(lFile >> m >> mThrust >> mf >> a >> f >> id)
    {
        Type lander2(m, mThrust, mf, a, f, id);
        pQueue.insert(lander2);
    }

    lFile.close();
}

//non-member helper function to print lander info
void printLanderInfo(lander& l)
{
    cout << "Rocket " << l.get_id() << endl
         << "Fuel: " << l.get_fuel_amount() << endl
         << "Altitude: " << l.get_altitude() << endl
         << "Velocity: " <<l.get_velocity() << endl << endl;
}

//non-member helper function to print mission status
void printMissionStatus(lander& l)
{
    cout << "\nLander ID:  " << l.get_id() 
         << " Altitude: " << l.get_altitude()
         << " mission aborted." ;
}

//non-member helper template function to simulate the landing process from a sim file
template <class Type>
void simulateLanding(string &simFile, priorityQ<Type> &pQueue)
{
    double fRate;
    bool check;

    ifstream sFile(simFile);
    checkFileOpen(sFile, simFile);

    while(sFile >> fRate && !pQueue.isEmpty())
    {
        check = false;

        //valid input check
        while(!check)
        {
            if(sFile.fail())
            {
                sFile.clear();
                sFile.ignore('\n');
            }

            if(fRate >= 0 && fRate <= 1)
            {
                check = true;
            }
        }

        //get the lander with the highest priority and print its info
        lander hPriority = pQueue.getHighestPriority();
        printLanderInfo(hPriority);

        //update the flow rate, simulate the landing, and print status
        hPriority.change_flow_rate(fRate);
        hPriority.simulate();

        char landerStatus = hPriority.get_status();

        if(landerStatus == 'c')
        {
            cout << "Rocket ID: " << hPriority.get_id() << " has crashed :( At least nobody was on board\n\n";    
        }
        else
        {
            //insert updated lander into pQueue
            pQueue.insert(hPriority);
        }

        //remove element with highest priority from the queue
        pQueue.deleteHighestPriority();
    }

    cout << "\nThere are landers still trying to land...";

    //print status of remaining landers
    while(!pQueue.isEmpty())
    {
        lander landing = pQueue.getHighestPriority();
        printMissionStatus(landing);
        pQueue.deleteHighestPriority();
    }

    cout << endl;
    sFile.close();
}

#endif