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
int c; //Cantidad de cuarteles

//Definición de funciones

//leerPueblo, función que lee un archivo "pueblo.in" y lo retorna de una forma más "usable"
//DOM: const char* (archivoEntrada)
//REC: TDAgrafo
	TDAgrafo* leerPueblo(const char *nombreArchivo){
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
			fscanf(pf, "%d %d", &c,&i); printf("\ni = %d, c = %d\n",i,c);	
			TDAgrafo *G=crearGrafoVacio(i);	
            //caso 2: "Las siguientes c líneas"
            int* cLineas = (int*)malloc(c * sizeof(int));
            for (size_t x = 0; x < c; x++){
                fscanf(pf,"%d",&cLineas[x]);
            }
            //caso3: 
			//dependiendo de las lineas de archivo, 
			//1 para grafo no dirigido no ponderado
			for(int k=0;k<i;k++){
				fscanf(pf,"%d %d %d",&a,&j,&w);
				G->adyacencias[a-1][j-1] = w;
				G->adyacencias[j-1][a-1] = w;
			}
			fclose(pf);
			return  G;	
		}
	}
//leerCuarteles, función que lee un archivo "pueblo.in" y lo retorna de una forma más "usable"
//DOM: const char* (archivoEntrada)
//REC: arreglo con los cuarteles
	int* leerCuarteles(const char *nombreArchivo){
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
			TDAgrafo *G=crearGrafoVacio(i);	
            //caso 2: "Las siguientes c líneas"
            int* cLineas = (int*)malloc(c * sizeof(int));
            for (size_t x = 0; x < c; x++){
                fscanf(pf,"%d",&cLineas[x]);
				imprimirArreglo(cLineas,c);
            }
            fclose(pf);
			return  cLineas;	
        }
    }
//BLOQUE PRINCIPAL
int main(int argc, char const *argv[]){
    //Declaramos los argumentos como archivo de entrada y salida
    archivoEntrada = argv[1];
    if (argc < 3){printf("\nDebe especificar un archivo de Entrada y otro de Salida.\n");}
    archivoSalida = argv[2];
    //Creamos un grafo representando el "pueblo" y un arreglo
    TDAgrafo* grafo = leerPueblo(archivoEntrada);
    int* cuarteles = (int*)malloc(c * sizeof(int));
	cuarteles = leerCuarteles(archivoEntrada);
    //Imprimimos el grafo y su arreglo
    imprimirMatrizAdyacencia(grafo);
    imprimirArreglo(cuarteles,c); printf("AYUDA\n");

}