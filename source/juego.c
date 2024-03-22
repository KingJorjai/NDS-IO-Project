/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos

// Librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

int tiempo;

void juego()
{	
	// Definiciones de variables
	int i=9;
	int tecla=0;;

	ESTADO=ESPERA;
	
	// Escribe en la fila 22 columna 5 de la pantalla	
	iprintf("\x1b[22;5HProbando la pantalla de texto");						

/* Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas */
	iprintf("\x1b[23;5HProbando la escritura con variable. Valor=%d", i);
	visualizarFondoUno();

	//*******************************EN LA 2.ACTIVIDAD ********************************//
        // LLAMADAS A REALIZAR:
	// Configurar el teclado.
	// Configurar el temporizador.
	// Establecer las rutinas de atención a interrupciones
	// Habilitar las interrupciones del teclado.
	// Habilitar las interrupciones del temporizador.
	// Habilitar interrupciones.
	//******************************************************************************//

	


	while(1)
	{	
		
      /*******************************EN LA 1.ACTIVIDAD*****************************************/
		/* Si el estado es ESPERA: codificar aquí la encuesta del teclado, sacar por pantalla la tecla que se ha pulsado, y si se pulsa la tecla START cambiar de estado */
	
		if (ESTADO==ESPERA && TeclaDetectada()) {
		
			tecla = TeclaPulsada();

			iprintf("\x1b[12;0HLa tecla pulsada es: %d", tecla);
			
			if (tecla == START) {

				iprintf("\x1b[14;0HCambia de estadio");

				visualizarPuerta();
				ESTADO = CERRADA;
			}
		}


	}
	// Valorar si hay que inhibir las interrupciones
}



