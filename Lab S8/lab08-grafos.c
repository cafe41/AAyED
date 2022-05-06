#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"

int main() 
{

	TDAgrafo* grafo;

	grafo=leerGrafoNoDirigido("Grafito.in");

	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo);
	printf("----------\n");

	TDAlista* listaE = obtenerAdyacentes(grafo,0);
	recorrerLista(listaE);
	EsCamino(grafo,listaE);
	TDAlista* secuencia = crearListaVacia();insertarInicio(secuencia,2);insertarInicio(secuencia,1);insertarInicio(secuencia,4);insertarInicio(secuencia,3); insertarInicio(secuencia,2); insertarInicio(secuencia,0);
	recorrerLista(secuencia);
	EsCamino(grafo,secuencia);
	EsCiclo(grafo,secuencia);
	insertarNodoFinal(secuencia,0);
	recorrerLista(secuencia);
	EsCiclo(grafo,secuencia);
	// int vertA = 1;
	// int vertB = 3;
	// if (adyacenciaNodos(grafo,vertA,vertB)) 
	// {
	// 	printf("Los vertices %d y %d son adyacentes\n", vertA, vertB);
	// }
	// else 
	// {
	//  	printf("Los vertices %d y %d no son adyacentes\n", vertA, vertB);
	// }	

	return 0;
}



