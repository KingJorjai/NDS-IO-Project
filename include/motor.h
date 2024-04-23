/*---------------------------------------------------------------------------------
motor.h
---------------------------------------------------------------------------------*/

//Elementos
extern int NLadrillos;

typedef struct
{
	double vx;	// Velocidad horizontal
	double vy;	// Velocidad vertical
	
	double x;		// Posición en x
	double y;		// Posición en y
} Pelota;

typedef struct
{
	int destruido;	// DESTRUIDO , NO_DESTRUIDO
	
	double x;		// Posición en x
	double y;		// Posición en y
} Bloque;

typedef struct
{
	double x;		// Posición en x
	double y;		// Posición en y
} Barra;

extern Barra barra;
extern Pelota pelota;
extern Bloque bloques[50];


// Colisiones
extern int PelotaTocaSuelo();
extern int PelotaTocaPared();
extern int PelotaTocaLadrillo();
extern void CalcularRebote(int direccion);


// Pelota
#define VPELOTA_BASE 1		// Pendiente de revisar
extern void InicializarPelota();
extern void ActualizarPelota();

// Bloque
#define DESTRUIDO 1
#define NO_DESTRUIDO 0

// Barra
#define BARRA_X_INICIAL 96	// Pendiente de revisar
#define BARRA_Y_INICIAL	160	// Pendiente de revisar
void InicializarBarra();

// Dibujar Sprites
extern void Cargarnivel();

extern void DibujarPelota();
extern void DibujarBarra();

extern void OcultarPelota();
extern void OcultarBarra();
extern void OcultarBloques();