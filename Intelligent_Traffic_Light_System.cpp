// Anton Savelyev
// Project: Intelligent Traffic Light System
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

#define CARS 10 // # cars coming from each direction. 40 cars total
#define RUN_TIME 125 // 125 seconds (5 seconds longer than it should take to run)

using namespace std;

int globalID; // global ID for each car arriving at the intersection

queue<int> globalQ; //a global Q

pthread_t threadID;
// a lock for each queue/direction and for the intersection (globalQ).
pthread_mutex_t globalQLock;
pthread_mutex_t globalIDLock; // lock for changing the globalid (i.e. car id)
pthread_mutex_t intersectionLock; // lock for one car passing through the intersection

int getrand(int min,int max) //return a number x s.t. min <= x < max
{
	     return(rand()%(max-min)+min);
}

void init()
{
    globalID = 1; //first car will have ID = 1
    pthread_mutex_init(&globalIDLock, NULL);
    pthread_mutex_init(&intersectionLock, NULL);
    pthread_mutex_init(&globalQLock, NULL);
}
// Now will test to create an intersection with only 1 direction. North
void *north(void *null)
{
    int localID;
    double duration; //for checking how long a car will be waiting at the front of its lane
    clock_t start; //variable will be used to calculate wait time

    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock); // releasing globalID

    usleep(getrand(100000, 1000000)); //lets say it takes somewhere between 1/10th of a second and 1 seconds to get to the intersection.
    pthread_mutex_lock(&globalQLock); // locking the queue to push car
    globalQ.push(localID);
    pthread_mutex_unlock(&globalQLock);
    start = clock(); // Now the car has arrived at intersection. Let's start the timer.


    while(1) //Checking cars properties here
    {
        if (localID == globalQ.front()) // Current Car is in the front of its lane and first at the intersection. Lets Proceed
        {
            break;
        }
        else //Current car is not first in line. Lets wait
        {
            usleep(10); // sleep for 10 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC; //car will go through the intersecion. this is how long it has been waiting.
    globalQ.pop(); // taking it off the line
    cout << "Car from NORTH lane with ID: " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting at the light for: "<< duration<<" seconds."<<endl;
    sleep(3); // takes 3 seconds to drive through the intersection
    cout << "Car from NORTH lane with ID: " << localID << " LEAVING the intersection." << endl<<endl;
    pthread_mutex_unlock(&intersectionLock); //releasing the intersection
}

void *east(void *null)
{
    int localID;
    double duration; //for checking how long a car will be waiting at the front of its lane
    clock_t start; //variable will be used to calculate wait time

    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock); // releasing globalID

    usleep(getrand(100000, 1000000)); //lets say it takes somewhere between 1/10th of a second and 1 seconds to get to the intersection.
    pthread_mutex_lock(&globalQLock); // locking the queue to push car
    globalQ.push(localID);
    pthread_mutex_unlock(&globalQLock);
    start = clock(); // Now the car has arrived at intersection. Let's start the timer.

    while(1) //Checking cars properties here
    {
        if (localID == globalQ.front()) // Current Car is in the front of its lane and first at the intersection. Lets Proceed
        {
            break;
        }
        else //Current car is not first in line. Lets wait
        {
            usleep(10); // sleep for 10 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    globalQ.pop();
    cout << "Car from EAST lane with ID:  " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting at the light for: "<<duration<<" seconds."<<endl;
    sleep(3);
    cout << "Car from EAST lane with ID:  " << localID << " LEAVING the intersection." << endl <<endl;
    pthread_mutex_unlock(&intersectionLock); // give other cars a chance to pass
}


void *south(void *null)
{
    int localID;
    double duration; //for checking how long a car will be waiting at the front of its lane
    clock_t start; //variable will be used to calculate wait time

    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock); // releasing globalID

    usleep(getrand(100000, 1000000)); //lets say it takes somewhere between 1/10th of a second and 1 seconds to get to the intersection.
    pthread_mutex_lock(&globalQLock); // locking the queue to push car
    globalQ.push(localID);
    pthread_mutex_unlock(&globalQLock);
    start = clock(); // Now the car has arrived at intersection. Let's start the timer.

    while(1) //Checking cars properties here
    {
        if (localID == globalQ.front()) // Current Car is in the front of its lane and first at the intersection. Lets Proceed
        {
            break;
        }
        else //Current car is not first in line. Lets wait
        {
            usleep(10); // sleep for 10 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    globalQ.pop();
    cout << "Car from SOUTH lane with ID: " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting at the light for: "<<duration<< " seconds."<<endl;
    sleep(3);
    cout << "Car from SOUTH lane with ID: " << localID << " LEAVING the intersection." << endl<<endl;
    pthread_mutex_unlock(&intersectionLock); // give other cars a chance to pass
}


void *west(void *null)
{
    int localID;
    double duration; //for checking how long a car will be waiting at the front of its lane
    clock_t start; //variable will be used to calculate wait time

    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock); // releasing globalID

    usleep(getrand(100000, 1000000)); //lets say it takes somewhere between 1/10th of a second and 1 seconds to get to the intersection.

    pthread_mutex_lock(&globalQLock); // locking the queue to push car
    globalQ.push(localID);
    pthread_mutex_unlock(&globalQLock);
    start = clock(); // Now the car has arrived at intersection. Let's start the timer.

    while(1) //Checking cars properties here
    {
        if (localID == globalQ.front()) // Current Car is in the front of its lane and first at the intersection. Lets Proceed
        {
            break;
        }
        else //Current car is not first in line. Lets wait
        {
            usleep(10); // sleep for 10 microsecond to allow for other cars to proceed if they must
            continue;
        }
    }
    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    globalQ.pop();
    cout << "Car from WEST lane with ID:  " << localID << " ENTERING the intersection." << endl;
    cout << "It has been waiting for: "<< duration <<" seconds."<< endl;
    sleep(3);
    cout << "Car from WEST lane with ID:  " << localID << " LEAVING the intersection." << endl<<endl;
    pthread_mutex_unlock(&intersectionLock); // give other cars a chance to pass
}

int main()
{
    init();
    srand(time(0));
    for(int i = 0; i < CARS; i++) //first car will be car with ID 1; Last ID is 40
    {
        pthread_create (&threadID, NULL, north, NULL);
        pthread_create (&threadID, NULL, east, NULL);
        pthread_create (&threadID, NULL, south, NULL);
        pthread_create (&threadID, NULL, west, NULL);
        usleep(10);
    }
    sleep(RUN_TIME); //sleep for sufficient times to allow for all threads to finish running.
    cout << "Finished." << endl;
    return 0;
}
