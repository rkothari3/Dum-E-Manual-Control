#include <ESP32Servo.h>

// 6 Servos
Servo baseSwivel;
Servo baseUpDown;
Servo armBigServo;
Servo armSmallServo;
Servo gripperUpDown;
Servo gripperOpenClose;

// Servo Pins
int baseSwivelPin = 13;
int baseUpDownPin = 12;
int armBigServoPin = 14;
int armSmallServoPin = 27;
int gripperUpDownPin = 26;
int gripperOpenClosePin = 25;

void setup()
{
    Serial.begin(115200);
    Serial.println("Project Dum-E Manual Control Starting...");
    myservo.setPeriodHertz(100);

    // MG996R
    baseSwivel.attach(servoPin, 600, 2400);
    baseUpDown.attach(servoPin, 600, 2400);
    armBigServo.attach(servoPin, 600, 2400);
    // SG90
    armSmallServo.attach(servoPin, 600, 2400);
    gripperUpDown.attach(servoPin, 600, 2400);
    gripperOpenClose.attach(servoPin, 600, 2400);
}

void loop()
{
}