	//Laboratorio 8 y 9
	//NOMBRE: GUSTAVO VERGARA
	//SECCIÓN: 0-B-2
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "C:\Users\gvergara\GIT\AAyED\Lab S9\TDAlista.h"
	#include "C:\Users\gvergara\GIT\AAyED\Lab S9\TDApila.h"
	#include "C:\Users\gvergara\GIT\AAyED\Lab S9\TDAcola.h"

	/*------------- estructura de datos -------------*/

	typedef struct matrizGrafo 
	{
		int cvertices;
		int** adyacencias;
	}TDAgrafo;


	/*----------------- operaciones -----------------*/

	TDAgrafo* crearGrafoVacio(int vertices) 
	{
		TDAgrafo* grafo = (TDAgrafo*)malloc(sizeof(TDAgrafo));
		grafo->cvertices = vertices;
		grafo->adyacencias = (int**)malloc(vertices * sizeof(int*));
		int i,j;
		for (i = 0; i < vertices; i++) 
		{
			grafo->adyacencias[i] = (int*)malloc(vertices * sizeof(int));
			//Inicializa en cero
			for(j=0;j<vertices;j++){
				grafo->adyacencias[i][j] = 0;
			}	
		}
		return grafo;
	}

	void imprimirMatrizAdyacencia(TDAgrafo* grafo) {
		int i, j;
		
		for (i = 0; i < grafo->cvertices; i++) 
		{
			printf("%d | ", i);
			for (j = 0; j < grafo->cvertices; j++) 
			{
				printf("%d ", grafo->adyacencias[i][j]);
			}
			printf("\n");
		}
	}

	int adyacenciaNodos(TDAgrafo * grafo, int vertA, int vertB) 
	{
		if (grafo->adyacencias[vertA - 1][vertB - 1] == 1) 
		{
			return 1;
		}
		return 0;
	}


	//NoDirigido NoPonderado
	TDAgrafo* leerGrafoNoDirigido(char *nombreArchivo){
		FILE*pf;		   //para abrir archivo
		pf = fopen(nombreArchivo,"r");
		int n_vertices, m_aristas;
		int i,j,k;
		if (pf ==NULL){
			printf("Error de archivo\n");
			return NULL;
		}else{
			//Cantidad de nodos y aristas
			fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
			TDAgrafo *G=crearGrafoVacio(n_vertices);	
			//dependiendo de las lineas de archivo, 
			// 1 para grafo no dirigido no ponderado
			for(k=0;k<m_aristas;k++){
				fscanf(pf,"%d %d",&i, &j);
				G->adyacencias[i-1][j-1] = 1;
				G->adyacencias[j-1][i-1] = 1;
			}
			fclose(pf);
			return  G;
		}
	}

	//Actividad 1 - Lab 8
	//obtenerAdyacentes, funcion que obtiene los valores adyacentes del nodo actual
	//DOM: TDAgrafo X vertice (int)
	//REC: listaEnlazada
	TDAlista* obtenerAdyacentes(TDAgrafo* grafo, int vertice){
		int v = vertice;
		TDAlista* lista = crearListaVacia();
		for(size_t i = 0; i < grafo->cvertices; i++){
			//retorna lista enlazada con adyacentes
			if (grafo->adyacencias[v][i] == 1) {
				insertarInicio(lista,i);
			}
		}
		return lista;
	}
	//Actividad 2 - Lab 8
	//esCamino, entrega 1 (true) si hay camino entre toda la secuencia entregada (lista enlazada), sino 0 (false)
	//DOM: grafo X listaEnlazada
	//REC: int (bool)
	int EsCamino( TDAgrafo* grafo, TDAlista* secuencia ){ //asumo que secuencia son 2 nodos entre los que debería haber camino [1]-[4], por ejemplo
		nodo* auxiliar = secuencia->inicio;
		while(auxiliar->siguiente != NULL){
			if (adyacenciaNodos(grafo,auxiliar->dato+1,auxiliar->siguiente->dato+1	) == 0){
				printf("%d y %d no son camino.\n",auxiliar->dato,auxiliar->siguiente->dato);
				return 0; // 0 = false
			}
			printf("%d y %d son camino, ",auxiliar->dato,auxiliar->siguiente->dato);
			auxiliar = auxiliar->siguiente;
		}
		printf("\n");
		return 1; // 1 = true
	}

	//Actividad 3 - Lab 8
	//esCiclo, función que entrega un 1 (true), si se genera un ciclo dentro de la secuencia entregada,
	//un ciclo se genera cuando a través de más de 3 caminos, vuelve a aparecer el valor inicial de la secuencia.
	//DOM: grafo X listaEnlazada
	//REC: int (bool)
	int EsCiclo( TDAgrafo* grafo, TDAlista* secuencia){ //La secuencia debería ser de largo mayor a 2
		nodo* auxiliar = secuencia->inicio; int i = 0;
		while(auxiliar->siguiente != NULL){
			if (adyacenciaNodos(grafo,auxiliar->dato+1,auxiliar->siguiente->dato+1) == 0) {
				printf("Los nodos %d y %d no son adyacentes, por lo que la secuencia no puede ser un ciclo.\n",auxiliar->dato,auxiliar->siguiente->dato);
				return 0;
			}
			else if (i >= 3) { //solo si i >= 3 (informacion sacada del ppt)
				if (auxiliar->dato == secuencia->inicio->dato || auxiliar->siguiente->dato == secuencia->inicio->dato) { //compara el dato de aux con el dato de la secuencia
					printf("La secuencia es un ciclo.\n");
					return 1;
				}
			}
			auxiliar = auxiliar->siguiente;
			i++;
		}
		printf("La secuencia no es un ciclo.\n");
		return 0;
	}

	//Función extra:
	//cicloPrint, 
	//DOM:
	//REC:
	//reciclada del lab 4
	void cicloPrint(int* arreglo, int n){
		for(size_t i = 0; i < n; i++){
			if (n==1) {
				printf("\nel arreglo es: (%d)\n", arreglo[i]);
			}
			else if (i==0) {
				printf("\nel arreglo es: (%d, ", arreglo[i]);
			}
			else if (i==n-1){
				printf("%d) \n", arreglo[i]);
			}
			else {
			printf("%d, ", arreglo[i]);
			}
		}
	}
	//Actividad 1 - Lab 9
	//recorridoProfundidad,
	//DOM: TDAgrafo X vertice (int)
	//REC: VOID
	void recorridoProfundidad(TDAgrafo* grafo, int vertice){
		TDApila* S = crearPilaVacia(100);
		int* visitados = calloc(grafo->cvertices,sizeof(int*)); //arreglo con ceros, de tamaño cvertices e int*
		apilar(S, vertice);
		while(!esPilaVacia(S)){
			cicloPrint(visitados,grafo->cvertices); 
			int u = S->tope->dato;
			desapilar(S);
			if (visitados[u-1] == 0) {
				visitados[u-1] = 1;
				printf("%d Esta visitado\n",u);
				TDAlista* lista = obtenerAdyacentes(grafo,u);
				nodo* aux = lista->inicio;
				while(aux != NULL){
					if (visitados[aux->dato - 1] == 0) {
						apilar(S,aux->dato);
						printf("Adyacente = %d\n", S->tope->dato);
						
					}
					recorrerLista(lista);
					aux = aux->siguiente;
				}
			}
			cicloPrint(visitados,grafo->cvertices); 
		}
	}