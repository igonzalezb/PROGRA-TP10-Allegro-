/////////////////////////////////////////////// EMU_PORTS /////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//  Analisis de la salida correspondiente a lo que se haya ingresado.                                //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "emu_ports.h"


////////////////////////////////////////////// bitSet /////////////////////////////////////////////////
//                                                                                                   //
// Pone en 1 el n-ésimo bit del puerto port.                                                         //
// Recibe:    puerto (tipo MY_REG), numero de bit y puerto (tipo int) del enum                       //
// Devuelve: el puerto (MY_REG)		                                                                 //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG bitSet(MY_REG reg, uint n, int port)
{
        uint mask = (1<<n); //Se crea una mascara de 0 y un 1 en el bit que se desea editar
        
        switch (port) //Hace un OR entre la mascara y el puerto
        {
            case (PORTA):
                reg.by.hi = ((mask) |  (reg.by.hi));
                //printf("RESULT PORTA: %X\n", reg.by.hi);
                break;
            
            case (PORTB):
                reg.by.lo = ((mask) |  (reg.by.lo));
                //printf("RESULT PORTB: %X\n", reg.by.lo);
                break;
            
            case (PORTD):
                reg.w.word = ((mask) |  (reg.w.word));
                //printf("RESULT PORTD: %X\n", reg.w.word);
                break;
                
        }
    return reg;
        
}

////////////////////////////////////////////// bitClr /////////////////////////////////////////////////
//                                                                                                   //
// Pone en 0 el n-ésimo bit del puerto port.                                                          //
// Recibe:  puerto (tipo MY_REG), numero de bit y puerto (tipo int) del enum                                                                                   //
// Devuelve:     el puerto (MY_REG)	                                                                              //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG bitClr (MY_REG reg, uint n, int port) // Pone en 0 el n-ésimo bit del puerto port.
{
        uint mask = (~(1<<n)); //Se crea una mascara de 1 y un 0 en el bit que se desea editar
        //printf("MASK: %X\n", mask);
        
        switch (port) //Hace un AND entre la mascara y el puerto
        {
            case (PORTA):
                reg.by.hi = ((mask) & (reg.by.hi));
                //printf("RESULT PORTA: %X\n", reg.by.hi);
                break;
            
            case (PORTB):
                reg.by.lo = ((mask) & (reg.by.lo));
                //printf("RESULT PORTB: %X\n", reg.by.lo);
                break;
            
            case (PORTD):
                reg.w.word = ((mask) & (reg.w.word));
                //printf("RESULT PORTD: %X\n", reg.w.word);
                break;
                
        }
        return reg;
}

////////////////////////////////////////////// bitToggle ///////////////////////////////////////////////
//                                                                                                   //
// Pone en 1 el n-ésimo bit del puerto port si estaba en 0, en 0 de lo contrario.                    //
// Recibe:  puerto (tipo MY_REG), numero de bit y puerto (tipo int) del enum                         //
// Devuelve:  el puerto (MY_REG)	                                                                 //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG bitToggle (MY_REG reg, uint n, int port) // Pone en 1 el n-ésimo bit del puerto port si estaba en 0, en 0 de lo contrario.
{
    
        uint mask = (1<<n); //Se crea una mascara de 0 y un 1 en el bit que se desea editar
        
        switch (port) //Hace un XOR entre la mascara y el puerto
        {
            case (PORTA):
                reg.by.hi = ((mask) ^ (reg.by.hi));
                //printf("RESULT PORTA: %X\n", reg.by.hi);
                break;
            
            case (PORTB):
                reg.by.lo = ((mask) ^ (reg.by.lo));
                //printf("RESULT PORTB: %X\n", reg.by.lo);
                break;
            
            case (PORTD):
                reg.w.word = ((mask) ^ (reg.w.word));
                //printf("RESULT PORTD: %X\n", reg.w.word);
                break;
                
        }
        return reg;
}

////////////////////////////////////////////// bitGet /////////////////////////////////////////////////
//                                                                                                   //
// Devuelve el valor del n-ésimo bit del puerto port.                                                //
// Recibe:   puerto (tipo MY_REG), numero de bit y puerto (tipo int) del enum                        //
// Devuelve:  el puerto (MY_REG)	                                                                 //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

uint bitGet(MY_REG reg, uint n, int port) // Devuelve el valor del n-ésimo bit del puerto port.
{
    uint mask = (1<<n); //Se crea una mascara de 0 y un 1 en el bit que se desea editar
    
    uint bit;
    
        switch (port) //Hace un AND BITWISE entre la mascara y el puerto. Luego un AND entre un 1 y el resultado anterior. Si habia un 1 devuelve un 1 y si habia un 0 devuelve un 0
        {
            case (PORTA):
                bit = (((mask) & (reg.by.hi)) && 1);
                //printf("RESULT bit PORTA: %X\n", bit);
                break;
            
            case (PORTB):
                bit = (((mask) & (reg.by.lo)) && 1);
                //printf("RESULT bit PORTB: %X\n", bit);
                break;
            
            case (PORTD):
                bit = (((mask) & (reg.w.word)) && 1);
                //printf("RESULT bit PORTD: %X\n", bit);
                break;
                
        }
    return bit;   
}

////////////////////////////////////////////// maskOn /////////////////////////////////////////////////
//                                                                                                   //
// Una máscara es una secuencia binaria, que indica los números de bits que se van a poner en 1.     //
// Recibe:  puerto (tipo MY_REG), mascara y puerto (tipo int) del enum                               //
// Devuelve:   el puerto (MY_REG)	                                                                 //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG maskOn(MY_REG port_a, uint mask, int port) // Una máscara es una secuencia binaria, que indica los números de bits que se van a poner en 1. Ejemplo: si mask = 00010001, se van a encender los bits 0 y 4 del puerto port.
{
    
        switch (port) //Hace un OR entre la mascara y cada puerto
        {
            case (PORTA):
                port_a.by.hi = ((mask) |  (port_a.by.hi));
                //printf("RESULT PORTA: %X\n", port_a.by.hi);
                break;
            
            case (PORTB):
                port_a.by.lo = ((mask) |  (port_a.by.lo));
                //printf("RESULT PORTB: %X\n", reg.by.lo);
                break;
            
            case (PORTD):
                port_a.w.word = ((mask) |  (port_a.w.word));
                //printf("RESULT PORTD: %X\n", reg.w.word);
                break;
                
        }
        
  return port_a;      
        
}

////////////////////////////////////////////// maskOff ////////////////////////////////////////////////
//                                                                                                   //
// Pone en 0 los bits indicados por la máscara                                                       //
// Recibe:    puerto (tipo MY_REG), mascara y puerto (tipo int) del enum                             //
// Devuelve:   el puerto (MY_REG)	                                                                 //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG maskOff(MY_REG reg, uint mask, int port) // Pone en 0 los bits indicados por la máscara (al igual que en el ejemplo anterior).
{
  switch (port) //Hace un AND entre la mascara y cada puerto
        {
            case (PORTA):
                reg.by.hi = ((mask) & (reg.by.hi));
                //printf("RESULT PORTA: %X\n", reg.by.hi);
                break;
            
            case (PORTB):
                reg.by.lo = ((mask) & (reg.by.lo));
                //printf("RESULT PORTB: %X\n", reg.by.lo);
                break;
            
            case (PORTD):
                reg.w.word = ((mask) & (reg.w.word));
                //printf("RESULT PORTD: %X\n", reg.w.word);
                break;
                
        } 
  return reg;
}

////////////////////////////////////////////// maskToggle /////////////////////////////////////////////////
//                                                                                                      //
// Invierte el valor de los bits indicados por la máscara                                               //
// Recibe:  puerto (tipo MY_REG), mascara y puerto (tipo int) del enum                                 //
// Devuelve:   el puerto (MY_REG)	                                                                   //
//                                                                                                    //
///////////////////////////////////////////////////////////////////////////////////////////////////////

MY_REG maskToggle(MY_REG reg, uint mask, int port) // Invierte el valor de los bits indicados por la máscara
                                                   //(al igual que en el ejemplo anterior).
{
   switch (port) //Hace un XOR entre la mascara y cada puerto
        {
            case (PORTA):
                reg.by.hi = ((mask) ^ (reg.by.hi));  
                //printf("RESULT PORTA: %X\n", reg.by.hi);
                break;
            
            case (PORTB):
                reg.by.lo = ((mask) ^ (reg.by.lo));
                //printf("RESULT PORTB: %X\n", reg.by.lo);
                break;
            
            case (PORTD):
                reg.w.word = ((mask) ^ (reg.w.word));
                //printf("RESULT PORTD: %X\n", reg.w.word);
                break;
                
        } 
   return reg;
}

