#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos
#define _USE_MATH_DEFINES
#include <math.h>		// Librería de funciones matemáticas

#include "definiciones.h"
#include "motor.h"
#include "sprites.h"
#include "perifericos.h"

//-----------//
// ELEMENTOS //
//-----------//



//---------------//
// DECLARACIONES //
//---------------//

int NLadrillos;
int NLadrillosRestantes;
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
	if (pelota.y >= ALTO_PANTALLA-PELOTA_ALTO /*debajo*/)
		return 1;
	else
		return 0;
}

/*
* Devuelve la pared con la que toca (IZQUIERDA/DERECHA/ARRIBA) o si no la toca (0)
*/
int PelotaTocaPared()
{
	if (pelota.y < 0)
		return ABAJO;
	
	if (pelota.x < 0)
		return DERECHA;
	
	if (pelota.x + PELOTA_ANCHO > ANCHO_PANTALLA)
		return IZQUIERDA;
	
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
	int colision=0,vertical=0,horizontal=0,arriba=0,abajo=0,izquierda=0,derecha=0,i;
	colision = 0;

	Bloque bloque; // Bloque con el que colisiona
	// double centroPelotaX; // Centro horizontal de la pelota
	// double centroPelotaY; // Centro vertical de la pelota
	
	for(i=0; i<NLadrillos; i++)
	{
		bloque = bloques[i];
		if (bloque.destruido == NO_DESTRUIDO)
		{
			horizontal = (pelota.x+PELOTA_ANCHO > bloque.x && pelota.x < bloque.x+BLOQUE_ANCHO); // acotado horiz.
			vertical = (pelota.y+PELOTA_ALTO > bloque.y && pelota.y < bloque.y+BLOQUE_ALTO); // acotado vert.
			
			if (horizontal && vertical)
			{
				colision = 1;
			
				if (pelota.y < bloque.y) arriba = 1;
				if (pelota.y+PELOTA_ALTO > bloque.y+BLOQUE_ALTO) abajo = 1;

				if (pelota.x < bloque.x) izquierda = 1;
				if (pelota.x+PELOTA_ANCHO > bloque.x+BLOQUE_ANCHO) derecha = 1;
			}
			
			if (colision)
			{
				bloques[i].destruido = DESTRUIDO;
				BorrarBloque(2+i,bloque.x,bloque.y);
				NLadrillosRestantes -= 1;

				if		(arriba && !abajo && !izquierda && !derecha) return ARRIBA;
				else if (!arriba && abajo && !izquierda && !derecha) return ABAJO;
				else if (!arriba && !abajo && izquierda && !derecha) return IZQUIERDA;
				else if (!arriba && !abajo && !izquierda && derecha) return DERECHA;
				else if (arriba && !abajo && izquierda && !derecha) return ARRIBA_IZQUIERDA;
				else if (arriba && !abajo && !izquierda && derecha) return ARRIBA_DERECHA;
				else if (!arriba && abajo && izquierda && !derecha) return ABAJO_IZQUIERDA;
				else if (!arriba && abajo && !izquierda && derecha) return ABAJO_DERECHA;
				else
				{
					pelota.vx = -pelota.vx;
					pelota.vy = -pelota.vy;
					return -1; // No debería llegar aquí
				}
			}
		}
	}
	return 0;
}
/**
 * Devuelve 1 si la pelota toca la barra, 0 en caso contrario.
*/
int PelotaTocaBarra()
{
	// Verdadero si la pelota está tocando la barra
	int colision = pelota.y+PELOTA_ALTO > BARRA_Y_INICIAL
		&& pelota.y+PELOTA_ALTO < BARRA_Y_INICIAL+BARRA_ALTO
		&& pelota.x+PELOTA_ANCHO>=barra.x
		&& pelota.x <= barra.x+BARRA_ANCHO;

	if (colision)
	{
		double centroPelota = pelota.x + PELOTA_ANCHO/2;	// Centro horizontal de la pelota
		double centroBarra = barra.x + BARRA_ANCHO/2;		// Centro horizontal de la barra

		double desvio = centroPelota - centroBarra;	// Positivo si la pelota está a la derecha de la barra
		double maxDesvio = BARRA_ANCHO/2;			// Máximo desvío posible
		desvio = desvio/maxDesvio;					// Normalizar el desvío

		const double limDesvio = 0.7;					// Límite de desvío
		// Limitar el desvío
		if (desvio > limDesvio) desvio = limDesvio;
		if (desvio < -limDesvio) desvio = -limDesvio;

		pelota.vx = desvio;							// Cambiar la velocidad horizontal
		pelota.vy = -sqrt(1-pow(fabs(desvio),2));			// Cambiar la velocidad vertical


		return 1;
	}
	else return 0;
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
			pelota.vy = -fabs(pelota.vy);
			break;
		case ABAJO:
			pelota.vy = fabs(pelota.vy);
			break;
		case IZQUIERDA:
			pelota.vx = -fabs(pelota.vx);
			break;
		case DERECHA:
			pelota.vx = fabs(pelota.vx);
			break;
		case ARRIBA_IZQUIERDA:
			pelota.vx = -fabs(pelota.vx);
			pelota.vy = -fabs(pelota.vy);
			break;
		case ARRIBA_DERECHA:
			pelota.vx = fabs(pelota.vx);
			pelota.vy = -fabs(pelota.vy);
			break;
		case ABAJO_IZQUIERDA:
			pelota.vx = -fabs(pelota.vx);
			pelota.vy = fabs(pelota.vy);
			break;
		case ABAJO_DERECHA:
			pelota.vx = fabs(pelota.vx);
			pelota.vy = fabs(pelota.vy);
			break;
		case -1:
			// No debería llegar aquí
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
	pelota.vx = (( (double)(rand()%20) ) - 10) / 15;
	pelota.vy = sqrt(1-pow(pelota.vx,2));
	pelota.velocidad = PELOTA_V_INICIAL;

	pelota.x = PELOTA_X_INICIAL;
	pelota.y = PELOTA_Y_INICIAL;
}

/*
* Actualiza la posición de la pelota en función
* de su velocidad actual. 
*/
void ActualizarPelota()
{
	pelota.x += pelota.vx * pelota.velocidad;
	pelota.y += pelota.vy * pelota.velocidad;
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
	if(x != barra.x-BARRA_ANCHO/2 && x > BARRA_ANCHO/2 && x < ANCHO_PANTALLA-BARRA_ANCHO/2)
	{
		barra.x = x-BARRA_ANCHO/2;
	}
}

//-----------------//
// DIBUJAR SPRITES //
//-----------------//

/*
* Crea el array de bloques y establece el número de ladrillos para cada nivel
*/
void CargarNivel()
{
	int i,x,y;
	switch(NivelActual)
	{
		default:
			NLadrillos = 12;
			x = 10; y = 10;
			Bloque bloque;
			bloque.destruido = NO_DESTRUIDO;

			for (i=0; i<NLadrillos/2; i++)
			{
				
				bloque.x = x;
				bloque.y = y;

				bloques[i] = bloque;
				
				x+=40;
			}
			x = 10; y = 40;
			for (i=NLadrillos/2; i<NLadrillos; i++)
			{
				bloque.x = x;
				bloque.y = y;

				bloques[i] = bloque;
				
				x+=40;
			}
			
	
	}
	NLadrillosRestantes = NLadrillos;
}

void DibujarPelota()
{
	int int_x,int_y;
	int_x = (int) round(pelota.x);
	int_y = (int) round(pelota.y);
	
	MostrarPelota(0,int_x,int_y);
}

void DibujarBarra()
{
	int int_x;
	int_x = (int) round(barra.x);
	
	MostrarBarra(1,int_x,BARRA_Y_INICIAL-BARRA_ALTO);
}

void DibujarBloques()
{
	int i,int_x,int_y;
	Bloque bloque;
	for (i=0; i<NLadrillos; i++)
	{
		bloque = bloques[i];
		if (bloque.destruido == NO_DESTRUIDO)
		{
			int_x = (int) round(bloque.x);
			int_y = (int) round(bloque.y);

			MostrarBloque(2+i,int_x,int_y-BLOQUE_ALTO);
		}
	}

}

void OcultarPelota()
{
	int int_x,int_y;
	int_x = (int) round(pelota.x);
	int_y = (int) round(pelota.y);
	
	BorrarPelota(0,int_x,int_y);
}

void OcultarBarra()
{
	int int_x;
	int_x = (int) round(barra.x)-16;
	
	BorrarBarra(1,int_x,BARRA_Y_INICIAL);
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

			BorrarBloque(2+i,int_x,int_y-BLOQUE_ALTO);
		}
	}
}