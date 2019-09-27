#include <stdint.h>

#define ESC_REG(x)          (*((volatile uint32_t *)(x)))           //macro para escolher registrador

#define SYSCTL_RCGCGPIO    0x400FE608   //base registrador RCGCGPIO somado ao offset do registrador
#define GPIO_O_DR2R         0x500       //offset registrador GPIODR2R
#define GPIO_O_DEN          0x51C       //offset registrador GPIODEN
#define GPIO_O_DIR          0x400       //offset registrador GPIODIR
#define GPIO_O_DATA         0x00        //offset registrador GPIODATA

#define portalGPIO_A        0x01        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_B        0x02        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_C        0x04        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_D        0x08        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_E        0x10        //offsets para cada portal a partir do RCGCGPIO
#define portalGPIO_F        0x20        //offsets para cada portal a partir do RCGCGPIO

#define portalBASE_GPIO_A  0x40004000   //GPIO Port A (APB) base
#define portalBASE_GPIO_B  0x40005000   //GPIO Port B (APB) base
#define portalBASE_GPIO_C  0x40006000   //GPIO Port C (APB) base
#define portalBASE_GPIO_D  0x40007000   //GPIO Port D (APB) base
#define portalBASE_GPIO_E  0x40024000   //GPIO Port E (APB) base
#define portalBASE_GPIO_F  0x40025000   //GPIO Port F (APB) base

#define PINO_0                  0x01    //00000001
#define PINO_1                  0x02    //00000010
#define PINO_2                  0x04    //00000100
#define PINO_3                  0x08    //00001000
#define PINO_4                  0x10    //00010000
#define PINO_5                  0x20    //00100000
#define PINO_6                  0x40    //01000000
#define PINO_7                  0x80    //10000000

#define SYSCTL_RCGC2_R     0x400FE108   //base registrador RCGC2
#define SYSCTL_RCGC2_GPIOF 0x00000020   //offset para acessar o Port F do registrador RCGC2
#define GPIO_PORTF_DIR_R   0x40025400   //GPIO Port F (APB) base + offset registrador GPIODIR
#define GPIO_PORTF_DEN_R   0x4002551C   //GPIO Port F (APB) base + offset registrador GPIODEN
#define GPIO_PORTF_DATA_R  0x400253FC   //1111111100 -- faz a mudanca de todos os valores para os necessários, com o deslocamento de 2 bits <<
#define GPIO_PORTF_DR2R    0x40025500   //GPIO Port F (APB) base + offset registrador GPIODR2R
#define GPIO_PORTF_PUR     0x40025510   //GPIO Port F (APB) base + offset registrador GPIOPUR

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


int main(void)
{
    volatile uint32_t ui32Loop, ui32Loop1;

    // Habilita o portal de GPIO F
    habilitaClockportal(portalGPIO_F);

    // Faz leitura dummy para efeito de atraso
    ui32Loop = ESC_REG(SYSCTL_RCGC2_R);

    // Habilita o pino 3 do portal F, configura como saída digital
    configuraPinoSaida(portalBASE_GPIO_F, PINO_3);

    // Habilita o pino 4 do portal, configura como entrada com weak pull up
    ESC_REG(GPIO_PORTF_PUR)|= 0x10;

    configuraPinoEntrada(portalBASE_GPIO_F, PINO_4);

    // Loop principal
    while(1)
    {
        // Atraso
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

        if (leituraGPIO(portalBASE_GPIO_F, PINO_4) == 0x10) //botao esta setado quando nao apertado
        {
            escritaGPIO(portalBASE_GPIO_F, PINO_3, 0xFF);
        }
        else
            escritaGPIO(portalBASE_GPIO_F, PINO_3, 0x00);
    }
}
