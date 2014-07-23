Arduino_LS7366R
===============

Synchronous use of two LS7366R decoders on Arduino environnement.

The goal is to provide an interface for reading two LS7366R at the same time without missing ticks.
The solution is to send the order LOAD for register CNTR into OTR via SPI with the two chips on slave mode, afterwards we can read each chip via OTR.
