/**############################################################################################

 * @file mi_main.c
 * @author Javier Prieto Infante	
 * @date 19 Mar 2019
 * @brief Tester de las funciones implementadas.

 ##############################################################################################*/

#include "mi_io.h"
//#include <conio.h>
#include <dos.h>

#define BYTE unsigned char

int main(){

	//Variables
	//BYTE modo;
	int linea, columna, color;
   enum types tipo_cursor = NORMAL;

	// (1) khbit ###################################################
	   clrscr();
   	cputs("Pulse una tecla para continuar (prueba del kbhit):");
   	while(!kbhit());
   	cprintf("\r\nTecla pulsada...\r\n",getch());
	   getch();

	// (4) gotoxy ###################################################
	   cputs("Prueba del gotoxy. Voy a avanzar una linea en Y y 10 caracteres en X. Pulse una tecla para continuar.\n");
   	linea = whereY() + 1;
   	columna = whereX() + 10;
   	gotoxy(columna,linea);

	// (2) whereX ###################################################
   	cprintf("Prueba del wherex/y. El cursor esta en (X=%d,Y=%d).Pulse una tecla para continuar.\n",columna+1,linea+1);
   	getch();

	// (3) whereY ###################################################
	   cprintf("Prueba del wherex/y. El cursor esta en (X=%d,Y=%d).Pulse una tecla para continuar.\n",columna+1,linea+1);
   	getch();

	// (5) setcursortype ###################################################
	   cputs("\nCursor invisible: ");
   	tipo_cursor = INVISIBLE;
   	setcursortype(tipo_cursor);
   	getch();
   	cputs("\nCursor grueso: ");
   	tipo_cursor = GRUESO;
   	setcursortype(tipo_cursor);
   	getch();
   	cputs("\nCursor normal: ");
   	tipo_cursor = NORMAL;
   	setcursortype(tipo_cursor);
   	getch();

	// (6) setvideomode ###################################################
	   setvideomode('d');
      cputs("Restituir modo de video");
      getch();
      setvideomode(3);
      clrscr();
      cputs("Pulse una tecla para finalizar\n");
      getch();
      
	// (7) getvideomode ###################################################

      
	// (8) textcolor ###################################################
	// (9) textbackground ###############################################
	   cputs("Cambiamos de color. FG=RED, BG=BLUE\n");
   	getch();
   	textcolor(4);
   	textbackground(1);
   	cputchar('P',1);
   	getch();
   	textcolor(7);	// COLOR DE FUENTE POR DEFECTO
   	textbackground(0); // FONDO AZUL PARA HACER EL CLEAR SCREAN
   	clrscr();

	// (10) clrscr ###################################################
	   cputs("Prueba del clrscr. Pulse una tecla para borrar la pantalla.\n");
   	getch();
   	clrscr();
   	cputs("Pantalla borrada. A partir de este punto voy a borrar la linea.\n");
   	

	// (11) clreol ###################################################
	   cputs("Pantalla borrada. A partir de este punto NO voy a borrar la linea.");
   	getch();
   	gotoxy(40,0);
   	clreol();
   	getch();
   	clrscr();

	// (12) scrollup ###################################################
	// (13) scrolldown ###################################################
	   cputs("Ahora hacemos scrollup de 1 linea\n");
   	getch();
   	cputs("Ahora hacemos scrolldown de 1 linea\n");
   	textbackground(4); // FONDO ROJO PARA EL SCROLL
   	color = 7;
   	scrollup(1, color, 0, 0, 24, 79);
   	getch();
   	scrolldown(1, color, 0, 0, 24, 79);
   	getch();
   	clrscr();

	


	// (14) cputchar ###################################################
   cputs("Prueba del cputchar\n");
   cputchar('P',1);

	// (15) getche ###################################################

	// (16) cputs ###################################################

	return 0;
}