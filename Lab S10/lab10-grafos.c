#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"

int main() 
{
	//base
	
	TDAgrafo* grafo;
	grafo=leerGrafoNoDirigidoPonderado("grafo10ponderado.in");
	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo);
	printf("----------\n");
	
	printf("Camino : \n");
	//TDAlista* encontrarCamino(TDAgrafo* grafo, int inicio, int fin);

	
	//Semana 10 Actividad 
	//Dijkstra(grafo, 2); 

	return 0;
}