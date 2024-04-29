#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos
#include <math.h>		// Librería de funciones matemáticas

#include "definiciones.h"
#include "motor.h"
#include "sprites.h"

//-----------//
// ELEMENTOS //
//-----------//



//---------------//
// DECLARACIONES //
//---------------//

int NLadrillos;
Bloque bloques[50];

//------------//
// COLISIONES //
//------------//

/*
* Devuelve 1 -> Si la pelota toca el suelo
* Devuelve 0 -> En caso contrario
*/
int PelotaTocaSuelo()
{
	if (pelota.y >= ALTO_PANTALLA-32 /*debajo*/)
		return 1;
	else
		return 0;
}

/*
* Devuelve la pared con la que toca (IZQUIERDA/DERECHA/ARRIBA) o si no la toca (0)
*/
int PelotaTocaPared()
{
	if (pelota.y <=0)
		return ARRIBA;
	
	else if (pelota.x <= 0)
		return IZQUIERDA;
	
	else if (pelota.x >= ANCHO_PANTALLA-32)
		return DERECHA;
	
	else
		return 0;
}

/*
* Devuelve en qué posición relativa está el ladrillo con el que colisiona
* (ARRIBA/ABAJO/IZQUIERDA/DERECHA) o si no está tocando ningún ladrillo (0).
* 
* TODO: No tengo ni idea de si esto funciona o no. Hay que comprobarlo.
*/
int PelotaTocaLadrillo()
{	
	Bloque bloque;
	int colision, arriba, abajo, izquierda, derecha, i;
	for (i=0; i<NLadrillos; i++)
	{
		bloque = bloques[i];
		
		colision = bloque.y<=pelota.y && pelota.y+16<=bloque.y+32 &&
				bloque.x<=pelota.x && pelota.x+16<=bloque.x+32;	
		arriba = bloque.y+32 <= pelota.y+16;
		abajo =	bloque.y >= pelota.y;
		izquierda =	bloque.x+32 <= pelota.x+16;
		derecha = bloque.x >= pelota.x;
		
		if (colision) // if (colisión=true)
		{
			if (abajo) return ABAJO;
			if (arriba) return ARRIBA;
			if (izquierda) return IZQUIERDA;
			if (derecha) return DERECHA;
		}
	}
	
	return 0; // No hay colisión
}

/*
* Actualiza la velocidad de la pelota en función de en qué
* posición relativa se encuentra el objeto contra el que colisiona.
*/
void CalcularRebote(int direccion)
{
	switch(direccion)
	{
		case ARRIBA:
		case ABAJO:
			pelota.y = -pelota.y;
			break;
		
		case IZQUIERDA:
		case DERECHA:
			pelota.x = -pelota.x;
			break;
		
		default:
			break;
	}
}

//----------------//
// CONTROL PELOTA //
//----------------//

/*
* Le da la velocidad inicial a la pelota.
*/
void InicializarPelota()
{
	// Arbitrario por ahora
	pelota.x = 0.5;
	pelota.y = 0.5;
}

/*
* Actualiza la posición de la pelota en función
* de su velocidad actual. 
*/
void ActualizarPelota()
{
	pelota.x += pelota.vx;
	pelota.y += pelota.vy;
}


//---------------//
// CONTROL BARRA //
//---------------//

/*
* Da un valor inicial a las coordenadas de la barra.
*/
void InicializarBarra()
{
	barra.x = BARRA_X_INICIAL;
}

void ActualizarBarra()
{
	int x = TactilGetX();
	if(x != barra.x && x > 16 && x < ANCHO_PANTALLA-16)
	{
		barra.x = x;
		DibujarBarra();
	}
}

//-----------------//
// DIBUJAR SPRITES //
//-----------------//

void CargarNivel()
{
	int i,x,y;
	switch(NivelActual)
	{
		default:
			NLadrillos = 4;
			x = 10; y = 10;
			for (i=0; i<NLadrillos; i++)
			{
				bloques[i].destruido = NO_DESTRUIDO;
				bloques[i].x = x;
				bloques[i].y = y;
				
				x+=70;
			}
			
	
	}
}

void DibujarPelota()
{
	int int_x,int_y;
	int_x = (int) round(pelota.x);
	int_y = (int) round(pelota.y);
	
	MostrarPelota(2,int_x,int_y);
}

void DibujarBarra()
{
	int int_x;
	int_x = (int) round(barra.x)-16;
	
	MostrarBarra(2,int_x,0);
}

void DibujarBloques()
{
	int i,int_x,int_y;
	Bloque bloque;
	for (i=0; i<NLadrillos; i++)
	{
		if (bloques[i].destruido == NO_DESTRUIDO)
		{
			bloque = bloques[i];
			int_x = (int) round(bloque.x);
			int_y = (int) round(bloque.y);

			MostrarBloque(2,int_x,int_y);
		}
	}

}

void OcultarPelota()
{
	int int_x,int_y;
	int_x = (int) round(pelota.x);
	int_y = (int) round(pelota.y);
	
	BorrarPelota(2,int_x,int_y);
}

void OcultarBarra()
{
	int int_x;
	int_x = (int) round(barra.x)-16;
	
	BorrarBarra(2,int_x,0);
}

void OcultarBloques()
{
	int i,int_x,int_y;
	Bloque bloque;
	for (i=0; i<NLadrillos; i++)
	{
		if (bloques[i].destruido == NO_DESTRUIDO)
		{
			bloque = bloques[i];
			int_x = (int) round(bloque.x);
			int_y = (int) round(bloque.y);

			BorrarBloque(2,int_x,int_y);
		}
	}
}