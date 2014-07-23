// Copyright 2014 Werdroid
// Author Vladimir Kosmala

#include "LS7366R.h"

#include <SPI.h>
#include <Arduino.h>

// Constructors ////////////////////////////////////////////////////////////////

LS7366R::LS7366R(unsigned char _leftSelect, unsigned char _rightSelect, unsigned char mdr0_conf, unsigned char mdr1_conf)
{
	leftSelect = _leftSelect;
	rightSelect = _rightSelect;

	pinMode(leftSelect, OUTPUT);
	pinMode(rightSelect, OUTPUT);
	SPI.begin();

	digitalWrite(leftSelect, LOW);
	SPI.transfer(WR | MDR0);
	SPI.transfer(mdr0_conf);
	digitalWrite(leftSelect, HIGH);
	
	digitalWrite(leftSelect, LOW);
	SPI.transfer(WR | MDR1);
	SPI.transfer(mdr1_conf);
	digitalWrite(leftSelect, HIGH);

	digitalWrite(rightSelect, LOW);
	SPI.transfer(WR | MDR0);
	SPI.transfer(mdr0_conf);
	digitalWrite(rightSelect, HIGH);
	
	digitalWrite(rightSelect, LOW);
	SPI.transfer(WR | MDR1);
	SPI.transfer(mdr1_conf);
	digitalWrite(rightSelect, HIGH);

	reset();
}

// Public Methods //////////////////////////////////////////////////////////////

void LS7366R::reset()
{
	digitalWrite(leftSelect, LOW);
	digitalWrite(rightSelect, LOW);
	SPI.transfer(CLR | CNTR);
	digitalWrite(leftSelect, HIGH);
	digitalWrite(rightSelect, HIGH);
}

void LS7366R::sync()
{
	long count;

	digitalWrite(leftSelect, LOW);
	digitalWrite(rightSelect, LOW);
	SPI.transfer(LOAD | OTR);
	digitalWrite(leftSelect, HIGH);
	digitalWrite(rightSelect, HIGH);

	digitalWrite(leftSelect, LOW);
	SPI.transfer(RD | OTR);
	count = SPI.transfer(0x00);
	count <<= 8;
	count |= SPI.transfer(0x00);
	count <<= 8;
	count |= SPI.transfer(0x00);
	count <<= 8;
	count |= SPI.transfer(0x00);
	digitalWrite(leftSelect, HIGH);
	leftValue = count;

	digitalWrite(rightSelect, LOW);
	SPI.transfer(RD | OTR);
	count = SPI.transfer(0x00);
	count <<= 8;
	count |= SPI.transfer(0x00);
	count <<= 8;
	count |= SPI.transfer(0x00);
	count <<= 8;
	count |= SPI.transfer(0x00);
	digitalWrite(rightSelect, HIGH);
	rightValue = count;
}

long LS7366R::left()
{
	return leftValue;
}

long LS7366R::right()
{
	return rightValue;
}
