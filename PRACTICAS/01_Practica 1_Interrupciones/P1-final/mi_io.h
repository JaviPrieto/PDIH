/**############################################################################################
 * @file mi_io.h
 * @author Javier Prieto Infante	
 * @date 19 Mar 2019
 * @brief Declaración de las funciones que ejecuta el programa.

 ##############################################################################################*/

#define BYTE unsigned char

enum types { INVISIBLE, NORMAL, GRUESO };

// (1) ############################################################
// indica si se ha pulsado alguna tecla
int kbhit();

// (2) ############################################################
// indica la posicion x actual del cursor

int whereX();

// (3) ############################################################
// indica la posicion y actual del cursor

int whereY();

// (4) ############################################################
// Mueve el cursor a la posición según las 
// coordenadas especificadas por los argumentos x e y.

void gotoxy(int x, int y);

// (5) ############################################################
// fijar el aspecto del cursor, debe admitir tres valores:
// INVISIBLE, NORMAL y GRUESO.

void setcursortype(enum types);

// (6) ############################################################
// fija el modo de video deseado

void setvideomode(BYTE modo);

// (7) ############################################################
// obtiene el modo de video actual

int getvideomode();

// (8) ############################################################
// modifica el color de primer plano con 
//que se mostrarán los caracteres

void textcolor(int color);

// (9) ############################################################
// modifica el color de fondo con que se 
// mostrarán los caracteres

void textbackground(int color);

// (10) ############################################################
// borra toda la pantalla

void clrscr();

// (11) ############################################################
// borra una línea desde la posición actual del cursor
// hasta el final de la misma

void clreol();

// (12) ############################################################
// desplazar toda la pantalla una línea 
// hacia arriba

void scrollup(int lineas, int color, int lsi, int csi, int lid, int cid);

// (13) ############################################################
// desplazar toda la pantalla una línea 
// hacia abajo

void scrolldown(int lineas, int color, int lsi, int csi, int lid, int cid);

// (14) ############################################################
// escribe un carácter en pantalla con el 
// color indicado actualmente

void cputchar(const char c, int repeticiones);

// (15) ############################################################
// Obtiene el caracter de teclado y lo muestra en pantalla

int migetche();

// (16) ############################################################
// imprime una cadena de caracteres en pantalla

void micputs(const char * c);