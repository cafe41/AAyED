#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"

// Variables globales



int main(int argc, char const *argv[])
{
	TDAgrafo* grafo;

	grafo=leerGrafoNoDirigido("grafo9conexo.in");

	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo);
	printf("----------\n");

	/* Resumen:
	Llamamos al recorrido por profundidad, función que irá viendo si el grafo es conexo,
	imprimiendo los números que estén enlazados al número que se le entregue,
	agregué una linea adicional al final, que en base a que todo esté "visitado",
	imprimirá un "el grafo es conexo" o "el grafo es desconexo"                       */
	//DOM: TDAgrafo X int (vertice)
	//REC: VOID (sin embargo, hará printf por consola)
	recorridoProfundidad(grafo,0);

	printf("----------\n");

	/* Resumen:
	El recorrido por anchura es distinto en algunas cosas con respecto al recorrido por
	profundidad, sin embargo, cumple el mismo proposito, simplemente usa otro método,
	nos imprimira los vertices visitados y luego si el grafo es conexo o no           */
	//DOM: TDAgrafo X int (vertice)
	//REC: VOID (sin embargo, hará printf por consola)
	recorridoAnchura(grafo,0);
	//Liberamos la memoria asignada al grafo
	free(grafo);
	return 0;
}



