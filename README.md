# LED_Light_DRAM
A LED array light sensor and DRAM investigation


LEDs can make useful ambient light sensors, which opens up a whole host of possibilities with very low cost hardware.

At  a minimum - all you need is a pair of GPIO lines from a microcontroller.

The PN junction in the LED acts as a small capacitor (a few pF). 

If you connect the LED with reverse bias (cathode to positive) you can charge up this capacitor to VCC from a GPIO output pin through a suitable resistor (typically a few hundred ohms).

If you then switch the GPIO pin to input, you can detect the logic state of the PN junction capacitor - whether it is above the logic 1 threshold voltage or below it.

The PN junction is sensitive to light, and the charge will leak away from it, according to the light level, reducing the voltage it presents to the GPIO input pin. The brighter the light, the faster the charge leaks away.

A simple while loop, reads the state of the GPIO input pin, and measures the time that it remains in the high state.

This pulse time will be anything from 1000uS in bright sunlight to about 10 seconds in total darkness. Effectively you have an integrating ADC of about 10 bits dynamic range.

This firmware should work on most "Arduino" compatible boards, but I found a problem with the new Pi Pico 2 (RP2350 version) where the GPIO pin would not register a change of state or go below 2V. - Further investigation required.

Accessing multiple LEDs.


Cathode Drive.

The cathode of each LED needs to be accessed in turn during the pre-charge phase where the LED is reverse biassed. The pre-charge is a short positive pulse, of  typically 10uS via a current limiting resistor. Once pre-charged the cathode is then connected to a high impedance input.

A octal tristate bi-directional transceiver is required to access the cathodes of an 8x8 LED array. This could be a 74HC245 for a parallel access, but a more elegant solution is to use a 74HC299 which is an 8-bit shift register with parallel tristate I/O. It reduces the wiring requirements, as the shift register can be driven using an SPI bus, and be multiplexed across many LED arrays.

Similarly the common anodes of the LED matrix can be driven with a 74HC595 8-bit latching shift register. The anode need only be driven low, during the pre-charge, and reading phase, and then high during the illumination phase. 






