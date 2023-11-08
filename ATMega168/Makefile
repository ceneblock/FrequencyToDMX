CC=avr-gcc
F_CPU=16000000
MCU=atmega168p

C_FLAGS=-g

FrequencyToDMX: main.c utils.c pinMap.c dmx.c
	$(CC) $(C_FLAGS) -mmcu=$(MCU) -DMCU=$(MCU) -DF_CPU=$(F_CPU) $^ -o $@

sim: FrequencyToDMX
	simavr -m $(MCU) $^

clean:
	-rm FrequencyToDMX

.PHONY: clean sim
