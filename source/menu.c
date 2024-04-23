#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos

// Librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"

int NivelActual;

void RestarNivel() 
{
    if (NivelActual == 1)
    {
        NivelActual =3;
    }
    else 
    {
        NivelActual = NivelActual-1;
    }
}

void SumarNIvel() 
{
    if (NivelActual == 3)
    {
        NivelActual =1;
    }
    else 
    {
        NivelActual = NivelActual+1;
    }
}
         