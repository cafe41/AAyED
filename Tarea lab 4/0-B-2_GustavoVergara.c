//Tarea 4 del laboratorio
//NOMBRE: GUSTAVO VERGARA
//SECCIÓN: 0-B-2

//Importación de librerías
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "TDAaAVL.h" //TDAaAVL y TDAlista están editados para tener un nodo con dos datos
#include "TDAlista.h"//De esta forma, serán usados en la tarea 4.

//Variables Globales

const char* archivoEntrada;
const char* archivoSalida; 

//Definición de funciones

//archivoToLista, función que lee el archivo de entrada y retorna una lista con los datos que contiene
//DOM: archivoEntrada
//REC: TDAlista
TDAlista* archivoToLista(const char* nombreArchivo){
	FILE *archivo = fopen(nombreArchivo, "r"); 

    struct stat sb;
    stat(nombreArchivo, &sb);

    char *file_contents = malloc(sb.st_size);
	TDAlista* listaEntrada = crearListaVacia();	//Asignamos memoria a una lista
	int d1, d2;

	//Creamos un ciclo que vaya leyendo el archivo y agregue las lineas a un nodo
	//Luego agregará ese nodo a una lista
    while (fscanf(archivo, "%d %d", &d1,&d2) != EOF) {
		insertarInicio(listaEntrada,d1,d2); //El nodo tiene dos datos
    }

	fclose(archivo);
	return listaEntrada;	
}

//listaToAVL, función que agrega los nodos de una lista a un arbolAVL
//como un número único
//DOM: TDAlista
//REC: TDAarbolAVL
TDAarbolAVL* listaToAVL(TDAlista* listaE){
	TDAarbolAVL* arbol = crearAVLVacio();
	nodo* aux = listaE->inicio;
	while (aux != NULL){
		//Decidí que era mejor recibir un solo dato en el AVL, así es balanceable
		int d1d2 = (aux->dato*100) + aux->dato2;
		insertarNodoAVL(arbol, d1d2);
		aux = aux->siguiente;
	}
	return arbol;
}

//transformarAVL, función que transforma la información del AVL a una lista.
//DOM: TDAarbolAVL X TDAnodoAVL X TDAlista X int X int
//REC: void
void transformarAVL(TDAarbolAVL* arbol, nodoAVL* nodo, TDAlista* listaSalida ,int x1, int x2){
	if (nodo!=NULL){
		int d1 = nodo->dato /100;
		int d2 = nodo->dato %100;
		//Llamado recursivo hijo izq
		transformarAVL(arbol,nodo->hijoIzquierdo,listaSalida,x1,x2);
		//
		if(x1==0){x1 = d1;} //Esto impide que se escriban horarios
		if (x2 < d1){
			//Cortamos x2 => [x1,x2]
			//Insertamos el nodo "creado" al inicio
			if (listaSalida->inicio == NULL){insertarInicio(listaSalida,x1,x2);}
			else{insertarNodoFinal(listaSalida,x1,x2);}
			x1 = 0;
		}
		if (x2 < d2){x2 = d2;}
		//Llamado recursivo caso hijo der
		transformarAVL(arbol,nodo->hijoDerecho,listaSalida,x1,x2);
	}
}
//AVLToLista, función que transforma los datos de un arbolAVL y los escribe en una lista
//DOM: TDAarbolAVL
//REC: TDAlista
TDAlista* AVLToLista(TDAarbolAVL* arbol){
	if (!esAVLvacio(arbol)){
		//Creamos una lista Vacía
		TDAlista* listaSalida = crearListaVacia();
		//Llamamos a la función recursiva
    	transformarAVL(arbol,arbol->inicio,listaSalida,0,8);
		return listaSalida;
	}
	else{
		printf("El árbol AVL está vacío\n");
	}
}

//escribirSalida, función que escribirá el dato1 y dato2 de un nodo 
//DOM: arreglo de char (nombreArchivo) X int
//REC: void (aunque crea y escribe dentro del archivo de salida)
void escribirSalida(const char* archivoSalida, TDAlista* listaE){
	FILE* archivo = fopen(archivoSalida, "w");
	nodo* aux = listaE->inicio;
	while (aux != NULL){ //Escribirá nodo por nodo en el archivo
		fprintf(archivo,"%d",aux->dato);
		fprintf(archivo,"%s"," ");
		fprintf(archivo,"%d",aux->dato2);
		fprintf(archivo,"%s","\n");
		aux = aux->siguiente;
	}
	fclose(archivo);
}

//BLOQUE PRINCIPAL
void main(int argc, char const *argv[]){
    //Declaramos los argumentos como archivo de entrada y salida
    archivoEntrada = argv[1];
    if (argc < 3){printf("\nDebe especificar un archivo de Entrada y otro de Salida.\n");}
    archivoSalida = argv[2];
	//Corremos el algoritmo que consigue la cantidad de vértices, para correr los otros
	if (archivoEntrada != NULL) {printf("La lista resultante es:\n");}
	//Leemos los datos del archivo y los asignamos a una lista enlazada
	TDAlista* listaEntrada = archivoToLista(archivoEntrada);
	recorrerLista(listaEntrada);printf("\n");
	//Creamos un arbolAVL en base a la lista con los datos de entrada
	TDAarbolAVL* arbolito = listaToAVL(listaEntrada);
	printf("Nuestro arbolAVL es:\n");
	recorridoInordenAVL(arbolito);printf("\n");
	//Balanceamos el arbolAVL
	//nodoMenorAlturaAVL recorrerá hasta el nodo más bajo, 
	//para ejecutar "recuperarBalance"
	recuperarBalanceAVL(arbolito,nodoMenorAlturaAVL(arbolito)); 
	//PASAMOS LO DEL AVL, YA ORDENADO A UNA LISTA
	TDAlista* listaSalida = AVLToLista(arbolito); //Plan B: pasar todo a un arreglo INORDEN
	recorrerLista(listaSalida);
	//Finalmente, escribimos la posicion y liberamos memoria
	//ESCRIBIR EN ARCHIVO DE SALIDA
	escribirSalida(archivoSalida,listaSalida);
	//LIBERAR MEMORIA
	free(listaEntrada);free(arbolito);free(listaSalida);
	printf("FIN\n");
}