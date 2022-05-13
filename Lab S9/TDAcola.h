#include <stdio.h>
#include <stdlib.h>
//#include "C:\Users\gvergara\GIT\AAyED\Lab S6\TDAlista.h"

/*------------- estructura de datos -------------*/
/*
typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* siguiente;
}nodo;
*/
typedef struct colaGenerica
{
    int capacidad;
    int size;
    nodo* frente;
    nodo* final;
}TDAcola;

/*------------- operaciones -------------*/

//creacColaVacia, función que crea una cola vacía, asignando punteros
//DOM: capacidad (int)
//REC: TDAcola
TDAcola* crearColaVacia (int capacidad){
    TDAcola* cola=(TDAcola*)malloc(sizeof(TDAcola));
    cola->capacidad=capacidad;
    cola->size=0;
    cola->frente=NULL;
    cola->final=NULL;
    return cola;
}
//esColaVacia, función que ve si la cola está vacía, si es así retorna 1, sino 0
//DOM: TDAcola
//REC: boolean (int)
int esColaVacia(TDAcola* cola)
{
  if (cola->size == 0)
    return 1;
  else
    return 0;
}

//encolar, función que agrega un nodo al final de la cola
//DOM: TDAcola X dato (int)
//REC: VOID
void encolar(TDAcola* cola, int dato){
    nodo* nodoAux = (nodo*)malloc(sizeof(nodo));
    nodoAux = cola->frente;
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato; nuevo->siguiente = NULL;
    
    if (cola->frente == NULL && cola->size < cola->capacidad) { //Caso 1: la cola está vacía, frente = final
        cola->frente = nuevo;
        cola->final = cola->frente;
        cola->size = cola->size + 1;
    }
    else if (cola->size < cola->capacidad) { //Caso 2: la cola no está llena ni vacía
        while(nodoAux->siguiente != NULL){
            nodoAux = nodoAux->siguiente;
        } //Recorremos la lista hasta el "final"
        nodoAux->siguiente = nuevo;
        cola->final = nuevo;
        cola->size = cola->size + 1;
    }
    else { //Caso 3: Cola llena
        printf("cola llena, no se pueden agregar mas elementos\n");
    }
}

//desencolar, función que "desencola" (quita) un nodo del inicio la cola
//DOM: TDAcola
//REC: VOID
void desencolar(TDAcola* cola){
    nodo* auxiliar;
    if(!esColaVacia(cola))
    {
    auxiliar=cola->frente;
    cola->frente=cola->frente->siguiente;
    cola->size = cola->size -1;
    free(auxiliar);
    }
}

//frente, función que retorna el frente (inicio) de una cola (TDAcola->inicio)
//DOM: TDAcola
//REC: TDAnodo
nodo* frente(TDAcola* cola){
    nodo* aux;
    aux = cola->frente;
    return aux;
}

//final, función que retorna el final de una cola (TDAcola->final)
//DOM: TDAcola
//REC: TDAnodo
nodo* final(TDAcola* cola){
    nodo* aux;
    aux = cola->final;
    return aux;
}

//Función extra:
//imprimirCola, función que imprime el frente y el final de la cola
void imprimirCola(TDAcola* cola){
    printf("El frente de la cola es: %d, El final de la cola es: %d\n",cola->frente->dato,cola->final->dato);
}