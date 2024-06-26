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
#include "menu.h"
#include "motor.h"
#include "consola.h"

// Variables globales
	int tiempo;		// ¿Esta de dónde sale?
	int NivelActual;	// Nivel seleccionado en el menú de selección
	touchPosition DatosPantalla;
	
// Elementos del juego
	Barra barra;
	Pelota pelota;
	int NLadrillos;

void juego()
{	
	// Definiciones de variables
	int tecla = -1;
	// Estado inicial
	ESTADO=MENU_INICIO;
	visualizarMenuInicio();

	// Configuración interrupciones
		
		// Interrupt Patcher
		EstablecerVectorInt();
		
		// Temporizador
			// Activar temporizador			---> Bit 7
			// Generar interrupción al desbordar	---> Bit 6
			// División de frecuencia: 1024		---> Bits 1,0
			int conf_Tempo	= 0x00C3;	// 0000 0000 1100 0011
			int latch 	= 65208; 	// 100 interrupciones por segundo
			ConfigurarTemporizador(latch, conf_Tempo);
			HabilitarIntTempo();
		// Teclado
			// Activar interrupciones por parte de la tecla A		---> Bit 0
			// Activar interrupciones por parte de la tecla START	---> Bit 3
			// Activar interrupciones por parte de la tecla ARRIBA	---> Bit 6
			// Activar interrupciones por parte de la tecla ABAJO	---> Bit 7
			// Activar interrupciones por parte del teclado			---> Bit 14
			int conf_Tec	= 0x40C9;	// 0100 0000 1100 1001
			ConfigurarTeclado(conf_Tec);
			HabilitarIntTeclado();

	// Bucle principal del juego
	mostrarInfo();
	while(1)
	{
		// Encuesta del teclado
		if (TeclaDetectada())
		{
			tecla = TeclaPulsada();
			iprintf("\x1b[20;0HLa tecla pulsada es: %d", tecla);
		}


		switch (ESTADO)
		{
			case JUEGO:
				
				if(TactilTocada())
				{
					ActualizarBarra();
				}
				if (tecla != -1)
				{
					switch (tecla)
					{
					case DERECHA:
						// Mover la barra a la derecha
						if (barra.x > 0)
						{
							barra.x -= BARRA_VX;
						}
						break;
					case IZQUIERDA:
						// Mover la barra a la izquierda
						if (barra.x < ANCHO_PANTALLA - BARRA_ANCHO)
						{
							barra.x += BARRA_VX;
						}
						break;
					}
				}
				break;
		}

		tecla = -1; // Reiniciar la tecla pulsada

	}
	// Valorar si hay que inhibir las interrupciones
}