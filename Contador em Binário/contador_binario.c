/* 
 * File:   contador_binario.c
 * Author: Nath�lia Maria Urenha Machado
 *
 * Created on 6 de Novembro de 2020, 10:02
 * 
 * Title: Contador em Bin�rio de 0 � 15 em C
 */

//configura��es padr�es
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




//Defini��o das constantes
#define _XTAL_FREQ 40000000  // Indica qual a velocidade do clock que o mic ta utilizando
#define botao1  RA0         //Primeiro bot�o a ser utilizado
#define botao2  RA1         //Segundo bot�o a ser utilizado   




//Declara��o das vari�veis globais
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

    //Configura��es de programa
    TRISA = 0B10111111; //Cada bit � a configura��o de entrada e saida de um dos pinos do mic
                        //quando recebe valor 1 � configurado como entrada, se recebe 0 � conf
                        //como sa�da
    
    TRISB = 0B11110000; //PORTB Bits de 7 a 4 Entradas, de 3 a 0 Sa�das
    CMCON = 7;          //Configura os bits de 0 a 3 da porta como digitais
    OSCF = 1;           //Configura o clock iterno em 4MHz
    PORTA = 0;          //Inicializa as portas
    PORTB = 0;
    
    __delay_ms(30);     //Delay
    
    /*
    * L�gica para cada LED acender conforme um contador em bin�rio
    *
    * Ocorre a identifica��o do estado em que o led ficar�
    * conforme o n�mero armazenado no contador.
    *
    * O contador utiliza 4 bits, em fun��o disso ser� utilizado 4 LED's
    * Ser� poss�vel contar at� 15, conforme mostrado na tabela abaixo:
    * 
    * Decimal       Bin�rio
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
    * O programa dever� tratar as seguinte situa��es:
    * (1) Contar em ordem crescente de 0 a 15 quando for pressionado o bot�o 1
    * (2) Fazer com que volte para o 0 quando chegar em 15
    * (3) Contar em ordem decrescente quando for pressionado o bot�o 2 
    */
    
    //Inicio da L�gica para acender os LED'S contando em bin�rio
    
    //Situa��o 1 - contando em ordem crescente quando for precionado o bot�o1
    while(1) //LOOP INFINITO
    {
      
       if(!botao1)   //delay e segundo teste para inibir bounce
       {
        if(!botao1)
        {
          __delay_ms(20);

          while(!botao1) //Acender somente quando for precionado o bot�o1
          {
              
          }
          contador++;
          
          PORTB=contador;
        }
        //Situa��o 2: Fazer com que volte para o 0 quando chegar em 15
          if(contador == 15 )
          {
              __delay_ms(20);
              contador=0;
              PORTB=contador;
              __delay_ms(20);
          }
        }
        
        // Situa��o 3: Contar em ordem decrescente quando for pressionado o bot�o 2 
        if(botao2 == 1)   //delay e segundo teste para inibir bounce
        {
          if(botao2 == 1)
          {
            __delay_ms(20);

            while(botao2 == 1) //Acender somente quando for precionado o bot�o2
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