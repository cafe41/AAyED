#include <stdio.h>
#include <stdlib.h>
#include "TDAaAVL.h"

int main() 
{
	TDAarbolAVL* arbolAVL=crearAVLVacio();
	insertarNodoAVL(arbolAVL,20);
	recorridoInordenAVL(arbolAVL);
	insertarNodoAVL(arbolAVL,5);
	recorridoInordenAVL(arbolAVL);
	insertarNodoAVL(arbolAVL,10);
	recorridoInordenAVL(arbolAVL);
	insertarNodoAVL(arbolAVL,15);
	recorridoInordenAVL(arbolAVL);
	insertarNodoAVL(arbolAVL,12);
	recorridoInordenAVL(arbolAVL);
	return 0;
}


