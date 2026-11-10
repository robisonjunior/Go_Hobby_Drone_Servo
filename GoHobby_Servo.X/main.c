 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

// Ticks de tempo para a saída GP2 em microsegundos (1 tick = 1 us)
// 500 us  -> Servo 0°
// 2500 us -> Servo 180°
volatile uint16_t servo_pulse_ticks = 500; 

volatile uint16_t t_subida_gp0 = 0;
volatile uint16_t largura_pulso_lida = 0;
volatile uint8_t pulso_pronto = 0;

// ISR do Timer2: Disparada a cada 20 ms (50 Hz) para gerar a janela do Servo
void Servo_Pulse_Handler(void)
{
    IO_RA2_SetHigh();
    
    // Captura o tempo inicial no Timer1 sem zerá-lo
    uint16_t t_inicio = TMR1_Read();
    uint16_t pulso_alvo = servo_pulse_ticks;
    
    // Aguarda a contagem exata de microsegundos sem bloquear outras flags
    while ((uint16_t)(TMR1_Read() - t_inicio) < pulso_alvo);
    
    IO_RA2_SetLow();
}

// ISR do IOC (GP0): Apenas grava marcos de tempo no Timer1
void Custom_IO_RA0_Handler(void)
{
    uint16_t agora = TMR1_Read();

    // Borda de Subida (GP0 foi para HIGH)
    if (IO_RA0_GetValue() == 1) 
    {
        t_subida_gp0 = agora;
    }
    // Borda de Descida (GP0 foi para LOW)
    else 
    {
        // Subtração sem sinal de 16 bits trata o estouro (overflow) do Timer1 automaticamente!
        largura_pulso_lida = (uint16_t)(agora - t_subida_gp0);
        pulso_pronto = 1;
    }
}

int main(void)
{
    SYSTEM_Initialize();

    // Associa o handler customizado ao driver do pino RA0
    IO_RA0_SetInterruptHandler(Custom_IO_RA0_Handler);

    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();

    // Inicia o Timer1 para rodar livremente como cronômetro de precisão
    TMR1_Start();

    // Inicia o Timer2 para gerar o ciclo de 20 ms (50 Hz) do Servo
    TMR2_OverflowCallbackRegister(Servo_Pulse_Handler);
    TMR2_Start();

    while (1)
    {
        // Processa os dados fora do contexto de interrupção
        if (pulso_pronto)
        {
            pulso_pronto = 0;

            // Pulso ~1040 us lido em GP0 -> Ajusta GP2 para 0° (~500 us)
            if (largura_pulso_lida >= 800 && largura_pulso_lida <= 1300)
            {
                servo_pulse_ticks = 500; 
            }
            // Pulso ~2000 us lido em GP0 -> Ajusta GP2 para 180° (~2500 us)
            else if (largura_pulso_lida >= 1700 && largura_pulso_lida <= 2300)
            {
                servo_pulse_ticks = 2390; // 2500
            }
        }
    }
}