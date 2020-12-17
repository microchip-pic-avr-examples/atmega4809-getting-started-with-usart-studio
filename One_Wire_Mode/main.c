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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

typedef enum {
    SENDING = 0,
    OK,
    CONFLICT,
} status_t;

volatile char charToSend;
volatile status_t sendingStatus;

void waitTxReady(void);
status_t waitSendConfirmation(void);
void USART1_oneWireSend(char* str);
char USART1_oneWireReceive(void);
void USART1_oneWireInit(void);

ISR(USART1_RXC_vect)
{
    if (USART1.RXDATAL == charToSend)
    {
        sendingStatus = OK;
    }
    else
    {
        sendingStatus = CONFLICT;
    }
}

void waitTxReady(void)
{
    while (!(USART1.STATUS & USART_DREIF_bm))
    {
        ;
    }        
}

status_t waitSendConfirmation(void)
{
    sendingStatus = SENDING;
    /* Will change inside RXC interrupt handler */
    while(sendingStatus == SENDING)
    {
        ;
    }
    return sendingStatus;
}

void USART1_oneWireSend(char* str)
{
    PORTC.DIR |= PIN0_bm; /* C0 pin must be output to transmit */
    USART1.CTRLA |= USART_RXCIE_bm; /* Receive Complete Interrupt must be enabled */
    
    for(size_t i = 0; i < strlen(str); i++)
    {
        charToSend = str[i];
        waitTxReady();
        
        USART1.TXDATAL = charToSend;
        
        if(waitSendConfirmation() != OK)
        {
            break;
        }
    }
    
    USART1.CTRLA &= ~(USART_RXCIE_bm);
    PORTC.DIR &= ~PIN0_bm;
}

char USART1_oneWireReceive(void)
{
    while (!(USART1.STATUS & USART_RXCIF_bm))
    {
        ;
    }        
    return USART1.RXDATAL;
}

void USART1_oneWireInit(void) 
{
    PORTC.DIR &= ~PIN0_bm;

    USART1.BAUD = (uint16_t)USART1_BAUD_RATE(9600); 
    
    USART1.CTRLA |= USART_LBME_bm;
    USART1.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;   
}

int main(void)
{   
    USART1_oneWireInit();
    
    /* Enable global interrupts */
    sei();
        
    while (1) 
    {
        USART1_oneWireSend("Microchip.\r\n");
        _delay_ms(500);
    }
}