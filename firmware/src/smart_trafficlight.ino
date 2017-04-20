#include "trafficlight.h"

Trafficlight trafficlight1(4,5,6);
Trafficlight trafficlight2(9,10,11);

void setup(){


}

void loop(){
    static bool road = 0;
    static unsigned long previousTime = 5000;
    static int traffic_delay = 5000;

    //TODO: create an interrupt to change traffic_delay and 
    //change priority to ambulance lane

    if( (millis() - previousTime) > traffic_delay ){
        road = !road;
        changePriority(road);
        //reset to normal traffic
        traffic_delay = 5000;
        previousTime = millis();
    }
}

void changePriority(bool road)
{
    //ambulance lane
    if(road){
        trafficlight2.clear();
        trafficlight2.ready();
        delay(2000);
        trafficlight2.stop();
        delay(1000);
        trafficlight1.go();
    }

    else{
        trafficlight1.clear();
        trafficlight1.ready();
        delay(2000);
        trafficlight1.stop();
        delay(1000);
        trafficlight2.go();
    }
}