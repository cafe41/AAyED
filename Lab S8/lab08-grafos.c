//Laboratorio 8
//NOMBRE: GUSTAVO VERGARA
//SECCIÓN: 0-B-2

#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"

int main() 
{
	//Estas lineas venian por defecto:
	TDAgrafo* grafo;

	grafo=leerGrafoNoDirigido("Grafito.in");

	printf("Matriz de adyacencia: \n");
	imprimirMatrizAdyacencia(grafo);
	printf("----------\n");
	//Creamos una listaEnlazada, con los adyacentes del 0 (1 y 2)
	TDAlista* listaE = obtenerAdyacentes(grafo,0);
	recorrerLista(listaE); //La imprimimos por consola
	//Comprobamos si hay camino en la lsta definida anteriormente (1 y 2)
	EsCamino(grafo,listaE);
	//Creamos una nueva lista, llamada "secuencia"
	TDAlista* secuencia = crearListaVacia();insertarInicio(secuencia,2);insertarInicio(secuencia,1);insertarInicio(secuencia,4);insertarInicio(secuencia,3); insertarInicio(secuencia,2); insertarInicio(secuencia,0);
	recorrerLista(secuencia); //La imprimimos por consola
	//Comprobamos si el contenido de secuencia es camino
	EsCamino(grafo,secuencia);
	//Comprobamos si el contenido de secuencia es ciclo
	EsCiclo(grafo,secuencia);
	eliminarFinal(secuencia); insertarNodoFinal(secuencia,3); insertarNodoFinal(secuencia,2); insertarNodoFinal(secuencia,0);
	recorrerLista(secuencia); //La imprimimos por consola
	//Comprobamos si el contenido de secuencia es ciclo nuevamente
	EsCiclo(grafo,secuencia);
	//Liberamos memoria
	free(grafo);free(secuencia);
	return 0;
}