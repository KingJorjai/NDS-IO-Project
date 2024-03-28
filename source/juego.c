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

// Variables globales
	int tiempo;	// ¿Esta de dónde sale?
	int seg;	// Rutina Ktimer0 - Escribir cuántos segundos han pasado

void juego()
{	
	// Definiciones de variables
	int tecla = 0;

	// Estado inicial
	ESTADO=ESPERA;
	
	// Configuración interrupciones
		
		// Interrupt Patcher
		EstablecerVectorInt();
		
		// Temporizador
			// Activar temporizador			---> Bit 7
			// Generar interrupción al desbordar	---> Bit 6
			// División de frecuencia: 1024		---> Bits 1,0
			int conf_Tempo	= 0x00C3;	// 0000 0000 1100 0011
			int latch 	= 58982; 	// 5 interrupciones por segundo
			ConfigurarTemporizador(latch, conf_Tempo);
			HabilitarIntTempo();
		// Teclado
			// Activar interrupciones por parte de la tecla A ---> Bit 0
			// Activar interrupciones por parte del teclado   ---> Bit 14
			int conf_Tec	= 0x4001;	// 0100 0000 0000 0001
			ConfigurarTeclado(conf_Tec);
			HabilitarIntTeclado();

	// Bucle principal del juego
	while(1)
	{	
		// Autómata
		switch (ESTADO)
		{
			case ESPERA:
				
				// Encuesta del teclado
				if (TeclaDetectada())
				{
					// Ktec: <tecla>
					
						// Visualizar(tecla)
						tecla = TeclaPulsada();
						iprintf("\x1b[12;0HLa tecla pulsada es: %d", tecla);
					
					// Ktec: <START>
					if (tecla == START)
					{
						visualizarPuerta();
						PonerEnMarchaTempo();
						seg=0;
						ESTADO = CERRADA;
					}
				}
				break;
			
			case CERRADA:
				
				// No hay nada por ahora - Se gestiona por Interrupción
				
				break;
			
			case ABIERTA:
				
				// No hay nada por ahora - Se gestiona por Interrupción
				
				break;
		}


	}
	// Valorar si hay que inhibir las interrupciones
}



