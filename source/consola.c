//Ultima tecla por encuesta, interrupcion, estado, puntuacion, nombres, controles, vidas

//Ultima tecla por interrupcion, estado.

//Habria que meter luego todos en un mostrarInfo y que depende del estado del juego muestre una informacion u otra.
#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos

// Librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
#include "menu.h"
#include "motor.h"

int vidas;
int tecla = -1;
int puntuacion = 0;
int ESTADO;

void mostrarInfo(){
    //Siempre mostrar la ultima tecla detectada.

    if(ESTADO == MENU_INICIO){
        consoleClear();
        iprintf("\x1b[0;0HCreadores: Jorge, Jon, Lander.");
        iprintf("\x1b[6;0H¡Pulsa START para comenzar!");
    }
    else if(ESTADO == MENU_SELECTOR){
        consoleClear();
        iprintf("\x1b[0;0HUtiliza las flechas para elegir nivel");
        iprintf("\x1b[6;0HPulsa A para entrar al nivel");
    }   
    else if(ESTADO == JUEGO){
        consoleClear();
        iprintf("\x1b[0;0HPuntos: %d", puntuacion);
        iprintf("\x1b[6;0HVidas: %d", vidas);
        iprintf("\x1b[12;0HMueve la barra tocando la\npantalla inferior o\nusando las flechas");
        iprintf("\x1b[18;0HPulsa START para pausar el juego");
    }
    else if(ESTADO == PAUSA_REANUDAR || ESTADO == PAUSA_VOLVER){
        consoleClear();
        iprintf("\x1b[0;0HPuntos: %d", puntuacion);
        iprintf("\x1b[6;0HVidas: %d", vidas);
        iprintf("\x1b[12;0HPulsa START para\nreanudar el juego");
    }
}
