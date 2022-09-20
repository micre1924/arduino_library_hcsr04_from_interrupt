#include <Arduino.h>
#include "hcsr04_from_interrupt.h"

namespace mrc{
	void hcsr04_from_interrupt::onChangeInterruptAction() {
		if(digitalRead(hcsr04_from_interrupt::echoPin)) {
			data.echoStartTimestamp = micros();
		}
		else {
			data.EchoPeriode = micros() - data.echoStartTimestamp;
			data.echoStartTimestamp = micros();
			data.distance = ( (331.3F + (0.606F * data.envTemperature)) * data.EchoPeriode ) / 2000;
			onMeasureEnd(data);
			if(data.distance > data.maxDistance || data.distance < data.minDistance ) onInvalidMeasure(data); else onValidMeasure(data);
		}
	}

	hcsr04_from_interrupt::hcsr04_from_interrupt(int triggerPin, int echoPin ,int initEnvTemp = 22){
		pinMode(echoPin, INPUT);
		pinMode(triggerPin, OUTPUT);
		this->triggerPin = triggerPin;
		this->echoPin = echoPin;
		data.envTemperature = initEnvTemp;
	}
	void hcsr04_from_interrupt::trigger(){
		digitalWrite(triggerPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(triggerPin, LOW);
		onMeasureStart(data);
	}
}