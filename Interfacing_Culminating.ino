// ShieldBot SumBot QTI and MOTOR test - Written by Mr.K 2021.12.09

#include <Servo.h> //include servo library
// Declare left and right servos
Servo servoLeft;
Servo servoRight;

// declare constants for sensor pins
const int TRIGGER_PIN = 8;
const int ECHO_PIN = 7;
const int Right_QTI_PIN = 5;
const int Left_QTI_PIN = 6;
const int Right_IR_LED_PIN = 3;
const int Right_IR_REC_PIN = 4;
const int Left_IR_LED_PIN = 10;
const int Left_IR_REC_PIN = 11;

float duration;
float distance;

void setup() {
  //attach servos
  servoLeft.attach(13);
  servoRight.attach(12);

  // set the QTI pins as an input:
  pinMode(Left_QTI_PIN, INPUT);
  pinMode(Right_QTI_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

   // start serial communication
  Serial.begin(9600);
}

void loop() {
  //read QTI values
  bool Left_QTI_sensorValue = digitalRead(Left_QTI_PIN);
  bool Right_QTI_sensorValue = digitalRead(Right_QTI_PIN);

  //UltraSonic Measurement Calculation Section
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  

  // IR Detection Section 
  tone(Left_IR_LED_PIN, 38000, 8);
  delay(1);
  int Left_ir = digitalRead(Left_IR_REC_PIN);
  delay(1);
  tone(Right_IR_LED_PIN, 38000, 8);
  delay(1);
  int Right_ir = digitalRead(Right_IR_REC_PIN);
  delay(1);
  

  //Testing the operation of left QTI and motor together
  if (distance<30)  { // ultrasonic sensor view less than 30
    motorControl(1700, 1300); 
    Serial.print("attack");
  } else if(Left_ir == 0){
    motorControl(1450, 1450);
    Serial.print("left");
  } else if(Right_ir == 0){
    motorControl(1550, 1550);
    Serial.print("right");
  }  else if(Right_ir == 0 && Left_ir == 0){
    motorControl(1700, 1300);
    Serial.print("both");
  } else{
    motorControl(1520, 1480);
    Serial.print("advance");
  }

  //test operation of right QTI and motor together
  if (Right_QTI_sensorValue == 0 || Left_QTI_sensorValue == 0) {
    motorControl(1500, 1500); // stop
    motorControl(1300, 1700); // reverse
    Serial.print(Left_QTI_sensorValue);//1 = black, 0 = white
    Serial.print("  ");
    Serial.println(Right_QTI_sensorValue);//1 = black, 0 = white
    delay(500);
    // begin fully randomized turning sequence
    int randomTurn = random(0, 2);
    Serial.println(randomTurn);
    if (randomTurn == 0) {
      int randomTurnLeft = random(1300, 1450);
      motorControl(randomTurnLeft, randomTurnLeft);
    } else if (randomTurn == 1) {
      int randomTurnRight = random(1550, 1700);
      motorControl(randomTurnRight, randomTurnRight);
    }
    delay(800);
  }

}
void motorControl(int Lmotor, int Rmotor){
  servoLeft.writeMicroseconds(Lmotor);
  servoRight.writeMicroseconds(Rmotor);
}
