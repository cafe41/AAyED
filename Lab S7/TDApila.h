#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
   int dato;
   struct nodoGenerico* siguiente;
}nodo;

typedef struct
{
  int capacidad;
  int size;
  nodo* tope;
}TDApila;

/*------------- operaciones -------------*/

TDApila* crearPilaVacia(int capacidad)
{
  TDApila* pila=(TDApila*)malloc(sizeof(TDApila));
  pila->capacidad=capacidad;
  pila->size=0;
  pila->tope=NULL;
  return pila;
}

int esPilaVacia(TDApila* pila)
{
  if (pila->size == 0)
    return 1;
  else
    return 0;
}


/*------------- Actividad 2 -------------*/
void apilar(TDApila* pila, int dato){
  nodo* nodoAux = (nodo*)malloc(sizeof(nodo));
  nodoAux->dato = dato;
  
  if (pila->size < pila->capacidad) {
    nodoAux->siguiente = pila->tope;
    pila->tope = nodoAux;
    pila->size = pila->size + 1;
  }
  else {
    printf("pila llena, no se pueden agregar mas elementos\n");
  }
}

void desapilar(TDApila* pila){
  nodo* nodoAux = (nodo*)malloc(sizeof(nodo));
  
  if (esPilaVacia(pila)) {
    printf("La pila esta vacia\n");
  }
  else {
    nodoAux = pila->tope;
    pila->tope = pila->tope->siguiente;
    pila->size = pila->size - 1;
  }
  free(nodoAux);
}

nodo* tope(TDApila* pila){
  nodo* nodoAux = (nodo*)malloc(sizeof(nodo));
  nodoAux = pila->tope;

  return nodoAux;
}

/*------------- Actividad 4 -------------*/
int buscarDatoPila(TDApila* pila, int dato){
  //Crear pila auxiliar para "ordenar nuevamente" a como estaba la pila
  TDApila* pilaAux = crearPilaVacia(pila->capacidad);
  //buscar = variable auxiliar que es 1 si encontró el número, sino es 0
  int buscar = 0;
  while(buscar == 0){
    if (esPilaVacia(pila)) { //Si no lo encuentra, se rinde y retorna 0
      while(!esPilaVacia(pilaAux)) { //ciclo para devolver todo a la pila
        apilar(pila, pilaAux->tope->dato);
        desapilar(pilaAux);
      }
      printf("0 (No se pudo encontrar el dato)\n");
      return 0;
    }
    
    else if (pila->tope->dato == dato) { //Si lo encuentra, retorna 1
      while(!esPilaVacia(pilaAux)) { //ciclo para devolver todo a la pila
        apilar(pila, pilaAux->tope->dato);
        desapilar(pilaAux);
      }
      buscar = 1; //Creo que no es necesario, pero no se me ocurre otra forma de perpetuar el ciclo
      printf("1 (Dato encontrado)\n");
      return 1;
    }

    else { //Agrega un elemento a la pilaAux y lo quita de la pila
      apilar(pilaAux, pila->tope->dato);
      desapilar(pila);
    }
  }
}

