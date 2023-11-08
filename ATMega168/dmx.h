#ifndef DMX_H
#define DMX_H
#include <stdint.h>

#define MAX_DMX_CHANNELS 512
//void DMXmaxChannel(uint8_t channels);
//This is slightly misleading as it just copies the value over
void DMXwrite(uint8_t channel, uint8_t value);
void DMXusePin(uint8_t pin);

#endif
