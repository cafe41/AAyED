#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"

int main() 
{
	//Semana 10
	
	TDAgrafo* grafo;
	//Leemos el archivo con la función que se nos entregó en FuncionesExtras.txt
	grafo=leerGrafoNoDirigidoPonderado("grafo10ponderado.in");
	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo);
	printf("----------\n");
	
	//Actividad 1:
	//Corremos la función "encontrarCamino", la cual nos mostrará un camino posible entre dos vértices
	printf("Camino : ");
	TDAlista* camino = encontrarCamino(grafo, 2, 5);
	recorrerLista(camino);
	//Cabe mencionar además, que esta función nos servirá a futuro en el algoritmo Ford-Fulkerson
	
	//Actividad 2:
	//Corremos el algoritmo "dijkstra", 
	//algoritmo que nos entregará los caminos mínimos de un vertice hacia los demás.
	Dijkstra(grafo, 1);
	//Como agregado, mi función imprime los 3 arreglos al final, 
	//así se puede comprobar por consola que el algoritmo funciona 

	return 0;
}