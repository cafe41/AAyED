#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"


int main() 
{
	//Esto venía por defecto, solo cambié algunos errores de nombre al llamar la función
	TDAgrafo* grafo=leerGrafoNoDirigidoPonderado("GrafoMST.in");
		
	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo); printf("----------\n");
	//Acá inicia mi "intervencion"
	//Primero, calcularemos el peso del grafo base
	int pesoBase = pesoMST(grafo);
	printf("El valor del peso MST del grafo base es: %d\n",pesoBase); printf("----------\n");
	//Creamos un nuevo grafo, llamado "grafoK", el cuál será el grafo obtenido de nuestra función MSTKruskal
	TDAgrafo* grafoK = MSTKruskal(grafo);
    //imprimir matriz resultante
	printf("Matriz de Kruskal: \n");
	imprimirMatrizAdyacencia(grafoK); printf("----------\n");
	//Calculamos el pesoMST (sumatoria del peso de los vertices)
	int pesoKruskal = pesoMST(grafoK);
	printf("El valor del peso MST del grafo con Kruskal es: %d\n",pesoKruskal); printf("----------\n");
	return 0;
}