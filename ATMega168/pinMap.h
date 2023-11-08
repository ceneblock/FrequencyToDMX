#ifndef PINMAP_H
#define PINMAP_H

#include <avr/io.h>

#include <stdint.h>

enum PIN_MODES { DISABLED, INPUT, OUTPUT, ANALOG_IN, ANALOG_OUT };

typedef struct 
{
  uint8_t name;
  char    port;
  uint8_t valid;
  uint8_t pwm;
  enum PIN_MODES mode;
} pinMap_t;


#if MCU == atmega168p
extern pinMap_t pinMap[29];
#endif

#endif
