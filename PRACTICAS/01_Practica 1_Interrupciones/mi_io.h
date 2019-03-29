


// #####################################
// indica si se ha pulsado alguna tecla

void kbhit();

 

// #####################################
// indica la posicion x actual del cursor

int whereX();

// #####################################
// indica la posicion y actual del cursor

int whereY();

// #####################################
// Mueve el cursor a la posición según las 
// coordenadas especificadas por los argumentos x e y.

void gotoxy();


// #####################################
// fijar el aspecto del cursor, debe admitir tres valores:
// INVISIBLE, NORMAL y GRUESO.

void setcursortype(int tipo);

 

// #####################################
// fija el modo de video deseado

void setvideomode(int modo);

// #####################################
// obtiene el modo de video actual

int getvideomode();



// #####################################
// modifica el color de primer plano con 
//que se mostrarán los caracteres

void textcolor(int color);

// #####################################
// modifica el color de fondo con que se 
// mostrarán los caracteres

void textbackground(int color);



// #####################################
// borra toda la pantalla

void clrscr();

// #####################################
// borra una línea desde la posición actual del cursor
// hasta el final de la misma

void clreol();



// #####################################
// desplazar toda la pantalla una línea 
// hacia arriba

void scrollup();

// #####################################
// desplazar toda la pantalla una línea 
// hacia abajo

void scrolldown();



// #####################################
// escribe un carácter en pantalla con el 
// color indicado actualmente

void cputchar(int color);

// #####################################
// desplazar toda la pantalla una línea 
// hacia abajo

void getche(char c);

// #####################################
// imprime una cadena de caracteres en pantalla

void cputs(char c);