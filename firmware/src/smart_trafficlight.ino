#include "trafficlight.h"

#define TRAFFIC_DURATION 5000

int trigger_pin = 46;
Trafficlight trafficlight1(4,5,6);
Trafficlight trafficlight2(9,10,11);

void setup(){


}

void loop(){
    static bool road = 0;
    static unsigned long previousTime = 5000;
    static int traffic_delay = 5000;
    static bool is_triggered;

    is_triggered = digitalRead(trigger_pin);

    if(is_triggered){
        if(road == 0)
        {
           traffic_delay = 20000; 
        }
        else if(road == 1)
        {
            traffic_delay = 500;
        }
    }        
    

    //TODO: create an interrupt to change traffic_delay and 
    //change priority to ambulance lane

    if((millis() - previousTime) > traffic_delay ){
        if(!is_triggered)
        {
           changePriority(road);
            //reset to normal traffic
            traffic_delay = TRAFFIC_DURATION;
            road = !road;
        }
        else if(is_triggered)
        {
            traffic_delay = 10000;
        }
        previousTime = millis();
    }
}


void changePriority(bool road)
{
    //ambulance lane
    if(road){
        trafficlight2.clear();
        trafficlight2.ready();
        delay(1000);
        trafficlight2.stop();
        delay(500);
        trafficlight1.go();
    }

    else{
        trafficlight1.clear();
        trafficlight1.ready();
        delay(1000);
        trafficlight1.stop();
        delay(500);
        trafficlight2.go();
    }
}