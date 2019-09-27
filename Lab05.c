#include <stdint.h>

#define ESC_REG(x)          (*((volatile uint32_t *)(x)))

#define PINO_0                  0x01    //00000001
#define PINO_1                  0x02    //00000010
#define PINO_2                  0x04    //00000100
#define PINO_3                  0x08    //00001000
#define PINO_4                  0x10    //00010000
#define PINO_5                  0x20    //00100000
#define PINO_6                  0x40    //01000000
#define PINO_7                  0x80    //10000000

#define portalBASE_GPIO_A  0x40004000   //GPIO Port A (APB) base
#define portalBASE_GPIO_B  0x40005000   //GPIO Port B (APB) base
#define portalBASE_GPIO_C  0x40006000   //GPIO Port C (APB) base
#define portalBASE_GPIO_D  0x40007000   //GPIO Port D (APB) base
#define portalBASE_GPIO_E  0x40024000   //GPIO Port E (APB) base
#define portalBASE_GPIO_F  0x40025000   //GPIO Port F (APB) base

#define portalGPIO_A        0x01        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_B        0x02        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_C        0x04        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_D        0x08        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_E        0x10        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_F        0x20        //offsets para cada portal a partir do RCGCGPIO


#define SYSCTL_RCGCGPIO    0x400FE608   //base registrador RCGCGPIO somado ao offset do registrador
#define GPIO_O_DR2R         0x500       //offset registrador GPIODR2R
#define GPIO_O_DEN          0x51C       //offset registrador GPIODEN
#define GPIO_O_DIR          0x400       //offset registrador GPIODIR
#define GPIO_O_DATA         0x00        //offset registrador GPIODATA
#define SYSCTL_RCGC2_R     0x400FE108   //base registrador RCGC2
#define GPIO_PORTF_PDR     0x40025514   //GPIO Port F (APB) base + offset registrador GPIOPDR
#define GPIO_PORTF_PUR     0x40025510   //GPIO Port F (APB) base + offset registrador GPIOPDR
#define GPIO_LOCK           0x520
#define GPIO_LOCK_KEY           0x4C4F434B
#define GPIO_O_CR           0x524

#define NVIC_EN0            0xE000E100     //base + offset registrador EN0
#define NVIC_SWTRIG         0xE000EF00     //base + offset registrador SWTRIG

#define GPIOIM              0x410   // set=envia interrupt  clear=barra interrupt
#define GPIOIS              0x404   // set=detecta nivel  clear=detecta bordas
#define GPIOIBE             0x408   // set=detecta ambas as bordas se GPIOIS detecta bordas  clear=desabilita
#define GPIOIEV             0x40C   // set=nivel alto ou borda de subida  clear=nivel baixo ou borda de descida
#define GPIOICR             0x41C   // set=desliga o interrupt do pino se for de borda  clear=sem efeito
#define GPIORIS             0x414   //RO set=interrupt aconteceu no pino  clear=interrupt nao aconteceu no pino

//usa na func configIntGPIO
#define Nivel_0             0x00
#define Nivel_1             0x01
#define Rising_edge         0x02
#define Falling_edge        0x03
#define Both_edge           0x04

//Usados na func HabilitaInterrupcao
#define Interrupt_GPIO_A    0
#define Interrupt_GPIO_B    1
#define Interrupt_GPIO_C    2
#define Interrupt_GPIO_D    3
#define Interrupt_GPIO_E    4
#define Interrupt_GPIO_F    30

#define SYSCTL_RCGCTIMER   0x400FE604
#define moduloTimer0      0x01
#define moduloTimer1      0x02
#define moduloTimer2      0x04
#define moduloTimer3      0x08
#define moduloTimer4      0x10
#define moduloTimer5      0x20

#define TIMER_CTL_TAEN    0x01
#define TIMER_CTL_TBEN    0x100
#define TIMER_O_CTL     0x0C
#define TIMER0_BASE     0x40030000
#define TIMER1_BASE     0x40031000
#define TIMER2_BASE     0x40032000
#define TIMER3_BASE     0x40033000
#define TIMER4_BASE     0x40034000
#define TIMER5_BASE     0x40035000

#define TIMER_O_CFG     0x00
#define TIMER_O_TAMR    0x04
#define TIMER_O_TBMR    0x08
#define TIMER_CFG_A_ONE_SHOT  0x01 //down
#define TIMER_CFG_A_ONE_SHOT_UP  0x11 //up
#define TIMER_CFG_A_PERIODIC  0x02
#define TIMER_CFG_A_PERIODIC_UP  0x12
#define TIMER_CFG_B_ONE_SHOT  0x101 //down
#define TIMER_CFG_B_ONE_SHOT_UP  0x111 //up
#define TIMER_CFG_B_PERIODIC  0x102
#define TIMER_CFG_B_PERIODIC_UP  0x112

#define TIMER_O_TAILR    0x28
#define TIMER_O_TBILR    0x2C
#define TIMER_B      0x01
#define TIMER_O_IMR     0x18
#define TIMER_B_TIMEOUT    0x100
#define TIMER_A_TIMEOUT    0x01
#define TIMER_O_ICR     0x024

void habilitaClockportal(uint32_t portalGPIO){

    ESC_REG(SYSCTL_RCGCGPIO) |= portalGPIO;
}

void configuraPinoSaida(uint32_t portalBASE, uint8_t PINO){

    ESC_REG(portalBASE + GPIO_O_DR2R) |= PINO;
    ESC_REG(portalBASE + GPIO_O_DEN)  |= PINO;
    ESC_REG(portalBASE + GPIO_O_DIR)  |= PINO;
}

void configuraPinoEntrada(uint32_t portalBASE, uint8_t PINO){

    ESC_REG(portalBASE + GPIO_O_DR2R) |= PINO;
    ESC_REG(portalBASE + GPIO_O_DEN)  |= PINO;
    ESC_REG(portalBASE + GPIO_O_DIR)  &= ~(PINO);
}

uint32_t leituraGPIO(uint32_t portalBASE, uint8_t PINO){

    return (ESC_REG(portalBASE + (GPIO_O_DATA + (PINO<<2))));
}

void escritaGPIO(uint32_t portalBASE, uint8_t PINO, uint8_t VALOR){

    ESC_REG(portalBASE + (GPIO_O_DATA + (PINO<<2))) = VALOR;
}

void HabilitaGlobal(){
    __asm( " mrs r0, PRIMASK\n"
            " cpsie i\n"
            " bx lr\n");
}

void HabilitaInterrupcaoGPIO(uint32_t ui32Interrupcao){
    ESC_REG(NVIC_EN0) |= 1<<ui32Interrupcao;
}

void ConfigIntGPIO(uint32_t portalBASE, uint8_t PINO, uint32_t config){
    ESC_REG(portalBASE + GPIOIM) &= ~(PINO);

    if((config & 0x00) == 0x00){   //Level 0
        ESC_REG(portalBASE + GPIOIS) |= PINO;
        ESC_REG(portalBASE + GPIOIEV) &= ~(PINO);
        ESC_REG(portalBASE + GPIOIBE) &= ~(PINO);

    }else if((config & 0x01) == 0x01){  //Level 1
        ESC_REG(portalBASE + GPIOIS) |= PINO;
        ESC_REG(portalBASE + GPIOIEV) |= PINO;
        ESC_REG(portalBASE + GPIOIBE) &= ~(PINO);

    }else if((config & 0x02) == 0x02){  //Rising edge
        ESC_REG(portalBASE + GPIOIS) &= ~(PINO);
        ESC_REG(portalBASE + GPIOIEV) |= PINO;
        ESC_REG(portalBASE + GPIOIBE) &= ~(PINO);

    }else if((config & 0x03) == 0x03){  //Falling edge
        ESC_REG(portalBASE + GPIOIS) &= ~(PINO);
        ESC_REG(portalBASE + GPIOIEV) &= ~(PINO);
        ESC_REG(portalBASE + GPIOIBE) &= ~(PINO);

    }else if((config & 0x04) == 0x04){  //Both edge
        ESC_REG(portalBASE + GPIOIS) &= ~(PINO);
        ESC_REG(portalBASE + GPIOIBE) |= PINO;
    }

    ESC_REG(portalBASE + GPIOIM) |= PINO;
}

void LimpaInterrupt(uint32_t portalBASE, uint8_t PINO){
    ESC_REG(portalBASE + GPIOICR) = PINO;
}

void HabInterruptGPIO(uint32_t portalBASE, uint8_t PINO){
    ESC_REG(portalBASE + GPIOIM) |= PINO;
}

void DisInterruptGPIO(uint32_t portalBASE, uint8_t PINO){
    ESC_REG(portalBASE + GPIOIM) &= ~(PINO);
}


void habilitaClockTimer(uint32_t moduloTimer){
    ESC_REG(SYSCTL_RCGCTIMER) |= moduloTimer;
}

void configTimer(uint32_t TimerBase,uint32_t config){
    ESC_REG(TimerBase + TIMER_O_CTL) &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);
    ESC_REG(TimerBase + TIMER_O_CFG) = 0x00;
    ESC_REG(TimerBase + TIMER_O_TAMR) = (config & 0xFF);

    if(config & 0x100 == 0x100){
        ESC_REG(TimerBase + TIMER_O_TBMR) = (config & 0xFF); //usa tb com os 2 separados
    }
}

void ConfiguraPeriodoTimer(uint32_t TimerBase,uint32_t timer,uint32_t valor){ //timer a ou b
    ESC_REG(TimerBase + TIMER_O_TAILR) = valor;
    if(timer == TIMER_B){
        ESC_REG(TimerBase + TIMER_O_TBILR) = valor;
    }
}

void HabilitaIntTimer(uint32_t TimerBase, uint32_t flags){
    ESC_REG(TimerBase + TIMER_O_IMR) |= flags;
}

void DesabilitaIntTimer(uint32_t TimerBase, uint32_t flags){
    ESC_REG(TimerBase + TIMER_O_IMR) &= ~flags;
}

void LimpaIntTimer(uint32_t TimerBase, uint32_t flags){
    ESC_REG(TimerBase + TIMER_O_ICR) = flags;
}

void habilitaTimer(uint32_t TimerBase, uint32_t timer){
    ESC_REG(TimerBase + TIMER_O_CTL) |= (TIMER_CTL_TAEN);
    if(timer == TIMER_B){
        ESC_REG(TimerBase + TIMER_O_CTL) |= (TIMER_CTL_TBEN);
    }
}
void TrataGPIOF(){
    volatile uint32_t cont;
    if((ESC_REG(portalBASE_GPIO_F + GPIORIS) & PINO_4) == PINO_4){
        if((leituraGPIO(portalBASE_GPIO_F,PINO_3) & PINO_3) == PINO_3){
            escritaGPIO(portalBASE_GPIO_F,PINO_3,0x00);
        }else{
            escritaGPIO(portalBASE_GPIO_F,PINO_3,0xFF);
        }
        DisInterruptGPIO(portalBASE_GPIO_F,PINO_4);
        habilitaTimer(TIMER0_BASE , 0x00);
    }
    /*
    if((ESC_REG(portalBASE_GPIO_F + GPIORIS) & PINO_0) == PINO_0){
        escritaGPIO(portalBASE_GPIO_F,PINO_2,0xFF);
        for(cont=0;cont<2000000;cont++);
        escritaGPIO(portalBASE_GPIO_F,PINO_2,0x00);
        escritaGPIO(portalBASE_GPIO_F,PINO_1,0xFF);
        for(cont=0;cont<200000;cont++);
        escritaGPIO(portalBASE_GPIO_F,PINO_1,0x00);
        //LimpaInterrupt(portalBASE_GPIO_F,PINO_0);
    }
    //LimpaInterrupt(portalBASE_GPIO_F,PINO_0);*/
}


void TrataTimer0A(){
    //escritaGPIO(portalBASE_GPIO_F,PINO_1,0xFF);
    HabInterruptGPIO(portalBASE_GPIO_F,PINO_4);
    LimpaIntTimer(TIMER0_BASE , TIMER_A_TIMEOUT);
}

int main(void)
{
    uint32_t ui32Loop;

    habilitaClockportal(portalGPIO_F);

    ui32Loop = ESC_REG(SYSCTL_RCGC2_R);

    ESC_REG(portalBASE_GPIO_F+GPIO_LOCK) |= GPIO_LOCK_KEY;
    ESC_REG(portalBASE_GPIO_F+GPIO_O_CR) |= PINO_0;

    configuraPinoSaida(portalBASE_GPIO_F, PINO_3|PINO_2|PINO_1);
    configuraPinoEntrada(portalBASE_GPIO_F, PINO_4|PINO_0);
    ESC_REG(GPIO_PORTF_PUR)|= PINO_4|PINO_0;

    HabilitaGlobal();
    HabilitaInterrupcaoGPIO(Interrupt_GPIO_F);
    ConfigIntGPIO(portalBASE_GPIO_F,PINO_4,Rising_edge);
    ConfigIntGPIO(portalBASE_GPIO_F,PINO_0,Both_edge);
    HabInterruptGPIO(portalBASE_GPIO_F,PINO_4|PINO_0);

    ESC_REG(NVIC_EN0) |= 1<<19;
    habilitaClockTimer(moduloTimer0);
    configTimer(TIMER0_BASE,TIMER_CFG_A_ONE_SHOT);
    ConfiguraPeriodoTimer(TIMER0_BASE,0x00,0xF42400);
    HabilitaIntTimer(TIMER0_BASE , TIMER_A_TIMEOUT);
    while(1);


    return 0;
}
