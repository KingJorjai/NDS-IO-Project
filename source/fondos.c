
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación */

#include "fondos.h"
#include "graficos.h"
#include "MenuInicio.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include "JuegoFondo.h"
#include "PausaReanudar.h"
#include "PausaVolver.h"
#include "Ganar.h"
#include "Perder.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria */
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarMenuInicio() {
	dmaCopyHalfWords(DMA_CHANNEL,
        MenuInicioBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        MenuInicioBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

int NivelActual;
void visualizarNivel() {
	if (NivelActual == 1) {
	dmaCopyHalfWords(DMA_CHANNEL,
        Nivel1Bitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        Nivel1BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
    }

    if (NivelActual == 2) {
	dmaCopyHalfWords(DMA_CHANNEL,
        Nivel2Bitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        Nivel2BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
    }

    if (NivelActual == 3) {
	dmaCopyHalfWords(DMA_CHANNEL,
        Nivel3Bitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        Nivel3BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
    }
}

void visualizarJuegoFondo() {
	dmaCopyHalfWords(DMA_CHANNEL,
        JuegoFondoBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        JuegoFondoBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarPausaReanudar() {
	dmaCopyHalfWords(DMA_CHANNEL,
        PausaReanudarBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        PausaReanudarBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarPausaVolver() {
	dmaCopyHalfWords(DMA_CHANNEL,
        PausaVolverBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        PausaVolverBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarGanar() {
	dmaCopyHalfWords(DMA_CHANNEL,
        GanarBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        GanarBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarPerder() {
	dmaCopyHalfWords(DMA_CHANNEL,
        PerderBitmap, /* Variable que se genera automáticamente */
        (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
        PerderBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}