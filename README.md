Title: Intellignet Traffic Light System
Semester: Fall '15
Instructor: Dr. Ming Li
Institution: California State University, Fresno


Language: C++

Description: In this project, you are required to simulate an intelligent traffic light system with multithreading. A sensor is placed at each street intersection and communicates sensors in the car when close enough (50-100 meters). A FIFO queue is maintained by the sensor at the intersection to store RTP (Request To Pass) by cars. Cars whose request is at the HOL (Head of Line) is granted permission without stoping at the intersection. Your program should simulate random car arriving on the four directions and keeps running without deadlock, crashing, or unexpected termination.

Note: (i) FIFO queue can be considered a shared resources for all the cars when they arrive and leave; (ii) you can assume each car takes 3 seconds to drive through the intersection; (iii) turns are not required for implementation.

Bonus (15%): implement an improvement where N cars in one direction is given permission before allowing cars in another direction to pass. In addition, cars in opposite directions should be able to pass simultaneously without waiting for each other.

Bonus (10%): analyze the performance of your program through extensive experimental data. Metrics to analyze include average time to pass the intersection (waiting + time to drive through) and average waiting time. You can compare it with the "stop sign rule".
