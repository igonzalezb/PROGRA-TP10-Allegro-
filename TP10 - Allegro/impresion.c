/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <unistd.h>

#include "impresion.h"
#include "main.h"

long decimalToBinary(MY_REG);




MY_REG validacion (char c, MY_REG port_a) //Recibo el valor de la tecla ingresada y la union del puerto 
{
    
    if (c=='s') //Se prenden todos los leds
        {
            uint mask = 0xFFFF;
            port_a=maskOn (port_a, mask, PORTA); //Prendo los leds que dice la mascara (todos)
            impresion (port_a);
        
        }
    else if (c == 'c') //Se apagan todos los leds
        {
            uint mask = 0x0000;
            port_a=maskOff (port_a, mask, PORTA);
            impresion (port_a);
        }
    else if (c == 'b') //Los leds prendidos parpadean (se apagan y se vuelven a prender)
    
        {
            MY_REG blink;
            blink.w.word = 0x0000;
            impresion (blink);
            usleep(300000);
            system("clear");
            impresion (port_a);   
        }
      
            
      
    else if ((c >= '0') && (c<= '7')) //Se prende el led N
        {
            uint n = (c + 48);
            port_a=bitSet(port_a, n, PORTA);
            impresion (port_a);
            
        }
    return port_a;
}





void impresion (MY_REG port_a)
{
//=================TERMINAL==============================================================
    long binary;
    
    binary = decimalToBinary(port_a); //Convierto numero a un int "binario"
            
    system("clear");        
    
    printf( WHITE_TEXT "LEDs in" CYAN_TEXT " PORTA" WHITE_TEXT ": " RED_TEXT"%08ld\n" WHITE_TEXT, binary); //Lo imprimo en pantalla

   
}

long decimalToBinary(MY_REG port_a) //Convierte numeros a binarios
{
    int remainder; 
    long binary = 0, i = 1;
  
    while((port_a.by.hi) != 0) 
    {
        remainder = (port_a.by.hi)%2;
        (port_a.by.hi) = (port_a.by.hi)/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}



void welcome (void)
{
        system("clear");
        
        char c;
        printf(BLUE_TEXT "\t\t\tBienvenido\n");
        printf(MAGENTA_TEXT "INSTRUCCIONES:\n");
        printf(WHITE_TEXT " Si presiona un numero del" GREEN_TEXT " '0' " WHITE_TEXT "al" GREEN_TEXT " '7' " WHITE_TEXT "se enciende el LED de esa posicion\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 'b' " WHITE_TEXT "parpadean los LEDs encendidos\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 's' " WHITE_TEXT "se encienden todos los LEDs\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 'c' " WHITE_TEXT "se apagan todos los LEDs\n");
        printf(WHITE_TEXT " Si presiona" GREEN_TEXT " 'ESC' " WHITE_TEXT "finaliza el programa\n");
        
        
        printf(WHITE_TEXT"\n\n Por favor, presione" RED_TEXT " ENTER " WHITE_TEXT"para comenzar");
        while ((c = getchar()) != '\n')
            {
               continue; 
            }
        system("clear");
}