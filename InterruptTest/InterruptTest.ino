#include "Arduino.h"
#include <Servo.h>
#define SERVO_PIN     11
#define LPT 2 // scan loop counter
#define BUZZ_PIN     13

#define IN1  7    //Right motor(K1/K2) direction Pin 1
#define IN2  8    //Right motor(K1/K2) direction Pin 2
#define IN3  9    //Left motor(K3/K4) direction Pin 1
#define IN4  10   //Left motor(K3/K4) direction Pin 2
#define ENA  5    //ENA PWM speed pin for Right motor(K1/K2)
#define ENB  6    //ENB PWM speed pin for Left motor(K3/K4)

#define Echo_PIN    2 // Ultrasonic Echo pin connect to D11
#define Trig_PIN    3  // Ultrasonic Trig pin connect to D12

Servo head;
volatile unsigned long count2=0;
volatile unsigned long count3=0;
unsigned long prior_count=0;

void pulse2() {
	count2++;
}


void pulse3() {
	count3++;
}

void go_Advance()  //motor rotate clockwise -->robot go ahead
{
	digitalWrite(IN4,HIGH);
	digitalWrite(IN3,LOW);
	digitalWrite(IN2,HIGH );
	digitalWrite(IN1,LOW);
}
void stop_Stop() //motor brake -->robot stop
{
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4,LOW);
	set_Motorspeed(0,0);
}

/*set motor speed */
void set_Motorspeed(int lspeed,int rspeed) //change motor speed
{
	analogWrite(ENB,lspeed);//lspeed:0-255
	analogWrite(ENA,rspeed);//rspeed:0-255
}

void setup() {
//	pinMode(2, INPUT_PULLUP);
//	pinMode(3, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(2),pulse2,CHANGE);
	attachInterrupt(digitalPinToInterrupt(3),pulse3,CHANGE);

	/******L298N******/
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	pinMode(ENA, OUTPUT);
	pinMode(ENB, OUTPUT);

	stop_Stop();//stop move
	/*init HC-SR04*/
	// pinMode(Trig_PIN, OUTPUT);
	// pinMode(Echo_PIN,INPUT);
	// digitalWrite(Trig_PIN,LOW);
	/*init buzzer*/
	pinMode(BUZZ_PIN, OUTPUT);
	digitalWrite(BUZZ_PIN, HIGH);
	/*init servo*/
	head.attach(SERVO_PIN);
	head.write(90);
	delay(2000);
	Serial.begin(9600);

	Serial.println("\n*** Interrupt Test ***");
}

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

void loop() {
	long new_count2 = 0;
	long new_count3 = 0;

	Serial.println("Start motors for 10 secs");
	lastMicros = micros();
	set_Motorspeed(220, 220);
	go_Advance();

	unsigned long startMillis = millis();
	unsigned long lastTime = millis();

	while(millis() - startMillis < 10000) {
		new_count2 = count2;
		new_count3 = count3;

		if (new_count2 + new_count3 != prior_count) {
			printCounts(new_count2, new_count3);
			prior_count = new_count2 + new_count3;
		}

		delay(100); // print at reasonable speed
	}

	Serial.println("Stop motors for 10 secs");
	stop_Stop();
	delay(500);
	while(millis() - startMillis < 20000){
		new_count2 = count2;
		new_count3 = count3;

		if (new_count2 + new_count3 != prior_count) {
			printCounts(new_count2, new_count3);
			prior_count = new_count2 + new_count3;
		}

		delay(10); // print at reasonable speed
	}
	count2 = count3 = 0;
}
