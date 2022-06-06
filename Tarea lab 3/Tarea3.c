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

//leerCVertices, función que en base a lo escrito en el archivo de entrada.in ovtiene el numero de vertices
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
//DOM: arreglo de arreglos (int***) X int
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
		if (x == 999){} //ignoramos los cuarteles
		else{
			for (int j = i+1; j < v; j++){
				if (arreglo[j]==999){} //ignoramos los cuarteles			
				else if (x = arreglo[j]){
					return 1;
				}
			}
		}
	}
	return 0;
}
//posCuartelIdeal, función que calcula la posición ideal para el cuartel, en base al arreglo entregado
//DOM: arreglo de ints (int*)
//REC: int
int posCuartelIdeal(int* aSumaDistanciasC, int* aSumaDijkstras, int c, int v){
	int pos; int x;
	if (c == 1) { //Si solo hay un cuartel, buscamos la interseccion más lejana al cuartel
		if (!distanciasIguales(aSumaDijkstras,v)){ //Si no hay distancias iguales, se irá por la interseccion con menor distancia a otras
			x = aSumaDijkstras[0]; pos = 0;
			for (size_t i = 0; i < v; i++){
				if (x > aSumaDijkstras[i]){
					x = aSumaDijkstras[i];
					pos = i;
				}
			}
		}
		else { //Si hay distancias iguales, se irá por quien tenga mayor distancia al cuartel
			x = aSumaDistanciasC[0]; pos = 0;
			for (size_t i = 0; i < v; i++){
				if (x < aSumaDistanciasC[i]){
					x = aSumaDistanciasC[i];
					pos = i;
				}
			}			
		}
		
	}
	else { //Si hay más de un cuartel, se irá por quien tenga la menor suma de distancias de dijkstra 
		x = aSumaDijkstras[0]; pos = 0;
		for (size_t i = 0; i < v; i++){
			if (x > aSumaDijkstras[i]){
				x = aSumaDijkstras[i];
				pos = i;
			}
		}
	}
	return pos;
}

//BLOQUE PRINCIPAL
int main(int argc, char const *argv[]){
    //Declaramos los argumentos como archivo de entrada y salida
    archivoEntrada = argv[1];
    if (argc < 3){printf("\nDebe especificar un archivo de Entrada y otro de Salida.\n");}
    archivoSalida = argv[2];
	//Corremos el algoritmo que consigue la cantidad de vértices, para correr los otros
	if (archivoEntrada != NULL) { printf("\nEl grafo y sus datos son:\n"); }
	//Leemos los datos del archivo y los asignamos a variables
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
	printf("El dijkstra-distancia para cada vertice es:\n");
	int*** arregloDijkstras = cicloDijkstra(grafo); printf("\n");
	//Sumamos los arreglos de distancia de dijstra, de cada arreglo en uno solo
	int* sumaDistanciasCuarteles = sumaDijkstrasCuarteles(arregloDijkstras, cuarteles, c, v);
	printf("El arreglo con la suma de las distancias de los cuarteles es:\n");
	imprimirArreglo(sumaDistanciasCuarteles,v); printf("\n");
	//test
	int* sumas = sumaDijkstras(arregloDijkstras, cuarteles, c, v);
	printf("El arreglo con la suma de las distancias de un vertice a los otros es:\n");
	imprimirArreglo(sumas,v); printf("\n");
	//Con la suma de los algoritmos, encontraremos donde construir un cuartel
	int posicionIdeal = posCuartelIdeal(sumaDistanciasCuarteles, sumas, c, v);
	printf("Posicion ideal = %d\n",posicionIdeal+1);
}