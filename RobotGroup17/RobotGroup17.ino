#include <tcs3200.h>

#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_OUT A4

#define IR_1 4
#define IR_2 7
#define IR_3 8
#define IR_4 12

#define LED_R 25
#define LED_G 26
#define LED_B 27

#define MOTOR_PIN1 3
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 9

#define US_TRIG 10
#define US_ECHO 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // setup infrared pins
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);


  // setup motor pins
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  // setup ultrasonic pins
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
}

// state logic
String currentState = "Null";
String oldCurrentState = "Null";

// turning logic
String turnDirection = ""; // keep track of the current turn direction.
String lastTurnDirection = ""; // store the last turn direction to decide the next turn if sharp turn is detected.
bool isTurning = false; // flag to show if the robot is turning or not.
bool wallDetected = false; // flag to show if the robot has detected a wall with the ultrasonic sensor

int currentDistance = 0;

unsigned long colorSensorMillis = 0; // timer to track the last report of the color sensors
unsigned long irSensorMillis = 0; // timer to track the last report of the IR sensors
unsigned long ultrasonicSensorMillis = 0; // timer to track the last report of the ultrasonic sensor
unsigned long currentMillis = 0;

void loop() {
  // put your main code here, to run repeatedly:

  // get the current run time in milliseconds
  currentMillis = millis();

  // check the states of the IR sensors every 500ms
  if (currentMillis - irSensorMillis >= 500) {
    irSensorMillis = currentMillis;
    readInfrared();
  }

  // read the color sensor
  if (currentMillis - colorSensorMillis >= 250) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }

  // read the ultrasonic sensor
  if (currentMillis - ultrasonicSensorMillis >= 500)
  {
    ultrasonicSensorMillis = currentMillis;
    readUltrasonic();
  }
  /*
    test motor control by creating a routine that moves
    the robot forward for 1 second and then turns 90 degrees right.
    you will have to adjust the delay after the turn to make it a perfect square.
  */
  /*motorControl(255, 255); // go forward
  delay(1000);
  motorControl(0, 0); // stop momentarily
  delay(100);
  motorControl(255, -255); // turn to the right
  delay(500);
  motorControl(0, 0); // stop momentarily
  delay(100); */

  robotLogic();
}
