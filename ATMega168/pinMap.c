#include "pinMap.h"

#if MCU == atmega168p

pinMap_t pinMap[29] = {
  { 0x00,   0, 0, 0, 0, DISABLED},
  {  PC6, 'C', 1, 0, 0, DISABLED},
  {  PD0, 'D', 1, 0, 0, DISABLED},
  {  PD1, 'D', 1, 0, 0, DISABLED},
  {  PD2, 'D', 1, 0, 0, DISABLED},
  {  PD3, 'D', 1, 0, 0, DISABLED},
  {  PD4, 'D', 1, 0, 0, DISABLED},
  { 0x00,   0, 0, 0, 0, DISABLED},
  { 0x00,   0, 0, 0, 0, DISABLED},
  {  PB6, 'B', 1, 0, 0, DISABLED}, //OSC pin
  {  PB7, 'B', 1, 0, 0, DISABLED}, //OSC pin
  {  PD5, 'D', 1, 0, 0, DISABLED},
  {  PD6, 'D', 1, 0, 0, DISABLED},
  {  PD7, 'D', 1, 0, 0, DISABLED},
  {  PB0, 'B', 1, 0, 0, DISABLED},
  {  PB1, 'B', 1, 0, 0, DISABLED},
  {  PB2, 'B', 1, 0, 0, DISABLED},
  {  PB3, 'B', 1, 0, 0, DISABLED},
  {  PB4, 'B', 1, 0, 0, DISABLED},
  {  PB5, 'B', 1, 0, 0, DISABLED},
  { 0x00,   0, 0, 0, 0, DISABLED},
  { 0x00,   0, 0, 0, 0, DISABLED},
  { 0x00,   0, 0, 0, 0, DISABLED},
  {  PC0, 'C', 1, 1, 0, DISABLED},
  {  PC1, 'C', 1, 1, 1, DISABLED},
  {  PC2, 'C', 1, 1, 2, DISABLED},
  {  PC3, 'C', 1, 1, 3, DISABLED},
  {  PC4, 'C', 1, 1, 4, DISABLED},
  {  PC5, 'C', 1, 1, 5, DISABLED}
};

#endif

