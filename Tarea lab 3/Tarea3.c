//Tarea 3 del laboratorio
//NOMBRE: GUSTAVO VERGARA
//SECCIÓN: 0-B-2

//Importación de librerías
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "TDAgrafo.h"

//Variables Globales

const char* archivoEntrada;
const char* archivoSalida; 

//Definición de funciones

//leerDatos, función que en base a lo escrito en el archivo de entrada.in ovtiene el numero de vertices
//DOM: char (nombre archivo)
//REC: int
int* leerDatos(const char *nombreArchivo){
	FILE*pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int c, i;
	int v= 0; //Realmente solo nos importa "v"
	int a,j,w,cuartel;
	if (pf == NULL){
		printf("Error de archivo vertices\n");
		return NULL;
	}else{
		//Caso 1 y 2 siguen siendo necesarios para recorrer el archivo, sin embargo no son necesario los arreglos que contienen los datos
		//caso 1: "c i"
		//Asignamos "c" e "i"
		fscanf(pf, "%d %d", &c,&i);
		TDAgrafo* G = crearGrafoVacio(i);
		//caso 2: "Las siguientes c líneas"
		int* cLineas = (int*)malloc(c * sizeof(int));
		for (size_t x = 0; x < c; x++){
			fscanf(pf,"%d",&cLineas[x]);
		}
		//caso 3: 
		//dependiendo de las lineas de archivo, 
		//1 para grafo no dirigido no ponderado
		for(int k=0;k<i;k++){
			fscanf(pf,"%d %d %d",&a,&j,&w);
			if (a > v) {v = a;}
			if (j > v) {v = j;}
		}
		//Liberamos las otras estucturas no usadas
		free(G);free(cLineas);
	}
	fclose(pf);
	int* arreglo = (int*)malloc(3 * sizeof(int));
	arreglo[0] = c; arreglo[1] = i; arreglo[2] = v; 
	return  arreglo;
}
//leerPueblo, función que lee un archivo "pueblo.in" y lo retorna de una forma más "usable"
//DOM: const char* (archivoEntrada)
//REC: TDAgrafo
TDAgrafo* leerPueblo(const char *nombreArchivo, int v){
	FILE*pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int c, i;
	int a,j,w,cuartel;
	if (pf ==NULL){
		printf("Error de archivo grafo\n");
		return NULL;
	}else{ 
		//caso 1: "c i"
		//Asignamos "c" e "i"
		fscanf(pf, "%d %d", &c,&i); printf("cuarteles = %d, intersecciones = %d\n",c,i);
		TDAgrafo* G = crearGrafoVacio(v);	
		//caso 2: "Las siguientes c líneas"
		int* cLineas = (int*)malloc(c * sizeof(int));
		for (size_t x = 0; x < c; x++){
			fscanf(pf,"%d",&cLineas[x]);
			cLineas[x] = cLineas[x] -1;
		}
		//caso 3: 
		//dependiendo de las lineas de archivo, 
		//1 para grafo no dirigido no ponderado
		for(int k=0;k<i;k++){
			fscanf(pf,"%d %d %d",&a,&j,&w);
			G->adyacencias[a-1][j-1] = w;
			G->adyacencias[j-1][a-1] = w;
		}
		free(cLineas);
		fclose(pf);
		return  G;	
	}
}
//leerCuarteles, función que lee un archivo "pueblo.in" y lo retorna de una forma más "usable"
//DOM: const char* (archivoEntrada)
//REC: arreglo con los cuarteles
int* leerCuarteles(const char *nombreArchivo, int v){
	FILE*pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int c, i;
	if (pf ==NULL){
		printf("Error de archivo arreglo\n");
		return NULL;
	}else{
		//caso 1: "c i", lo recorremos para llegar a las siguientes lineas
		//Asignamos "c" e "i"
		fscanf(pf, "%d %d", &c,&i); 
		TDAgrafo* G = crearGrafoVacio(v);	
		//caso 2: "Las siguientes c líneas"
		int* cLineas = (int*)malloc(c * sizeof(int)); 
		for (size_t x = 0; x < c; x++){
			fscanf(pf,"%d",&cLineas[x]);
			cLineas[x] = cLineas[x] -1;
		}
		fclose(pf);
		return cLineas;	
	}
}
//cicloDijkstra, función que crea un arreglo con los arreglos de dijkstra para cada posición
//DOM: TDAgrafo
//REC: arreglo de arreglos (int***)
int*** cicloDijkstra(TDAgrafo* grafo){
	int*** dijkstras = (int***)malloc(grafo->cvertices * sizeof(int**));
	for (int i = 0; i < grafo->cvertices; i++){
		//asignamos memoria y creamos un arreglo con 3 arreglos (los de dijkstra)
		dijkstras[i] = (int**)malloc(3 * sizeof(int*));
		Dijkstra(grafo,i);
		for (int j = 0; j < 3; j++){
			dijkstras[i][j] = (int*)malloc(grafo->cvertices * sizeof(int));
			if (j == 0){
				dijkstras[i][j]= dDistancia;
				printf("%d",i);
				for (size_t z = 10; z < 1000; z = z * 10){
					if (!(i / z != 0)){
						printf(" ");
					} 
				}
				imprimirArreglo(dijkstras[i][j], grafo->cvertices);
			}
			else if (j == 1){
				dijkstras[i][j]= dPadre;
			}
			else if (j == 2){
				dijkstras[i][j]= dVisitado;
			}
		}
	}
	return dijkstras;
}
//sumaDijkstrasCuarteles, función que suma las distancias de las distancias de dijkstra para cada cuartel.
//DOM: arreglo de arreglos (int***) X arreglo (int*) X int X int
//REC: arreglo de ints (int*)
int* sumaDijkstrasCuarteles(int*** arregloDijkstras, int* cuarteles, int c, int v){
	int* arregloSumas = (int*)malloc(v * sizeof(int));
	//Primer ciclo, suma las distancias de los dijkstras de cada cuartel
	for (size_t i = 0; i < c; i++){
		for (size_t j = 0; j < v; j++){
			arregloSumas[j]= arregloSumas[j] + arregloDijkstras[cuarteles[i]][0][j];
		}
	}
	//Segundo ciclo, pone un 0 donde haya ya un cuartel
	for (size_t i = 0; i < c; i++){
		arregloSumas[cuarteles[i]]= 0; 
	}
	return arregloSumas;
}
//sumaDijkstras, arreglo con el total de la suma de las distancias para cada vertice
//DOM: arreglo de arreglos (int***) X arreglo (int*) X int X int
//REC: arreglo de int (int*)
int* sumaDijkstras(int*** arregloDijkstras, int* cuarteles, int c, int v){
	int* sumas = (int*)malloc(v * sizeof(int));
	//Primer ciclo, suma las distancias de los dijstras para cada vertice
	for (size_t i = 0; i < v; i++){
		for (size_t j = 0; j < v; j++){
			sumas[i] = sumas[i] + arregloDijkstras[i][0][j];
		}
	}
	//Segundo ciclo, pone un 999 donde haya ya un cuartel
	for (size_t i = 0; i < c; i++){
		sumas[cuarteles[i]]= 999; 
	}
	return sumas;
}
//distanciasIguales(), función que en base a la suma de las distancias de un vertice a otros, 
//revisa que no sean iguales, si son iguales retorna 1, sino 0
//DOM: arreglo de ints (int*) X int
//REC: int (boolean)
int distanciasIguales(int* arreglo, int v){
	for (int i = 0; i < v; i++){
		int x = arreglo[i];
		if (x == 999 || x == 99999){} //ignoramos los cuarteles
		else{
			for (int j = i+1; j < v; j++){
				if (arreglo[j]==999 || arreglo[j]==99999){} //ignoramos los cuarteles			
				else if (x = arreglo[j]){
					return 1;
				}
			}
		}
	}
	return 0;
}
//maxDijkstra, función que consigue el max del arreglo distancia de dijkstra para cada vertice
//DOM: arreglo de arreglos (int***) X arreglo (int*) X int X int
//REC: arreglo de int (int*)
int* maxDijkstra(int*** arregloDijkstras, int* cuarteles, int c, int v){
	int* maximos = (int*)malloc(v * sizeof(int));
	int x = 0;
	//Primer ciclo: asigna el máximo de las distancias de cada vertice a la posicion del vertice en "maximos"
	for(int i = 0; i < v; i++){
		for(int j = 0; j < v; j++){
			if (arregloDijkstras[i][0][j] > x) {
				x = arregloDijkstras[i][0][j];
			}	
		}
		maximos[i] = x;
	}
	//Segundo ciclo: agrega "99999" a los cuarteles para que sean ignorados a la hora de buscar minimo, asumiendo que ninguna distancia es mayor a 999999
	for (int i = 0; i < c; i++){
		maximos[cuarteles[i]]= 99999; 
	}

	return maximos;
	}
//posCuartelIdeal, función que calcula la posición ideal para el cuartel, en base al minimo de los maximos de las distancias
//DOM: arreglo de ints (int*)
//REC: int
int posCuartelIdeal(int*** arregloDijkstras, int* cuarteles, int c, int v){
	//asignamos arreglos e ints a usar
	int pos; int x;
	int* sumaDCuarteles = sumaDijkstrasCuarteles(arregloDijkstras,cuarteles,c,v);
	int* sumaDs = sumaDijkstras(arregloDijkstras,cuarteles,c,v);
	int* maximos = maxDijkstra(arregloDijkstras,cuarteles,c,v);
	 //Si no hay distancias iguales: Se elige el que tenga menor distancia a las demás
	x = maximos[0]; pos = 0;
	for(int i = 1; i < v; i++){	
		if (x > maximos[i]) {
			x = maximos[i];
			pos = i;
		}
	}
	if (distanciasIguales(maximos,v)) { //En caso de que hayan distancias de dijkstra iguales:
		if (c == 1) { //Si solo hay un cuartel:
			int y = sumaDCuarteles[0];
			int* comparador = calloc(v,sizeof(int));
			//Primer ciclo, detecta el mayor valor dentro del arreglo de la suma dijkstra de los cuarteles
			for(int i = 1; i < v; i++){	
				if (y < sumaDCuarteles[i]) {
					y = sumaDCuarteles[i];
				}
			}
			//Segundo ciclo, asigna los valores de la mayor distancia a los cuarteles al arreglo comparador
			for (int i = 0; i < v; i++){
				if (sumaDCuarteles[i] == y){
					comparador[i] = y;
				}
			}
			//Tercer ciclo, revisa opciones "viables" al comparar ambos arreglos
			for (int i = 0; i < v; i++){
				if (comparador[i] != 0){
					if (maximos[i] == x){
						pos = i; //Finalmente, asigna la posicion a ese espacio
					}
				}
			}
			
		}
		else if (c > 1) {//Si hay mas de un cuartel: 
		//asigna la "posicion" al intervalo que tenga menos distancia comparado a los otros
			int y = sumaDs[0];
			int* comparador = calloc(v,sizeof(int));
			//Primer ciclo, asigna "y" a donde va el minimo de los maximos (asumiendo que son más de 1)
			for (int i = 0; i < v; i++){
				if (x == maximos[i]){
					comparador[i] = x;
				}
			}
			//Segundo ciclo, asigna el menor valor del arreglo a "y" en base a los minimos de los maximos
			for(int i = 1; i < v; i++){	
				if (comparador[i] == x && y > sumaDs[i]) {
					y = sumaDs[i];
					pos = i;
				}
			}
		}
	}
	printf("El arreglo con los maximos de cada dijkstra:\n");
	imprimirArreglo(maximos,v); printf("\n");
	return pos;
}
//escribirPosicion, función que escribe la posicionIdeal + 1 en el archivoSalida.out
//DOM: arreglo de char (nombreArchivo) X int
//REC: void (aunque crea y escribe dentro del archivo de salida)
void escribirPosicion(const char* archivoSalida, int posicion ){
	FILE* archivo = fopen(archivoSalida, "w");
	fprintf(archivo,"%d",posicion+1);
	fclose(archivo);
}
//BLOQUE PRINCIPAL
void main(int argc, char const *argv[]){
    //Declaramos los argumentos como archivo de entrada y salida
    archivoEntrada = argv[1];
    if (argc < 3){printf("\nDebe especificar un archivo de Entrada y otro de Salida.\n");}
    archivoSalida = argv[2];
	//Corremos el algoritmo que consigue la cantidad de vértices, para correr los otros
	if (archivoEntrada != NULL) { printf("\nEl grafo y sus datos son:\n"); }
	//Leemos los datos del archivo y los asignamos a variables, para luego liberar "datos"
	int* datos = leerDatos(archivoEntrada);
	int c = datos[0]; int i = datos[1]; int v = datos[2]; free(datos);
	if (archivoEntrada != NULL) { printf("vertices = %d, ", v); }
    //Creamos un grafo representando el "pueblo" y un arreglo con los cuarteles
    TDAgrafo* grafo = leerPueblo(archivoEntrada, v);
    int* cuarteles = leerCuarteles(archivoEntrada, v);
    //Imprimimos el grafo y el arreglo
    imprimirMatrizAdyacencia(grafo); printf("\n");
    if (archivoEntrada != NULL) { printf("Las posiciones de los cuarteles son:\n"); }
	imprimirArreglo(cuarteles, c); printf("\n");
	//Creamos un "mega-arreglo" con los arreglos de dijkstra para cada vertice
	printf("El arreglo dijkstra-distancia para cada vertice es:\n");
	int*** arregloDijkstras = cicloDijkstra(grafo); printf("\n");
	//Con la suma de los algoritmos, encontraremos donde construir un cuartel
	int posicionIdeal = posCuartelIdeal(arregloDijkstras, cuarteles, c, v);
	printf("Posicion ideal = %d (%d en C)\n",posicionIdeal+1, posicionIdeal);
	//Finalmente, escribimos la posicion y liberamos memoria
	escribirPosicion(archivoSalida,posicionIdeal);
	free(arregloDijkstras); free(grafo); free(cuarteles);
}