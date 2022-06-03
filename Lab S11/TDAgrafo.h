	//Laboratorio 8 y 9
	//NOMBRE: GUSTAVO VERGARA
	//SECCIÓN: 0-B-2
	
	#include <stdio.h>
	#include <stdlib.h>
	#include "TDAlista.h"
	#include "TDApila.h"
	#include "TDAcola.h"

	//Variables globales

	int* dPadre; int* dDistancia; int* dVisitado;

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

	//NoDirigido Ponderado
	TDAgrafo* leerGrafoNoDirigidoPonderado(char *nombreArchivo){
		FILE*pf;		   //para abrir archivo
		pf = fopen(nombreArchivo,"r");
		int n_vertices, m_aristas;
		int i,j,w,k;
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
				fscanf(pf,"%d %d %d",&i, &j,&w);
				G->adyacencias[i-1][j-1] = w;
				G->adyacencias[j-1][i-1] = w;
			}
			fclose(pf);
			return  G;	
		}
	}

	//Funciones extra y propias
	//imprimirArreglo, función que imprime un arreglo
	//DOM: arreglo X int (largo del arreglo (n))
	//REC: print del arreglo
	void imprimirArreglo(int* arreglo, int n){
		for(size_t i = 0; i < n; i++){
			if (n==1) {
				printf("(%d)\n", arreglo[i]);
			}
			else if (i==0) {
				printf("(%d, ", arreglo[i]);
			}
			else if (i==n-1){
				printf("%d) \n", arreglo[i]);
			}
			else {
			printf("%d, ", arreglo[i]);
			}
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
			if (grafo->adyacencias[v][i] >= 1) {
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

	//Actividad 1 - Lab 10

	//quedanSinVisitar, función que retorna 0 si no hay vertices por visitar, sino 1
	//DOM: Arreglo int X int (length arreglo)
	//REC: boolean (0 o 1)
	//Función de la actividad 2, pero la usé en la 1 tambien, asi que la moví hacia acá
	int quedanSinVisitar(int* visitados, int largoVisitados){
		for (size_t i = 0; i < largoVisitados; i++){ //Quedan sin visitar?
			if (visitados[i]==0)
			{
				return 1; //Si (true)
			}
		}
		return 0; //No (false)
	}

	//encontrarCamino, función que encuentra un camino entre un vertice y otro (vertice final)
	//DOM: TDAgrafo X vertice X verticeFinal
	//REC: TDAlista
	TDAlista* encontrarCamino(TDAgrafo* grafo, int vertice, int verticeFinal){
		TDAlista* secuencia = crearListaVacia(); 
		TDAlista* adyacentes = crearListaVacia(); 
		int vActual = vertice; nodo* aux;
		int* visitados = calloc(grafo->cvertices, sizeof(int));
		visitados[vActual] = 1; //Marcamos el primer vertice, para que no lo tome en cuenta dentro del ciclo
		insertarInicio(secuencia,vActual);
		while (vActual != verticeFinal) { //El ciclo se repite para el camino actual, si no ha sido visitado
			int x = 0; //x es un contador que nos ayudará a salir del while que viene
			adyacentes = obtenerAdyacentes(grafo, vActual);
			aux = adyacentes->inicio; 
			if (!quedanSinVisitar(visitados,grafo->cvertices)){//Si no quedan sin visitar, termina el ciclo con un 0
				printf("No quedan más vertices que visitar, no hay camino\n");
				return 0;
			}
			//ver qué vertice (que no esté visitado) tiene enlace con el vertice actual
			else {
				while (aux != NULL && x != 1){
					if (buscarDato(adyacentes,verticeFinal)){ //Priorizará el vertice final, si existe arista con él
						//Ciclo que mueve el aux hasta el dato 
						while (aux->dato != verticeFinal){
							aux = aux->siguiente;
						}
						//Luego agrega el vertice como si fuese cualquier otro
						visitados[aux->dato] = 1;
						vActual = aux->dato;
						insertarInicio(secuencia,vActual);
						x = 1;
					}
					
					else if (visitados[aux->dato] != 1){ //Sino, se irá por lo primero que encuentre
						//Agrega el vertice a la secuencia y lo marca como visitado
						visitados[aux->dato] = 1;
						vActual = aux->dato;
						insertarInicio(secuencia,vActual);
						x = 1;
					}
					aux = aux->siguiente;
				}
			}
		}
	return secuencia;
	}

	//Actividad 2 - Lab 10

	//extraerMinimo, algoritmo que retorna la posición del elemento que posea la minima distancia desde el vertice inicial, 
	//que no haya sido visto
	//DOM: arreglo int X int
	//REC: int (posición arreglo)
	int extraerMinimo(int* dDistancia, int length){
		int minimo = 9999; //Asumiendo que el peso no es más que 9999
		int indice;
		for (size_t i = 0; i < length; i++){
			if (dVisitado[i]==0){//Si no ha sido visitado
				if (dDistancia[i] < minimo && dDistancia[i] > 0){
					minimo = dDistancia[i];
					indice = i;
				}
			}
		}
		return indice;
	}

	//Algoritmo Dijkstra, algoritmo que busca el camino mínimo de un vertice del grafo hacia otros
	//DOM: TDAgrafo X int (vertice)
	//REC: VOID
	//Basado en el pseudocódigo
	void Dijkstra(TDAgrafo* grafo, int vertice){
		//Asignamos la memoria a los 3 arreglos:
		dDistancia = (int*)malloc(sizeof(int *)* grafo->cvertices);
		dPadre = (int*)malloc(sizeof(int *)* grafo->cvertices);	
		dVisitado = (int*)malloc(sizeof(int *)* grafo->cvertices);
		//Les asignamos valores:
		for (size_t w = 0; w < grafo->cvertices; w++){
			dPadre[w] = 0;
			dVisitado[w]= 0;
			if (grafo->adyacencias[vertice][w] > 0){
				dDistancia[w]=grafo->adyacencias[vertice][w];
				dPadre[w]=vertice;
			}
			else {
				dDistancia[w]= 666;
			}
		}
		dDistancia[vertice]= 0;
		dVisitado[vertice]= 1; //El vertice inicial es marcado como visitado
		while (quedanSinVisitar(dVisitado,grafo->cvertices)){
			int u = extraerMinimo(dDistancia,grafo->cvertices);
			dVisitado[u]= 1;
			TDAlista* listaAdc = obtenerAdyacentes(grafo,u);//Obtenemo9s una lista de los adyacentes a "u", distintos de 0
			nodo* aux = listaAdc->inicio;
			while (aux != NULL){
				if (dDistancia[aux->dato] > dDistancia[u] + grafo->adyacencias[u][aux->dato]){
					dDistancia[aux->dato] = dDistancia[u] + grafo->adyacencias[u][aux->dato];
					dPadre[aux->dato] = u;
				}
				aux = aux->siguiente;
			}	
		}
		//Imprimimos los arreglos resultantes:
		printf("\nDistancia : ");imprimirArreglo(dDistancia,grafo->cvertices);
		printf("Padres : ");imprimirArreglo(dPadre,grafo->cvertices);
		printf("Visitados : ");imprimirArreglo(dVisitado,grafo->cvertices);
	}

	//Actividad 1 - Lab 11 - Kruskal

	//Nodo de Kruskal
	typedef struct nodoKruskal {
		int dato;
		int i;
		int j;
		struct nodoKruskal* siguiente;
	}nodoK;

	//Lista de Kruskal
	typedef struct listaKruskal {
		nodoK* inicio;	
	}TDAlistaK;


	//Operaciones lista Kruskal

	//crearListaKVacia, función que inicializa el puntero de una lista de kruskal
	//DOM: TDAlistaK
	//REC: TDAlistaK
	TDAlistaK* crearListaKVacia(){
	TDAlistaK* lista=(TDAlistaK*)malloc(sizeof(TDAlistaK));
	lista->inicio=NULL;
	return lista;
	}

	//insertarInicioKruskal, función que agrega un nodo de kruskal al inicio de una lista
	//DOM: lista X int (i) X int (j) X int (dato = peso)
	//REC: void
	void insertarInicioKruskal(TDAlistaK* lista, int i, int j, int dato){
		nodoK* nuevo=(nodoK*)malloc(sizeof(nodoK));
		nuevo->dato=dato;
		nuevo->i = i;
		nuevo->j = j;
		nuevo->siguiente = lista->inicio;
		lista->inicio=nuevo;
	}

	//esListaKVacia, retorna un 1 si la lista está vacia, sino un 0
	//DOM: TDAlistaK
	//REC: int (boolean)
	int esListaKVacia(TDAlistaK* lista)
	{
	if (lista->inicio == NULL)
		return 1;
	else
		return 0;
	}

	//recorrerListaK, imprime por consola los valores dentro de una listaK
	//DOM: TDAlistaK
	//REC: void
	void recorrerListaK(TDAlistaK* lista) {
		if (!esListaKVacia(lista)){
			nodoK* auxiliar=lista->inicio;
			while (auxiliar!=NULL){
				printf("[%d,%d,%d] ",auxiliar->dato, auxiliar->i, auxiliar->j);
				auxiliar=auxiliar->siguiente;
			}
			printf("\n");
		}
		else {printf("La lista esta vacía\n");}
	}

	//esCiclico, función que retorna 1 si el grafo es cíclico, sino un 0.
	//DOM: TDAgrafo x int (vertice)
	//REC: int (boolean)
	int esCiclico(TDAgrafo* grafo, int vertice){
		TDAcola* Q = crearColaVacia(9999); //le puse 100 para marcar un máximo, dudo que llegue a más de 100 a menos que sea forzado a
		int* visitados = calloc(grafo->cvertices,sizeof(int*)); //creamos una lista con 0
		visitados[vertice] = 1; //marcamos el primer vertice como visitado
		int recorrido = 0;
		while(quedanSinVisitar(visitados,grafo->cvertices)){ //si quedan sin visitar:
			recorrido = recorrido +1;
			encolar(Q,vertice); //encolamos el vertice
			while (!esColaVacia(Q)){ //Mientras la cola no este vacia
				int w = Q->frente->dato;
				desencolar(Q); //desencolamos la cola, ya que lo asignamos a w
				TDAlista* lista = obtenerAdyacentes(grafo,w);
				nodo* aux = lista->inicio; //aux apunta al inicio de la lista con los adyacentes de w
				while (aux != NULL){
					if (visitados[aux->dato] == 0) { //si el dato en aux no ha sido visitado,
						encolar(Q,aux->dato);        //encola el dato en Q
						visitados[aux->dato] = recorrido;    //y lo marca como visitado
						}
					else {
						free(Q);
						return 1;
						}
					aux = aux->siguiente; //aux = siguiente nodo en la lista
				}
			}
		}
		free(Q);
		return 0;
	}

	//extraerMinimoKruskal, algoritmo que retorna la posición del elemento que posea la minima distancia desde el vertice inicial, 
	//que no haya sido visto
	//DOM: TDAlista
	//REC: nodoKruskal
	nodoK* extraerMinimoKruskal(TDAlistaK* listaKruskal){
		int minimo = 9999; //Asumiendo que el peso no es más que 9999
		nodoK* aux = listaKruskal->inicio; 
		int pos = 0; int index;
		while (aux != NULL){
			if (aux->dato < minimo && aux->dato > 0){
				minimo = aux->dato;
				index = pos;
			}
			pos = pos + 1;
			aux = aux->siguiente;
		}
		//Creamos un nodo auxA y lo llevamos al nodo en la posición index - 1
		nodoK* auxA = listaKruskal->inicio;
		for(size_t i = 0; i < index - 1; i++){
			auxA = auxA->siguiente;
		}
		//Creamos un nodo nuevo, con los datos del nodo que debemos tener
		aux = auxA->siguiente;
		auxA->siguiente = auxA->siguiente->siguiente;
		return aux;
	}

	//MSTKruskal, función que aplica el algoritmo de kruskal a un grafo, para generar otro grafo bajo los standares de kruskal
	//DOM: TDAgrafo
	//REC: TDAgrafo
	TDAgrafo* MSTKruskal(TDAgrafo* grafo){
		TDAlistaK* listaKruskal = crearListaKVacia();
		TDAgrafo* grafoKruskal = crearGrafoVacio(grafo->cvertices);
		int n = grafo->cvertices;
		int m = 0;
		printf("A");
		for(size_t i = 0; i < n; i++){
			for(size_t j = 0; j < n; j++){
				if (grafo->adyacencias[i][j] > 0) {
					insertarInicioKruskal(listaKruskal,i,j,grafo->adyacencias[i][j]);
				}
			}
		}
		printf("B");
		while(m<=n-1 && !esListaKVacia(listaKruskal)){
			nodoK* nodoK = extraerMinimoKruskal(listaKruskal);
			grafoKruskal->adyacencias[nodoK->i][nodoK->j] = nodoK->dato; 
			if (esCiclico(grafoKruskal, 0)) {
				grafoKruskal->adyacencias[nodoK->i][nodoK->j] = 0; 
			}
			recorrerListaK(listaKruskal);
			imprimirMatrizAdyacencia(grafoKruskal);
		}
		printf("C");
		return grafoKruskal;
	}