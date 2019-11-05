#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_uart.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"

void Trata_UART0_RX(){
    uint32_t dado;
    dado=UARTCharGetNonBlocking(UART0_BASE);
    dado++;
    UARTCharPutNonBlocking(UART0_BASE,dado);
    UARTIntClear(UART0_BASE,UART_INT_RX);
    return;
}


int main(void)
{
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_2_5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    UARTEnable(UART0_BASE);
    UARTIntEnable(UART0_BASE,UART_INT_RX);

    while(1);
	return 0;
}
