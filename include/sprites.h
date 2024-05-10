// Curso 2023-2024

extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;

extern void memoriaReserva();

/* Para cada uno de los 256 valores que puede tomar un Píxel le da un color en la pantalla secundaria. El valor 0 es transparente y los valores sin definir negros */
extern void EstablecerPaletaPrincipal();

/* Carga en memoria los Sprites dibujados */
extern void GuardarSpritesMemoria();

/* Esta función dibuja un rombo en la posición de pantalla x,y. A cada rombo que queramos sacar en pantalla se le debe asignar un índice distinto que puede tomara valores entre 0 y 126 */
extern void MostrarPelota(int indice, int x, int y);
extern void MostrarBloque(int indice, int x, int y);
extern void MostrarBarra(int indice, int x, int y);

/* Esta función borra de la pantalla el rombo con el índice que se le indique como parámetro */
extern void BorrarPelota(int indice, int x, int y);
extern void BorrarBloque(int indice, int x, int y);
extern void BorrarBarra(int indice, int x, int y);