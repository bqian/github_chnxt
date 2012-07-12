/************************************************************
machine_auto.ch
Machine Robot Autonomous Data Collection Example
By Joshua Galbraith
Modified by Binsen Qian

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the machine robot model
autonomously, as well as demonstrate how to collect and plot
sensor data from the NXT.
*************************************************************/

#include <conio.h>
#include <stdio.h>
#include <chplot.h>
#include <nxt.h>

FILE *stream;
CPlot plot;
ChNXT nxt;
int speed=30;
int quit = 0,    //used to exit for loop
        i,           //counter variable
        result;      //stores result of function
int ultraValue, position;
double gearratio = (8.0 / 56) * (1.0 / 24);
enum {numpoints = 90};  //desired number of data points
const int anglestep = 2;	//angle moved between steps
double angle[numpoints];//angle calculated from the tachometer
int distance[numpoints];//data received from the ultrasonic sensor

/* Connect to NXT exit if failure */
if (!nxt.connect()) {
    printf("\nPress any key to quit.");
    while (!_kbhit()); //wait for key press
    exit(0);
}

/* Initialize arm. (Set sensor types and initialize variables) */
printf("\nInitializing arm for autonomous control...\n");
result = nxt.setSensor(PORT_3, ULTRASONIC, RAWMODE);
if (result == 0) {
    printf("\nSensor Setup failed. Exiting program.");
    while (!_kbhit());  //wait for key press
    nxt.disconnect();	//stop interfacing. This also stops the motors.
    exit(0);
}
for (i = 0; i < numpoints; i++) {
    angle[i] = 0;
    distance[i] = 0;
}

/* print usage information to the user*/
printf("\n%d Data points will be collected with a"
       "step size of %d.", numpoints, anglestep);
printf("\nPlease ensure that the arm can rotate"
       "%d degrees from its current position.", (numpoints*anglestep));
printf("\nPress any key to continue. Press q at any time to quit.");
if (getch() == 'q') {
    printf("\nQuitting program.");
    Sleep(1500);
    exit(0);
}

/* begin Autonomous loop*/
for (i = 0; i < numpoints; i++) {
    /* get sensor data, if success print data, else print error*/
    if ((ultraValue = nxt.getSensor(PORT_3))) {
        distance[i] = ultraValue;
        if ((position = nxt.getTacho(ROBOT_JOINT3))) {
            angle[i] = (position * gearratio);
            printf("\nSample: %d,  distance: %d,  Angle: %f",
                   i, distance[i], angle[i]);
        }
    }
    else	
        printf("\nError!");
    /* check if q was pressed and if so exit program*/
    if (!_kbhit) {
        if (getch() == 'q') {
            printf("\nQuitting program.");
            break;
        }
    }
    /* rotate arm by anglestep (rotate motor anglestep/gear ratio)*/
    nxt.moveJoint(ROBOT_JOINT3, (anglestep / gearratio));
    Sleep(1000);

} //end of for(i=0;i<numpoints-1;i++)

/* Stop interfacing. This also stops the motors and sensors.*/
nxt.disconnect();
printf("\n");


//log data to the file output.csv
stream = fopen("output.csv", "w");
for (i = 0; i < numpoints; i++) {
    fprintf(stream, "%f,%d\n", angle[i], distance[i]);
}
fclose(stream);

//plot data in CH using a polar graph
plot.polarPlot(PLOT_ANGLE_DEG);
plot.data2D(angle, distance);
plot.sizeRatio(1);
plot.grid(PLOT_ON);
plot.plotting();

//wait for user and exit program
printf("Data plotted.\nPress any key to exit.");
while (!_kbhit()); //wait for key press
