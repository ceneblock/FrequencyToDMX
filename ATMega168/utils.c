#include "utils.h"

#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>

void serialInit(unsigned int baudRate)
{
  //splitting up this way to make it easier to read
  unsigned int ubrr = ( (F_CPU / 16) / baudRate) - 1;
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void writeCharacter(char data)
{
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}

void writeString(char *data, unsigned int length)
{
  for(unsigned int x = 0; x < length; ++x)
  {
    writeCharacter(data[x]);
  }
}

void pinMode(uint8_t pinNum, enum PIN_MODES mode)
{
  pinMap_t pin = pinMap[pinNum];

  if(pin.mode != mode)
  {
    switch(pin.port)
    {
      case 'A':
        //not supported on atmega168
        pin.mode = mode;
        break;
      case 'B':
        if(pin.adc == false)
        {
        }
        else
        {
          if(mode == INPUT || mode == OUTPUT)
          {
            DDRB = (mode == INPUT) ? DDRB & !(1 << pin.name) : DDRB | (1 << pin.name);
          }
        }
        pin.mode = mode;
        break;
      case 'C':
        if(pin.adc == false)
        {
        }
        else
        {
          if(mode == INPUT || mode == OUTPUT)
          {
            DDRC = (mode == INPUT) ? DDRC & !(1 << pin.name) : DDRC | (1 << pin.name);
          }
        }
        pin.mode = mode;
        break;
      case 'D':
        if(pin.adc == false)
        {
        }
        else
        {
          if(mode == INPUT || mode == OUTPUT)
          {
            DDRD = (mode == INPUT) ? DDRD & !(1 << pin.name) : DDRD | (1 << pin.name);
          }
        }
        pin.mode = mode;
        break;
      default:
        //invalid pin
        break;
    }
  }
}

void analogInit()
{
  ADMUX  |= (1 << REFS0); //I promise to use an external cap on AREF
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //set the prescaler to
    //128 since my frequency is 16MHz and ADC CLK >= 50Khz && < 200KHz
    //TODO: base on F_CPU value instead of hard coding

  ADCSRA |= (1 << ADEN); //Enable the ADC
}

bool digitalRead(uint8_t pinNum)
{
  pinMap_t pin = pinMap[pinNum];

  bool result = false;
  if(pin.mode == INPUT)
  {
    switch(pin.port)
    {
      case 'A':
        //not supported on atmega168
        break;
      case 'B':
        result = PINB & (1 << pin.name);
        break;
      case 'C':
        result = PINC & (1 << pin.name);
        break;
      case 'D':
        result = PIND & (1 << pin.name);
        break;
      default:
        //invalid pin
        break;
    }
  }

  return result;
}

void digitalWrite(uint8_t pinNum, bool value)
{
  pinMap_t pin = pinMap[pinNum];

  if(pin.mode == OUTPUT)
  {
    switch(pin.port)
    {
      case 'A':
        //not supported on atmega168
        break;
      case 'B':
        if(value == true)
        {
          PORTB |= (1 << pin.name);
        }
        else
        {
          PORTB &= !(1 << pin.name);
        }
        break;
      case 'C':
        if(value == true)
        {
          PORTC |= (1 << pin.name);
        }
        else
        {
          PORTC &= !(1 << pin.name);
        }
        break;
      case 'D':
        if(value == true)
        {
          PORTD |= (1 << pin.name);
        }
        else
        {
          PORTD &= !(1 << pin.name);
        }
        break;
      default:
        //invalid pin
        break;
    }
  }
}

