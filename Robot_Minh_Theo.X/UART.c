#include <xc.h>
#include "UART.h"
#include "ChipConfig.h"
#include "main.h"
#define BAUDRATE 115200
#define BRGVAL ((FCY/BAUDRATE)/4)-1

void InitUART(void) {
    U1MODEbits.STSEL = 0; // 1-stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 1; // Low Speed mode
    U1BRG = BRGVAL; // BAUD Rate Setting
    U1STAbits.UTXISEL0 = 1; // Interrupt after one Tx character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IFS0bits.U1TXIF = 0; // clear TX interrupt flag
    IEC0bits.U1TXIE = 1; // enable UART Tx interrupt
    U1STAbits.URXISEL = 0; // Interrupt after one RX character is received;
    IFS0bits.U1RXIF = 0; // clear RX interrupt flag
    IEC0bits.U1RXIE = 1; // Disable UART Rx interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART Tx
}

//Interruption en mode loopback


//void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
//    IFS0bits.U1RXIF = 0; // clear RX interrupt flag
//    /* check for receive errors */
//    if (U1STAbits.FERR == 1) {
//        U1STAbits.FERR = 0;
//    }
//    /* must clear the overrun error to keep uart receiving */
//    if (U1STAbits.OERR == 1) {
//        U1STAbits.OERR = 0;
//    }
//    /* get the data */
//    while (U1STAbits.URXDA == 1) {
//        U1TXREG = U1RXREG;
//    }
//}


void SendMessageDirect(unsigned char* message, int length) {
    unsigned char i = 0;
    for (i = 0; i < length; i++) {
        while (U1STAbits.UTXBF); // wait while Tx buffer full
        U1TXREG = *(message)++; // Transmit one character
    }
}