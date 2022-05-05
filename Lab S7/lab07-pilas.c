#include <stdio.h>
#include <stdlib.h>
#include "TDApila.h"

int main(){
  TDApila* pila = crearPilaVacia(3);
  apilar(pila, 1); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  apilar(pila, 2); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  apilar(pila, 3); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  desapilar(pila); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  desapilar(pila); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  desapilar(pila); // El programa deja de funcionar si se intenta imprimir el "dato" de NULL
  desapilar(pila); 
  apilar(pila, 4); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  apilar(pila, 5); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  apilar(pila, 6); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  apilar(pila, 7); 

  buscarDatoPila(pila, 3); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);
  buscarDatoPila(pila, 6); printf("tope pila: %d, size: %d/%d\n", pila->tope->dato, pila->size, pila->capacidad);

  return 0;
}