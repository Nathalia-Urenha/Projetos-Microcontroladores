/* 
 * File:   contador_binario.c
 * Author: Nathália Maria Urenha Machado
 *
 * Created on 6 de Novembro de 2020, 10:02
 * 
 * Title: Contador em Binário de 0 à 15 em C
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
#define botao1  RA0         //Primeiro botão a ser utilizado
#define botao2  RA1         //Segundo botão a ser utilizado   




//Declaração das variáveis globais
char contador=0; //contador
void Delay(int a);
int tempo=0;

/*
 * 
 * 
 * 
 * 
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
    
    __delay_ms(30);     //Delay
    
    /*
    * Lógica para cada LED acender conforme um contador em binário
    *
    * Ocorre a identificação do estado em que o led ficará
    * conforme o número armazenado no contador.
    *
    * O contador utiliza 4 bits, em função disso será utilizado 4 LED's
    * Será possível contar até 15, conforme mostrado na tabela abaixo:
    * 
    * Decimal       Binário
    *---------------------------
    *   0             0000
    *   1             0001
    *   2             0010
    *   3             0011
    *   4             0100
    *   5             0101
    *   6             0110
    *   7             0111
    *   8             1000
    *   9             1001
    *   10            1010
    *   11            1011
    *   12            1100
    *   13            1101
    *   14            1110
    *   15            1111
    * 
    * O programa deverá tratar as seguinte situações:
    * (1) Contar em ordem crescente de 0 a 15 quando for pressionado o botão 1
    * (2) Fazer com que volte para o 0 quando chegar em 15
    * (3) Contar em ordem decrescente quando for pressionado o botão 2 
    */
    
    //Inicio da Lógica para acender os LED'S contando em binário
    
    //Situação 1 - contando em ordem crescente quando for precionado o botão1
    while(1) //LOOP INFINITO
    {
      
       if(!botao1)   //delay e segundo teste para inibir bounce
       {
        if(!botao1)
        {
          __delay_ms(20);

          while(!botao1) //Acender somente quando for precionado o botão1
          {
              
          }
          contador++;
          
          PORTB=contador;
        }
        //Situação 2: Fazer com que volte para o 0 quando chegar em 15
          if(contador == 15 )
          {
              __delay_ms(20);
              contador=0;
              PORTB=contador;
              __delay_ms(20);
          }
        }
        
        // Situação 3: Contar em ordem decrescente quando for pressionado o botão 2 
        if(botao2 == 1)   //delay e segundo teste para inibir bounce
        {
          if(botao2 == 1)
          {
            __delay_ms(20);

            while(botao2 == 1) //Acender somente quando for precionado o botão2
            {

            }
            contador--;

            PORTB=contador;
          }
        }    
    }
}
 void Delay(int a)
{
    for (int i=a; i>0; i--)
        __delay_ms(1);
}