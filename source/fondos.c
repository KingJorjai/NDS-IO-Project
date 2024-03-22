
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación */

#include "fondos.h"
#include "graficos.h"
#include "FondoUno.h"
#include "FondoDos.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria */
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarFondoUno() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoUnoBitmap, /* Variable que se genera automáticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoUnoBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarFondoDos() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     FondoDosBitmap, /* Variable que se genera automáticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoDosBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}
