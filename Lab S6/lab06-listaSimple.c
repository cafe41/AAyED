#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"

int main()
{
  TDAlista* lista=crearListaVacia();
  insertarInicio(lista,2); insertarInicio(lista,4); insertarInicio(lista,7); insertarInicio(lista,5); 
  recorrerLista(lista);
  eliminarInicio(lista); eliminarInicio(lista);
  recorrerLista(lista);
  insertarInicio(lista,3); 
  recorrerLista(lista);
  existeDato(lista, 4);
  printf("La cantdad de nodos es: %d\n",obtenerNumeroNodos(lista));
  insertarNodoFinal(lista, 20);
  recorrerLista(lista);
  insertarNodoDespues(lista, 10, 2);
  recorrerLista(lista);
  eliminarFinal(lista);
  recorrerLista(lista);
  eliminarDato(lista, 4);
  recorrerLista(lista);
  printf("El dato del nodo es: %d y su siguiente es: %d",obtenerNodo(lista,1)->dato,obtenerNodo(lista,1)->siguiente->dato);
  return 0;
}