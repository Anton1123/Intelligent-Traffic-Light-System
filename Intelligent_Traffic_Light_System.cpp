// Anton Savelyev
// Project: Intelligent Traffic Light System
// Semester: Fall '15 @ Fresno State
// Class: CSCI 144
// Professor: Dr. Ming Li

// Instructions
// Compile in command line using: g++ -pthread Intelligent_Traffic_Light_System.cpp -o run.exe
// Run in command line by using: ./run.exe

#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h> // for usleep()

#define CARS 10 // # cars coming from each direction. 40 cars total
#define RUN_TIME 125 // 125 seconds (5 seconds longer than it should take to run)

using namespace std;

int globalID; // global ID for each car arriving at the intersection

// a queue for each direction.
queue<int> northQ;
queue<int> eastQ;
queue<int> southQ;
queue<int> westQ;

pthread_t threadID;

// a lock for each queue/direction.
pthread_mutex_t northLock;
pthread_mutex_t eastLock;
pthread_mutex_t southLock;
pthread_mutex_t westLock;

pthread_mutex_t globalIDLock; // lock for changing the globalid (i.e. car id)
pthread_mutex_t intersectionLock; // lock for one car passing through the intersection

// Now will test to create an intersection with only 1 direction. North

void init()
{
    globalID = 1; //first car will have ID = 1
    pthread_mutex_init(&northLock, NULL);
    pthread_mutex_init(&eastLock, NULL);
    pthread_mutex_init(&southLock, NULL);
    pthread_mutex_init(&westLock, NULL);
    pthread_mutex_init(&globalIDLock, NULL);
    pthread_mutex_init(&intersectionLock, NULL);
}

void *north(void *null)
{

    int localID;
    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock);

    pthread_mutex_lock(&northLock); // locking the queue
    northQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock(&northLock);

    while(1) //Checking cars properties here
    {
        pthread_mutex_lock(&northLock); // Lock the north lane to check if car is in the front of the lane
        if (localID == northQ.front()) // Current Car is in the front of the lane... Lets Proceed
            break;
        else //Current car is not in front on its lane. Lets wait
        {
            pthread_mutex_unlock(&northLock); //Give other cars a chance to pass to the intersection
            usleep(3); // sleep for 3 microsecond to allow for other cars to proceed if they must
            continue;
        }

    }

    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    cout << "Car from NORTH lane with ID: " << localID << " ENTERING the intersection." << endl;
    sleep(3);
    cout << "Car from NORTH lane with ID: " << localID << " LEAVING the intersection." << endl;
    pthread_mutex_unlock(&intersectionLock); // give other cars a chance to pass

    pthread_mutex_unlock(&northLock); //Unlocking north Lane 

    pthread_mutex_lock(&northLock);//Locking north lane mutex before popping
    northQ.pop();
    pthread_mutex_unlock(&northLock);
}


void *east(void *null)
{

    int localID;
    pthread_mutex_lock(&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock(&globalIDLock);

    pthread_mutex_lock(&eastLock); // locking the queue
    eastQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock(&eastLock);

    while(1) //Checking cars properties here
    {
        pthread_mutex_lock(&eastLock); // Lock the east lane to check if car is in the front of the lane
        if (localID == eastQ.front()) // Current Car is in the front of the lane... Lets Proceed
            break;
        else //Current car is not in front on its lane. Lets wait
        {
            pthread_mutex_unlock(&eastLock); //Give other cars a chance to pass to the intersection
            usleep(3); // sleep for 3 microsecond to allow for other cars to proceed if they must
            continue;
        }

    }

    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    cout << "Car from EAST lane with ID:  " << localID << " ENTERING the intersection." << endl;
    sleep(3);
    cout << "Car from EAST lane with ID:  " << localID << " LEAVING the intersection." << endl;
    pthread_mutex_unlock(&intersectionLock); // give other cars a chance to pass

    pthread_mutex_unlock(&eastLock); //Unlocking east Lane 

    pthread_mutex_lock(&eastLock);//Locking east lane mutex before popping
    eastQ.pop();
    pthread_mutex_unlock(&eastLock);
}


void *south(void *null)
{

    int localID;
    pthread_mutex_lock (&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock (&globalIDLock);

    pthread_mutex_lock (&southLock); // locking the queue
    southQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock (&southLock);

    while(1) //Checking cars properties here
    {
        pthread_mutex_lock (&southLock); // Lock the south lane to check if car is in the front of the lane
        if (localID == southQ.front()) // Current Car is in the front of the lane... Lets Proceed
            break;
        else //Current car is not in front on its lane. Lets wait
        {
            pthread_mutex_unlock (&southLock); //Give other cars a chance to pass to the intersection
            usleep(3); // sleep for 1 microsecond to allow for other cars to proceed if they must
            continue;
        }

    }

    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    cout << "Car from SOUTH lane with ID: " << localID << " ENTERING the intersection." << endl;
    sleep(3);
    cout << "Car from SOUTH lane with ID: " << localID << " LEAVING the intersection." << endl;
    pthread_mutex_unlock(&intersectionLock); // give other cars a chance to pass

    pthread_mutex_unlock(&southLock); //Unlocking south Lane 

    pthread_mutex_lock(&southLock);//Locking south lane mutex before popping
    southQ.pop();
    pthread_mutex_unlock(&southLock);
}


void *west(void *null)
{

    int localID;
    pthread_mutex_lock (&globalIDLock); // locking globalIDLock mutex in order to update globalID
    localID = globalID++; // update globalID after reserving that ID for a car in north lane
    pthread_mutex_unlock (&globalIDLock);

    pthread_mutex_lock (&westLock); // locking the queue
    westQ.push(localID); // pushing the local car into northQ.
    pthread_mutex_unlock (&westLock);

    while(1) //Checking cars properties here
    {
        pthread_mutex_lock (&westLock); // Lock the west lane to check if car is in the front of the lane
        if (localID == westQ.front()) // Current Car is in the front of the lane... Lets Proceed
            break;
        else //Current car is not in front on its lane. Lets wait
        {
            pthread_mutex_unlock (&westLock); //Give other cars a chance to pass to the intersection
            usleep(3); // sleep for 3 microsecond to allow for other cars to proceed if they must
            continue;
        }

    }

    // Car is in the front so let's proceed to allow it to pass through intersection.
    pthread_mutex_lock(&intersectionLock); // need to lock the intersection. Function call will block until mutex is available
    cout << "Car from WEST lane with ID:  " << localID << " ENTERING the intersection." << endl;
    sleep(3);
    cout << "Car from WEST lane with ID:  " << localID << " LEAVING the intersection." << endl;
    pthread_mutex_unlock(&intersectionLock); // give other cars a chance to pass

    pthread_mutex_unlock(&westLock); //Unlocking west Lane 

    pthread_mutex_lock(&westLock);//Locking west lane mutex before popping
    westQ.pop();
    pthread_mutex_unlock(&westLock);
}


int main()
{
    init();

    for(int i = 0; i < CARS; i++) //first car will be car with ID 1; Last ID is 40
    {
        pthread_create (&threadID, NULL , north, NULL);
        pthread_create (&threadID, NULL , east, NULL);
        pthread_create (&threadID, NULL , south, NULL);
        pthread_create (&threadID, NULL , west, NULL);
    }
    sleep(RUN_TIME); //sleep for sufficient times to allow for all threads to finish running.

    cout << "Finished." << endl;

    return 0;
}
