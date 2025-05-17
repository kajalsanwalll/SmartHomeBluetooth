#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void UART_init(unsigned int ubrr) {
    
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

  
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

   
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

char UART_receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void LED_init() {
    DDRB |= (1 << PB0);  
}

void LED_ON() {
    PORTB |= (1 << PB0); 
}

void LED_OFF() {
    PORTB &= ~(1 << PB0); 
}

int main(void) {
    UART_init(103);  
    LED_init();

    while (1) {
        char command = UART_receive();

        if (command == '1') {
            LED_ON();  
        } else if (command == '0') {
            LED_OFF();  
        }
    }
}
