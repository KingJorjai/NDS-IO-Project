/*-------------------------------------------------------------------------------------------------
Código desarrollado basado en el ejemplo "Simple sprite demo" de dovoto y en otro de Jaeden Amero.
---------------------------------------------------------------------------------------------------*/

//Includes
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		
#include "sprites.h"
#include "definiciones.h"

//----------------------------------------------DECLARACIONES DE LOS SPRITES--------------------------------------------
u16* gfxPelota; //Declaracion de la pelota
u16* gfxBloque; //Declaracion del bloque
u16* gfxBarra;  // Declaracion de la barra


//Reservar memoria para cada sprite que se quiera mostrar en pantalla
void memoriaReserva(){
	/* Por cada sprite que se quiera incluir en la pantalla principal hay que hacer algo equivalente a lo que sigue */
	gfxPelota= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxBloque=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	gfxBarra=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
}

/* A cada uno de los 256 valores que puede tomar un píxel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES 
*/

//-------------------------------------------ESTABLECER PALETAS DE COLORES-----------------------------------------------
//Establecemos la paleta de colores para la pelota
void EstablecerPaletaPelota(){
	SPRITE_PALETTE[0] = RGB15(30,30,30);
	SPRITE_PALETTE[1] = RGB15(22,22,22);
	SPRITE_PALETTE[2] = RGB15(1,1,1);
	SPRITE_PALETTE[3] = RGB15(0,0,0);
	SPRITE_PALETTE[4] = RGB15(0,0,0);
	SPRITE_PALETTE[5] = RGB15(0,0,0);
	SPRITE_PALETTE[6] = RGB15(31,31,31);
	SPRITE_PALETTE[7] = RGB15(3,3,3);
	SPRITE_PALETTE[8] = RGB15(0,0,0);
	SPRITE_PALETTE[9] = RGB15(30,30,30);
	SPRITE_PALETTE[10] = RGB15(18,18,18);
	SPRITE_PALETTE[11] = RGB15(0,0,0);
	SPRITE_PALETTE[12] = RGB15(2,2,2);
	SPRITE_PALETTE[13] = RGB15(0,0,0);
	SPRITE_PALETTE[14] = RGB15(0,0,0);
	SPRITE_PALETTE[15] = RGB15(3,3,3);
	SPRITE_PALETTE[16] = RGB15(19,19,19);
	SPRITE_PALETTE[17] = RGB15(0,0,0);
	SPRITE_PALETTE[18] = RGB15(19,19,19);
	SPRITE_PALETTE[19] = RGB15(1,1,1);
	SPRITE_PALETTE[20] = RGB15(30,30,30);
	SPRITE_PALETTE[21] = RGB15(30,30,30);
	SPRITE_PALETTE[22] = RGB15(16,16,16);
	SPRITE_PALETTE[23] = RGB15(16,16,16);
	SPRITE_PALETTE[24] = RGB15(15,15,15);
	SPRITE_PALETTE[25] = RGB15(30,30,30);
	SPRITE_PALETTE[26] = RGB15(11,11,11);
	SPRITE_PALETTE[27] = RGB15(16,16,16);
	SPRITE_PALETTE[28] = RGB15(13,13,13);
	SPRITE_PALETTE[29] = RGB15(10,10,10);
	SPRITE_PALETTE[30] = RGB15(29,29,29);
}

//Establecemos la paleta de colores para los bloques, 
void EstablecerPaletaBloque(){
	SPRITE_PALETTE[0] = RGB15(28,3,4);
	SPRITE_PALETTE[1] = RGB15(28,3,4);
}
//si vamos a meter diferentes colores para cada bloque creo que deberiamos usar una paleta para cada bloque o cambiar la paleta

//Establecemos la paleta de colores para la barra 
void EstablecerPaletaBarra(){
	SPRITE_PALETTE[0] = RGB15(19,8,19);
	SPRITE_PALETTE[1] = RGB15(19,8,20);
	SPRITE_PALETTE[2] = RGB15(18,10,18);
	SPRITE_PALETTE[3] = RGB15(31,29,31);
	SPRITE_PALETTE[4] = RGB15(31,31,31);
	SPRITE_PALETTE[5] = RGB15(31,31,30);
	SPRITE_PALETTE[6] = RGB15(31,30,30);
	SPRITE_PALETTE[7] = RGB15(31,30,31);
	SPRITE_PALETTE[8] = RGB15(30,31,31);
	SPRITE_PALETTE[9] = RGB15(30,31,31);
	SPRITE_PALETTE[10] = RGB15(30,31,30);
	SPRITE_PALETTE[11] = RGB15(31,31,30);
}

/* Definición de un sprite de 16x16 píxeles para dibujar un rombo */
/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 píxeles. Los primeros 64 (8x8) píxeles que indicamos
aparecerán en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
últimos en el cuadrante inferior derecho */

//-----------------------------------DEFINICIONES DE LOS DIBUJOS DE LOS SPRITES------------------------------------------
//El array que contiene la forma y colores de la pelota
u8 pelota[256] = 
{
	0,1,2,3,4,4,4,5,6,7,5,4,4,8,4,4,9,4,4,4,3,4,8,4,10,11,11,4,4,3,3,4,12,4,4,4,13,5,4,3,4,3,4,13,3,4,14,4,4,13,4,4,4,5,4,8,4,4,4,3,5,4,4,4,4,5,4,15,16,9,6,6,4,5,4,4,17,9,6,6,8,4,5,3,8,18,6,0,4,4,8,5,4,19,20,6,4,8,11,4,4,11,21,6,4,4,4,11,8,4,6,9,8,4,8,4,4,4,22,6,4,4,3,4,3,3,17,6,4,3,5,4,5,4,4,4,17,8,4,3,4,4,4,3,23,4,11,3,4,4,4,4,6,24,5,4,4,3,4,4,6,6,23,4,3,4,3,5,21,9,9,25,26,4,5,4,6,9,6,6,6,27,4,5,0,6,0,6,21,6,6,9,3,4,4,4,4,8,4,6,4,8,5,5,4,4,3,9,5,3,4,4,5,3,4,6,3,4,8,3,4,4,3,6,4,4,4,8,3,3,4,6,4,14,4,4,11,4,28,6,8,4,8,4,29,30,6,0,0,6,9,6,0,6,6,6,
};

//El array que contiene la forma y colores de los bloques
u8 bloque[1024] = 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	
};

//El array que contiene la forma y colores de la barra
u8 barra[1024] = 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,5,6,5,6,5,6,5,7,4,7,4,7,4,7,4,4,8,4,8,4,8,4,8,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,5,6,5,6,5,6,5,7,4,7,4,7,4,7,4,4,8,4,8,4,8,4,8,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,5,6,5,6,5,6,5,7,4,7,4,7,4,7,4,4,8,4,8,4,8,4,8,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,6,5,6,5,6,5,6,5,7,4,7,4,7,4,7,4,4,8,4,8,4,8,4,8,8,9,8,9,8,9,8,9,8,9,8,9,8,9,8,9,5,10,5,10,5,10,5,10,5,11,5,11,5,11,5,11,7,5,7,5,7,5,7,5,7,7,7,7,7,7,7,7,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,8,9,8,9,8,9,8,9,8,9,8,9,8,9,8,9,5,10,5,10,5,10,5,10,5,11,5,11,5,11,5,11,7,5,7,5,7,5,7,5,7,7,7,7,7,7,7,7,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,8,9,8,9,8,9,8,9,8,9,8,9,8,9,8,9,5,10,5,10,5,10,5,10,5,11,5,11,5,11,5,11,7,5,7,5,7,5,7,5,7,7,7,7,7,7,7,7,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,8,9,8,9,8,9,8,9,8,9,8,9,8,9,8,9,5,10,5,10,5,10,5,10,5,11,5,11,5,11,5,11,7,5,7,5,7,5,7,5,7,7,7,7,7,7,7,7,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,	
};

/* Carga en memoria cada uno de los sprites que hemos dibujado */

//----------------------------------------------CARGAR EN MEMORIA LOS SPRITES---------------------------------------------
void GuardarSpritesMemoria(){ 
	int i;
	//sprite de la pelota, 16x16
	for(i = 0; i < 16 * 16 / 2; i++) {	
		gfxPelota[i] = pelota[i*2] | (pelota[(i*2)+1]<<8);				
	}

	//sprite de los bloques, 32x32
	for(i = 0; i < 32 * 32 / 2; i++) {	
		gfxBloque[i] = bloque[i*2] | (bloque[(i*2)+1]<<8);				
	}

	//sprite de la barra, 32x32
	for(i = 0; i < 32 * 32 / 2; i++) {	
		gfxBarra[i] = barra[i*2] | (barra[(i*2)+1]<<8);				
	}
}

/* Esta función dibuja un rombo en la posición x,y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un índice distinto, un valor entre 0 y 126 */

//----------------------------------------------MOSTRAR Y BORRAR LOS SPRITES----------------------------------------------
//Muestra la pelota
void MostrarPelota(int indice, int x, int y){ 
	oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxPelota,// +16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
	); 

	oamUpdate(&oamMain);  
}

//Borra la pelota
void BorrarPelota(int indice, int x, int y){
	oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxPelota,// +16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
	); 

	oamUpdate(&oamMain); 
}

//Muestra el bloque
void MostrarBloque(int indice, int x, int y){ 
	oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxBloque,// +16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
	); 

	oamUpdate(&oamMain);  
}

//Borra el bloque
void BorrarBloque(int indice, int x, int y){
	oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxBloque,// +16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	oamUpdate(&oamMain); 
}

//Muestra la barra
void MostrarBarra(int indice, int x, int y){ 
	oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxBarra,// +16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
	); 
		
	oamUpdate(&oamMain);  
}

//Borra la barra
void BorrarBarra(int indice, int x, int y){
	oamSet(&oamMain, // main graphics engine context
		indice,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxBarra,// +16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
	); 

	oamUpdate(&oamMain);
}