#include <stdio.h>
#include <stdlib.h>
#include "TDAabb.h"

int main() 
{
	nodoABB* nodo;
	TDAabb* arbolBB=crearABBVacio();
	
	insertarNodoABB(arbolBB,9);
	recorridoInordenABB(arbolBB);
	return 0;
}