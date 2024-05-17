/*---------------------------------------------------------------------------------
motor.h
---------------------------------------------------------------------------------*/
// Direcciones extra
#define ARRIBA_DERECHA 64
#define ARRIBA_IZQUIERDA 65
#define ABAJO_DERECHA 74
#define ABAJO_IZQUIERDA 75

//Elementos
extern int NLadrillos;
extern int NLadrillosRestantes;

typedef struct
{
	double velocidad;	// Velocidad de la pelota

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
} Barra;

extern Barra barra;
extern Pelota pelota;
extern Bloque bloques[32];


// Colisiones
extern int PelotaTocaSuelo();
extern int PelotaTocaPared();
extern int PelotaTocaLadrillo();
extern int PelotaTocaBarra();
extern void CalcularRebote(int direccion);


// Pelota
#define PELOTA_V_INICIAL 0.5
#define PELOTA_X_INICIAL 128
#define PELOTA_Y_INICIAL 81
#define PELOTA_ANCHO 16
#define PELOTA_ALTO 16
extern void InicializarPelota();
extern void ActualizarPelota();

// Bloque
#define DESTRUIDO 1
#define NO_DESTRUIDO 0
#define BLOQUE_ALTO 16
#define BLOQUE_ANCHO 32

// Barra
#define BARRA_X_INICIAL 96
#define BARRA_Y_INICIAL	160
#define BARRA_ANCHO 32
#define BARRA_ALTO 16
#define BARRA_VX 0.1
extern void InicializarBarra();
extern void ActualizarBarra();

// Dibujar Sprites
extern void CargarNivel();
void cargarBloques(char nivel[4][8]);

extern void DibujarPelota();
extern void DibujarBarra();
extern void DibujarBloques();

extern void OcultarPelota();
extern void OcultarBarra();
extern void OcultarBloques();