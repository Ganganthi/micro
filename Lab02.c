#include <stdint.h>

//Registradores
#define RCC         0x400FE060
#define RCC2        0x400FE070
#define MISC        0x400FE058  // Masked Interrupt Status and Clear
#define RIS         0x400FE050

//Valores dentro de RCC
#define RCC_ACG          0x08000000  // Auto Clock Gating
#define RCC_SYSDIV_M     0x07800000  // System Clock Divisor
#define RCC_USESYSDIV    0x00400000  // Enable System Clock Divider
#define RCC_USEPWMDIV    0x00100000  // Enable PWM Clock Divisor
#define RCC_PWMDIV_M     0x000E0000  // PWM Unit Clock Divisor
#define RCC_PWMDIV_2     0x00000000  // PWM clock /2
#define RCC_PWMDIV_4     0x00020000  // PWM clock /4
#define RCC_PWMDIV_8     0x00040000  // PWM clock /8
#define RCC_PWMDIV_16    0x00060000  // PWM clock /16
#define RCC_PWMDIV_32    0x00080000  // PWM clock /32
#define RCC_PWMDIV_64    0x000A0000  // PWM clock /64
#define RCC_PWRDN        0x00002000  // PLL Power Down
#define RCC_BYPASS       0x00000800  // PLL Bypass
#define RCC_XTAL_M       0x000007C0  // Crystal Value
#define RCC_XTAL_4MHZ    0x00000180  // 4 MHz
#define RCC_XTAL_4_09MHZ 0x000001C0  // 4.096 MHz
#define RCC_XTAL_4_91MHZ 0x00000200  // 4.9152 MHz
#define RCC_XTAL_5MHZ    0x00000240  // 5 MHz
#define RCC_XTAL_5_12MHZ 0x00000280  // 5.12 MHz
#define RCC_XTAL_6MHZ    0x000002C0  // 6 MHz
#define RCC_XTAL_6_14MHZ 0x00000300  // 6.144 MHz
#define RCC_XTAL_7_37MHZ 0x00000340  // 7.3728 MHz
#define RCC_XTAL_8MHZ    0x00000380  // 8 MHz
#define RCC_XTAL_8_19MHZ 0x000003C0  // 8.192 MHz
#define RCC_XTAL_10MHZ   0x00000400  // 10 MHz
#define RCC_XTAL_12MHZ   0x00000440  // 12 MHz
#define RCC_XTAL_12_2MHZ 0x00000480  // 12.288 MHz
#define RCC_XTAL_13_5MHZ 0x000004C0  // 13.56 MHz
#define RCC_XTAL_14_3MHZ 0x00000500  // 14.31818 MHz
#define RCC_XTAL_16MHZ   0x00000540  // 16 MHz
#define RCC_XTAL_16_3MHZ 0x00000580  // 16.384 MHz
#define RCC_XTAL_18MHZ   0x000005C0  // 18.0 MHz
#define RCC_XTAL_20MHZ   0x00000600  // 20.0 MHz
#define RCC_XTAL_24MHZ   0x00000640  // 24.0 MHz
#define RCC_XTAL_25MHZ   0x00000680  // 25.0 MHz
#define RCC_OSCSRC       0x00000030  // Oscillator Source
#define RCC_OSCSRC_MAIN  0x00000000  // MOSC
#define RCC_OSCSRC_INT   0x00000010  // IOSC
#define RCC_OSCSRC_INT4  0x00000020  // IOSC/4
#define RCC_OSCSRC_30    0x00000030  // 30 kHz
#define RCC_MOSCDIS      0x00000001  // Main Oscillator Disable
#define RCC_SYSDIV_S     23
#define RCC_XTAL_S       6           // Shift to the XTAL field

//Valores de RCC2
#define RCC2_USERCC2     0x80000000  // Use RCC2
#define RCC2_DIV400      0x40000000  // Divide PLL as 400 MHz vs. 200
                                            // MHz
#define RCC2_SYSDIV2_M   0x1F800000  // System Clock Divisor 2
#define RCC2_SYSDIV2LSB  0x00400000  // Additional LSB for SYSDIV2
#define RCC2_USBPWRDN    0x00004000  // Power-Down USB PLL
#define RCC2_PWRDN2      0x00002000  // Power-Down PLL 2
#define RCC2_BYPASS2     0x00000800  // PLL Bypass 2
#define RCC2_OSCSRC2_M   0x00000070  // Oscillator Source 2
#define RCC2_OSCSRC2_MO  0x00000000  // MOSC
#define RCC2_OSCSRC2_IO  0x00000010  // PIOSC
#define RCC2_OSCSRC2_IO4 0x00000020  // PIOSC/4
#define RCC2_OSCSRC2_30  0x00000030  // 30 kHz
#define RCC2_OSCSRC2_32  0x00000070  // 32.768 kHz
#define RCC2_SYSDIV2_S   23

#define INT_PLL_LOCK        0x40

//Valores poss�veis de entrada para fun��o ConfigClock
#define SYSCTL_SYSDIV_1         0x07800000  // Processor clock is osc/pll /1
#define SYSCTL_SYSDIV_2         0x00C00000  // Processor clock is osc/pll /2
#define SYSCTL_SYSDIV_3         0x01400000  // Processor clock is osc/pll /3
#define SYSCTL_SYSDIV_4         0x01C00000  // Processor clock is osc/pll /4
#define SYSCTL_SYSDIV_5         0x02400000  // Processor clock is osc/pll /5
#define SYSCTL_SYSDIV_6         0x02C00000  // Processor clock is osc/pll /6
#define SYSCTL_SYSDIV_7         0x03400000  // Processor clock is osc/pll /7
#define SYSCTL_SYSDIV_8         0x03C00000  // Processor clock is osc/pll /8
#define SYSCTL_SYSDIV_9         0x04400000  // Processor clock is osc/pll /9
#define SYSCTL_SYSDIV_10        0x04C00000  // Processor clock is osc/pll /10
#define SYSCTL_SYSDIV_11        0x05400000  // Processor clock is osc/pll /11
#define SYSCTL_SYSDIV_12        0x05C00000  // Processor clock is osc/pll /12
#define SYSCTL_SYSDIV_13        0x06400000  // Processor clock is osc/pll /13
#define SYSCTL_SYSDIV_14        0x06C00000  // Processor clock is osc/pll /14
#define SYSCTL_SYSDIV_15        0x07400000  // Processor clock is osc/pll /15
#define SYSCTL_SYSDIV_16        0x07C00000  // Processor clock is osc/pll /16
#define SYSCTL_SYSDIV_17        0x88400000  // Processor clock is osc/pll /17
#define SYSCTL_SYSDIV_18        0x88C00000  // Processor clock is osc/pll /18
#define SYSCTL_SYSDIV_19        0x89400000  // Processor clock is osc/pll /19
#define SYSCTL_SYSDIV_20        0x89C00000  // Processor clock is osc/pll /20
#define SYSCTL_SYSDIV_21        0x8A400000  // Processor clock is osc/pll /21
#define SYSCTL_SYSDIV_22        0x8AC00000  // Processor clock is osc/pll /22
#define SYSCTL_SYSDIV_23        0x8B400000  // Processor clock is osc/pll /23
#define SYSCTL_SYSDIV_24        0x8BC00000  // Processor clock is osc/pll /24
#define SYSCTL_SYSDIV_25        0x8C400000  // Processor clock is osc/pll /25
#define SYSCTL_SYSDIV_26        0x8CC00000  // Processor clock is osc/pll /26
#define SYSCTL_SYSDIV_27        0x8D400000  // Processor clock is osc/pll /27
#define SYSCTL_SYSDIV_28        0x8DC00000  // Processor clock is osc/pll /28
#define SYSCTL_SYSDIV_29        0x8E400000  // Processor clock is osc/pll /29
#define SYSCTL_SYSDIV_30        0x8EC00000  // Processor clock is osc/pll /30
#define SYSCTL_SYSDIV_31        0x8F400000  // Processor clock is osc/pll /31
#define SYSCTL_SYSDIV_32        0x8FC00000  // Processor clock is osc/pll /32
#define SYSCTL_SYSDIV_33        0x90400000  // Processor clock is osc/pll /33
#define SYSCTL_SYSDIV_34        0x90C00000  // Processor clock is osc/pll /34
#define SYSCTL_SYSDIV_35        0x91400000  // Processor clock is osc/pll /35
#define SYSCTL_SYSDIV_36        0x91C00000  // Processor clock is osc/pll /36
#define SYSCTL_SYSDIV_37        0x92400000  // Processor clock is osc/pll /37
#define SYSCTL_SYSDIV_38        0x92C00000  // Processor clock is osc/pll /38
#define SYSCTL_SYSDIV_39        0x93400000  // Processor clock is osc/pll /39
#define SYSCTL_SYSDIV_40        0x93C00000  // Processor clock is osc/pll /40
#define SYSCTL_SYSDIV_41        0x94400000  // Processor clock is osc/pll /41
#define SYSCTL_SYSDIV_42        0x94C00000  // Processor clock is osc/pll /42
#define SYSCTL_SYSDIV_43        0x95400000  // Processor clock is osc/pll /43
#define SYSCTL_SYSDIV_44        0x95C00000  // Processor clock is osc/pll /44
#define SYSCTL_SYSDIV_45        0x96400000  // Processor clock is osc/pll /45
#define SYSCTL_SYSDIV_46        0x96C00000  // Processor clock is osc/pll /46
#define SYSCTL_SYSDIV_47        0x97400000  // Processor clock is osc/pll /47
#define SYSCTL_SYSDIV_48        0x97C00000  // Processor clock is osc/pll /48
#define SYSCTL_SYSDIV_49        0x98400000  // Processor clock is osc/pll /49
#define SYSCTL_SYSDIV_50        0x98C00000  // Processor clock is osc/pll /50
#define SYSCTL_SYSDIV_51        0x99400000  // Processor clock is osc/pll /51
#define SYSCTL_SYSDIV_52        0x99C00000  // Processor clock is osc/pll /52
#define SYSCTL_SYSDIV_53        0x9A400000  // Processor clock is osc/pll /53
#define SYSCTL_SYSDIV_54        0x9AC00000  // Processor clock is osc/pll /54
#define SYSCTL_SYSDIV_55        0x9B400000  // Processor clock is osc/pll /55
#define SYSCTL_SYSDIV_56        0x9BC00000  // Processor clock is osc/pll /56
#define SYSCTL_SYSDIV_57        0x9C400000  // Processor clock is osc/pll /57
#define SYSCTL_SYSDIV_58        0x9CC00000  // Processor clock is osc/pll /58
#define SYSCTL_SYSDIV_59        0x9D400000  // Processor clock is osc/pll /59
#define SYSCTL_SYSDIV_60        0x9DC00000  // Processor clock is osc/pll /60
#define SYSCTL_SYSDIV_61        0x9E400000  // Processor clock is osc/pll /61
#define SYSCTL_SYSDIV_62        0x9EC00000  // Processor clock is osc/pll /62
#define SYSCTL_SYSDIV_63        0x9F400000  // Processor clock is osc/pll /63
#define SYSCTL_SYSDIV_64        0x9FC00000  // Processor clock is osc/pll /64
#define SYSCTL_SYSDIV_2_5       0xC1000000  // Processor clock is pll / 2.5
#define SYSCTL_SYSDIV_3_5       0xC1800000  // Processor clock is pll / 3.5
#define SYSCTL_SYSDIV_4_5       0xC2000000  // Processor clock is pll / 4.5
#define SYSCTL_SYSDIV_5_5       0xC2800000  // Processor clock is pll / 5.5
#define SYSCTL_SYSDIV_6_5       0xC3000000  // Processor clock is pll / 6.5
#define SYSCTL_SYSDIV_7_5       0xC3800000  // Processor clock is pll / 7.5
#define SYSCTL_SYSDIV_8_5       0xC4000000  // Processor clock is pll / 8.5
#define SYSCTL_SYSDIV_9_5       0xC4800000  // Processor clock is pll / 9.5
#define SYSCTL_SYSDIV_10_5      0xC5000000  // Processor clock is pll / 10.5
#define SYSCTL_SYSDIV_11_5      0xC5800000  // Processor clock is pll / 11.5
#define SYSCTL_SYSDIV_12_5      0xC6000000  // Processor clock is pll / 12.5
#define SYSCTL_SYSDIV_13_5      0xC6800000  // Processor clock is pll / 13.5
#define SYSCTL_SYSDIV_14_5      0xC7000000  // Processor clock is pll / 14.5
#define SYSCTL_SYSDIV_15_5      0xC7800000  // Processor clock is pll / 15.5
#define SYSCTL_SYSDIV_16_5      0xC8000000  // Processor clock is pll / 16.5
#define SYSCTL_SYSDIV_17_5      0xC8800000  // Processor clock is pll / 17.5
#define SYSCTL_SYSDIV_18_5      0xC9000000  // Processor clock is pll / 18.5
#define SYSCTL_SYSDIV_19_5      0xC9800000  // Processor clock is pll / 19.5
#define SYSCTL_SYSDIV_20_5      0xCA000000  // Processor clock is pll / 20.5
#define SYSCTL_SYSDIV_21_5      0xCA800000  // Processor clock is pll / 21.5
#define SYSCTL_SYSDIV_22_5      0xCB000000  // Processor clock is pll / 22.5
#define SYSCTL_SYSDIV_23_5      0xCB800000  // Processor clock is pll / 23.5
#define SYSCTL_SYSDIV_24_5      0xCC000000  // Processor clock is pll / 24.5
#define SYSCTL_SYSDIV_25_5      0xCC800000  // Processor clock is pll / 25.5
#define SYSCTL_SYSDIV_26_5      0xCD000000  // Processor clock is pll / 26.5
#define SYSCTL_SYSDIV_27_5      0xCD800000  // Processor clock is pll / 27.5
#define SYSCTL_SYSDIV_28_5      0xCE000000  // Processor clock is pll / 28.5
#define SYSCTL_SYSDIV_29_5      0xCE800000  // Processor clock is pll / 29.5
#define SYSCTL_SYSDIV_30_5      0xCF000000  // Processor clock is pll / 30.5
#define SYSCTL_SYSDIV_31_5      0xCF800000  // Processor clock is pll / 31.5
#define SYSCTL_SYSDIV_32_5      0xD0000000  // Processor clock is pll / 32.5
#define SYSCTL_SYSDIV_33_5      0xD0800000  // Processor clock is pll / 33.5
#define SYSCTL_SYSDIV_34_5      0xD1000000  // Processor clock is pll / 34.5
#define SYSCTL_SYSDIV_35_5      0xD1800000  // Processor clock is pll / 35.5
#define SYSCTL_SYSDIV_36_5      0xD2000000  // Processor clock is pll / 36.5
#define SYSCTL_SYSDIV_37_5      0xD2800000  // Processor clock is pll / 37.5
#define SYSCTL_SYSDIV_38_5      0xD3000000  // Processor clock is pll / 38.5
#define SYSCTL_SYSDIV_39_5      0xD3800000  // Processor clock is pll / 39.5
#define SYSCTL_SYSDIV_40_5      0xD4000000  // Processor clock is pll / 40.5
#define SYSCTL_SYSDIV_41_5      0xD4800000  // Processor clock is pll / 41.5
#define SYSCTL_SYSDIV_42_5      0xD5000000  // Processor clock is pll / 42.5
#define SYSCTL_SYSDIV_43_5      0xD5800000  // Processor clock is pll / 43.5
#define SYSCTL_SYSDIV_44_5      0xD6000000  // Processor clock is pll / 44.5
#define SYSCTL_SYSDIV_45_5      0xD6800000  // Processor clock is pll / 45.5
#define SYSCTL_SYSDIV_46_5      0xD7000000  // Processor clock is pll / 46.5
#define SYSCTL_SYSDIV_47_5      0xD7800000  // Processor clock is pll / 47.5
#define SYSCTL_SYSDIV_48_5      0xD8000000  // Processor clock is pll / 48.5
#define SYSCTL_SYSDIV_49_5      0xD8800000  // Processor clock is pll / 49.5
#define SYSCTL_SYSDIV_50_5      0xD9000000  // Processor clock is pll / 50.5
#define SYSCTL_SYSDIV_51_5      0xD9800000  // Processor clock is pll / 51.5
#define SYSCTL_SYSDIV_52_5      0xDA000000  // Processor clock is pll / 52.5
#define SYSCTL_SYSDIV_53_5      0xDA800000  // Processor clock is pll / 53.5
#define SYSCTL_SYSDIV_54_5      0xDB000000  // Processor clock is pll / 54.5
#define SYSCTL_SYSDIV_55_5      0xDB800000  // Processor clock is pll / 55.5
#define SYSCTL_SYSDIV_56_5      0xDC000000  // Processor clock is pll / 56.5
#define SYSCTL_SYSDIV_57_5      0xDC800000  // Processor clock is pll / 57.5
#define SYSCTL_SYSDIV_58_5      0xDD000000  // Processor clock is pll / 58.5
#define SYSCTL_SYSDIV_59_5      0xDD800000  // Processor clock is pll / 59.5
#define SYSCTL_SYSDIV_60_5      0xDE000000  // Processor clock is pll / 60.5
#define SYSCTL_SYSDIV_61_5      0xDE800000  // Processor clock is pll / 61.5
#define SYSCTL_SYSDIV_62_5      0xDF000000  // Processor clock is pll / 62.5
#define SYSCTL_SYSDIV_63_5      0xDF800000  // Processor clock is pll / 63.5
#define SYSCTL_USE_PLL          0x00000000  // System clock is the PLL clock
#define SYSCTL_USE_OSC          0x00003800  // System clock is the osc clock
#define SYSCTL_XTAL_1MHZ        0x00000000  // External crystal is 1MHz
#define SYSCTL_XTAL_1_84MHZ     0x00000040  // External crystal is 1.8432MHz
#define SYSCTL_XTAL_2MHZ        0x00000080  // External crystal is 2MHz
#define SYSCTL_XTAL_2_45MHZ     0x000000C0  // External crystal is 2.4576MHz
#define SYSCTL_XTAL_3_57MHZ     0x00000100  // External crystal is 3.579545MHz
#define SYSCTL_XTAL_3_68MHZ     0x00000140  // External crystal is 3.6864MHz
#define SYSCTL_XTAL_4MHZ        0x00000180  // External crystal is 4MHz
#define SYSCTL_XTAL_4_09MHZ     0x000001C0  // External crystal is 4.096MHz
#define SYSCTL_XTAL_4_91MHZ     0x00000200  // External crystal is 4.9152MHz
#define SYSCTL_XTAL_5MHZ        0x00000240  // External crystal is 5MHz
#define SYSCTL_XTAL_5_12MHZ     0x00000280  // External crystal is 5.12MHz
#define SYSCTL_XTAL_6MHZ        0x000002C0  // External crystal is 6MHz
#define SYSCTL_XTAL_6_14MHZ     0x00000300  // External crystal is 6.144MHz
#define SYSCTL_XTAL_7_37MHZ     0x00000340  // External crystal is 7.3728MHz
#define SYSCTL_XTAL_8MHZ        0x00000380  // External crystal is 8MHz
#define SYSCTL_XTAL_8_19MHZ     0x000003C0  // External crystal is 8.192MHz
#define SYSCTL_XTAL_10MHZ       0x00000400  // External crystal is 10 MHz
#define SYSCTL_XTAL_12MHZ       0x00000440  // External crystal is 12 MHz
#define SYSCTL_XTAL_12_2MHZ     0x00000480  // External crystal is 12.288 MHz
#define SYSCTL_XTAL_13_5MHZ     0x000004C0  // External crystal is 13.56 MHz
#define SYSCTL_XTAL_14_3MHZ     0x00000500  // External crystal is 14.31818 MHz
#define SYSCTL_XTAL_16MHZ       0x00000540  // External crystal is 16 MHz
#define SYSCTL_XTAL_16_3MHZ     0x00000580  // External crystal is 16.384 MHz
#define SYSCTL_XTAL_18MHZ       0x000005C0  // External crystal is 18.0 MHz
#define SYSCTL_XTAL_20MHZ       0x00000600  // External crystal is 20.0 MHz
#define SYSCTL_XTAL_24MHZ       0x00000640  // External crystal is 24.0 MHz
#define SYSCTL_XTAL_25MHZ       0x00000680  // External crystal is 25.0 MHz
#define SYSCTL_OSC_MAIN         0x00000000  // Osc source is main osc
#define SYSCTL_OSC_INT          0x00000010  // Osc source is int. osc
#define SYSCTL_OSC_INT4         0x00000020  // Osc source is int. osc /4
#define SYSCTL_OSC_INT30        0x00000030  // Osc source is int. 30 KHz
#define SYSCTL_OSC_EXT4_19      0x80000028  // Osc source is ext. 4.19 MHz
#define SYSCTL_OSC_EXT32        0x80000038  // Osc source is ext. 32 KHz
#define SYSCTL_INT_OSC_DIS      0x00000002  // Disable internal oscillator
#define SYSCTL_MAIN_OSC_DIS     0x00000001  // Disable main oscillator

#define WRITE_REG(x) (*((volatile unsigned int *)(x)))

void ConfigClock (unsigned int ui32Config);



void ConfigClock (unsigned int ui32Config)
{
    unsigned int ui32Delay, ui32RCC, ui32RCC2;

    //
    // Get the current value of the RCC and RCC2 registers.
    //
    ui32RCC = WRITE_REG(RCC);
    ui32RCC2 = WRITE_REG(RCC2);

    //
    // Bypass the PLL and system clock dividers for now.
    //
    ui32RCC |= RCC_BYPASS;
    ui32RCC &= ~(RCC_USESYSDIV);
    ui32RCC2 |= RCC2_BYPASS2;

    //
    // Write the new RCC value.
    //
    WRITE_REG(RCC) = ui32RCC;
    WRITE_REG(RCC2) = ui32RCC2;

    //
    // See if the oscillator needs to be enabled.
    //
    if((ui32RCC & RCC_MOSCDIS) && !(ui32Config & RCC_MOSCDIS))
    {
        //
        // Make sure that the required oscillators are enabled.  For now, the
        // previously enabled oscillators must be enabled along with the newly
        // requested oscillators.
        //
        ui32RCC &= (~RCC_MOSCDIS | (ui32Config & RCC_MOSCDIS));

        //
        // Write the new RCC value.
        //
        WRITE_REG(RCC) = ui32RCC;

        //
        // Wait for a bit, giving the oscillator time to stabilize.  The number
        // of iterations is adjusted based on the current clock source; a
        // smaller number of iterations is required for slower clock rates.
        //
        if(((ui32RCC2 & RCC2_USERCC2) &&
            (((ui32RCC2 & RCC2_OSCSRC2_M) == RCC2_OSCSRC2_30) ||
             ((ui32RCC2 & RCC2_OSCSRC2_M) ==
              RCC2_OSCSRC2_32))) ||
           (!(ui32RCC2 & RCC2_USERCC2) &&
            ((ui32RCC & RCC_OSCSRC) == RCC_OSCSRC_30)))
        {
            //
            // Delay for 4096 iterations.
            //
            for(ui32Delay = 4096; ui32Delay>0; ui32Delay--);
        }
        else
        {
            //
            // Delay for 524,288 iterations.
            //
            for(ui32Delay = 524288; ui32Delay>0; ui32Delay--);

        }
    }

    //
    // Set the new crystal value and oscillator source.  Because the OSCSRC2
    // field in RCC2 overlaps the XTAL field in RCC, the OSCSRC field has a
    // special encoding within ui32Config to avoid the overlap.
    //
    ui32RCC &= ~(RCC_XTAL_M | RCC_OSCSRC);
    ui32RCC |= ui32Config & (RCC_XTAL_M | RCC_OSCSRC);
    ui32RCC2 &= ~(RCC2_USERCC2 | RCC2_OSCSRC2_M);
    ui32RCC2 |= ui32Config & (RCC2_USERCC2 | RCC_OSCSRC);
    ui32RCC2 |= (ui32Config & 0x00000008) << 3;

    //
    // Write the new RCC value.
    //
    WRITE_REG(RCC) = ui32RCC;
    WRITE_REG(RCC2) = ui32RCC2;

    //
    // Wait for a bit so that new crystal value and oscillator source can take
    // effect.
    //

    //
    // Set the PLL configuration.
    //
    ui32RCC &= ~RCC_PWRDN;
    ui32RCC |= ui32Config & RCC_PWRDN;
    ui32RCC2 &= ~RCC2_PWRDN2;
    ui32RCC2 |= ui32Config & RCC2_PWRDN2;

    //
    // Clear the PLL lock interrupt.
    //
    WRITE_REG(MISC) = INT_PLL_LOCK;

    //
    // Write the new RCC value.
    //
    if(ui32RCC2 & RCC2_USERCC2)
    {
        WRITE_REG(RCC2) = ui32RCC2;
        WRITE_REG(RCC) = ui32RCC;
    }
    else
    {
        WRITE_REG(RCC) = ui32RCC;
        WRITE_REG(RCC2) = ui32RCC2;
    }

    //
    // Set the requested system divider and disable the appropriate
    // oscillators.  This value is not written immediately.
    //
    ui32RCC &= ~(RCC_SYSDIV_M | RCC_USESYSDIV |
                 RCC_MOSCDIS);
    ui32RCC |= ui32Config & (RCC_SYSDIV_M | RCC_USESYSDIV |
                             RCC_MOSCDIS);
    ui32RCC2 &= ~(RCC2_SYSDIV2_M);
    ui32RCC2 |= ui32Config & RCC2_SYSDIV2_M;
    if(ui32Config & RCC2_DIV400)
    {
        ui32RCC |= RCC_USESYSDIV;
        ui32RCC2 &= ~(RCC_USESYSDIV);
        ui32RCC2 |= ui32Config & (RCC2_DIV400 | RCC2_SYSDIV2LSB);
    }
    else
    {
        ui32RCC2 &= ~(RCC2_DIV400);
    }

    //
    // See if the PLL output is being used to clock the system.
    //
    if(!(ui32Config & RCC_BYPASS))
    {
        //
        // Wait until the PLL has locked.
        //
        for(ui32Delay = 32768; ui32Delay > 0; ui32Delay--)
        {
            if(WRITE_REG(RIS) & INT_PLL_LOCK)
            {
                break;
            }
        }

        //
        // Enable use of the PLL.
        //
        ui32RCC &= ~(RCC_BYPASS);
        ui32RCC2 &= ~(RCC2_BYPASS2);
    }

    //
    // Write the final RCC value.
    //
    WRITE_REG(RCC) = ui32RCC;
    WRITE_REG(RCC2) = ui32RCC2;

    //
    // Delay for a little bit so that the system divider takes effect.
    //
    for(ui32Delay = 16; ui32Delay > 0; ui32Delay--);
}


//=========================================================================================

#define ESC_REG(x)                  (*((volatile uint32_t *)(x)))

#define SYSCTL_RCGC2_R              0x400FE108
#define SYSCTL_RCGC2_GPIOF          0x00000020
#define GPIO_PORTF_DIR_R            0x40025400
#define GPIO_PORTF_DEN_R            0x4002551C
#define GPIO_PORTF_DATA_R           0x400253FC

#define SYSCTL_RCC_R                0x400FE060
#define SYSCTL_RCC2_R               0x400FE070


int main(void)
{
    volatile uint32_t ui32Loop;

    // Habilita o portal de GPIO F
    ESC_REG(SYSCTL_RCGC2_R) = SYSCTL_RCGC2_GPIOF;

    // Faz leitura dummy para efeito de atraso
    ui32Loop = ESC_REG(SYSCTL_RCGC2_R);

    // Habilita o pino 3 do portal F, configura como saída digital
    ESC_REG(GPIO_PORTF_DIR_R) = 0x08;
    ESC_REG(GPIO_PORTF_DEN_R) = 0x08;

    // Loop principal
    while(1)
    {
        // Acende o LED
        ESC_REG(GPIO_PORTF_DATA_R)|= 0x08;

        // Atraso
        for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
        {
        }

        // Apaga o LED
        ESC_REG(GPIO_PORTF_DATA_R) &= ~(0x08);

        // Atraso
        for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
        {
        }
    }
}
