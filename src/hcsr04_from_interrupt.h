#include "Arduino.h"

// - static members is not the way this is planned, but for temporary function of the library tollerated
// - there is a temporary limit of one instance of this class because of the interruption management
class hcsr04_from_interrupt{
public:
    
    static int envTemperature;
    static int triggerPin;
    static int echoPin;
    static int distanceMM;
    static unsigned long echoStartTimestamp;
    static unsigned int triggerEchoPeriode;

    /*
    @param triggerPin don't has to be interruptable
    @param echoPin must be interruptable
     */
    hcsr04_from_interrupt(int triggerPin, int echoPin ,int initEnvTemp = 22);
    void trigger(int envTemp);
    // set this function as the callback for interrupt on the "echoPin"
    static void onChangeInterrupt();
};