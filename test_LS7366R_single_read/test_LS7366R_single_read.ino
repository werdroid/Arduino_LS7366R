#include <SPI.h>
#include <Arduino.h>

#define CLR B00000000
#define RD B01000000
#define WR B10000000
#define LOAD B11000000

#define MDR0 B00001000
#define MDR1 B00010000
#define DTR B00011000
#define CNTR B00100000
#define OTR B00101000
#define STR B00110000

// filter factor 1
// async index
// no index
// free-running
// 4x quadrature
#define MDR0_CONF B00000011

// no flag
// enabled
// 32 bits
#define MDR1_CONF B00000000

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(SS, OUTPUT);
  
  
  digitalWrite(SS, LOW);
  SPI.transfer(WR | MDR0);
  SPI.transfer(MDR0_CONF);
  digitalWrite(SS, HIGH);
  
  digitalWrite(SS, LOW);
  SPI.transfer(WR | MDR1);
  SPI.transfer(MDR1_CONF);
  digitalWrite(SS, HIGH);
  
  digitalWrite(SS, LOW);
  SPI.transfer(CLR | CNTR);
  digitalWrite(SS, HIGH);
}

long count = 0;

void loop() {
  digitalWrite(SS, LOW);
  byte b = SPI.transfer((byte) RD | CNTR);
  count = SPI.transfer(0x00);
  count <<= 8;
  count |= SPI.transfer(0x00);
  count <<= 8;
  count |= SPI.transfer(0x00);
  count <<= 8;
  count |= SPI.transfer(0x00);
  digitalWrite(SS, HIGH);
  Serial.print(count);
  Serial.println();
  delay(100);
}
