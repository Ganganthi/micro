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
#include"driverlib/i2c.h"

#define SLAVE_ADDR          0x48
#define RG_TEMP             0x00
#define RG_CONFIG           0x01
#define RG_TLOW             0x02
#define RG_THIGH            0x03

#define TAXA_37             0b00000000
#define TAXA_18             0b00100000
#define TAXA_9              0b01000000
#define TAXA_4              0b01100000

void trataUART0(void){
    uint32_t ui8;
    ui8 = UARTCharGetNonBlocking(UART0_BASE);
    ui8++;

    UARTCharPutNonBlocking(UART0_BASE, ui8);

    UARTIntClear(UART0_BASE, UART_INT_RX);
}

//Passo 10

uint32_t get_temp(void){
    uint32_t dado;
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, true);
    I2CMasterDataPut(I2C0_BASE, RG_TEMP);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

    while(I2CMasterBusy(I2C0_BASE)){}
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while(I2CMasterBusy(I2C0_BASE)){}
    dado = I2CMasterDataGet(I2C0_BASE);

    return dado;
}

//Passo 11
void taxa_amostragem(uint32_t taxa){
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, true);
    I2CMasterDataPut(I2C0_BASE, RG_CONFIG);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    I2CMasterDataPut(I2C0_BASE, taxa);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

    I2CMasterDataPut(I2C0_BASE, 0x00);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
}

int main(void)
{
    uint32_t temperatura;

    //Passo 2
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_2_5);

    //Passo 3
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    //Passo 4
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //Passo 5
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    //Passo 6
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

    //Passo 7
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3); //dados sda
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2); //clock scl

    //Passo 8
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0)){}
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);

    //Passo 9
    I2CMasterEnable(I2C0_BASE);

    //Passo 10


    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTEnable(UART0_BASE);

//    IntMasterEnable(); //Passo 11
//    IntEnable(INT_UART0); //Passo 10
//    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //Passo 9

    //configurando FIFO
    //ATIVA INTERRUPCAO QUANDO O NIVEL FOR ATINGIDO
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    UARTFIFOEnable(UART0_BASE);



    while(1){
        temperatura = get_temp();
        SysCtlDelay(SysCtlClockGet()/3);
        UARTCharPutNonBlocking(UART0_BASE, temperatura);
    }
    return 0;
}
