/*-------------------------------------
perifericos.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"


int tecla; // Variable para guardar la tecla pulsada; valorar si es necesaria



int TeclaDetectada() 
{
	// Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int TeclaPulsada() 
{

	// Devuelve el código de la tecla pulsada utilizando para ello las constantes definidas en 
	// definiciones.h:  A=0;B=1;SELECT=2;START=3;IZQUIERDA=4;DERECHA=5;
	// ARRIBA=6;ABAJO=7;R=8;L=9;
	
	// Comprobar A
	if ( (~TECLAS_DAT & 0x0001)!=0) return A;
	if ( (~TECLAS_DAT & 0x0002)!=0) return B;
	if ( (~TECLAS_DAT & 0x0004)!=0) return SELECT;
	if ( (~TECLAS_DAT & 0x0008)!=0) return START;
	if ( (~TECLAS_DAT & 0x0010)!=0) return IZQUIERDA;
	if ( (~TECLAS_DAT & 0x0020)!=0) return DERECHA;
	if ( (~TECLAS_DAT & 0x0040)!=0) return ARRIBA;
	if ( (~TECLAS_DAT & 0x0080)!=0) return ABAJO;
	if ( (~TECLAS_DAT & 0x0100)!=0) return R;
	if ( (~TECLAS_DAT & 0x0200)!=0) return L;
	
	// kienkojonesapulsaounatekla
	return -1;
}

void ConfigurarTeclado(int Conf_Tec)
{
	TECLAS_CNT = TECLAS_CNT | Conf_Tec;
	// Configuración del teclado. Modificar su registro de control en base a los bits
        // activados en el parametro Conf_Tec	
}

void ConfigurarTemporizador(int Latch, int Conf_Tempo)
{
	
	// Configuración del temporizador. El latch es el valor del registro de datos del temporizador
        // Activar los bits del registro de control necesarios en base a los bits activados en el parámetro Conf_Tempo

}

void HabilitarIntTeclado()
{
	// Habilitar las interrupciones del teclado
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 
	IME=0;
        // ESCRIBID AQUÍ VUESTRO CÓDIGO
		TECLAS_CNT |= 0x21FF;
		//Las teclas activadas son: 010 0001 1111 1111 = 21FF (del 1 al 9 y 14)
	IME=1;
}

void InhibirIntTeclado()
{

	// Deshabilitar las interrupciones del teclado
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 

	IME=0;
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	TECLAS_CNT &= 0x5E00;
	IME=1;
}  

void HabilitarIntTempo()
{


	// Habilitar las interrupciones del temporizador (timer0)
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 
	IME=0;
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	
	IME=1;
}

void InhibirIntTempo()
{

	// Deshabilitar las interrupciones del temporizador (timer0)
	// Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	// y después volver a habilitar las interrupciones de forma general 
	IME=0;
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	
	IME=1;

}

void PonerEnMarchaTempo()
{
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	TIMER0_CNT |= 0x0040;
}

void PararTempo()
{
	// ESCRIBID AQUÍ VUESTRO CÓDIGO
	TIMER0_CNT &= 0x7FBF;
}
