
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación */

#include "fondos.h"
#include "graficos.h"
#include "FondoUno.h"
#include "FondoDos.h"
#include "Puerta.h"
#include "PuertaAbierta.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria */
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

//Visualiza la pantalla que sale al inicio, la imagen se llama MenuInicio
void visualizarMenuInicio() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
        MenuInicioBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        MenuInicioBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

//Visualiza la pantalla que sale mientras vas seleccionando el nivel, la imagen se llama Nivel
void visualizarNivel() {
		
	dmaCopyHalfWords(DMA_CHANNEL,
        NivelBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        NivelBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

//Visualiza la pantalla que sale de fondo mientras juegas, la imagen se llama Juego
void visualizarJuego() {
		
	dmaCopyHalfWords(DMA_CHANNEL,
        JuegoBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        JuegoBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

//Visualiza la pantalla que sale al entrar al menu de pausa, la imagen se llama Pausa
void visualizarPausa() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
		PausaBitmap, /* Variable que se genera automáticamente */
		(uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
		PausaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

//Visualiza la pantalla que sale al ganar, la imagen se llama Ganar
void visualizarGanar() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
			 GanarBitmap, /* Variable que se genera automáticamente */
			 (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
			 GanarBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

//Visualiza la pantalla que sale al perder, la imagen se llama Perder
void visualizarPerder() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
			 PerderBitmap, /* Variable que se genera automáticamente */
			 (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
			 PerderBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}