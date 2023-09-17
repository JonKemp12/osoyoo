/*
 */

#define speedPinR 5    //  RIGHT PWM pin connect MODEL-X ENA
#define RightDirectPin1  7    //Right Motor direction pin 1 to MODEL-X IN1
#define RightDirectPin2  8    //Right Motor direction pin 2 to MODEL-X IN2
#define speedPinL 6    // Left PWM pin connect MODEL-X ENB
#define LeftDirectPin1  9    //Left Motor direction pin 1 to MODEL-X IN3
#define LeftDirectPin2  10   //Left Motor direction pin 1 to MODEL-X IN4

/***************motor control***************/




void updateLeftDrive(int speed)
{

	int balancedSpeedValue = abs(speed);


	if (speed > 0) {
		digitalWrite(LeftDirectPin1, LOW);
		digitalWrite(LeftDirectPin2, HIGH);
		analogWrite(speedPinL, balancedSpeedValue);
	}
	if (speed < 0) {
		digitalWrite(LeftDirectPin1, HIGH);
		digitalWrite(LeftDirectPin2, LOW);
		analogWrite(speedPinL, balancedSpeedValue);
	}
	if (speed == 0) {
		digitalWrite(LeftDirectPin1, LOW);
		digitalWrite(LeftDirectPin2, LOW);
	}
}

void updateRightDrive(int speed)
{

	int balancedSpeedValue = abs(speed);

	if (speed > 0) {
		digitalWrite(RightDirectPin1, LOW);
		digitalWrite(RightDirectPin2, HIGH);
		analogWrite(speedPinR, balancedSpeedValue);
	}
	if (speed < 0) {
		digitalWrite(RightDirectPin1, HIGH);
		digitalWrite(RightDirectPin2, LOW);
		analogWrite(speedPinR, balancedSpeedValue);
	}
	if (speed == 0) {
		digitalWrite(RightDirectPin1, LOW);
		digitalWrite(RightDirectPin2, LOW);
	}
}

void setup() {
	pinMode(RightDirectPin1, OUTPUT);
	pinMode(RightDirectPin2, OUTPUT);
	pinMode(speedPinL, OUTPUT);
	pinMode(LeftDirectPin1, OUTPUT);
	pinMode(LeftDirectPin2, OUTPUT);
	pinMode(speedPinR, OUTPUT);

	Serial.begin(9600);
}

void loop() {
	Serial.setTimeout(60000);
	Serial.println("* Enter Lspeed, Rspeed");
	while (Serial.available() == 0) {}

		int lSpeed = Serial.parseInt();
		int rSpeed = Serial.parseInt();

		Serial.print("  Setting speeds: left:");
		Serial.print(lSpeed);
		Serial.print("  right:");
		Serial.print(rSpeed);
		Serial.println(" ");

		updateLeftDrive(lSpeed);
		updateRightDrive(rSpeed);
}
