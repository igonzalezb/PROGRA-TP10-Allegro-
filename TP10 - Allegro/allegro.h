

#ifndef ALLEGRO_H

#include "emu_ports.h"


#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h>

#define SCREEN_W    1024
#define SCREEN_H    320
#define LED_SIZE    64
#define FPS         60.0


int allegro (MY_REG);


enum LED_NUMBER {
   LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7
};

enum MYKEYS {
   KEY_S, KEY_C, KEY_B, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7
};

enum THEME {
    DEFAULT, POKEMON, MARIO
};




#endif /* ALLEGRO_H */

