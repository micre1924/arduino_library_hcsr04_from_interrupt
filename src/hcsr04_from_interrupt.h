#include "Arduino.h"

class hcsr04_from_interrupt{
public:
    int envTemperature = 22;
    int triggerPin = -1;
    int echoPin = -1;
    int distanceMM = -1;
    unsigned long echoStartTimestamp = 0;
    unsigned int triggerEchoPeriode = 0;

    /*
    @param triggerPin don't has to be interruptable
    @param echoPin must be interruptable
     */
    hcsr04_from_interrupt(int triggerPin, int echoPin ,int initEnvTemp = 22);
    void trigger(int envTemp);
    // set this function as the callback for interrupt on the "echoPin"
    void interruptAction();
};