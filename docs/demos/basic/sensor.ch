/* File name: sensor.ch
 * A breif introduction of using sensors of NXT.*/

#include <nxt.h>

ChNXT nxt;

/* Setup sensors and check sensor connection */
int status1=2, status2=2;

/* Variables to store values gotten from NXT */
int touchValue, ultraValue;

/* Connect to NXT */
nxt.connect();

/* Save status of NXT_SENSORPORT1, and NXT_SENSORPORT4 */
status1 = nxt.setSensor(NXT_SENSORPORT1, 
            NXT_SENSORTYPE_TOUCH, NXT_SENSORMODE_BOOLEANMODE);

status2 = nxt.setSensor(NXT_SENSORPORT4,
            NXT_SENSORTYPE_ULTRASONIC, NXT_SENSORMODE_RAWMODE);
    
/* Check connection status sensors connection */
if(status1) {
    printf("Fail to setup sensors.\n");
    exit(-1);
}
    
if(status2) {
    printf("Fail to setup sensors.\n");
    exit(-1);
}

/* get values collected by sensors from NXT */
nxt.getSensor(NXT_SENSORPORT1, touchValue);
nxt.getSensor(NXT_SENSORPORT4, ultraValue);

/* display the values we got onto the screen */
printf("Touch sensor: %d\n", touchValue);
printf("Ultrasonic sensor: %d\n", ultraValue);
