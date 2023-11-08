#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <avr/io.h>

#include "utils.h"

#define STROBE 6
#define RESET 11
#define DC_One A0
#define DC_Two A2

int LeftFrequencies[7], RightFrequencies[7], AverageFrequencies[7];

#define DMX_PIN 3
#define DMX_MULTIPLIER 5
#define DMX_DEVICES 1

#define DEBUG 1

enum DMX_CHANNELS { BRIGHTNESS = 1, RED = 2, GREEN = 3, BLUE = 4, DMX_STROBE = 5};

void setup();
void loop();
void collectFrequencies();
void printFrequencies();
void displayFrequencies();

void setup()
{
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  serialInit(9600);
}

void loop()
{
  while(true)
  {
#if DEBUG == 1
    printFrequencies();
#endif
  }
}

int main()
{
  //"borrow" some Arduino function names
  setup();
  loop();
  return EXIT_SUCCESS;
}

void printFrequencies()
{
  unsigned int buffSize = 160;
  char data[buffSize];
  int offset = 0;
  for(int x = 0; x < 7; ++x)
  {
    offset += snprintf(data + offset, buffSize - offset, "Band %d: %i ", x, AverageFrequencies[x]);
    if(offset == -1)
    {
      //Go ahead and write everything if the buffer filled up
      writeString(data, buffSize);
      writeCharacter('\n');
      offset = 0;
    }
  }
  if(offset != -1)
  {
    writeString(data, offset);
    writeCharacter('\n');
  } 
}

void displayFrequencies()
{
  unsigned int blueAverage  = (AverageFrequencies[0] + AverageFrequencies[1] + AverageFrequencies[2]) / 3;
  unsigned int redAverage   = (AverageFrequencies[2] + AverageFrequencies[3] + AverageFrequencies[4] + AverageFrequencies[5]) / 4;
  unsigned int greenAverage = (AverageFrequencies[4] + AverageFrequencies[5] + AverageFrequencies[6]) / 3;

  for(char device = 1; device <= DMX_DEVICES; ++device)
  {
    /*
    DmxSimple.write(device * BRIGHTNESS, 255);  //max brightness
    DmxSimple.write(device * RED, redAverage);
    DmxSimple.write(device * GREEN, greenAverage);
    DmxSimple.write(device * BLUE, blueAverage);
    DmxSimple.write(device * DMX_STROBE, 0); //turn off strobe
    */
  }
}

