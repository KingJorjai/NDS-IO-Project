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

// TODO:
// - Arreglar las interrupciones del teclado
//	Puede ser literalmente cualquier cosa
//	Las interrupciones de Timer0 en principio funcionan bien
void RutAtencionTeclado()
{
	if (ESTADO == CERRADA)
	{	
		if (TeclaPulsada()==A)
		{
			ESTADO=ABIERTA;
			visualizarPuertaAbierta();
			seg3=0;
			MostrarRombo(1, 5, 5);
			MostrarRomboGrande(2, 100, 100);
		}
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
