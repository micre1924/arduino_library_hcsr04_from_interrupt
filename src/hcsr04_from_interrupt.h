#include "Arduino.h"

// for this to work you have to manually attache the interrupt to a callback (<uniqe_callback>))
// like attachInterrupt(digitalPinToInterrupt(<echoPin>), <uniqe_callback>, CHANGE);
// for every instance insert void <uniqe_callback>() { <created_instance>.onChangeInterruptAction(); }
// before setup() function to prevent scope issues
class hcsr04_from_interrupt{
public:
    
    int envTemperature;
    int triggerPin;
    int echoPin;
    int distanceMM;
    unsigned long echoStartTimestamp;
    unsigned int triggerEchoPeriode;

    /*
    @param triggerPin don't has to be interruptable
    @param echoPin must be interruptable
     */
    hcsr04_from_interrupt(int triggerPin, int echoPin ,int initEnvTemp = 22);
    void trigger();
    // set this function as the callback for interrupt on the "echoPin"
    void onChangeInterruptAction();
};