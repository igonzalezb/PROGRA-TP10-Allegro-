#ifndef EMU_PORTS_H
#define EMU_PORTS_H


#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

enum imprime {PORTA, PORTB, PORTD};

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint16_t word;   // (2 Bytes)
} WORD_REG;

typedef struct
{
    uint8_t lo; // (2 bytes)
    uint8_t hi; 
} BYTE_REG;

typedef struct
{   
    //15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
    
    uint16_t b0  :1 ; // Low - Port B
    uint16_t b1  :1 ; 
    uint16_t b2  :1 ;
    uint16_t b3  :1 ;
    uint16_t b4  :1 ;
    uint16_t b5  :1 ;
    uint16_t b6  :1 ;
    uint16_t b7  :1 ;
    
    uint16_t b8  :1 ;   //High - Port A
    uint16_t b9  :1 ;
    uint16_t b10 :1 ;
    uint16_t b11 :1 ;
    uint16_t b12 :1 ;
    uint16_t b13 :1 ;
    uint16_t b14 :1 ;
    uint16_t b15 :1 ;
} BIT_REG;

typedef union        
{
	WORD_REG  w;    // word (2 bytes)
	BYTE_REG  by;   // lo(1 byte),hi(1byte) (2 bytes)
	BIT_REG   bi;   // 16 bits
} MY_REG;


////////////////////////////////////////////////////////////////////////////////

//==============================================================================

MY_REG bitSet(MY_REG, uint, int);

MY_REG bitClr (MY_REG, uint, int);

MY_REG bitToggle (MY_REG, uint, int);

uint bitGet(MY_REG, uint, int);

MY_REG maskOn(MY_REG, uint, int);

MY_REG maskOff(MY_REG, uint, int);

MY_REG maskToggle(MY_REG, uint, int);

//==============================================================================
#endif

