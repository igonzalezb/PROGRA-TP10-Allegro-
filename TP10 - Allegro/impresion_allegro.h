
#ifndef IMPRESION_ALLEGRO_H
#define IMPRESION_ALLEGRO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h>

#include "emu_ports.h"

void impresion_allegro (MY_REG, ALLEGRO_BITMAP *, ALLEGRO_BITMAP *);

MY_REG validacion_allegro (char, MY_REG, ALLEGRO_BITMAP *,ALLEGRO_BITMAP *);

void OnOff (ALLEGRO_BITMAP *led, char c);

#endif /* IMPRESION_ALLEGRO_H */

