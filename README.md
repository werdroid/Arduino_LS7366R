Arduino_LS7366R
===============

Synchronous use of two LS7366R decoders on Arduino environnement.

The goal is to provide an interface for reading two LS7366R at the same time without missing ticks for a robot having two wheels.
The solution is to send the order LOAD for register CNTR into OTR via SPI with the two chips on slave mode, afterwards we can read each chip via OTR.

By [Vladimir.sh](http://vladimir.sh) for [Werdroid.fr](http://werdroid.fr)

Usage
=========

- Wire your components with SPI to Arduino like the photo below
- Wire the two slave lines
- Copy LS7366R.h and LS7366R.cpp in your project

```cpp
#include <SPI.h>
#include "LS7366R.h"

int slave_pin_left = 10;
int slave_pin_right = 11;

LS7366R encoders(slave_pin_left, slave_pin_right, MDR0_CONF, MDR1_CONF);

void setup() {
  Serial.begin(9600);
  encoders.reset();
}

void loop() {
  encoders.sync();
  Serial.print(encoders.left());
  Serial.print(" ");
  Serial.print(encoders.right());
  Serial.println();
  delay(100);
}
```

![Arduino LS7366R](https://raw.githubusercontent.com/werdroid/Arduino_LS7366R/master/LS7366R_example/breadboard_pic.jpg)

License
----

MIT

**Free Software, Hell Yeah!**
