#include <stdio.h>
#include <stdlib.h>
#include "TDAarbolBinario.h"

int main() 
{	
	//Se crea un TDAarbol, llamado "arbolBinario" y le agregamos nodos.
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
	//Eliminamos los nodos 4, 5 y 9
	//Primero el 4:
	eliminarNodoAB(arbolBinario,4);
	printf("In-Orden luego de eliminar 4: ["); recorridoInordenAB(arbolBinario); printf("]\n");
	//Luego el 5: 
	eliminarNodoAB(arbolBinario,5);
	printf("In-Orden luego de eliminar 5: ["); recorridoInordenAB(arbolBinario); printf("]\n");
	//Luego el 9:
	eliminarNodoAB(arbolBinario,9);
	printf("In-Orden luego de eliminar 9: ["); recorridoInordenAB(arbolBinario); printf("]\n");
	//Fin del programa.
	return 0;
}