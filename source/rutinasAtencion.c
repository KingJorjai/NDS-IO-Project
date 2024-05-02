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
				vidas = 3;
				ESTADO=ESPERA;
			}
			else
			// Cambio de nivel
			if (tecla == ABAJO)
				{
					SumarNivel();
					visualizarNivel();
				}
			else if (tecla == ARRIBA)
				{
					RestarNivel();
					visualizarNivel();
				}
			break;

		case ESPERA:
			if (tecla==START || tecla==A)
			{
				PonerEnMarchaTempo();
				tick = 0;
				seg10 = 0;
				tiempo= 0;
				ESTADO=JUEGO;
			}
			break;

		case JUEGO:
			if (tecla==START)
			{
				PararTempo();
				visualizarPausa();
				OcultarPelota();
				OcultarBloques();
				OcultarBarra();
				ESTADO=PAUSA;
			}
			break;

		case PAUSA:
			if (tecla==START)
			{
				
				PonerEnMarchaTempo();
				visualizarJuegoFondo();
				DibujarPelota();
				DibujarBloques();
				DibujarBarra();
				ESTADO=JUEGO;
			}
			break;
		
		case PERDER: case GANAR:
			if (tecla==A)
			{
				NivelActual = 1;
				visualizarNivel();
				ESTADO=MENU_SELECTOR;
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
			ActualizarPelota();
			DibujarPelota();

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

			// DEBUG

			iprintf("\x1b[10;0HColisión con la barra: %d", PelotaTocaBarra());
			iprintf("\x1b[16;0HColisión con bloque: %d", PelotaTocaLadrillo());

			///

			if(PelotaTocaLadrillo()!=0 && NLadrillos>1)
			{
				CalcularRebote(PelotaTocaLadrillo());
			}		
			
			if(PelotaTocaSuelo()!=0 && vidas > 1)
			{
				InicializarPelota();
				vidas -= 1;
			}
			
			if(PelotaTocaPared()!=0)
			{
				CalcularRebote(PelotaTocaPared());	// El cambio de pantalla
			}
			
			if(PelotaTocaSuelo()!=0 && vidas==1)
			{
				OcultarPelota();
				OcultarBarra();
				OcultarBloques();
				visualizarPerder();
				ESTADO=PERDER;
			}
			
			if(PelotaTocaLadrillo()!=0 && NLadrillos==1)
			{
				OcultarPelota();
				OcultarBarra();
				visualizarGanar();
				ESTADO=GANAR;
			}
			if (PelotaTocaBarra() != 0)
			{
				CalcularRebote(ARRIBA);
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

