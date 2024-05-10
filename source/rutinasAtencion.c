/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"
#include "motor.h"
#include "menu.h"

int ESTADO;	// Para controlar el estado del autómata en que esté
int seg10;	// Para ver si pasan diez segundos
int tiempo;	// Lleva la cuenta de los segundos que pasan
int tick;	// Se suma uno en cada interrupción de KTimer0
int vidas;	// Vidas restantes
int puntuacion;	// Puntuación del jugador

void RutAtencionTeclado()
{
	int tecla = TeclaPulsada();
	switch (ESTADO)
	{	
		case MENU_INICIO:
			if (tecla==START)
			{
				NivelActual=1;
				visualizarNivel();	// Fondo
				ESTADO=MENU_SELECTOR;
				mostrarInfo();
			}
			break;

		case MENU_SELECTOR:
		
			// Selección de nivel
			if (tecla==A)
			{
				visualizarJuegoFondo();
				CargarNivel();
				InicializarBarra();
				InicializarPelota();
				DibujarPelota();
				DibujarBarra();
				DibujarBloques();
				PonerEnMarchaTempo();
				tick = 0;
				seg10 = 0;
				tiempo= 0;
				vidas = 3;
				ESTADO=JUEGO;
				mostrarInfo();
			}
			else
			// Cambio de nivel
			if (tecla == ABAJO)
				{
					SumarNivel();
					visualizarNivel();
					mostrarInfo();
				}
			else if (tecla == ARRIBA)
				{
					RestarNivel();
					visualizarNivel();
					mostrarInfo();
				}
			break;

		case JUEGO:
			if (tecla==START)
			{
				PararTempo();
				visualizarPausaReanudar();
				OcultarPelota();
				OcultarBloques();
				OcultarBarra();
				ESTADO=PAUSA_REANUDAR;
				mostrarInfo();
			}
			break;

		case PAUSA_REANUDAR:
			if (tecla==START || tecla==A)
			{
				
				PonerEnMarchaTempo();
				visualizarJuegoFondo();
				DibujarPelota();
				DibujarBloques();
				DibujarBarra();
				ESTADO=JUEGO;
				mostrarInfo();
			}
			if (tecla==ARRIBA || tecla==ABAJO)
			{
				visualizarPausaVolver();
				ESTADO=PAUSA_VOLVER;
				mostrarInfo();
			}
			
			break;
		case PAUSA_VOLVER:
			if (tecla==A)
			{
				visualizarNivel();
				ESTADO=MENU_SELECTOR;
				mostrarInfo();
			}
			if (tecla==ARRIBA || tecla==ABAJO)
			{
				visualizarPausaReanudar();
				ESTADO=PAUSA_REANUDAR;
				mostrarInfo();
			}
			if (tecla==START)
			{
				PonerEnMarchaTempo();
				visualizarJuegoFondo();
				DibujarPelota();
				DibujarBloques();
				DibujarBarra();
				ESTADO=JUEGO;
				mostrarInfo();
			}
			break;
		
		case PERDER: case GANAR:
			if (tecla==START || tecla==A)
			{
				NivelActual = 1;
				puntuacion = 0;
				visualizarNivel();
				ESTADO=MENU_SELECTOR;
				mostrarInfo();
			}
			break;
	}
}

void RutAtencionTempo()
{
	static int seg=0;
	switch (ESTADO)
		{
		case JUEGO:
			tick++;

			if (tick==100)
			{
				tick=0;
				seg++;
				tiempo++;
				if (seg==10)
				{
					seg=0;
					seg10=1;
				}
			}
			
			ActualizarPelota();
			DibujarPelota();
			DibujarBarra();
			///
			int pelotaTocaBarra = PelotaTocaBarra();
			int pelotaTocaLadrillo = PelotaTocaLadrillo();
			int pelotaTocaPared = PelotaTocaPared();
			int pelotaTocaSuelo = PelotaTocaSuelo();

			if(pelotaTocaLadrillo!=0 && NLadrillos>1)
			{
				CalcularRebote(pelotaTocaLadrillo);
				puntuacion += 133;
				mostrarInfo();
			}		
			
			if(pelotaTocaSuelo!=0 && vidas != 0)
			{
				InicializarPelota();
				vidas -= 1;
				mostrarInfo();
			}
			
			if(pelotaTocaPared!=0)
			{
				CalcularRebote(pelotaTocaPared);
			}

			
			if(pelotaTocaSuelo!=0 && vidas==0)
			{
				OcultarPelota();
				OcultarBarra();
				OcultarBloques();
				visualizarPerder();
				ESTADO=PERDER;
			}
			
			if(NLadrillosRestantes==0)
			{
				PararTempo();
				OcultarPelota();
				OcultarBarra();
				OcultarBloques();
				visualizarGanar();
				ESTADO=GANAR;
			}

			break;
	}
}

void EstablecerVectorInt()
{
	/*
	void irqSet(u32 mask, IntFn handler);
	Introduce información en el Vector de Interrupciones.
	Su orden de ejecución establece las prioridades.
	*/
	
	irqSet(IRQ_TIMER0, RutAtencionTempo); // Temporizador
	irqSet(IRQ_KEYS, RutAtencionTeclado); // Teclado
	
}

