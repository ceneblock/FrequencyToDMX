#include "dmx.h"
#include "utils.h"

uint8_t dmxBuffer[MAX_DMX_CHANNELS];
pinMap_t *DMXpin = &pinMap[0];

void DMXusePin(uint8_t pin)
{
  //Set up the pin
  pinMode(pin, OUTPUT);

  DMXpin = &pinMap[pin];
}

void DMXwrite(uint8_t channel, uint8_t value)
{
  //roll over
  if(channel > MAX_DMX_CHANNELS)
  {
    channel = 0;
  }

  dmxBuffer[channel] = value;
} 
