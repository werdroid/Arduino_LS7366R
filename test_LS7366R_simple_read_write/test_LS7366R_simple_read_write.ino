#include <SPI.h>
#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(SS, OUTPUT);
}

void loop() {
  // Write 5 in register MDR0
  digitalWrite(SS, LOW);
  SPI.transfer((byte) B10001000);
  SPI.transfer(0x05);
  digitalWrite(SS, HIGH);
  
  // Read MDR0, should be 5
  digitalWrite(SS, LOW);
  Serial.print("commande: ");
  Serial.println((byte) B01001000, BIN);
  byte b = SPI.transfer((byte) B01001000);
  byte b1 = SPI.transfer(0x00);
  digitalWrite(SS, HIGH);
  Serial.print(b1, HEX);
  Serial.println();
  delay(100);
}
