/**############################################################################################

 * @file mi_io.c
 * @author Javier Prieto Infante	
 * @date 19 Mar 2019
 * @brief Implementación de las funciones que ejecuta el programa.

 ##############################################################################################*/

#include "mi_io.h"
#include <dos.h>

#define BYTE unsigned char

//VARIABLES GLOBALES

BYTE FG_COLOR = 7;	// Color del texto. Por defecto sera el 7 (gris claro)
BYTE BG_COLOR = 0; // Color de fondo. Por defecto sera el 0 (negro)
int ALTO = 24;	// Alto de la consola
int ANCHO = 79; // Ancho de la consola


// (1)
/**############################################################################################
 * @brief Indica si se ha pulsado alguna tecla
 *
 * La funcion llama a la subfuncion 1 de la interrupcion numero 16. Una
 * vez llamada, devuelve el registro cflag (zero flag), en el cual se
 * almacena un 0 si se ha pulsado una tecla y un 1 en caso contrario.
 *
 * @return devuelve el valor del registro zero flag
 ############################################################################################*/

int kbhit(){
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este 
	//caso, es "deteccion de tecla pulsada en bufer de teclado"
	inregs.h.ah = 0x01;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina 
	//de "gestion del teclado"
	int86(0x16, &inregs, &outregs);

	return outregs.x.cflag;
} 

// (2)
/**############################################################################################
 * @brief Indica la posición x actual del cursor
 *
 * La funcion llama a la subfuncion 3 de la interrupcion numero 10. Una
 * vez llamada, devuelve el registro dl, en el cual se
 * almacena la columna actual donde se encuentra el cursor.
 *
 * @return devuelve el valor del registro dl
 ############################################################################################*/

int whereX(){
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, 
	//en este caso, es "obtener tamaño y posicion del cursor"
	inregs.h.ah = 0x03;
	inregs.h.bh = 0x00;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina 
	//de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	return outregs.h.dl;

}

// (3)
/**############################################################################################
 * @brief Indica la posición y actual del cursor
 *
 * La funcion llama a la subfuncion 3 de la interrupcion numero 10. Una
 * vez llamada, devuelve el registro dh, en el cual se
 * almacena la fila actual donde se encuentra el cursor.
 *
 * @return devuelve el valor del registro dh
 ############################################################################################*/

int whereY(){
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, 
	//en este caso, es "obtener tamaño y posicion del cursor"
	inregs.h.ah = 0x03;
	inregs.h.bh = 0x00;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con 
	// la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	return outregs.h.dh;

}

// (4)
/**############################################################################################
 * @brief Mueve el cursor a una posicion determinada
 *
 * La funcion llama a la subfuncion 2 de la interrupcion numero 10. Dicha subfuncion
 * mueve el cursor a la posicion que se le indique
 *
 * @param x Indica la columna donde se quiere colocar el cursor
 * @param y Indice la fila donde se quiere colocar el cursor
 ############################################################################################*/

void gotoxy(int x, int y){
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, 
	// en este caso, es "colocar el cursor en una posicion determinada"
	inregs.h.ah = 0x02;

	// En el registro dx introducimos la fila y la columna donde queremos colocar el cursor
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la 
	//rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

}

// (5)
/**############################################################################################
 * @brief Fija el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO
 *
 * La funcion llama a la subfuncion 1 de la interrupcion numero 10. Dicha subfuncion
 * fija el aspecto del cursor en funcion de los numeros de linea que se le indiquen
 *
 * @param tipo_cursor Indica el tipo de cursor que desea establecer. (INVISIBLE,NORMAL o GRUESO)
 ############################################################################################*/

void setcursortype(enum types tipo_cursor){
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, 
	// en este caso, es "fijar el tamaño del cursor en modo texto"
	inregs.h.ah = 0x01;

	switch(tipo_cursor){
		case NORMAL:
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case GRUESO:
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
		case INVISIBLE:
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
	}

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia 
	//con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);
}

// (6)
/**############################################################################################
 * @brief Fija el modo de video deseado
*
* La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion
* fija el modo de video que se le indique.
*
* @param modo Es un caracter que indica el modo que se desea. Dicho caracter se debe traducir 
              al decimal adecuado
 ############################################################################################*/

void setvideomode(BYTE modo){
	union REGS inregs, outregs;

	inregs.h.ah = 0x00;
	inregs.h.al = modo;
	int86(0x10,&inregs,&outregs);
} 

// (7)
/**############################################################################################
 * @brief Obtiene el modo de video actual
*
* La funcion llama a la subfuncion 15 de la interrupcion numero 10. Dicha subfuncion nos devuelve el
* en el registro al el modo de video usado actualmente
*
* @return un entero que representa el modo de video actual
* @note la relacion entre los enteros y los modos de video se pueden observar en el fichero main.c
 ############################################################################################*/

int getvideomode(){
	union REGS inregs, outregs;

	//la rutina que queremos, en este caso, es "averiguar el modo de video"
	inregs.h.ah = 0xF;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia 
	//con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	return outregs.h.al;

} 

// (8)
/**############################################################################################
* @brief Modifica el color de primer plano con que se mostrarán los caracteres
*
* La funcion modifica la variable global FG_COLOR, la cual almacena el color en el que
* se escribe el texto por consola.
 ############################################################################################*/

void textcolor(int color){
	FG_COLOR = color;  // La funcion modifica la variable global FG_COLOR, la cual almacena el 
					   // color en el que se escribe el texto por consola.
}

// (9)
/**############################################################################################
* @brief Modifica el color de fondo con que se mostrarán los caracteres
*
* La funcion modifica la variable global BG_COLOR, la cual almacena el color en el que
* se escribe el fondo de los caracteres por consola.
 ############################################################################################*/

void textbackground(int color){
	BG_COLOR = color;	// La funcion modifica la variable global BG_COLOR, la cual almacena el 
						// color de fondo de la consola	
} 

// (10)
/**############################################################################################
* @brief Borra toda la pantalla
*
* Esta funcion borra toda la pantalla haciendo que la funcion scrollup deslice la pantalla
* hacia arriba tantas lineas como alto tenga la consola. Ademas, situa el cursor en la posicion 0,0.
 ############################################################################################*/

void clrscr(){
	int color = BG_COLOR << 4 | FG_COLOR;

	scrollup(ALTO+1, color, 0, 0, ALTO, ANCHO);
	gotoxy(0,0);

}

// (11)
/**############################################################################################
* @brief Borra una línea desde la posición actual del cursor hasta el final de la misma
*
* Esta funcion borra desde la posicion actual del cursor hasta el final de la linea (end of line, eof)
* haciendo uso de una de las caracteristicas de scrollup; y es que, cuando se llama a scrollup con el
* numero de lineas establecido en 0, se borra desde la (linea, columna) hasta la (linea, columna) que se
* desee
 ############################################################################################*/

void clreol(){
	int linea = whereY();	// Linea actual
	int columna = whereX();	// Columna actual

	int color = BG_COLOR << 4 | FG_COLOR;

	scrollup(0, color, linea, columna, linea, ANCHO);

}

// (12)
/**############################################################################################
* @brief Desplaza toda la pantalla una línea hacia arriba
*
* La funcion llama a la subfuncion 6 de la interrupcion numero 10. Dicha subfuncion
* desplaza toda la pantalla hacia arriba el numero de lineas que se le indiquen. Si 
* se le indican 0 lineas, borra la pantalla entre los puntos que se quieran (mediante lsi, csi, lid, cid.
*
* @param lineas Numero de lineas que se desean desplazar. 0 para borrar.
* @param color Color de relleno para los espacios en blanco. Los tres primeros bits indican el color de fondo
* y los tres ultimos el color del texto.
* @param lsi Linea superior izquierda. Linea inicial desde la que se desea comenzar a desplazar/borrar.
* @param csi Columna superior izquierda. Columna inicial desde la que se desea comenzar a desplazar/borrar.
* @param lid Linea inferior derecha. Linea final hasta la que se desea desplazar/borrar.
* @param cid Columna inferior derecha. Columna final hasta la que se desea desplazar/borrar.
 ############################################################################################*/

void scrollup(int lineas, int color, int lsi, int csi, int lid, int cid){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	
	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "desplazar zona de pantalla hacia arriba"
	inregs.h.ah = 0x06;

	// En el resto de registros introducimos todos los parametros descritos anteriormente
	inregs.h.al = lineas;
	inregs.h.bh = color;
	inregs.h.ch = lsi;
	inregs.h.cl = csi;
	inregs.h.dh = lid;
	inregs.h.dl = cid;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	// Una vez realizado el desplazamiento de la pantalla, desplazamos el cursor un mismo numero de lineas
	gotoxy(whereX(),whereY()-lineas);
}

// (13)
/**############################################################################################
* @brief Desplaza toda la pantalla una línea hacia abajo
*
* La funcion llama a la subfuncion 7 de la interrupcion numero 10. Dicha subfuncion
* desplaza toda la pantalla hacia abajo el numero de lineas que se le indiquen. Si 
* se le indican 0 lineas, borra la pantalla entre los puntos que se quieran (mediante lsi, csi, lid, cid.
*
* @param lineas Numero de lineas que se desean desplazar. 0 para borrar.
* @param color Color de relleno para los espacios en blanco. Los tres primeros bits indican el color de fondo
* y los tres ultimos el color del texto.
* @param lsi Linea superior izquierda. Linea inicial desde la que se desea comenzar a desplazar/borrar.
* @param csi Columna superior izquierda. Columna inicial desde la que se desea comenzar a desplazar/borrar.
* @param lid Linea inferior derecha. Linea final hasta la que se desea desplazar/borrar.
* @param cid Columna inferior derecha. Columna final hasta la que se desea desplazar/borrar.
 ############################################################################################*/

void scrolldown(int lineas, int color, int lsi, int csi, int lid, int cid){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "desplazar zona de pantalla hacia abajo"
	inregs.h.ah = 0x07;

	inregs.h.al = lineas;
	inregs.h.bh = color;
	inregs.h.ch = lsi;
	inregs.h.cl = csi;
	inregs.h.dh = lid;
	inregs.h.dl = cid;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);
} 

// (14)
/**############################################################################################
* @brief Escribe un caracter en pantalla con el color indicado actualmente
*
* La funcion llama a la subfuncion 9 de la interrupcion numero 10. Dicha subfuncion
* imprime un caracter por pantalla con el color indicado y el numero de veces que se desee.
* Finalmente avanza el cursor.
*
* @param caracter Caracter que se desea imprimir
* @param repeticiones Numero de veces que se desea imprimir el caracter
* @see avanzar_cursor
 ############################################################################################*/

void cputchar(const char c, int repeticiones){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	int color = BG_COLOR << 4 | FG_COLOR;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "escribir un caracter en pantalla"
	inregs.h.ah = 0x09;

	// En el resto de registros se introducen el caracter, el color y el numero de veces que se desea imprimir el caracter
	inregs.h.al = c;
	inregs.h.bl = color;
	inregs.h.bh = 0x00;
	inregs.x.cx = repeticiones;

	// Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
	int86(0x10, &inregs, &outregs);

	// Finalmente avanzamos el cursor
	//avanzar_cursor();
}

// (15)
/**############################################################################################
* @brief Obtiene el caracter de teclado y lo muestra en pantalla
*
* La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion
* lee un caracter desde el teclado y lo almacena en el registro al. En caso de ser
* una tecla especial queda almacenado en el ah.
*
* @return Decimal que representa el caracter introducido por teclado
 ############################################################################################*/
int migetche(){
	// Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
	// seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
	union REGS inregs, outregs;
	int caracter;

	// En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "leer un caracter desde el teclado"
	inregs.h.ah = 0x00;

	// Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "gestion del teclado"
	int86(0x16, &inregs, &outregs);

	// Si al es 0 significa que es un caracter especial. 1 en caso contrario
	if(outregs.h.al != 0)
		caracter = outregs.h.al;
	else
		caracter = outregs.h.ah;

	cputchar(caracter, 1);

	return caracter;
}

// (16)
/**############################################################################################
* @brief Imprime una cadena de caracteres en pantalla
*
* La funcion hace uso de la funcion cputchar para ir imprimiendo por pantalla
* uno a uno los caracteres de la cadena que se desea imprimir. Lo que hacemos es que
* vamos leyendo los caracteres de la cadena introducida hasta llegar al caracter
* de fin de linea ('\0'). Si el caracter es distinto del de salto de linea (\n)
* lo imprimimos y avanzamos al siguiente caracter. Si el caracter leido es el de 
* salto de linea, situamos el cursor al inicio de la siguiente linea y avanzamos
* el indice para leer el siguiente caracter
*
* @param cadena Cadena que se desea imprimir
* @return decimal que representa al ultimo caracter leido
 ############################################################################################*/

void micputs(const char * cadena){
	int i = 0;	// Indice para recorrer la cadena
	int linea = whereY();	// Linea actual
	int columna = whereX();	// Columna actual

	while(cadena[i] != '\0'){
		if(cadena[i] != '\n')
			cputchar(cadena[i],1);
		else {
			columna = 0;

			if(linea < ALTO)
				linea = linea + 1;
			else {
				scrollup(1, FG_COLOR, 0, 0, ALTO, ANCHO);
				linea = ALTO;
			}

			gotoxy(columna, linea);
		}

		i = i+1;	// Avanzamos el indice
	}

	return cadena[i];
}