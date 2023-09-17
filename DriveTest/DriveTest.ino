#include "Arduino.h"
#include <Servo.h>
#include <Motor.h>


#define Echo_PIN    2 // Ultrasonic Echo pin connect to D11
#define Trig_PIN    3  // Ultrasonic Trig pin connect to D12

// Global variables & defs:
// Distance sensor:
#define Echo_PIN    2 // Ultrasonic Echo pin connect to D11
#define Trig_PIN    3  // Ultrasonic Trig pin connect to D12
#define SERVO_PIN     11
Servo head;

// Motors:
Motor leftMotor = Motor(LEFT);
Motor rightMotor = Motor(RIGHT);

// Report:
long lastCount2 = 0;
long lastCount3 = 0;
unsigned long lastMicros = 0;

void printCounts(long count2, long count3) {
	unsigned long nowMicros = micros();
	unsigned long time   = nowMicros - lastMicros;

	unsigned long speed2 = (count2 - lastCount2) * 1000000 / time;
	unsigned long speed3 = (count3 - lastCount3) * 1000000 / time;

	Serial.print(time);
	Serial.print(" : 2: ");
	Serial.print(count2);
	Serial.print(" - ");
	Serial.print(speed2);
	Serial.print(" count/s ** 3: ");
	Serial.print(count3);
	Serial.print(" - ");
	Serial.print(speed3);
	Serial.print(" count/s.");
	Serial.println("");


	lastMicros = nowMicros;
	lastCount2 = count2;
	lastCount3 = count3;
}


//The setup function is called once at startup of the sketch
void setup()
{
	/*init servo*/
	head.attach(SERVO_PIN);
	head.write(90);

	// Init both motors
	leftMotor.setup();
	rightMotor.setup();

	Serial.begin(9600);
	Serial.println("\n*** Motor Drive Test ***");

	// Start test:
	Serial.println("Start motors for 2 secs");

	unsigned long startMillis = millis();



	while(millis() - startMillis < 10000) {
		leftMotor.drive(20);
		rightMotor.drive(20);

	}

}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
}
