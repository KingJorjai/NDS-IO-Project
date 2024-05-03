#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos
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
	if (pelota.y <= 0)
		return ARRIBA;
	
	else if (pelota.x <= 0)
		return IZQUIERDA;
	
	else if (pelota.x + PELOTA_ANCHO >= ANCHO_PANTALLA)
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
	//int colision = 0; // Add variable declaration and initialize to 0
	int vertical,horizontal,i;
	
	for(i=0; i<NLadrillos; i++)
	{
		bloque = bloques[i];

		if (bloque.destruido == NO_DESTRUIDO)
		{
			vertical = (pelota.x+PELOTA_ANCHO > bloque.x && pelota.x < bloque.x+BLOQUE_ANCHO) // acotado horiz.
				&& (pelota.y == bloque.y+BLOQUE_ALTO || pelota.y+PELOTA_ALTO == bloque.y );
		
			horizontal = (pelota.y+PELOTA_ALTO > bloque.y && pelota.y < bloque.y+BLOQUE_ALTO) // acotado vert.
				&& (pelota.x == bloque.x+BLOQUE_ANCHO || pelota.x+PELOTA_ANCHO == bloque.x );

		if (vertical || horizontal)
		{
			bloques[i].destruido = DESTRUIDO;
			BorrarBloque(2+i,bloque.x,bloque.y);
			NLadrillosRestantes -= 1;

			if (vertical) return ABAJO;
			if (horizontal) return IZQUIERDA;
		}
		}
		
	}

	return 0; // No hay colisión
}

int PelotaTocaBarra()
{
	if ((int)(pelota.y) == BARRA_Y_INICIAL
		/*&& pelota.x+PELOTA_ANCHO>=barra.x
		&& barra.x+BARRA_ANCHO>=pelota.x*/)
	return 1;
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
		case ABAJO:
			pelota.vy = -pelota.vy;
			break;
		
		case IZQUIERDA:
		case DERECHA:
			pelota.vx = -pelota.vx;
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
	pelota.vx = 0.5;
	pelota.vy = 0.5;
	pelota.x = PELOTA_X_INICIAL;
	pelota.y = PELOTA_Y_INICIAL;
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
	if(x != barra.x && x > BARRA_ANCHO/2 && x < ANCHO_PANTALLA-BARRA_ANCHO/2)
	{
		barra.x = x;
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
	int_x = (int) round(barra.x)-16;
	
	MostrarBarra(1,int_x,BARRA_Y_INICIAL);
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

			MostrarBloque(2+i,int_x,int_y-BLOQUE_ANCHO/2);
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

			BorrarBloque(2+i,int_x,int_y);
		}
	}
}