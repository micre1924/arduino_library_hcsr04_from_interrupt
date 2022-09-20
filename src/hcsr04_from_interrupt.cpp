#include <Arduino.h>
#include "hcsr04_from_interrupt.h"

namespace mrc{

	void nullCallback(hcsr04Args) {};

	void hcsr04_from_interrupt::onChangeInterruptAction() {
		if(digitalRead(hcsr04_from_interrupt::echoPin)) {
			data.echoStartTimestamp = micros();
			onEchoStarted(data);
		}
		else {
			data.EchoPeriode = micros() - data.echoStartTimestamp;
			data.echoStartTimestamp = micros();
			data.distance = ( (331.3F + (0.606F * data.envTemperature)) * data.EchoPeriode ) / 2000;
			onFinishedMeasurement(data);
			if(data.distance > data.maxDistance || data.distance < data.minDistance ) onInvalidMeasurement(data); else onValidMeasurement(data);
		}
	}

	hcsr04_from_interrupt::hcsr04_from_interrupt(uint8_t triggerPin, uint8_t echoPin, uint16_t minDistance, uint16_t maxDistance, int initEnvTemp){
		pinMode(echoPin, INPUT);
		pinMode(triggerPin, OUTPUT);
		this->triggerPin = triggerPin;
		this->echoPin = echoPin;
		data.envTemperature = initEnvTemp;
		data.minDistance = minDistance;
		data.maxDistance = maxDistance;
	}
	void hcsr04_from_interrupt::trigger(){
		digitalWrite(triggerPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(triggerPin, LOW);
		onMeasuring(data);
	}
}