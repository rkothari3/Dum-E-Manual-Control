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

// Current positions (start at middle position)
int baseSwivelPos = 90;
int baseUpDownPos = 90;
int armBigServoPos = 90;
int armSmallServoPos = 90;
int gripperUpDownPos = 90;
int gripperOpenClosePos = 90;

int stepSize = 5;   // Small step for smooth movement

void setup()
{
    Serial.begin(115200);
    Serial.println("Project Dum-E Manual Control Starting...");

    // MG996R
    baseSwivel.attach(baseSwivelPin, 600, 2400);
    baseUpDown.attach(baseUpDownPin, 600, 2400);
    armBigServo.attach(armBigServoPin, 600, 2400);

    // SG90
    armSmallServo.attach(armSmallServoPin, 600, 2400);
    gripperUpDown.attach(gripperUpDownPin, 600, 2400);
    gripperOpenClose.attach(gripperOpenClosePin, 600, 2400);

    // Move all servos to starting position
    baseSwivel.write(baseSwivelPos);
    baseUpDown.write(baseUpDownPos);
    armBigServo.write(armBigServoPos);
    armSmallServo.write(armSmallServoPos);
    gripperUpDown.write(gripperUpDownPos);
    gripperOpenClose.write(gripperOpenClosePos);

    Serial.println("All servos attached!");
    printControls();
}

void loop()
{
    if (Serial.available() > 0)
    {
        char key = Serial.read();

        switch (key)
        {
        // Base Swivel (Left/Right)
        case 'q':
            baseSwivelPos = constrain(baseSwivelPos - stepSize, 0, 180);
            baseSwivel.write(baseSwivelPos);
            Serial.print("Base Swivel: ");
            Serial.println(baseSwivelPos);
            break;
        case 'w':
            baseSwivelPos = constrain(baseSwivelPos + stepSize, 0, 180);
            baseSwivel.write(baseSwivelPos);
            Serial.print("Base Swivel: ");
            Serial.println(baseSwivelPos);
            break;

        // Base Up/Down
        case 'a':
            baseUpDownPos = constrain(baseUpDownPos - stepSize, 0, 180);
            baseUpDown.write(baseUpDownPos);
            Serial.print("Base Up/Down: ");
            Serial.println(baseUpDownPos);
            break;
        case 's':
            baseUpDownPos = constrain(baseUpDownPos + stepSize, 0, 180);
            baseUpDown.write(baseUpDownPos);
            Serial.print("Base Up/Down: ");
            Serial.println(baseUpDownPos);
            break;

        // Big Arm Servo
        case 'z':
            armBigServoPos = constrain(armBigServoPos - stepSize, 0, 180);
            armBigServo.write(armBigServoPos);
            Serial.print("Arm Big: ");
            Serial.println(armBigServoPos);
            break;
        case 'x':
            armBigServoPos = constrain(armBigServoPos + stepSize, 0, 180);
            armBigServo.write(armBigServoPos);
            Serial.print("Arm Big: ");
            Serial.println(armBigServoPos);
            break;

        // Small Arm Servo
        case 'e':
            armSmallServoPos = constrain(armSmallServoPos - stepSize, 0, 180);
            armSmallServo.write(armSmallServoPos);
            Serial.print("Arm Small: ");
            Serial.println(armSmallServoPos);
            break;
        case 'r':
            armSmallServoPos = constrain(armSmallServoPos + stepSize, 0, 180);
            armSmallServo.write(armSmallServoPos);
            Serial.print("Arm Small: ");
            Serial.println(armSmallServoPos);
            break;

        // Gripper Up/Down
        case 'd':
            gripperUpDownPos = constrain(gripperUpDownPos - stepSize, 0, 180);
            gripperUpDown.write(gripperUpDownPos);
            Serial.print("Gripper Up/Down: ");
            Serial.println(gripperUpDownPos);
            break;
        case 'f':
            gripperUpDownPos = constrain(gripperUpDownPos + stepSize, 0, 180);
            gripperUpDown.write(gripperUpDownPos);
            Serial.print("Gripper Up/Down: ");
            Serial.println(gripperUpDownPos);
            break;

        // Gripper Open/Close
        case 'c':
            gripperOpenClosePos = constrain(gripperOpenClosePos - stepSize, 0, 180);
            gripperOpenClose.write(gripperOpenClosePos);
            Serial.print("Gripper Open/Close: ");
            Serial.println(gripperOpenClosePos);
            break;
        case 'v':
            gripperOpenClosePos = constrain(gripperOpenClosePos + stepSize, 0, 180);
            gripperOpenClose.write(gripperOpenClosePos);
            Serial.print("Gripper Open/Close: ");
            Serial.println(gripperOpenClosePos);
            break;

        // Help menu
        case 'h':
            printControls();
            break;

        // Reset to center
        case '0':
            resetToCenter();
            break;
        }
    }
}

void printControls()
{
    Serial.println("\n=== DUM-E CONTROLS ===");
    Serial.println("Q/W - Base Swivel Left/Right");
    Serial.println("A/S - Base Up/Down");
    Serial.println("Z/X - Big Arm Servo");
    Serial.println("E/R - Small Arm Servo");
    Serial.println("D/F - Gripper Up/Down");
    Serial.println("C/V - Gripper Open/Close");
    Serial.println("0   - Reset to Center");
    Serial.println("H   - Show this help");
    Serial.println("=====================\n");
}

void resetToCenter()
{
    Serial.println("Resetting to center...");

    // Smooth movement to center
    while (baseSwivelPos != 90 || baseUpDownPos != 90 || armBigServoPos != 90 ||
           armSmallServoPos != 90 || gripperUpDownPos != 90 || gripperOpenClosePos != 90)
    {

        if (baseSwivelPos < 90)
            baseSwivelPos++;
        else if (baseSwivelPos > 90)
            baseSwivelPos--;
        baseSwivel.write(baseSwivelPos);

        if (baseUpDownPos < 90)
            baseUpDownPos++;
        else if (baseUpDownPos > 90)
            baseUpDownPos--;
        baseUpDown.write(baseUpDownPos);

        if (armBigServoPos < 90)
            armBigServoPos++;
        else if (armBigServoPos > 90)
            armBigServoPos--;
        armBigServo.write(armBigServoPos);

        if (armSmallServoPos < 90)
            armSmallServoPos++;
        else if (armSmallServoPos > 90)
            armSmallServoPos--;
        armSmallServo.write(armSmallServoPos);

        if (gripperUpDownPos < 90)
            gripperUpDownPos++;
        else if (gripperUpDownPos > 90)
            gripperUpDownPos--;
        gripperUpDown.write(gripperUpDownPos);

        if (gripperOpenClosePos < 90)
            gripperOpenClosePos++;
        else if (gripperOpenClosePos > 90)
            gripperOpenClosePos--;
        gripperOpenClose.write(gripperOpenClosePos);
    }

    Serial.println("Reset complete!");
}