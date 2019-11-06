#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_ints.h"
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/interrupt.h"
#include"driverlib/pin_map.h"
#include"driverlib/uart.h"


/**
 * main.c
 */

// Passos 12 e 13
void trataUART0(void){
    uint32_t ui8;
    ui8 = UARTCharGetNonBlocking(UART0_BASE);
    ui8++;

    UARTCharPutNonBlocking(UART0_BASE, ui8);

    UARTIntClear(UART0_BASE, UART_INT_RX);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_2_5);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTEnable(UART0_BASE);

    IntMasterEnable(); //Passo 11
    IntEnable(INT_UART0); //Passo 10
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //Passo 9



    while(1);
	return 0;
}
