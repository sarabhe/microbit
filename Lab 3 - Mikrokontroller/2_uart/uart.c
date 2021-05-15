#include "uart.h"


void uart_init(){
    GPIO->PIN_CNF[25] = 0;
    GPIO->PIN_CNF[24] = 1;

    UART->PSELTXD = 24;
    UART->PSELRXD = 25;

    UART->BAUDRATE = 0x00275000;

    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4;

    UART->STARTRX = 1;
}

void uart_send(char letter){
    UART->STARTTX = 1;
    UART->TXD = letter;

    while (!UART->TXDRDY){
        
    }
    UART->TXDRDY = 0;
    UART->STOPTX = 1;
}

char uart_read(){
    UART->STARTRX = 1;

    if (!UART->RXDRDY){
        return '\0';
    }

    UART->RXDRDY = 0;
    return UART->RXD;
}

