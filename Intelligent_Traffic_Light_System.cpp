// Anton Savelyev
// Project: Intelligent Traffic Light System (Final)
// Semester: Fall '15 @ Fresno State
// Class: CSCI 144
// Professor: Dr. Ming Li

// Instructions
// Change the CARS and RUN_TIME variable to the desired values.
// Compile in command line using: g++ -pthread Intelligent_Traffic_Light_System.cpp -o run.exe
// Run in command line by using: ./run.exe

#include <iostream>
#include <pthread.h>
#include <queue>
#include <cstdlib> //for rand()
#include <unistd.h> // for usleep()
#include <ctime> //for clock(), clock_t, CLOCKS_PER_SEC

#define CARS 100 // # cars all together
#define RUN_TIME 200 // seconds the program will wait for to allow all cars to pass

using namespace std;

int globalID; // global ID for each car arriving at the intersection

// a queue for each direction.
queue<int> northQ;
queue<int> eastQ;
queue<int> southQ;
queue<int> westQ;
queue<int> intersectionQ;

pthread_t threadID;

// a lock for each queue/direction.
pthread_mutex_t northLock;
pthread_mutex_t eastLock;
pthread_mutex_t southLock;
pthread_mutex_t westLock;
pthread_mutex_t intersectionQLock;

pthread_mutex_t globalIDLock; // lock for changing the globalid (i.e. car id)
pthread_mutex_t intersectionLock; // lock for one car passing through the intersection

int getrand(int min,int max) //return a number x s.t. min <= x < max
{
	     return(rand()%(max-min)+min);
}

void init()
{
    globalID = 1; //first car will have ID = 1
    pthread_mutex_init(&northLock, NULL);
    pthread_mutex_init(&eastLock, NULL);
    pthread_mutex_init(&southLock, NULL);
    pthread_mutex_init(&westLock, NULL);
    pthread_mutex_init(&intersectionQLock, NULL);
    pthread_mutex_init(&globalIDLock, NULL);
    pthread_mutex_init(&intersectionLock, NULL);
}

// This is a function for a car moving north.
void *north(void *null)
{

    int localID;
    double duration; //for checking how long a car will be waiting at the front of its lane
    clock_t start;

    pthread_mutex_lock(&northLock); // locking the queue
    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock);
    northQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock(&northLock);

    sleep(2); //say it takes 2 seconds to get to the intersection
    pthread_mutex_lock(&intersectionQLock);
    intersectionQ.push(localID);
    pthread_mutex_unlock(&intersectionQLock);
    start = clock(); // Now the car has arrived at intersection. Let's start the timer.

    while(1) //Checking cars properties here
    {
        if ((localID == northQ.front()) && (localID == intersectionQ.front())) // Current Car is in the front of the lane... Lets Proceed
        {
            break;
        }
        else //Current car is not in front on its lane. Lets wait
        {
            usleep(1); // sleep for 1 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    northQ.pop();
    intersectionQ.pop();
    cout << "Car from NORTH lane with ID: " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting at the light for: "<< duration<<" seconds."<<endl;
    sleep(3);
    cout << "Car from NORTH lane with ID: " << localID << " LEAVING the intersection." << endl<<endl;
    pthread_mutex_unlock(&intersectionLock);
}

void *east(void *null)
{

    int localID;
    double duration;
    clock_t start;

    pthread_mutex_lock(&eastLock); // locking the queue
    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock);
    eastQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock(&eastLock);

    sleep(2); //say it takes 2 seconds to get to the intersection
    pthread_mutex_lock(&intersectionQLock);
    intersectionQ.push(localID);
    pthread_mutex_unlock(&intersectionQLock);
    start = clock();

    while(1) //Checking cars properties here
    {
        if ((localID == eastQ.front()) && (localID == intersectionQ.front())) // Current Car is in the front of the lane... Lets Proceed
        {
            break;
        }
        else //Current car is not in front on its lane. Lets wait
        {
            usleep(1); // sleep for 1 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    eastQ.pop();
    intersectionQ.pop();
    cout << "Car from EAST lane with ID:  " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting at the light for: "<<duration<<" seconds."<<endl;
    sleep(3);
    cout << "Car from EAST lane with ID:  " << localID << " LEAVING the intersection." << endl <<endl;
    pthread_mutex_unlock(&intersectionLock);
}

void *south(void *null)
{

    int localID;
    double duration;
    clock_t start;

    pthread_mutex_lock (&southLock); // locking the queue
    pthread_mutex_lock (&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock (&globalIDLock);
    southQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock (&southLock);

    sleep(2); //say it takes 2 seconds to get to the intersection
    pthread_mutex_lock(&intersectionQLock);
    intersectionQ.push(localID);
    pthread_mutex_unlock(&intersectionQLock);
    start = clock();

    while(1) //Checking cars properties here
    {
        if ((localID == southQ.front()) && (localID == intersectionQ.front())) // Current Car is in the front of the lane... Lets Proceed
        {
            break;
        }
        else //Current car is not in front on its lane. Lets wait
        {
            usleep(1); // sleep for 1 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    southQ.pop();
    intersectionQ.pop();
    cout << "Car from SOUTH lane with ID: " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting at the light for: "<<duration<< " seconds."<<endl;
    sleep(3);
    cout << "Car from SOUTH lane with ID: " << localID << " LEAVING the intersection." << endl<<endl;
    pthread_mutex_unlock(&intersectionLock);
}

void *west(void *null)
{

    int localID;
    double duration;
    clock_t start;

    pthread_mutex_lock (&westLock); // locking the queue
    pthread_mutex_lock (&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock (&globalIDLock);
    westQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock (&westLock);

    sleep(2); //say it takes 2 seconds to get to the intersection
    pthread_mutex_lock(&intersectionQLock);
    intersectionQ.push(localID);
    pthread_mutex_unlock(&intersectionQLock);
    start = clock();

    while(1) //Checking cars properties here
    {
        if ((localID == westQ.front()) && (localID == intersectionQ.front())) // Current Car is in the front of the lane... Lets Proceed
        {
            break;
        }
        else //Current car is not in front on its lane. Lets wait
        {
            usleep(1); // sleep for 1 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    westQ.pop();
    intersectionQ.pop();
    cout << "Car from WEST lane with ID:  " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting for: "<< duration <<" seconds."<< endl;
    sleep(3);
    cout << "Car from WEST lane with ID:  " << localID << " LEAVING the intersection." << endl<<endl;
    pthread_mutex_unlock(&intersectionLock);
}

int main()
{
    init();
    srand(time(0));
    int k = 0;
    for(int i = 0; i < CARS; i++) //first car will be car with ID 1; Last ID is 40
    {
        k = getrand(1,5);
        if(k == 1)
        {
            pthread_create (&threadID, NULL, north, NULL);
        }
        else if (k == 2)
        {
            pthread_create (&threadID, NULL, east, NULL);
        }
        else if (k == 3)
        {
            pthread_create (&threadID, NULL, south, NULL);
        }
        else
        {
            pthread_create (&threadID, NULL, west, NULL);
        }
        sleep(1); //a car will be created every second.
    }
    sleep(RUN_TIME); //sleep for sufficient times to allow for all threads to finish running.
    cout << "Finished." << endl;
    return 0;
}
