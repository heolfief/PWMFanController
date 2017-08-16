/*
 * Fume extractor code.c
 *
 * Created: 11/06/2017 14:01:29
 * Author : Heol
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void init_PWM();
void init_ADC();

int main(void)
{
	init_PWM();											// Initialize non inverting Fast PWM mode on OC0A
	init_ADC();											// Initialize ADC on ADC3
	
	sei();												// Enable global interrupts
    while (1);											// PWM is driven by ADC interrupt
}

ISR(ADC_vect)											// Interrupt on ADC conversion complete
{
	OCR0A = ~ADCH;										// Set PWM duty cycle to 8 bits ADC value
	ADCSRA |= (1<<ADSC);								// Start another ADC conversion
}

void init_PWM()
{
	DDRB   |= (1<<PB0);									// PB0 as output
	
	TCCR0A |= (1<<WGM01) | (1<<WGM00);					// ... Fast PWM mode
		
	TCCR0A |= (1<<COM0A1);								// ...
	TCCR0A &= ~(1<<COM0A0);								// ... Non-inverting mode
	
	TCCR0B &= ~((1<<CS02) | (1<<CS01));					// ...
	TCCR0B |= (1<<CS00);								// ... No prescaler
}

void init_ADC()
{
	ADMUX &= ~((0<<REFS1) | (1<<REFS0));				// VCC used as Voltage Reference
	ADMUX |= (1<<ADLAR);								// ADC Left Adjust Result
	ADMUX &= ~((1<<MUX3) | (1<<MUX2));					// ...
	ADMUX |= (1<<MUX1) | (1<<MUX0);						// ... Select ADC3
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);	    // ADC clock prescaler /128
	ADCSRA |= (1<<ADIE) | (1<<ADEN);					// Enable ADC and enable interrupt
	ADCSRA |= (1<<ADSC);								// Start ADC conversion
}
