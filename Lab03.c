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
#define GPIO_LOCK           0x520
#define GPIO_LOCK_KEY           0x4C4F434B
#define GPIO_O_CR           0x524

#define habL1       escritaGPIO(portalBASE_GPIO_F,PINO_4,0xFF)
#define habL2       escritaGPIO(portalBASE_GPIO_B,PINO_0,0xFF)
#define habL3       escritaGPIO(portalBASE_GPIO_B,PINO_1,0xFF)
#define habL4       escritaGPIO(portalBASE_GPIO_B,PINO_5,0xFF)

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
//============================================================================
//  Placa catodo


#define habD1       escritaGPIO(portalBASE_GPIO_B,PINO_6,0x00)
#define habD2       escritaGPIO(portalBASE_GPIO_B,PINO_7,0x00)
#define habD3       escritaGPIO(portalBASE_GPIO_D,PINO_2,0x00)
#define habD4       escritaGPIO(portalBASE_GPIO_D,PINO_3,0x00)

void limpaBarramento(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0|PINO_1|PINO_2|PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4|PINO_5|PINO_6|PINO_7,0x00);
    escritaGPIO(portalBASE_GPIO_D,PINO_6,0xFF);
}

void limpaDigito(){
    escritaGPIO(portalBASE_GPIO_B,PINO_6|PINO_7,0xFF);
    escritaGPIO(portalBASE_GPIO_D,PINO_2|PINO_3,0xFF);
}

void set0(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
}
void set1(){
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
}
void set2(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void set3(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void set4(){
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void set5(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void set6(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void set7(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
}
void set8(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void set9(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void setA(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void setB(){
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void setC(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
}
void setD(){
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void setE(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
void setF(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0xFF);
}
//==========================================================
//  Placa anodo
/*
#define habD1       escritaGPIO(portalBASE_GPIO_B,PINO_6,0xFF)
#define habD2       escritaGPIO(portalBASE_GPIO_B,PINO_7,0xFF)
#define habD3       escritaGPIO(portalBASE_GPIO_D,PINO_2,0xFF)
#define habD4       escritaGPIO(portalBASE_GPIO_D,PINO_3,0xFF)

void limpaBarramento(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0|PINO_1|PINO_2|PINO_3,0xFF);
    escritaGPIO(portalBASE_GPIO_C,PINO_4|PINO_5|PINO_6|PINO_7,0xFF);
    escritaGPIO(portalBASE_GPIO_D,PINO_6,0x00);
}
void limpaDigito(){
    escritaGPIO(portalBASE_GPIO_B,PINO_6|PINO_7,0x00);
    escritaGPIO(portalBASE_GPIO_D,PINO_2|PINO_3,0x00);
}

void set0(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
}
void set1(){
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
}
void set2(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void set3(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void set4(){
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void set5(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void set6(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void set7(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
}
void set8(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void set9(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void setA(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void setB(){
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void setC(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
}
void setD(){
    escritaGPIO(portalBASE_GPIO_E,PINO_1,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_2,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void setE(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_E,PINO_3,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}
void setF(){
    escritaGPIO(portalBASE_GPIO_E,PINO_0,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_4,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_C,PINO_6,0x00);
}*/
//======================================================================
void crescente(uint8_t x){
    switch(x){
        case 0:
            set0();
            return;
        case 1:
            set1();
            return;
        case 2:
            set2();
            return;
        case 3:
            set3();
            return;
        case 4:
            set4();
            return;
        case 5:
            set5();
            return;
        case 6:
            set6();
            return;
        case 7:
            set7();
            return;
        case 8:
            set8();
            return;
        case 9:
            set9();
            return;
        case 10:
            setA();
            return;
        case 11:
            setB();
            return;
        case 12:
            setC();
            return;
        case 13:
            setD();
            return;
        case 14:
            setE();
            return;
        case 15:
            setF();
            return;
        default:
            limpaBarramento();
            return;
    }
}
void limpaMatriz(){
    escritaGPIO(portalBASE_GPIO_B,PINO_0|PINO_1|PINO_5,0x00);
    escritaGPIO(portalBASE_GPIO_F,PINO_4,0x00);
}
uint8_t matriz(){
    limpaMatriz();
    habL1;
    if(leituraGPIO(portalBASE_GPIO_F, PINO_0) == 0x01){
        return 0;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_1) == 0x02){
        return 1;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_2) == 0x04){
        return 2;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_3) == 0x08){
        return 3;
    }

    limpaMatriz();
    habL2;
    if(leituraGPIO(portalBASE_GPIO_F, PINO_0) == 0x01){
        return 4;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_1) == 0x02){
        return 5;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_2) == 0x04){
        return 6;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_3) == 0x08){
        return 7;
    }

    limpaMatriz();
    habL3;
    if(leituraGPIO(portalBASE_GPIO_F, PINO_0) == 0x01){
        return 8;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_1) == 0x02){
        return 9;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_2) == 0x04){
        return 10;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_3) == 0x08){
        return 11;
    }

    limpaMatriz();
    habL4;
    if(leituraGPIO(portalBASE_GPIO_F, PINO_0) == 0x01){
        return 12;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_1) == 0x02){
        return 13;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_2) == 0x04){
        return 14;
    }
    if(leituraGPIO(portalBASE_GPIO_F, PINO_3) == 0x08){
        return 15;
    }
    return 16;
}

void display(uint8_t n1,uint8_t n2,uint8_t n3,uint8_t n4){
    uint32_t ui32Loop;
    limpaBarramento();
    limpaDigito();
    crescente(n1);
    habD1;
    for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);

    limpaBarramento();
    limpaDigito();
    crescente(n2);
    habD2;
    for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);

    limpaBarramento();
    limpaDigito();
    crescente(n3);
    habD3;
    for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);

    limpaBarramento();
    limpaDigito();
    crescente(n4);
    habD4;
    for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);

}

int main(void)
{
    volatile uint32_t ui32Loop, delay;
    volatile uint8_t cont;

    habilitaClockportal(portalGPIO_B);
    habilitaClockportal(portalGPIO_C);
    habilitaClockportal(portalGPIO_D);
    habilitaClockportal(portalGPIO_E);
    habilitaClockportal(portalGPIO_F);

    ui32Loop = ESC_REG(SYSCTL_RCGC2_R);

    ESC_REG(portalBASE_GPIO_F+GPIO_LOCK) |= GPIO_LOCK_KEY;
    ESC_REG(portalBASE_GPIO_F+GPIO_O_CR) |= PINO_0;

    configuraPinoSaida(portalBASE_GPIO_B, PINO_0|PINO_1|PINO_5|PINO_6|PINO_7);
    configuraPinoSaida(portalBASE_GPIO_C, PINO_4 | PINO_5 | PINO_6 | PINO_7);
    configuraPinoSaida(portalBASE_GPIO_D, PINO_2|PINO_3|PINO_6);
    configuraPinoSaida(portalBASE_GPIO_E, PINO_2|PINO_3|PINO_0|PINO_1);
    configuraPinoSaida(portalBASE_GPIO_F, PINO_4);

    //configuraPinoEntrada(portalBASE_GPIO_F, PINO_4);
    configuraPinoEntrada(portalBASE_GPIO_F, PINO_0|PINO_1|PINO_2|PINO_3);
    ESC_REG(GPIO_PORTF_PDR)|= 0x17;

    cont=0;
    delay=0;


    /*while(1){//ex 2

        limpaBarramento();
        limpaDigito();
        crescente(cont);
        habD1;habD2;habD3;habD4;
        for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);
        if(delay == 0){
            delay=1000;
            if(cont==15){cont=0;}
            else {cont++;}
        }else{
            delay--;
        }
    }*/
//======================================================================================
    /*
  while(1){//ex 3
      display(0,1,2,3);
    }*/
//======================================================================================

    /*while(1){//ex 4
        limpaBarramento();
        limpaDigito();
        crescente(cont);
        habD4;
        for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);
        if(delay == 0){
            delay=1000;
            if(cont==15){cont=0;}
            else {cont++;}
        }else{
            delay--;
        }
    }*/
//======================================================================================
   /* while(1){//ex 6
        if (leituraGPIO(portalBASE_GPIO_F, PINO_4) == 0x10){
            limpaBarramento();
            limpaDigito();
            crescente(cont);
            habD4;
            for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);
            if(cont==15)cont=0;
            else cont++;
            for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);
        }else{
            limpaBarramento();
            limpaDigito();
            crescente(cont);
            habD4;
            for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);
//            if(cont==15)cont=0;
//            else cont++;
//            for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);
        }

    }*/
//======================================================================================
    /*delay=300000;
    while(1){//ex 7
        if(delay==0){
            if (leituraGPIO(portalBASE_GPIO_F, PINO_4) == 0x10){
                //nada
            }else{
                limpaBarramento();
                limpaDigito();
                crescente(cont);
                habD4;
                for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);
                if(cont==15)cont=0;
                else cont++;
                delay=300000;
            }
        }else{
            delay--;
        }

    }*/
//======================================================================================
    /*uint8_t n1=16,n2=16,n3=16,n4=0,mat;
    while(1){//ex 8
        mat=matriz();
        if(mat!=16){
            n4=mat;
        }
        display(n1,n2,n3,n4);
        for(ui32Loop = 0; ui32Loop < 2000; ui32Loop++);
    }*/
//======================================================================================
    uint8_t n1=0,n2=0,n3=0,n4=0,mat;
    while(1){//ex 8
        mat=matriz();
        if(mat!=16){
            if(delay == 0){
                delay=100;
                n1=n2;
                n2=n3;
                n3=n4;
                n4=mat;
            }
        }
        if(delay>0)delay--;
        display(n1,n2,n3,n4);
    }


	return 0;
}
