#include <stdio.h>
#include <stdlib.h>
#include "TDAarbolBinario.h"

int main() 
{	
	//Se crea un TDAarbol, llamado "arbolBinario"
	TDAarbolBinario* arbolBinario=crearArbolBinarioVacio();
	insertarNodoAB(arbolBinario,0,9,0);
	insertarNodoAB(arbolBinario,9,1,0);
	insertarNodoAB(arbolBinario,9,5,1);
	insertarNodoAB(arbolBinario,1,6,0);
	insertarNodoAB(arbolBinario,1,2,1);
	insertarNodoAB(arbolBinario,5,10,0);
	insertarNodoAB(arbolBinario,10,4,0);
	insertarNodoAB(arbolBinario,10,8,1);
	insertarNodoAB(arbolBinario,8,3,1);
	//Ejecutamos las funciones que muestran los ordenes por consola:
	printf("In-Orden: ["); recorridoInordenAB(arbolBinario); printf("]\n");
	printf("Pre-Orden: ["); recorridoPreordenAB(arbolBinario); printf("]\n");
	printf("Post-Orden: ["); recorridoPostordenAB(arbolBinario); printf("]\n");
	//Calculamos el número de hojas con la función "numHojasAB":
	printf("Cantidad de hojas: "); numHojasAB(arbolBinario); printf("\n");
	//
	printf("Padre: %d Nodo: %d\n",buscarPadreAB(arbolBinario,2)->dato,buscarNodoAB(arbolBinario,2)->dato);
	
	return 0;
}