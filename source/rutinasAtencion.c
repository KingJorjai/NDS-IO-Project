/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"

int ESTADO; // Para controlar el estado del autómata en que esté
int seg3;   // Para ver si pasan tres segundos

void RutAtencionTeclado()
{
	switch (ESTADO)
	{	
		case: MENU_INICIO
		if (TeclaPulsada()==START)
		{
			VisualizarNivel();
			NivelActual=1
			VisualizarJuego();	// Fondo
		}
		break:

		case MENU_SELECTOR:
		if (TeclaPulsada()==A)
		{
			VisualizarJuego();	// Fondo
			CargarNivel();		// Sprites
			DibujarPelota();	// Sprite
			Dibujar jugador();	// Sprite
			vidas = 3;		// Vidas
			DibujarBloques();	// Sprites
			ESTADO=ESPERA;
		}
		break:

		case ESPERA:
		if (TeclaPulsada()==START)
		{
			InicializarPelota();
			VisualizarFondo();
			PonerEnMarchaTempo()
			tic = 0;
			seg10 = 0;
			tiempo= 0;
			ESTADO=JUEGO;
		}
		break:

		case JUEGO:
		if (TeclaPulsada()==START)
		{
			PararTempo();
			VisualizarPausa();
			PararPelota();
			BorrarPelota();
			BorrarBloques();
			BorrarJugador();
			ESTADO=PAUSA;
		}
		else if(TactilTocada())
		{
			Jugador.x = DatosPantalla.px
		}
		else if(PelotaTocaLadrillo() && NLadrillos>1)
		{
			CalcularRebote();
			EstablecerDireccionPelota();
			EliminarLadrillo();
		}		
		else if(PelotaTocaSuelo() && vidas > 1)
		{
			InicializarPelota();
			vidas -= 1;
		}
		else if(PelotaTocaPared())
		{
			CalcularRebote();	// El cambio de pantalla
			EstablecerDireccionPelota(); //se incluye en esta función
		}
		else if(PelotaTocaSuelo() && vidas = 1)
		{
		BorrarPelota();
		BorrarBloques();
		VisualizarPerder();
		ESTADO=PERDER;
		}
		else if(PelotaTocaLadrillo() && NLadrillos==1)
		{
		BorrarPelota();
		EliminarLadrillos();
		VisualizarGanar();
		ESTADO=GANAR;
		}
		}
		break:

		case PAUSA:
		else if (TeclaPulsada()==START)
		{
			PonerEnMarchaTempo();
			VisualizarJuego();
			ReaunudarPelota();
			DibujarPelota();
			DibujarBloques();
			MostrarJugador();
			ESTADO=JUEGO;
		}
		break:
		// no se si se puede hacer case perder ||ganar:
		case PERDER: case GANAR:
		if (TeclaPulsada()==A)
		{
		NivelActual = 1;
		VisualizarNivel(NivelActual);
		}
		break:
	}
	
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	

if (ESTADO!=ESPERA)
{
	tick++; 
	if (tick==5)
	{
		seg++;
		iprintf("\x1b[13;0HSegundos que han pasado=%d", seg); // Visualizar(Seg)
		tick=0;
		
		if (ESTADO == ABIERTA)
		{
			seg3++;
			if (seg3==3)
			{
				visualizarPuerta();
				seg3=0;
				ESTADO=CERRADA;
				BorrarRombo(1, 5, 5);
				BorrarRomboGrande(2, 100, 100);
			}
		}
				
	}
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

