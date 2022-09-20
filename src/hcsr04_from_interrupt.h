#include "Arduino.h"
typedef unsigned char uint8_t;

namespace mrc{

    struct hcsr04Args{
        // measured distance in mm
        int distance = 0;
        // last set environment temperature
        int envTemperature = 22;
        // minimal distance in mm
        int minDistance = 20;
        // maximal distance in mm
        int maxDistance = 20;
        // raw echo start timestamp that was used by the last measurement
        unsigned long echoStartTimestamp = 0;
        // raw time the echo signal is high
        unsigned int EchoPeriode = 0;
    };

    // for this to work you have to manually attach the interrupt to a callback (<uniqe_callback>))
    // like attachInterrupt(digitalPinToInterrupt(<echoPin>), <uniqe_callback>, CHANGE);
    // for every instance insert void <uniqe_callback>() { <created_instance>.onChangeInterruptAction(); }
    // before setup() function to prevent scope issues
    class hcsr04_from_interrupt{
    public:
        hcsr04Args data;
        uint8_t triggerPin;
        uint8_t echoPin;
        void(*onValidMeasure)(hcsr04Args);
        void(*onInvalidMeasure)(hcsr04Args);
        void(*onMeasureStart)(hcsr04Args);
        void(*onMeasureEnd)(hcsr04Args);
        /*
        @param triggerPin don't has to be interruptable
        @param echoPin must be interruptable
        */
        hcsr04_from_interrupt(uint8_t triggerPin, uint8_t echoPin ,int initEnvTemp = 22);
        void trigger();
        // set this function as the callback for interrupt on the "echoPin"
        void onChangeInterruptAction();
    };
}