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
void liberarLista(TDAlista* lista){
  while(!esListaVacia(lista)){
    eliminarInicio(lista);
  }
}

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

//Función extra, para imprimir "buscarDato". Dom: lista, dato. Rec: void, sale un print por consola.
void existeDato(TDAlista* lista, int dato){
  if (buscarDato(lista, dato) == 1) {
    printf("El numero %d esta dentro de la lista\n", dato);
  }
  else if (buscarDato(lista, dato) == 0) {
    printf("El numero no esta dentro de la lista\n");
  }
  
}

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

nodo* obtenerNodo(TDAlista* lista, int posicion){
  nodo* auxiliar=lista->inicio;
  for (size_t i = 0; i < posicion; i++)
  {
    auxiliar = auxiliar->siguiente;
  }
  return auxiliar;
}
