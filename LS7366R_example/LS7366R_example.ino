// Copyright 2014 Werdroid
// Author Vladimir Kosmala

#include <SPI.h>
#include "LS7366R.h"

LS7366R codeurs(SS, 10, MDR0_CONF, MDR1_CONF);

void setup() {
  Serial.begin(9600);
  codeurs.reset();
}

void loop() {
  codeurs.sync();
  Serial.print(codeurs.left());
  Serial.print(" ");
  Serial.print(codeurs.right());
  Serial.println();
  delay(100);
}

