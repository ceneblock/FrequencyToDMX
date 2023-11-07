
CC=avr-gcc
F_CPU=16000000
MCU=atmega168p

FrequencyToDMX: main.c
	$(CC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) $^ -o $@

sim: FrequencyToDMX
	simavr -m $(MCU) $^

clean:
	-rm FrequencyToDMX

.PHONY: clean sim
