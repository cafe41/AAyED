	//Laboratorio 8 y 9
	//NOMBRE: GUSTAVO VERGARA
	//SECCIÓN: 0-B-2
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "TDAlista.h"
	#include "TDApila.h"
	#include "TDAcola.h"

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

	//Actividad 1 - Lab 9
	//recorridoProfundidad, función que recorre un grafo a través del método de "profundidad"
	//Este es un método que va viendo los vertices adyacentes al vertice que se le de y los 
	//agrega a una pila, luego repite el proceso con los adyacentes a estos y asi recorre todo el 
	//grafo. Cuando termine la funcion, esta nos dirá si este es conexo o no.
	//DOM: TDAgrafo X vertice (int)
	//REC: VOID (pero imprimirá los resultados por consola)
	void recorridoProfundidad(TDAgrafo* grafo, int vertice){
		printf("Recorrido por profundidad: \n");
		TDApila* S = crearPilaVacia(100); //le puse 100 para marcar un máximo, dudo que llegue a más de 100 a menos que sea forzado a
		int* visitados = calloc(grafo->cvertices,sizeof(int*)); //arreglo con ceros, de tamaño cvertices e int*
		apilar(S, vertice); //apilamos el vertice inicial (entregado en el dominio) a la pila S
		while(!esPilaVacia(S)){ //mientras la pila no este vacia
			int u = S->tope->dato;
			desapilar(S); //Desapilamos, pues le dimos el dato a "u"
			if (visitados[u] == 0) { //Si u no ha sido visitado:
				visitados[u] = 1;    //lo marcamos como visitado
				printf("%d Esta visitado\n",u);
				TDAlista* lista = obtenerAdyacentes(grafo,u); //y apilamos sus adyacentes
				nodo* aux = lista->inicio;
				while(aux != NULL){
					if (visitados[aux->dato] == 0) {
						apilar(S,aux->dato);
					}
					aux = aux->siguiente;
				}
			}
		}
		//Esto imprimirá según la cantidad de numeros no-visitados, si el grafo es conexo o no
		int x = 0; 
		for (int i = 0; i < grafo->cvertices; i++){if (visitados[i] == 0){x++;}}
		if (x > 0){printf("No todos los vertices han sido visitados, el grafo es desconexo\n");}
		else{printf("Todos los vertices fueron visitados, el grafo es conexo.\n");}
	}
	//recorridoAnchura, función que recorre un grafo a través del método de "anchura"
	//Este es un método que va viendo los vertices adyacentes al vertice que se le de y los 
	//agrega a una cola, luego repite el proceso con los adyacentes a estos y asi recorre todo el 
	//grafo. Cuando termine la funcion, esta nos dirá si este es conexo o no.
	//DOM: TDAgrafo X vertice (int)
	//REC: VOID (pero imprimirá los resultados por consola)
	void recorridoAnchura(TDAgrafo* grafo, int vertice){
		printf("Recorrido por anchura: \n");
		TDAcola* Q = crearColaVacia(100); //le puse 100 para marcar un máximo, dudo que llegue a más de 100 a menos que sea forzado a
		int* visitados = calloc(grafo->cvertices,sizeof(int*)); //creamos una lista con 0
		visitados[vertice] = 1; printf("%d Esta visitado\n",vertice); //marcamos el primer vertice como visitado
		encolar(Q,vertice); //encolamos el vertice
		while (!esColaVacia(Q)){ //Mientras la cola no este vacia
			int w = Q->frente->dato;
			desencolar(Q); //desencolamos la cola, ya que lo asignamos a w
			TDAlista* lista = obtenerAdyacentes(grafo,w);
			nodo* aux = lista->inicio; //aux apunta al inicio de la lista con los adyacentes de w
			while (aux != NULL){
				if (visitados[aux->dato] == 0) { //si el dato en aux no ha sido visitado,
					encolar(Q,aux->dato);        //encola el dato en Q
					visitados[aux->dato] = 1;    //y lo marca como visitado
					printf("%d Esta visitado\n",aux->dato);
					}
					aux = aux->siguiente; //aux = siguiente nodo en la lista
			}
		}
		//Esto imprimirá según la cantidad de numeros no-visitados, si el grafo es conexo o no
		int x = 0; 
		for (int i = 0; i < grafo->cvertices; i++){if (visitados[i] == 0){x++;}}
		if (x > 0){printf("No todos los vertices han sido visitados, el grafo es desconexo\n");}
		else{printf("Todos los vertices fueron visitados, el grafo es conexo.\n");}
	}