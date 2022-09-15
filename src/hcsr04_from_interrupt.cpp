#include <Arduino.h>
#include "hcsr04_from_interrupt.h"

void hcsr04_from_interrupt::onChangeInterruptAction() {
	if(digitalRead(hcsr04_from_interrupt::echoPin)) {
		echoStartTimestamp = micros();
	}
	else {
		triggerEchoPeriode = micros() - echoStartTimestamp;
		echoStartTimestamp = micros();
		distanceMM = ( (331.3F + (0.606F * envTemperature)) * triggerEchoPeriode ) / 2000;
	}
}

hcsr04_from_interrupt::hcsr04_from_interrupt(int triggerPin, int echoPin ,int initEnvTemp = 22){
	pinMode(echoPin, INPUT);
	pinMode(triggerPin, OUTPUT);
	this->triggerPin = triggerPin;
	this->echoPin = echoPin;
	this->envTemperature = initEnvTemp;
}
void hcsr04_from_interrupt::trigger(){
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
}