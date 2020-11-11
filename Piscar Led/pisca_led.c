/* 
 * File:   pisca_led.c
 * Author: Nathália Maria Urenha Machado
 *
 * Created on 6 de Novembro de 2020, 12:28
 */

//configurações padrões
// CONFIG
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//inclusao de bibliotecas
#include <xc.h>
#include<pic16f628a.h>
#include <stdio.h>
#include <stdlib.h>

//Definição das constantes
#define _XTAL_FREQ 40000000  // Indica qual a velocidade do clock que o mic ta utilizando
#define LED1 RB0

/*
 * 
 */
void main(void) {

    //Configurações de programa
    TRISA = 0B10111111; //Cada bit é a configuração de entrada e saida de um dos pinos do mic
                        //quando recebe valor 1 é configurado como entrada, se recebe 0 é conf
                        //como saída
    
    TRISB = 0B11110000; //PORTB Bits de 7 a 4 Entradas, de 3 a 0 Saídas
    CMCON = 7;          //Configura os bits de 0 a 3 da porta como digitais
    OSCF = 1;           //Configura o clock iterno em 4MHz
    PORTA = 0;          //Inicializa as portas
    PORTB = 0;
  
    //LOOP INFINITO
    //Escrever um código pra fazer o LED piscar
    while(1)
    {
      LED1 = 1;         //liga LED
       __delay_ms(30);       
       LED1 = 0;         //desliga led
      __delay_ms(30);
    }
}
