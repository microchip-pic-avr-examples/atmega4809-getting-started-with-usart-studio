/*
    \file   main.c
    \brief  Main file of the project.
    (c) 2020 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

#define F_CPU 3333333
#define USART1_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#define MAX_COMMAND_LEN		8
#define INIT_DELAY			10	/* Delay to invalidate the after-reset noise on the PC0 pin (TX) */

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

void USART1_init(void);
void USART1_sendChar(char c);
void USART1_sendString(char *str);
char USART1_readChar(void);
void LED_on(void);
void LED_off(void);
void LED_init(void);
void executeCommand(char *command);

void USART1_init(void)
{
    USART1.BAUD = (uint16_t)USART1_BAUD_RATE(9600);

    USART1.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
	
	PORTC.DIR |= PIN0_bm;
	PORTC.DIR &= ~PIN1_bm;
}

void USART1_sendChar(char c)
{
    while (!(USART1.STATUS & USART_DREIF_bm))
    {
        ;    
    }
    USART1.TXDATAL = c;
}

void USART1_sendString(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        USART1_sendChar(str[i]);
    }
}

char USART1_readChar(void)
{
    while (!(USART1.STATUS & USART_RXCIF_bm))
    {
        ;
    }
    return USART1.RXDATAL;
}

void LED_on(void)
{
    PORTB.OUT &= ~PIN5_bm;
}

void LED_off(void)
{
    PORTB.OUT |= PIN5_bm;
}

void LED_init(void)
{
    PORTB.DIR |= PIN5_bm;
	LED_off();
}

void executeCommand(char *command)
{
    if(strcmp(command, "ON") == 0)
    {
        LED_on();
        USART1_sendString("OK, LED ON.\r\n");
    }
    else if (strcmp(command, "OFF") == 0)
    {
        LED_off();
        USART1_sendString("OK, LED OFF.\r\n");
    } 
    else 
    {
        USART1_sendString("Type ON/OFF to control the LED.\r\n");
    }
}

int main(void)
{
    char command[MAX_COMMAND_LEN];
    uint8_t index = 0;
    char c;
	
	/* This delay invalidates the initial noise on the TX line, after device reset. */
    _delay_ms(10);
	
    USART1_init();
    LED_init();
	
    USART1_sendString("Type ON/OFF to control the LED.\r\n");
    
    while (1)
    {
        c = USART1_readChar();
        if(c != '\n' && c != '\r')
        {
            command[index++] = c;
            if(index > MAX_COMMAND_LEN)
            {
                index = 0;
            }
        }
        
        if(c == '\r')
        {
            command[index] = '\0';
            index = 0;
            executeCommand(command);
        }
    }
}