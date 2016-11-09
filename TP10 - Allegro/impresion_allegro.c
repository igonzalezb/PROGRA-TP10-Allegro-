/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <stdio.h>
#include <stdlib.h>

#include "allegro.h"

#include "impresion_allegro.h"




////////////////////////Validacion////////////////////////////////////////////////
//                                                                              //
// Recibe el valor de la tecla ingresada, la union del puerto, y dos punteros   //
// a bitmap(con un led encendido y otro apagado)                                //
//                                                                              //
//                                                                              //
// Hace diferentes acciones en funcion de lo que se le ingresa por teclado      //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

MY_REG validacion_allegro (char c, MY_REG port_a, ALLEGRO_BITMAP *ledOn, ALLEGRO_BITMAP *ledOff) 
{
	switch(c) 
	{   
    	//Se prenden todos los leds
    	case 's':
        	{
            	uint mask = 0xFFFF;
            	port_a=maskOn (port_a, mask, PORTA); //Prendo los leds que dice la mascara (todos)
            	impresion_allegro (port_a, ledOn, ledOff);
                
        	}
       	 	break;
        //Se apagan todos los leds
    	case 'c':  
        	{
            	uint mask = 0x0000;
            	port_a=maskOff (port_a, mask, PORTA); 
            	impresion_allegro (port_a, ledOn, ledOff);
                
        	}
        	break;
        //Los leds prendidos parpadean (se apagan y se vuelven a prender)
    	case 'b':
        	{   //BLINK 2
//                    uint mask = 0xFFFF;
//                    port_a=maskToggle(port_a, mask, PORTA);
//                    impresion_allegro (port_a, ledOn, ledOff);
//                    al_flip_display();
//                    port_a=maskToggle(port_a, mask, PORTA);
//                    impresion_allegro (port_a, ledOn, ledOff);
                    
                    //BLINK NORMAL
                        MY_REG blink;
                        blink.w.word = 0x0000;
                        impresion_allegro (blink, ledOn, ledOff);
                        system("clear");                        //PARA TERMINAL
                        al_flip_display();
                        impresion_allegro (port_a, ledOn, ledOff);
                        al_flip_display();                      //OJO!!!!!! SI LO DEJO BLINKEA EN MARRON SINO, SE PONE ROJA Y DESPUES VERDE
                }
        	break;
      
        //Se prende bit numero n
    	case '0':case '1': case '2': case '3': case '4': case '5': case '6': case '7': 
        	{
            	uint n = (c + '0');
            	port_a=bitSet(port_a, n, PORTA);
            	impresion_allegro (port_a, ledOn, ledOff);
                }
        	break;
    }
    return port_a;
}


/////////////////////////////// Impresion ////////////////////////////
//      Imprime un puerto segun el estado de sus leds               //
//      Recibe un puerto tipo MY_REG, y dos punteros a bitmap.      //
//      Un bitmap representa un led encendido y otro uno apagado    //
//////////////////////////////////////////////////////////////////////

void impresion_allegro (MY_REG port_a, ALLEGRO_BITMAP *ledOn, ALLEGRO_BITMAP *ledOff)
{
   
    uint mask;
    int i;
    
    
    for (i=7; i>=0; --i)
    {
        mask = (1<<i);

        if ((port_a.by.hi & mask))  //Si en este bit hay un 1 imprimo un led encendido
        {
            
            OnOff (ledOn, i);
        }

        else if (!(port_a.by.hi & mask))    //Si en el bit hay un 0 imprimo un led apagado
        {
            
            OnOff (ledOff, i);
        }
    }
}



///////////////////////////////////////// OnOff //////////////////////////////
//      Imprime en la pantalla un led encendido o apagado.                  //
//                                                                          //
//      Recibe el bitmat del led Encendido o Apagado, y el numero de led    //
//////////////////////////////////////////////////////////////////////////////
void OnOff (ALLEGRO_BITMAP *led, char c) 
{    
    float led_x = LED_SIZE/1.5;     //Coordenadas X del bitmap
    float led_y = SCREEN_H / 2.0 - LED_SIZE / 2.0; //Coordenadas Y del bitmap
    
    switch (c)
    {
            case (LED7):
               al_draw_bitmap(led, ((led_x + LED_SIZE) * 1), led_y, 0);
               break;
            case (LED6):
               al_draw_bitmap(led, ((led_x + LED_SIZE) * 2), led_y, 0);
               break;
            case (LED5):
               al_draw_bitmap(led, ((led_x + LED_SIZE) * 3), led_y, 0);
               break;
            case (LED4):
               al_draw_bitmap(led, ((led_x + LED_SIZE) * 4), led_y, 0);
               break;
            case (LED3):
               al_draw_bitmap(led, ((led_x + LED_SIZE) * 5), led_y, 0);
               break;
            case (LED2):
               al_draw_bitmap(led, ((led_x + LED_SIZE) * 6), led_y, 0);
               break;
            case (LED1):
               al_draw_bitmap(led, ((led_x + LED_SIZE) * 7), led_y, 0);
               break;
            case (LED0):
                al_draw_bitmap(led, ((led_x + LED_SIZE) * 8), led_y, 0);
                break;
    }
}

