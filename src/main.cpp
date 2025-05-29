/**
 * @Author: Cary Gerhardt
 * @Date:   2025-05-29 17:12:16
 * @Last Modified by:   Cary Gerhardt
 * @Last Modified time: 2025-05-29 17:13:20
 */
#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World");
  delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}