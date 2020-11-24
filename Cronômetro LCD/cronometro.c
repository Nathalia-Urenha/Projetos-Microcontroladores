/* 
 * File:   cronometro.c
 * Author: Nathália Maria Urenha Machado
 *
 * Data: 20/11/2020
 * 
 * MICROCONTROLADORES
 * 
 * Esse programa em C, realiza a contagem de um cronometro, que será mostrado
 * em um LCD.
 *
 */


//INCLUSÃO DE BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include "configuracao.h"
#include <pic18f4520.h>
#include "lcd.c"

/*
 * 
 */
//VARIÁVEIS
char cont_tempo=0, segundo=0, minuto=0, hora=0;
char tempo[4];

//FUNÇÕES
void mostrarLCD(char s, char m, char h);
void atualizarLCD(void);
void zerarLCD(void);


#define _XTAL_FREQ 4000000  //FREQUÊNCIA
#define botao PORTCbits.RC0 //BOTÃO QUE COMEÇA A CONTAGEM, QUE PAUSA A CONTAGEM, E ACENDE O LED VERDE
#define botao1 PORTCbits.RC1 //BOTÃO QUE ACENDE O LED VERMELHO
#define botao2 PORTCbits.RC2 //BOTÃO QUE ZERA A CONTAGEM
#define botao3 PORTCbits.RC3 //BOTÃO QUE RECOMEÇA A CONTAGEM
#define led1   PORTBbits.RB0 //LED VERDE
#define led2   PORTBbits.RB6 //LED VERMELHO

void main(void) 

{
    config();
    PORTA=0;
    PORTB=0;
    PORTD=0;
    PORTC=0;
    PORTE=0;
    TMR0=6;
    lcd_init();
    mostrarLCD(segundo, minuto, hora);
    while(1)
    {
        //ACENDE LED VERMELHO
        if(!botao1)
        {
           led2=1;                  
        }
        else
        {
            led2=0;
        }
        
        //COMEÇA CONTAGEM DO CRONOMETRO
        if(!botao)
        {
            while(!botao){}
            TMR0ON=!TMR0ON;
            
        }
        
        //ZERA CONTAGEM
        if(!botao2)
        {
            zerarLCD();
            break;
        }
        
        //RECOMEÇA CONTAGEM
        if(!botao3)
        {
            zerarLCD();
        }
               
    }
}

void atualizarLCD(void)
{
    segundo++;
    if(segundo>59)
    {
        segundo=0;
        minuto++;
    }
    mostrarLCD(segundo, minuto, hora);
}

void mostrarLCD(char s, char m, char h)
{
    sprintf(tempo, "%.2d:%.2d:%.2d", h, m, s);
    lcd_goto (1);
    lcd_puts(tempo);
}

void zerarLCD(void)
{
    hora=0;
    segundo=0;
    minuto=0;      
}

void __interrupt(high_priority) temp (void)
{
    if(TMR0IF)
    {
        TMR0IF=0;
        cont_tempo++;
        TMR0=6;
        if(cont_tempo>250)
        {
            cont_tempo=0;
            led1=!led1;
            atualizarLCD();
        }
    }
}