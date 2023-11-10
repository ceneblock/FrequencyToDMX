#ifndef UTILS_H
#define UTILS_H

#include "pinMap.h"

#include <stdbool.h>
#include <stdint.h>

void serialInit(unsigned int baudRate);
void writeCharacter(char data);
void writeString(char *data, unsigned int length);

void pinMode(uint8_t pinNum, enum PIN_MODES mode);
void analogInit(); //universal to all analog stuff I'll be doing
unsigned int analogRead(uint8_t pinNum);
bool digitalRead(uint8_t pinNum);
void digitalWrite(uint8_t pinNum, bool value);
#endif
