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

int ESTADO;	// Para controlar el estado del autómata en que esté
int seg10;	// Para ver si pasan diez segundos
int tiempo;	// Lleva la cuenta de los segundos que pasan
int tic;	// Se suma uno en cada interrupción de KTimer0
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
				visualizarJuegoFondo();	// Fondo
				CargarNivel();		// Sprites
				DibujarPelota();	// Sprite
				DibujarBarra();	// Sprite
				vidas = 3;		// Vidas
				DibujarBloques();	// Sprites
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
			if (tecla==START)
			{
				InicializarPelota();
				visualizarJuegoFondo();
				PonerEnMarchaTempo();
				tic = 0;
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
	static int tick=0;
	static int seg=0;	
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

