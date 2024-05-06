// Curso 2023-2024

/*-------------------------------------
definiciones.h
-------------------------------------*/
#include <nds.h> 		// Librería de la nds
#include <stdio.h>		// Librería de entrada/salida estándar de C
#include <stdlib.h>		// Librería estándar de C para reserva de memoria y conversiones numéricas
#include <unistd.h>		// Librería para asegurar la compatibilidad entre sistemas operativos


#define IME		(*(vuint32*)0x04000208) // Interrupt Master Enable -- Habilitar-deshabilitar todas las interrupciones
#define IE		(*(vuint32*)0x04000210) // Interrupt Enable -- Habilitar-deshabilitar las interrupciones de forma individual
#define IF		(*(vuint32*)0x04000214) // Interrupt Flag -- Registro de solicitud de interrupción

// Funciones para el tratamiento general de las interrupciones
#define HabilitarInterrupciones() IME=1 // Habilitar todas las interrupciones
#define DeshabilitarInterrrupciones() IME=0 // Deshabilitar todas las interrupciones

// Registros del teclado
#define TECLAS_DAT	(*(vu16*)0x4000130) // Registro de datos del teclado
#define TECLAS_CNT	(*(vu16*)0x4000132) // Registro de control del teclado

// Registros del temporizador Timer0
#define TIMER0_CNT   (*(vuint16*)0x04000102) // Registro de control del temporizador
#define TIMER0_DAT    (*(vuint16*)0x04000100) // Registro de datos del temporizador



// Acceso a los registros de la pantalla táctil
touchPosition PANT_DAT;

#define ANCHO_PANTALLA 256
#define ALTO_PANTALLA 192

// Nombres asignados a las teclas para facilitar la comprensión de nuestro código

#define A			0 
#define B			1
#define SELECT			2 
#define START			3
#define DERECHA			4 
#define IZQUIERDA		5
#define ARRIBA			6 
#define ABAJO			7
#define R			8 
#define L			9

// Nombres asignados a los estados
#define MENU_INICIO 0
#define MENU_SELECTOR 1
#define ESPERA 2
#define JUEGO 3
#define PAUSA_REANUDAR 4
#define PAUSA_VOLVER 5
#define PERDER 6
#define GANAR 7

// Variables globales
extern int ESTADO;
extern int NivelActual;
extern int tiempo;
extern int seg10;
extern int NivelActual;