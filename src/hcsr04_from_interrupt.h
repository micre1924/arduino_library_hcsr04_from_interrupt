#include "Arduino.h"

namespace mrc{

    struct hcsr04Args{
        // measured distance in mm
        uint16_t distance;
        // last set environment temperature
        int envTemperature;
        // minimal distance in mm
        uint16_t minDistance;
        // maximal distance in mm
        uint16_t maxDistance;
        // raw echo start timestamp that was used by the last measurement
        uint64_t echoStartTimestamp;
        // raw time the echo signal is high
        uint16_t EchoPeriode;
    };

    void nullCallback(hcsr04Args);

    // for this to work you have to manually attach the interrupt to a callback (<uniqe_callback>))
    // like attachInterrupt(digitalPinToInterrupt(<echoPin>), <uniqe_callback>, CHANGE);
    // for every instance insert void <uniqe_callback>() { <created_instance>.onChangeInterruptAction(); }
    // before setup() function to prevent scope issues
    class hcsr04_from_interrupt{
    public:
        hcsr04Args data;
        uint8_t triggerPin;
        uint8_t echoPin;
        void(*onValidMeasurement)(hcsr04Args) = nullCallback;
        void(*onInvalidMeasurement)(hcsr04Args) = nullCallback;
        void(*onMeasuring)(hcsr04Args) = nullCallback;
        void(*onFinishedMeasurement)(hcsr04Args) = nullCallback;
        void(*onEchoStarted)(hcsr04Args) = nullCallback;
        /*
        @param triggerPin don't has to be interruptable
        @param echoPin must be interruptable
        */
        hcsr04_from_interrupt(uint8_t triggerPin, uint8_t echoPin, uint16_t minDistance = 20, uint16_t maxDistance = 4000, int initEnvTemp = 22);
        void trigger();
        // set this function as the callback for interrupt on the "echoPin"
        void onChangeInterruptAction();
    };
}