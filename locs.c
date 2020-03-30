// Reveni (c) 2020 Baltasar MIT License <baltasarq@gmail.com>

/* Rooms */

#include "locs.h"

#include <string.h>


Loc locs[NumLocs];

void init_locs()
{
	int i = 0;

	// Init exits for all locs
    memset( locs, NumLocs, sizeof( Loc ) * NumLocs );

    // Mar
    locs[0].desc = "Buceando en el mar. Disfrutas de las paredes de roca, "
                   "corales y todo tipo de fauna a tu alrededor. La "
				   "temperatura es baja, "
                   "aunque agradable, y el movimiento del mar "
				   "reconfortantemente atenuado.";

	// Amarre D0
    locs[1].desc = "En este punto, el muelle hace una curva de norte a este. "
					"En el suelo, aparece pintado D-0 en grandes caracteres "
					"amarillos.";
	locs[1].exits[ ExitNorth ] = 4;
	locs[1].exits[ ExitEast ] = 2;

	// Cruce de amarres
    locs[2].desc = "Un gran hangar para embarcaciones se extiende al norte, "
					"este y oeste. El muelle de cemento permite acceder al "
					"agua, continuando en todas direcciones excepto el sur. ";
	locs[2].exits[ ExitNorth ] = 5;
	locs[2].exits[ ExitEast ] = 3;
	locs[2].exits[ ExitWest ] = 1;

	// Amarre D1: Submarino abandonado
	locs[3].desc = "El muelle hace una curva de norte a oeste. En el suelo "
				   "aparece trazado en grandes caracteres amarillos D-1. "
				   "En este hay un barco amarrado... es un submarino. Tiene "
				   "pinta de llevar abandonado mucho tiempo, y es que puedes "
				   "reconocerlo por las fotos y films: se trata de un submarino "
				   "de la Segunda Guerra Mundial.";
	locs[3].exits[ ExitNorth ] = 6;
	locs[3].exits[ ExitWest ] = 2;
	locs[3].exits[ ExitEast ] = 7;

	// Amarre D2
	locs[4].desc = "El muelle hace una curva de sur a este. En el suelo "
				   "aparece trazado en grandes caracteres amarillos D-2.";
	locs[4].exits[ ExitSouth ] = 1;
	locs[4].exits[ ExitEast ] = 5;

	// Amarre D3
	locs[5].desc = "El muelle permite caminar de este a oeste, y al sur. "
				   "Aparece trazado en grandes caracteres amarillos D-3. Una "
				   "escalerilla asciende en la oscuridad. "
                   "Notas que a una de las inactivas luces del techo se le ha "
                   "roto la pantalla, y hay cristales esparcidos por el suelo.";
	locs[5].exits[ ExitSouth ] = 2;
	locs[5].exits[ ExitEast ] = 6;
	locs[5].exits[ ExitWest ] = 4;
	locs[5].exits[ ExitUp ] = 14;

	// Amarre D4
	locs[6].desc = "El muelle traza una curva de oeste a sur. "
				   "Aparece trazado en grandes caracteres amarillos D-4.";
	locs[6].exits[ ExitSouth ] = 3;
	locs[6].exits[ ExitWest ] = 5;

	// Submarino
	locs[7].desc = "No sabes el motivo que explica que esta "
					"reliquia se encuentre en este lugar. Todas las escotillas "
					"se encuentran cerradas, casi soldadas. Excepto una. "
                    "Solo puedes volver al oeste.";
	locs[7].exits[ ExitWest ] = 3;

	// Planta superior
	locs[8].desc = "Un largo pasillo se interna en el complejo hacia ambos "
					"lados, este y oeste. Al norte, y al sur, "
					"dos puertas llevan a otras tantas estancias.";
	locs[8].exits[ ExitNorth ] = 9;
	locs[8].exits[ ExitSouth ] = 16;
	locs[8].exits[ ExitEast ] = 20;
	locs[8].exits[ ExitWest ] = 22;

	// Sala de maquinaria
	locs[9].desc = "Una gran sala llena de motores, palancas y engranajes "
					"oxidados, al menos a simple vista. Al sur, una puerta "
					"permite abandonar el lugar.";
	locs[9].exits[ ExitSouth ] = 8;

	// Elevador
	locs[10].desc = "El elevador es una simple caja de enrejado de metal, "
					"con un solo pulsador.";
	locs[10].exits[ ExitSouth ] = 20;

	// Pasillo oeste
	locs[11].desc = "El pasillo avanza de norte a sur. "
                    "Al este hay una puerta.";
    locs[11].exits[ ExitNorth ] = 22;
	locs[11].exits[ ExitEast ] = 18;
	locs[11].exits[ ExitSouth ] = 12;

    // Pasillo sur
	locs[12].desc = "El pasillo comunica los laterales del "
					"complejo. Arranca al norte para doblar hacia el este. Al "
					"sur hay una puerta.";
	locs[12].exits[ ExitNorth ] = 11;
    locs[12].exits[ ExitSouth ] = 14;
	locs[12].exits[ ExitEast ] = 21;

    // Pasillo este
	locs[13].desc = "El pasillo comunica el frente y la trasera del "
					"complejo. Arranca al oeste para doblar hacia el sur. ";
	locs[13].exits[ ExitSouth ] = 23;
    locs[13].exits[ ExitWest ] = 20;

    // Caja escalera
	locs[14].desc = "Una escalerilla parte hacia abajo, formando en este lugar "
                    "un reducido cuarto. Al norte hay un pasillo.";
	locs[14].exits[ ExitNorth ] = 12;
    locs[14].exits[ ExitDown ] = 5;

    // Control
	locs[15].desc = "La sala de control tiene una gran ventana "
                    "desde la que se puede apreciar el conjunto de los muelles. "
                    "Varios instrumentos se alinean bajo el ventanal, si bien "
                    "no eres capaz de deducir su objeto.";
	locs[15].exits[ ExitNorth ] = 21;

    // Despacho del almirante Underwood.
	locs[16].desc = "Un gran despacho que parece pertenecer, por lo que pone la mesa, "
                    "a un tal almirante Underwood. Si bien no se "
                    "puede decir que haya mucho lujo, los objetos de decorado "
                    "son adecuados. De entre ellos, una bandera estadounidense "
                    "destaca ocupando una de las paredes laterales. Un archivador, "
                    "una silla acolchada y un perchero completan el conjunto.";
	locs[16].exits[ ExitNorth ] = 8;

    // Despacho del secretario
    locs[17].desc = "El despacho ha pertenecido al secretario de la base "
                    "submarina. El lujo luce por su ausencia en un lugar "
                    "que destaca, si acaso, por su funcionalidad. Poco se "
                    "puede comentar, aparte de una mesa, archivador, perchero, "
                    "y silla.";
	locs[17].exits[ ExitNorth ] = 20;

    // Sala de seguridad
    locs[18].desc = "La sala guarda pocas cosas, entre todas ellas, una caja "
                    "de madera en su centro. Hay algunas baldas, pero no parece que "
                    "nada destaque por su utilidad.";
	locs[18].exits[ ExitWest ] = 11;

    // Sala de archivos
    locs[19].desc = "La sala de archivos guarda montones de polvorientos "
                    "papeles, totalmente amarillentos por el paso del tiempo. "
                    "Hay muchas baldas, soportando con dificultad el peso de "
                    "muchos legajos.";
	locs[19].exits[ ExitEast ] = 23;

    // Pasillo este
    locs[20].desc = "El pasillo posterior une la parte trasera de la base, de este, "
                    "a oeste. Un ascensor se encuentra al norte. Otra puerta lleva "
                    "al sur.";
    locs[20].exits[ ExitNorth ] = 10;
    locs[20].exits[ ExitSouth ] = 17;
    locs[20].exits[ ExitEast ] = 13;
    locs[20].exits[ ExitWest ] = 8;

    // Pasillo frontal
    locs[21].desc = "El pasillo frontal une la parte anterior de la base, de oeste, "
                    "a norte. Una puerta permite acceder a una sala al sur.";
    locs[21].exits[ ExitNorth ] = 23;
    locs[21].exits[ ExitSouth ] = 15;
    locs[21].exits[ ExitWest ] = 12;

    // Semi pasillo oeste
    locs[22].desc = "El pasillo dobla de sur a este. ";
    locs[22].exits[ ExitEast ] = 8;
    locs[22].exits[ ExitSouth ] = 11;

    // Semi pasillo este
    locs[23].desc = "El pasillo avanza de norte a sur. "
                    "Una puerta lleva al oeste.";
    locs[23].exits[ ExitNorth ] = 13;
    locs[23].exits[ ExitSouth ] = 21;
    locs[23].exits[ ExitWest ] = 19;
}
