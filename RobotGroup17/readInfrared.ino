int* readInfrared() {
  static int IRvalues[4];

  // read analog values from infra red sensors
  IRvalues[0] = digitalRead(IR_1);
  IRvalues[1] = digitalRead(IR_2);
  IRvalues[2] = digitalRead(IR_3);
  IRvalues[3] = digitalRead(IR_4);

  // print the read values to the serial monitor
  Serial.println("IR_1:" + IRvalues[0]);
  Serial.println("IR_2:" + IRvalues[1]);
  Serial.println("IR_3:" + IRvalues[2]);
  Serial.println("IR_4:" + IRvalues[3]);

  return IRvalues; // return the array of IR sensor values
}