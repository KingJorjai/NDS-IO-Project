/*---------------------------------------------------------------------------------
motor.h
---------------------------------------------------------------------------------*/

//Elementos
extern struct Pelota pelota;

extern struct Bloque bloques[50];
extern int numBloques;

extern Barra barra;

// Colisiones
extern int PelotaTocaSuelo();
extern int PelotaTocaPared();
extern int PelotaTocaLadrillo();
extern void CalcularRebote();


// Pelota
#define VPELOTA_BASE 1		// Pendiente de revisar
extern void InicializarPelota();
extern double[2] PararPelota();
extern void ReanudarPelota(double[2] velocidad);
extern void ActualizarPelota();

// Bloque
#define DESTRUIDO 1
#define NO_DESTRUIDO 0

// Barra
#define BARRA_X_INICIAL 96	// Pendiente de revisar
#define BARRA_Y_INICIAL	160	// Pendiente de revisar
void InicializarBarra();