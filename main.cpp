/**
 * A minimal example to use the ADC to read analog values
 * The precision in the example is 8 bit. If more precision is required the ADCL must be read first, then ADCH.
 *
 * -- Prescaling and Conversion Timing --
 * By default, the successive approximation circuitry requires an input clock frequency between 50
 * kHz and 200 kHz to get maximum resolution. If a lower resolution than 10 bits is needed, the
 * input clock frequency to the ADC can be higher than 200 kHz to get a higher sample rate.
 *
 * @author Igor Martens
 * @since 16.09.2018
 */

#define F_CPU 9600000UL

#include <avr/io.h>

void initADC() {
    ADMUX =
        (1 << ADLAR) |     // left shift result
        (0 << REFS0) |     // VCC used as analog reference.
        (1 << MUX1)  |     // use ADC3 for input (PB3), MUX bit 1
        (1 << MUX0);       // use ADC3 for input (PB3), MUX bit 0

    ADCSRA =
        (1 << ADEN)  |     // Enable ADC
        (1 << ADPS2) |     // set prescaler to 128, bit 2
        (1 << ADPS1) |     // set prescaler to 128, bit 1
        (1 << ADPS0);      // set prescaler to 128, bit 0
}

void setup() {
    initADC();
}

int main(void) {
    setup();

    while(1) {
        ADCSRA |= (1 << ADSC);         // start ADC measurement
        while (ADCSRA & (1 << ADSC));  // wait till conversion complete

        uint8_t val = ADCH;            // read value from ADC
    }

    return 0;
}
