#ifndef UTILS_H
#define UTILS_H

#include <avr/io.h>
//#include <util/setbaud.h>

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(3333333 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

void serialInit(unsigned int baudRate);
void writeCharacter(char data);
void writeString(char *data, unsigned int length);

#define FOSC 16000000 // Clock Speed
#define BAUD 9600

void serialInit(unsigned int baudRate)
{
  //splitting up this way to make it easier to read
  unsigned int ubrr = ( (FOSC / 16) / baudRate) - 1;
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

#endif
