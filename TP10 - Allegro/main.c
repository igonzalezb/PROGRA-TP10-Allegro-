/* 
 * File:   main.c
 * Author: 
 *
 * Created on October 20, 2016, 10:53 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "nonblock.h"
#include "emu_ports.h"
#include "impresion.h"


#include "allegro.h"


int main(void) 
{
    char c;
    int i=0;
    MY_REG port_a;
    
    if((ALLEGRO))
    {
        allegro(port_a);
        return (0);
    }
//=======================================================================================================================================================================================================================================================================
     
    else    //Terminal y Hardware
    {
            welcome();
    //==========================================================================================================================================================================================================================================================================

            port_a.w.word = 0x0000; //Asi empiezan todos los leds apagados

            impresion(port_a);  //Imprimo el puerto a

            nonblock(NB_ENABLE);

            while (c != '\e') //Funciona hasta que se apreta la tecla ESC
            {
                i=kbhit();

                if (i!=0)
                {
                    c= (fgetc(stdin)); //Obtengo lo ingresado por el teclado


                    if (VALIDO) //Si la tecla ingresada es valida continuo
                    {
                        system("clear"); //Limpio pantalla

                        port_a = validacion(c, port_a); //Ejecuto la operacion ingresada por el teclado
                    }

                }

            }

            nonblock(NB_DISABLE);

            system("clear"); //Limpio la pantalla
            return (0);
    }

    
    
}