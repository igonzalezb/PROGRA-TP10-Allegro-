/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "allegro.h"
#include "emu_ports.h"
#include "impresion_allegro.h"


int allegro (MY_REG port_a) 
{
    const char *title = {"PORT A - LEDs"};
           
    //MY_REG port_a;
    
    port_a.w.word = 0x0000; //Empiezo con todo el puerto apagado
    
    ALLEGRO_DISPLAY * display = NULL;
    
    ALLEGRO_BITMAP * welcome = NULL;
    
    ALLEGRO_BITMAP * start = NULL;
    
    ALLEGRO_BITMAP *ledOn = NULL;
    
    ALLEGRO_BITMAP *ledOff = NULL;
    
    ALLEGRO_BITMAP *icon = NULL;
    
    ALLEGRO_BITMAP *display_background;
    
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    
    ALLEGRO_TIMER *timer = NULL;
    
    ALLEGRO_SAMPLE *sample=NULL;
        
    bool key_pressed[11] = { false, false, false, false, false, false, false, false, false, false, false }; 

    bool redraw = false;
    
    bool do_exit = false; 
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                  Para elegir el THEME
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    printf("Welcome!\nPlese Select Theme (Number + Enter):\n0. DEFAULT\n1. POKEMON\n2. MARIO\n");
    int theme = (getchar()-48);  //SELECT THEME
    
    if (!((theme == DEFAULT) || (theme == POKEMON) || (theme == MARIO))){
        fprintf(stderr, "Failed to select Theme\n");
        return -1;
    }
        
    //DEFAULT, POKEMON, MARIO
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////   
    
    
    if(!al_init()) { //Inicializo Allegro
      fprintf(stderr, "Failed to initialize allegro!\n");
      return -1;
    }
    if(!al_init_image_addon()) { // Inicializo ADDON de las imagenes
        fprintf(stderr, "failed to initialize image addon !\n");
        return -1;
    }
    if(!al_install_keyboard()) {    //Inicializo el teclado
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
    }
    
    if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }
 
   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
//////////////////////////////////////////////////////////////////    
//                                                              //
//          Creacion de Variables de Allegro                    //
//                                                              //
//////////////////////////////////////////////////////////////////

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
      fprintf(stderr, "Failed to create display!\n");
      return -1;
    }
    
    welcome = al_load_bitmap("welcome.jpg");
    if(!welcome) {
      fprintf(stderr, "Failed to create welcome!\n");
      al_destroy_display(display);
      return -1;
    }
    
    
    start = al_load_bitmap("start.png");
    if(!welcome) {
      fprintf(stderr, "Failed to create start!\n");
      al_destroy_display(display);
      return -1;
    }
    
    
    icon = al_load_bitmap("icon.png");
    if(!icon) {
      fprintf(stderr, "Failed to create icon!\n");
      al_destroy_display(display);
      return -1;
    }
    
    
////////////////////////////////////////////////////////////////////////////////
//              THEMES: crea variables de allegro dependiendo del theme       //
////////////////////////////////////////////////////////////////////////////////
    
    switch (theme)
    {
        case (DEFAULT):
        {
            display_background = al_load_bitmap("background.png");
            if(!display_background) {
              fprintf(stderr, "Failed to create background bitmap!\n");
              al_destroy_display(display);
              return -1;
            }

            ledOn = al_load_bitmap("ledon.png");
            if(!ledOn) {
              fprintf(stderr, "Failed to create ledOn bitmap!\n");
              al_destroy_display(display);
              al_destroy_bitmap(display_background);

              return -1;
            }

            ledOff = al_load_bitmap("ledoff.png");
            if(!ledOn) {
              fprintf(stderr, "Failed to create ledOff bitmap!\n");
              al_destroy_display(display);
              al_destroy_bitmap(display_background);
              al_destroy_bitmap(ledOn);
              return -1;
            }
            sample = al_load_sample( "default.wav" );
            if (!sample){
              printf( "Audio clip sample not loaded!\n" ); 
              al_destroy_display(display);
              al_destroy_bitmap(display_background);
              al_destroy_bitmap(ledOn);
              al_destroy_bitmap(ledOff);
              
              return -1;
            }
            break;
        }
        case (POKEMON):
        {
            display_background = al_load_bitmap("background1.png");
            if(!display_background) {
              fprintf(stderr, "Failed to create background bitmap!\n");
              al_destroy_display(display);
              return -1;
            }

            ledOn = al_load_bitmap("ledon1.png");
            if(!ledOn) {
              fprintf(stderr, "Failed to create ledOn bitmap!\n");
              al_destroy_display(display);
              al_destroy_bitmap(display_background);

              return -1;
            }

            ledOff = al_load_bitmap("ledoff1.png");
            if(!ledOn) {
              fprintf(stderr, "Failed to create ledOff bitmap!\n");
              al_destroy_display(display);
              al_destroy_bitmap(display_background);
              al_destroy_bitmap(ledOn);
              return -1;
            }
            sample = al_load_sample( "pokemon.wav" );
            if (!sample){
              printf( "Audio clip sample not loaded!\n" ); 
              al_destroy_display(display);
              al_destroy_bitmap(display_background);
              al_destroy_bitmap(ledOn);
              al_destroy_bitmap(ledOff);
              
              return -1;
            }
            break;
        }
        case (MARIO):
        {
            display_background = al_load_bitmap("background2.jpg");
            if(!display_background) {
              fprintf(stderr, "Failed to create background bitmap!\n");
              al_destroy_display(display);
              return -1;
            }

            ledOn = al_load_bitmap("ledon2.png");
            if(!ledOn) {
              fprintf(stderr, "Failed to create ledOn bitmap!\n");
              al_destroy_display(display);
              al_destroy_bitmap(display_background);

              return -1;
            }

            ledOff = al_load_bitmap("ledoff2.png");
            if(!ledOn) {
              fprintf(stderr, "Failed to create ledOff bitmap!\n");
              al_destroy_display(display);
              al_destroy_bitmap(display_background);
              al_destroy_bitmap(ledOn);
              return -1;
            }
            sample = al_load_sample( "mario.wav" );
            if (!sample){
              printf( "Audio clip sample not loaded!\n" ); 
              al_destroy_display(display);
              al_destroy_bitmap(display_background);
              al_destroy_bitmap(ledOn);
              al_destroy_bitmap(ledOff);
              
              return -1;
            }
            break;
        }
            
    } 
    
////////////////////////////////////////////////////////////////////////////////
    
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
      fprintf(stderr, "Failed to create timer!\n");
      al_destroy_display(display);
      al_destroy_bitmap(display_background);
      al_destroy_bitmap(ledOn);
      al_destroy_bitmap(ledOff);
      al_destroy_sample(sample);
      return -1;
    }
  
    event_queue = al_create_event_queue();
    if(!event_queue) {
      fprintf(stderr, "Failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_bitmap(display_background);
      al_destroy_bitmap(ledOn);
      al_destroy_bitmap(ledOff);
      al_destroy_timer(timer);
      al_destroy_sample(sample);
      return -1;
    }
    
    
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO
    
    //Inicializo el display
    
    al_set_window_title(display, title); //Le pongo un titulo al display
    
    al_set_display_icon(display, icon);
    
    
//////////////////////////////////////////////////////////////   
    ALLEGRO_EVENT ev1;
    
    al_clear_to_color(al_color_name("white"));
    
    al_draw_bitmap(start,0 ,0, 0);
    
    al_flip_display();
    
    al_rest(1);
    
    al_draw_bitmap(welcome,0 ,0, 0);
     
    al_flip_display();
     
    al_wait_for_event(event_queue, &ev1);
    
   
    
     
     
////////////////////////////////////////////////////////////   
    
    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    
    al_draw_bitmap(display_background,0 ,0, 0);
    
    port_a = validacion_allegro('c', port_a, ledOn, ledOff); //Lo inicio Apagado
    
    al_flip_display();
    
    //Comienza el programa
    al_start_timer(timer);
    
    while(!do_exit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) 
        {
         if(key_pressed[KEY_S]) 
          port_a = validacion_allegro('s', port_a, ledOn, ledOff);  
         
         if(key_pressed[KEY_C]) 
            port_a = validacion_allegro('c', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_B]) 
            port_a = validacion_allegro('b', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_0]) 
            port_a = validacion_allegro('0', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_1]) 
            port_a = validacion_allegro('1', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_2]) 
            port_a = validacion_allegro('2', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_3]) 
            port_a = validacion_allegro('3', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_4]) 
            port_a = validacion_allegro('4', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_5]) 
            port_a = validacion_allegro('5', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_6]) 
            port_a = validacion_allegro('6', port_a, ledOn, ledOff);
         
         if(key_pressed[KEY_7]) 
            port_a = validacion_allegro('7', port_a, ledOn, ledOff);
         
         
         redraw = true;
      }
	  
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
         do_exit = true;
	  
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) 
	  {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_S:
               key_pressed[KEY_S] = true;
               break;
 
            case ALLEGRO_KEY_C:
               key_pressed[KEY_C] = true;
               break;
 
            case ALLEGRO_KEY_B: 
               key_pressed[KEY_B] = true;
               break;
 
            case ALLEGRO_KEY_0:
               key_pressed[KEY_0] = true;
               break;
            case ALLEGRO_KEY_1:
               key_pressed[KEY_1] = true;
               break;
            case ALLEGRO_KEY_2:
               key_pressed[KEY_2] = true;
               break;
            case ALLEGRO_KEY_3:
               key_pressed[KEY_3] = true;
               break;
            case ALLEGRO_KEY_4:
               key_pressed[KEY_4] = true;
               break;
            case ALLEGRO_KEY_5:
               key_pressed[KEY_5] = true;
               break;
            case ALLEGRO_KEY_6:
               key_pressed[KEY_6] = true;
               break;
            case ALLEGRO_KEY_7:
               key_pressed[KEY_7] = true;
               break;
         }
      }
	  
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) 
	  {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_S:
               key_pressed[KEY_S] = false;
               break;
 
            case ALLEGRO_KEY_C:
               key_pressed[KEY_C] = false;
               break;
 
            case ALLEGRO_KEY_B: 
               key_pressed[KEY_B] = false;
               break;
 
            case ALLEGRO_KEY_0:
               key_pressed[KEY_0] = false;
               break;
            case ALLEGRO_KEY_1:
               key_pressed[KEY_1] = false;
               break;
            case ALLEGRO_KEY_2:
               key_pressed[KEY_2] = false;
               break;
            case ALLEGRO_KEY_3:
               key_pressed[KEY_3] = false;
               break;
            case ALLEGRO_KEY_4:
               key_pressed[KEY_4] = false;
               break;
            case ALLEGRO_KEY_5:
               key_pressed[KEY_5] = false;
               break;
            case ALLEGRO_KEY_6:
               key_pressed[KEY_6] = false;
               break;
            case ALLEGRO_KEY_7:
               key_pressed[KEY_7] = false;
               break;
            case ALLEGRO_KEY_ESCAPE:
               do_exit = true;
               break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
		  
         redraw = false;
         al_flip_display();

      }
   }
   

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    al_stop_samples();
    al_uninstall_audio();
    al_uninstall_keyboard();
    al_uninstall_audio();

    
    al_destroy_display(display);
    al_destroy_bitmap(display_background);
    al_destroy_bitmap(ledOn);
    al_destroy_bitmap(ledOff);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    
    //al_destroy_sample(sample);    //ERROR SEGMENTATION FAULT    
    
    al_destroy_bitmap(welcome);
    al_destroy_bitmap(start);
    al_destroy_bitmap(icon);
    
    al_uninstall_system();
    
    return 0;
}