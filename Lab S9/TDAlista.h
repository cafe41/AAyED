#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* siguiente;
}nodo;

typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;


/*------------- operaciones -------------*/
//Estas funciones no fueron definidas por mi, por lo que no veo sentido en documentarlas.

TDAlista* crearListaVacia()
{
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->inicio=NULL;
  return lista;
}

int esListaVacia(TDAlista* lista)
{
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

void recorrerLista(TDAlista* lista)
{
  if (!esListaVacia(lista))
  {
    nodo* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      printf("%d ",auxiliar->dato);
      auxiliar=auxiliar->siguiente;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}

void insertarInicio(TDAlista* lista, int dato)
{
  nodo* nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->dato=dato;
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

void eliminarInicio(TDAlista* lista)
{
  nodo* auxiliar;
  if(!esListaVacia(lista))
  {
    auxiliar=lista->inicio;
    lista->inicio=lista->inicio->siguiente;
    free(auxiliar);
  }
}


/*------------- Actividad 2 -------------*/

//liberarLista, función que libera la memoria de la lista enlazada
//DOM: listaEnlazada
//REC: void
void liberarLista(TDAlista* lista){
  while(!esListaVacia(lista)){
    eliminarInicio(lista);
  }
}

//buscarDato, función que busca un dato dentro de la lista, imprime 1 si está, 0 si no.
//DOM: listaEnlazada X dato (int)
//REC: "boolean" (1 o 0)
int buscarDato(TDAlista* lista, int dato){
  nodo* auxiliar=lista->inicio;
  while(auxiliar != NULL){
    if (auxiliar->dato == dato){
      return 1;
    }
    auxiliar = auxiliar->siguiente;
  }
  return 0;
}

//existeDato, función extra, para imprimir "buscarDato". Dom: lista, dato. Rec: void, sale un print por consola.
//DOM: listaEnlazada x dato (int)
//REC: VOID
void existeDato(TDAlista* lista, int dato){
  if (buscarDato(lista, dato) == 1) {
    printf("El numero %d esta dentro de la lista\n", dato);
  }
  else if (buscarDato(lista, dato) == 0) {
    printf("El numero no esta dentro de la lista\n");
  }
  
}

//obtenerNumeroNodos, función que retorna la cantidad de nodos de la lista
//DOM: listaEnlazada
//REC: int
int obtenerNumeroNodos(TDAlista* lista){
  int i = 0;
  nodo* auxiliar=lista->inicio;
  while(auxiliar != NULL){
    i = i+1;
    auxiliar = auxiliar->siguiente;
  }
  return i;
}

/*------------- Actividad 3 -------------*/

//insertarNodoFinal, función que inserta un nodo con un dato, al final de una lista
//DOM: listaEnlazada x dato (int)
//REC: VOID
void insertarNodoFinal(TDAlista* lista, int dato){
  nodo* auxiliar=lista->inicio;
  while(auxiliar->siguiente != NULL){
    auxiliar = auxiliar->siguiente;
  } //Recorremos la lista hasta el "final"
  nodo* nuevo = (nodo*)malloc(sizeof(nodo));
  nuevo->dato = dato;
  nuevo->siguiente = NULL;
  auxiliar->siguiente = nuevo;
}

//insertarNodoDespues, función que agrega un nodo después de otro nodo, según el dato de este.
//DOM: listaEnlazada x dato (int) x datoAnterior (int)
//REC: VOID
void insertarNodoDespues(TDAlista* lista, int dato, int datoAnterior){
  nodo* auxiliar=lista->inicio;
  while(auxiliar->dato != datoAnterior){
    auxiliar = auxiliar->siguiente;
  } //Recorremos la lista hasta el "datoAnterior"
  nodo* nuevo = (nodo*)malloc(sizeof(nodo));
  nuevo->siguiente = auxiliar->siguiente;
  nuevo->dato = dato;
  auxiliar->siguiente = nuevo;
}

//eliminarFinal, función que elimina el final de una lista enlazada
//DOM: listaEnlazada
//REC: VOID
void eliminarFinal(TDAlista* lista){
  nodo* auxiliar=lista->inicio;
  while(auxiliar->siguiente != NULL){
    auxiliar = auxiliar->siguiente;
  } //Recorremos la lista hasta el "final"
  nodo* auxiliar2=lista->inicio;
  while(auxiliar2->siguiente->siguiente != NULL){
    auxiliar2 = auxiliar2->siguiente;
  } //Recorremos la lista hasta el "final-1"
  auxiliar2->siguiente = NULL;
  free(auxiliar);
}

//eliminarDato, función que elimina un nodo según el dato que tenga.
//DOM: listaEnlazada x dato (int)
//REC: VOID
void eliminarDato(TDAlista* lista, int dato){
  nodo* auxiliar=lista->inicio;
  while(auxiliar->dato != dato){
    auxiliar = auxiliar->siguiente;
  } //Recorremos la lista hasta el "dato-1"
  nodo* auxiliar2=lista->inicio;
  while(auxiliar2->siguiente->dato != dato){
    auxiliar2 = auxiliar2->siguiente;
  } //Recorremos la lista hasta el "dato-2"
  auxiliar2->siguiente = auxiliar->siguiente;
  free(auxiliar);
}

//obtenerNodo, función que entrega el nodo en cierta posición, dentro de una lista enlazada.
//DOM: listaEnlazada x posición (int)
//REC: TDAnodo
nodo* obtenerNodo(TDAlista* lista, int posicion){
  nodo* auxiliar=lista->inicio;
  for (size_t i = 0; i < posicion; i++)
  {
    auxiliar = auxiliar->siguiente;
  }
  return auxiliar;
}
