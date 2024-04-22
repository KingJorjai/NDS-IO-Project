#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos

#include "definiciones.h"

int BARRA_X_INICIAL;
int BARRA_Y_INICIAL;
//-----------//
// ELEMENTOS //
//-----------//

struct Pelota
{
	double vx;	// Velocidad horizontal
	double vy;	// Velocidad vertical
	
	double x;		// Posición en x
	double y;		// Posición en y
};
struct Bloque
{
	int destruido;	// DESTRUIDO , NO_DESTRUIDO
	
	double x;		// Posición en x
	double y;		// Posición en y
};
struct Barra
{
	double x;		// Posición en x
	double y;		// Posición en y
};

//---------------//
// DECLARACIONES //
//---------------//

struct Pelota pelota = {0, 0, 0, 0};

struct Bloque bloques[50];
int numBloques;

struct Barra barra;

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
struct Bloque bloque;
int PelotaTocaLadrillo()
{	
	int colision, arriba, abajo, izquierda, derecha, i;
	for (i=0; i<numBloques; i++)
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

void InicializarBarra()
{
	barra.x = BARRA_X_INICIAL;
	barra.y = BARRA_Y_INICIAL;
}