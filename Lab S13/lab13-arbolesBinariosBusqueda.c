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
	printf("\nActividad 1:\n");
	//Creamos los dos arboles que pide el enunciado:
	//Arbol1:
	insertarNodoABB(arbolBB1,9); insertarNodoABB(arbolBB1,1); insertarNodoABB(arbolBB1,6);
	insertarNodoABB(arbolBB1,2); insertarNodoABB(arbolBB1,5); insertarNodoABB(arbolBB1,10); 
	insertarNodoABB(arbolBB1,4); insertarNodoABB(arbolBB1,8); insertarNodoABB(arbolBB1,3);
	//Arbol2:
	insertarNodoABB(arbolBB2,6); insertarNodoABB(arbolBB2,3); insertarNodoABB(arbolBB2,1);
	insertarNodoABB(arbolBB2,5); insertarNodoABB(arbolBB2,16);insertarNodoABB(arbolBB2,10);
	insertarNodoABB(arbolBB2,7); insertarNodoABB(arbolBB2,13);insertarNodoABB(arbolBB2,15);
	
	//Luego verificamos que sean arboles
	//arbolBB1
	if(verificarABB(arbolBB1)){
		printf("arbolBB1 es un Arbol Binario de Busqueda\n");
	}
	else {printf("arbolBB1 NO un Arbol Binario de Busqueda\n");}
	//arbolBB2 
	if(verificarABB(arbolBB2)){
		printf("arbolBB2 es un Arbol Binario de Busqueda\n");
	}
	else {printf("arbolBB2 NO es un Arbol Binario de Busqueda\n");} 

	//Podemos observar que como el metodo "insertarNodoABB" siempre inserta un nodo de la manera correcta
	//Es imposible crear un arbolABB "mal configurado", por lo que la verificacion retorna 1 en ambos casos. 

	//Imprimimos los arboles por consola en modo "In-orden"
	printf("arbolBB1: "); recorridoInordenABB(arbolBB1);
	printf("arbolBB2: "); recorridoInordenABB(arbolBB2);	

	//Actividad2: 
	printf("\nActividad 2:\n");
	//Eliminamos nodos con el método creado
	printf("arbolBB2 - 16: "); eliminarNodoABB(arbolBB2, 16);
	//Mostramos el arbol resultante por consola
	recorridoInordenABB(arbolBB2);

	return 0;
}