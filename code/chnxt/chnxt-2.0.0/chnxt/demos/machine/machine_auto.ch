/* File name: machine_auto.ch
 *
 * Demonstrate the CH Mindstorms Control Package's ability 
 * to control the machine robot model autonomously, as well 
 * as demonstrate how to collect and plot sensor data from the NXT.*/

#include <conio.h>
#include <stdio.h>
#include <chplot.h>
#include <nxt.h>

CPlot plot;
ChNXT nxt;
double speedRatio = 0.30;
int quit = 0,                   //used to exit for loop
    i,                          //counter variable
    status;                     //stores status of function
int ultraValue, position;
double gearratio = (8.0 / 56) * (1.0 / 24);
enum {numpoints = 20};          //desired number of data points
const int anglestep = 2;	//angle moved between steps
double angle[numpoints];        //angle calculated from the tachometer
double distance[numpoints];     //data received from the ultrasonic sensor

/* Connect to NXT exit if failure */
if (nxt.connect()) {
    printf("\nPress any key to quit.");
    while (!_kbhit());          //wait for key press
    exit(-1);
}

/* Initialize arm. (Set sensor types and initialize variables) */
printf("\nInitializing arm for autonomous control...\n");
status = nxt.setSensor(NXT_SENSORPORT4, 
        NXT_SENSORTYPE_ULTRASONIC, NXT_SENSORMODE_RAWMODE);
if (status) {
    printf("\nSensor Setup failed. Exiting program.");
    while (!_kbhit());          //wait for key press
    nxt.disconnect();	        //stop interfacing. This also stops the motors.
    exit(-1);
}

for (i = 0; i < numpoints; i++) {
    angle[i] = 0;
    distance[i] = 0;
}

/* print usage information to the user*/
printf("\n%d Data points will be collected with a"
       "step size of %d.", numpoints, anglestep);
printf("\nPlease ensure that the arm can rotate"
       "%d degrees from its current position.", 
       (numpoints*anglestep));
printf("\nPress any key to continue. Press q at any time to quit.");

if (getch() == 'q') {
    printf("\nQuitting program.");
    delay(1.5);
    exit(0);
}

/* begin Autonomous loop*/
for (i = 0; i < numpoints; i++) {
    printf("hello\n");
    /* get sensor data, if success print data, else print error*/
    if ((nxt.getSensor(NXT_SENSORPORT4, ultraValue)) == 0) {
        distance[i] = ultraValue;
        if ((nxt.getJointAngle(NXT_JOINTA, angle[i])) == 0) {
            printf("\nSample: %d,  distance: %d,  Angle: %lf",
                   i, distance[i], angle[i]);
        }
    }else	
        printf("\nError!");

    /* check if q was pressed and if so exit program*/
    if (!_kbhit) {
        if (getch() == 'q') {
            printf("\nQuitting program.");
            break;
        }
    }
    /* rotate arm by anglestep (rotate motor anglestep/gear ratio)*/
    nxt.moveJoint(NXT_JOINTA, anglestep / gearratio);
    delay(1);
}

/* Stop interfacing. This also stops the motors and sensors.*/
nxt.disconnect();
printf("\n");

/* plot data in Ch */
plot.polarPlot(PLOT_ANGLE_DEG);
plot.data2DCurve(angle, distance, numpoints);
plot.sizeRatio(1);
plot.grid(PLOT_ON);
plot.plotting();
