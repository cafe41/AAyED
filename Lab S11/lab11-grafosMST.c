#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"


int main() 
{
	//Esto venía por defecto, solo cambié algunos errores de nombre al llamar la función
	TDAgrafo* grafo=leerGrafoNoDirigidoPonderado("GrafoMST.in");
		
	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo);
	printf("----------\n");

	//Acá inicia mi "intervencion"
	//Creamos un nuevo grafo, llamado "grafoK", el cuál será el grafo obtenido de nuestra función MSTKruskal
	TDAgrafo* grafoK = MSTKruskal(grafo);
    //imprimir matriz resultante
	imprimirMatrizAdyacencia(grafoK);
	
	return 0;
}