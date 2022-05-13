#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\gvergara\GIT\AAyED\Lab S8\TDAgrafo.h"

// Variables globales



int main(int argc, char const *argv[])
{
	TDAgrafo* grafo;

	grafo=leerGrafoNoDirigido("grafo9conexo.in");

	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo);
	printf("----------\n");

	/*TEST COLA
	TDAcola* cola = crearColaVacia(3);
	encolar(cola,1); imprimirCola(cola);
	encolar(cola,2); imprimirCola(cola);
	encolar(cola,3); imprimirCola(cola);
	desencolar(cola); imprimirCola(cola);		
	*/

	recorridoProfundidad(grafo,0);
	return 0;
}



