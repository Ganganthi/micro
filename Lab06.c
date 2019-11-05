#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"

/**
 * main.c
 */
int main(void)
{
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_2_5);
    volatile uint32_t x=SysCtlClockGet();
    while(1);

    /*
    SysCtlAltClkConfig(SYSCTL_ALTCLK_PIOSC);
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_2_5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));

    ADCSequenceConfigure(ADC0_BASE,1,ADC_TRIGGER_PROCESSOR,0xFF);
    ADCSequenceStepConfigure(ADC0_BASE,1,0,ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE,1,1,ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE,1,2,ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);

    uint32_t leituras[4];
    volatile uint32_t media, TempC, cont;

    while(1){
        ADCIntClear(ADC0_BASE, 1);
        ADCProcessorTrigger(ADC0_BASE, 1);
        while(!ADCIntStatus(ADC0_BASE, 1, false));
        ADCSequenceDataGet(ADC0_BASE, 1,leituras);
        media=0;
        for(cont=0;cont<4;cont++){
            media+=leituras[cont];
        }
        media+=2;
        media/=4;

        TempC=(1475-((2475*media) / 4096))/10;
    }*/
	return 0;
}
