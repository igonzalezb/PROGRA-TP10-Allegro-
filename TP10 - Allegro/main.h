

#ifndef MAIN_H
#define MAIN_H

// ============ Colored Text ===========

#define BLACK_TEXT		   "\e[30;1m"
#define RED_TEXT		   "\e[31;1m"
#define GREEN_TEXT 		   "\e[32;1m"
#define YELLOW_TEXT                "\e[33;1m"
#define BLUE_TEXT 		   "\e[34;1m"
#define MAGENTA_TEXT               "\e[35;1m"
#define CYAN_TEXT 	   	   "\e[36;1m"
#define WHITE_TEXT 		   "\e[37;1m"

// ============ Colored Text End ===========

#define ALLEGRO 1 //1 con allegro, 0 terminal

#define VALIDO ((((c<='7') && (c>='0')) || (c=='s') || (c=='c') || (c=='b')))

#endif /* MAIN_H */

