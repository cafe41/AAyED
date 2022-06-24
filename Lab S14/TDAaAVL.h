#include <stdio.h>
#include <stdlib.h>

/*--------------- estructura de datos -----------------*/

typedef struct nodoAVL
{
  int dato;
  struct nodoAVL* padre;
  struct nodoAVL* hijoIzquierdo;
  struct nodoAVL* hijoDerecho;
}nodoAVL;

typedef struct 
{
  nodoAVL* inicio;
}TDAarbolAVL;

/*--------------- operaciones de creación -----------------*/

TDAarbolAVL* crearAVLVacio()
{
  TDAarbolAVL* arbol=(TDAarbolAVL*)malloc(sizeof(TDAarbolAVL));
  arbol->inicio=NULL;
  return arbol;
}

int esAVLvacio(TDAarbolAVL* arbol)
{
  if (arbol->inicio == NULL)
    return 1;
  else
    return 0;
}

/*--------------- operaciones de posicion -----------------*/

//devuelve NULO si el árbol está vacío
nodoAVL* raizAVL(TDAarbolAVL* arbol)
{
  if (arbol!=NULL)
    return arbol->inicio;
  return NULL;
}

nodoAVL* padreNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (nodo!=NULL)
    return nodo->padre;
}

nodoAVL* hijoIzqNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (nodo!=NULL)
    return nodo->hijoIzquierdo;
}

nodoAVL* hijoDerNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (nodo!=NULL)
    return nodo->hijoDerecho;
}

nodoAVL* buscarMenorAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  nodoAVL* aux;
  if (!esAVLvacio(arbol))
  {
    aux=nodo;
    while (aux!=NULL)
    {
      if (aux->hijoIzquierdo!=NULL)
      {
        aux=aux->hijoIzquierdo;
      }
      else //es el aux es nodo que contiene dato
      {
        return aux;
      }
    }
  }
  return NULL;
}

int esHojaAVL(TDAarbolAVL* arbol, nodoAVL* nodo)
{
  if (!esAVLvacio(arbol))
  {
    if ((nodo->hijoIzquierdo==NULL)&&(nodo->hijoDerecho==NULL))
      return 1;
  }
  return 0;
}

/*--------------- operaciones de recorrido -----------------*/

void recorridoInorden(nodoAVL* nodo)
{
  if (nodo!=NULL)
  {
    //hijo izquierdo
    recorridoInorden(nodo->hijoIzquierdo);
    // raiz
    printf("%d ",nodo->dato);
    // hijo derecho
    recorridoInorden(nodo->hijoDerecho);
  }
}

void recorridoInordenAVL(TDAarbolAVL* arbol)
{
  if (!esAVLvacio(arbol))
  {
    printf("INORDEN: ");
    recorridoInorden(arbol->inicio);
    printf("\n");
  }
  else
    printf("El árbol AVL está vacío\n");
}

/*------------------ operaciones de balance --------------------*/

/***------------- actividad 1 -------------***/
int largoArbol(TDAarbolAVL* arbol, nodoAVL* nodo){
  if (nodo == NULL) {
    return 0;
  }
  else {
    
  }
}

int esBalanceadoNodoAVL(TDAarbolAVL* arbol, nodoAVL* nodo){
  if (!esAVLvacio(arbol)){
    int contador = 0;
    int ladoIzq = largoArbol(arbol, nodo->hijoIzquierdo); //Obtiene la altura del hijo izquierdo
    int ladoDer = largoArbol(arbol, nodo->hijoDerecho);   //Obtiene la altura del hijo derecho
    if (ladoIzq < ladoDer){
      while(ladoIzq < ladoDer){
        ladoIzq = ladoIzq + 1;
        contador = contador + 1;
      }
      if (contador > 1){
        return 0;
      }
      else {
        return 1;
      }
    }
    else if (ladoDer < ladoIzq) {
      ladoDer = ladoDer + 1;
      contador = contador + 1;
    }
    if (contador > 1){
        return 0;
      }
      else {
        return 1;
      }
  }
  else {printf("El arbol esta vacio\n");}
}


/***------------- actividad 2 -------------***/
void recuperarBalanceAVL(TDAarbolAVL* arbol, nodoAVL* z);



/*--------------- operaciones de búsqueda -----------------*/

nodoAVL* buscarNodoRecursivoAVL(nodoAVL* nodo, int dato)
{
  nodoAVL* aux;
  if (nodo!=NULL)
  {
    if (nodo->dato==dato)
      return nodo;
    else
    {
      if (dato < nodo->dato)
        return buscarNodoRecursivoAVL(nodo->hijoIzquierdo,dato);
      else
        return buscarNodoRecursivoAVL(nodo->hijoDerecho,dato);
    }
  }
}

nodoAVL* buscarNodoAVL(TDAarbolAVL* arbol, int dato)
{
  nodoAVL* aux;
  if (!esAVLvacio(arbol))
  {
    aux=arbol->inicio;
    return buscarNodoRecursivoAVL(aux,dato);
  }
  else
    return NULL;
}

/*--------------- operaciones de actualización -----------------*/

void insertarRaizAVL(TDAarbolAVL* arbol, int dato)
{
  nodoAVL* raiz=(nodoAVL*)malloc(sizeof(nodoAVL));
  raiz->dato=dato;
  raiz->hijoIzquierdo=NULL;
  raiz->hijoDerecho=NULL;
  raiz->padre=NULL;
  arbol->inicio=raiz;
}

void insertarNodoRecursivoAVL(TDAarbolAVL* arbol, nodoAVL* nodo, int dato)
{
  nodoAVL* nuevo;

  nuevo=(nodoAVL*)malloc(sizeof(nodoAVL));
  nuevo->dato=dato;
  nuevo->hijoIzquierdo=NULL;
  nuevo->hijoDerecho=NULL;

 if (dato <= nodo->dato)  //vamos por la izquierda
  {
    if (nodo->hijoIzquierdo==NULL) // no hay un hijo a la izquierda
    {
      nodo->hijoIzquierdo=nuevo;
      nuevo->padre=nodo;
    }
    else  //si ya hay un hijo a la izquierda
    {
      insertarNodoRecursivoAVL(arbol,nodo->hijoIzquierdo,dato);
    }
  }
  else //vamos por la derecha
  {
    if (nodo->hijoDerecho==NULL) // no hay un hijo a la izquierda
    {
      nodo->hijoDerecho=nuevo;
      nuevo->padre=nodo;
    }
    else  //si ya hay un hijo a la izquierda
    {
      insertarNodoRecursivoAVL(arbol,nodo->hijoDerecho,dato);
    }
  }
  /*** recuperarBalanceAVL(arbol,nodo); ***/
}

void insertarNodoAVL(TDAarbolAVL* arbol, int dato)
{
  if (!esAVLvacio(arbol))
  {
    insertarNodoRecursivoAVL(arbol,arbol->inicio,dato);
  }
  else
    insertarRaizAVL(arbol,dato);
}


/*** -------- actividad 3 ---------- ***/
void eliminarNodoAVL(TDAarbolAVL* arbol, int dato);







