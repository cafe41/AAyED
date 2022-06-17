#include <stdio.h>
#include <stdlib.h>
#include "TDAabb.h"

int main() 
{
	nodoABB* nodo;
	TDAabb* arbolBB1=crearABBVacio();
	TDAabb* arbolBB2=crearABBVacio();
	TDAabb* arbolTest=crearABBVacio();
	//Actividad 1:
	//Arbol1:
	insertarNodoABB(arbolBB1,9); insertarNodoABB(arbolBB1,1); insertarNodoABB(arbolBB1,5); insertarNodoABB(arbolBB1,6); 
	insertarNodoABB(arbolBB1,2); insertarNodoABB(arbolBB1,10); insertarNodoABB(arbolBB1,4); insertarNodoABB(arbolBB1,8);
	insertarNodoABB(arbolBB1,3);
	//Arbol2:
	insertarNodoABB(arbolBB2,6); insertarNodoABB(arbolBB2,3); insertarNodoABB(arbolBB2,16); insertarNodoABB(arbolBB2,1); 
	insertarNodoABB(arbolBB2,5); insertarNodoABB(arbolBB2,10); insertarNodoABB(arbolBB2,7); insertarNodoABB(arbolBB2,13);
	insertarNodoABB(arbolBB2,15);
	//Test:
	insertarNodoABB(arbolTest,10); insertarNodoABB(arbolTest,5); insertarNodoABB(arbolTest,78); insertarNodoABB(arbolTest,80); insertarNodoABB(arbolTest,35); 

	printf("arbolBB1 = %d\n", verificarABB(arbolBB1));
	printf("arbolBB2 = %d\n", verificarABB(arbolBB2));
	printf("arbolTest = %d\n", verificarABB(arbolTest));

	recorridoInordenABB(arbolBB1);
	recorridoInordenABB(arbolBB2);	
	recorridoInordenABB(arbolTest);

	eliminarNodoABB(arbolBB1, 9); eliminarNodoABB(arbolBB1, 1); eliminarNodoABB(arbolBB1, 5); eliminarNodoABB(arbolBB1, 6); eliminarNodoABB(arbolBB1, 2);
	eliminarNodoABB(arbolBB1, 10); eliminarNodoABB(arbolBB1, 4); 

	recorridoInordenABB(arbolBB1);

	recorridoInordenABB(arbolTest);

	return 0;
}