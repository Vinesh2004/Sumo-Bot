
// ShieldBot Sumo - QTI - Written by Mr.K 2021.12.10
// Test the operation of the QTI sensors

// declare constants for QTI sensor pins
const int Right_QTI_PIN = 5;
const int Left_QTI_PIN = 6;

void setup() {
  // start serial communication
  Serial.begin(9600);

  // set the QTI pins as an input:
  pinMode(Left_QTI_PIN, INPUT);
  pinMode(Right_QTI_PIN, INPUT);
}

void loop() {
  //read QTI values
  bool Left_QTI_sensorValue = digitalRead(Left_QTI_PIN);
  bool Right_QTI_sensorValue = digitalRead(Right_QTI_PIN);

  // print information to the serial monitor
  Serial.print(Left_QTI_sensorValue);//1 = black, 0 = white
  Serial.print("  ");
  Serial.println(Right_QTI_sensorValue);//1 = black, 0 = white
  delay(50);
}
