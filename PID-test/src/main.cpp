/********************************************************
 * PID Proportional on measurement Example
 * Setting the PID to use Proportional on measurement will
 * make the output move more smoothly when the setpoint
 * is changed.  In addition, it can eliminate overshoot
 * in certain processes like sous-vides.
 ********************************************************/
#include <Arduino.h>
#include <PID_v2.h>

#define PIN_INPUT 0
#define PIN_OUTPUT 3

// Specify the links and initial tuning parameters
PID_v2 myPID(2, 5, 1, PID::Direct, PID::P_On::Measurement);


void updateLeftDrive()
{
	curSpeedL -= mySign(curSpeedL - cmdSpeedL);

	int balancedSpeedValue = abs(curSpeedL * motorBiasL);


	if (curSpeedL > 0) {
		digitalWrite(LeftDirectPin1, LOW);
		digitalWrite(LeftDirectPin2, HIGH);
		analogWrite(speedPinL, balancedSpeedValue);
	}
	if (curSpeedL < 0) {
		digitalWrite(LeftDirectPin1, HIGH);
		digitalWrite(LeftDirectPin2, LOW);
		analogWrite(speedPinL, balancedSpeedValue);
	}
	if (curSpeedL == 0) {
		digitalWrite(LeftDirectPin1, LOW);
		digitalWrite(LeftDirectPin2, LOW);
	}
}

void updateRightDrive()
{
	curSpeedR -= mySign(curSpeedR - cmdSpeedR);

	int balancedSpeedValue = abs(curSpeedR * motorBiasR);


	if (curSpeedR > 0) {
		digitalWrite(RightDirectPin1, LOW);
		digitalWrite(RightDirectPin2, HIGH);
		analogWrite(speedPinR, balancedSpeedValue);
	}
	if (curSpeedR < 0) {
		digitalWrite(RightDirectPin1, HIGH);
		digitalWrite(RightDirectPin2, LOW);
		analogWrite(speedPinR, balancedSpeedValue);
	}
	if (curSpeedR == 0) {
		digitalWrite(RightDirectPin1, LOW);
		digitalWrite(RightDirectPin2, LOW);
	}
}





// Read a line from Serial.input
// May take PID values and speed to try
void readInput() {

}

// Run the test from 0 to speed and store results
void runTest() {
  // Set motor stopped

  // Start the PID

  // Loop n times:
  //    read & store values
  //    calculate PID output
  //    update motor speed
  // endLoop
  // Stop motor

}

// Print out the data captured
void outputResults() {

}

void setup() {
  carSetup();

  myPID.Start(analogRead(PIN_INPUT),  // input
              0,                      // current output
              100);                   // setpoint
  
}

void loop() {
  readInput();
  runTest();
  outputResults();

  const double input = analogRead(PIN_INPUT);
  const double output = myPID.Run(input);
  analogWrite(PIN_OUTPUT, output);
}

