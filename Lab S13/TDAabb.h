#include <stdio.h>
#include <stdlib.h>

/*--------------- estructura de datos -----------------*/

typedef struct nodoABB
{
  int dato;
  struct nodoABB* padre;
  struct nodoABB* hijoIzquierdo;
  struct nodoABB* hijoDerecho;
}nodoABB;

typedef struct 
{
  nodoABB* inicio;
}TDAabb;


typedef struct nodoAB
{
  int dato;
  struct nodoAB* padre;
  struct nodoAB* hijoIzquierdo;
  struct nodoAB* hijoDerecho;
}nodoArbolBinario;

typedef struct 
{
  nodoArbolBinario* inicio;
}TDAarbolBinario;

/*--------------- operaciones de creación -----------------*/

TDAabb* crearABBVacio()
{
  TDAabb* abb=(TDAabb*)malloc(sizeof(TDAabb));
  abb->inicio=NULL;
  return abb;
}

int esABBvacio(TDAabb* abb)
{
  if (abb->inicio == NULL)
    return 1;
  else
    return 0;
}

/*--------------- operaciones de posicion -----------------*/

//devuelve NULO si el árbol está vacío
nodoABB* raizABB(TDAabb* arbol)
{
  if (arbol!=NULL)
    return arbol->inicio;
  return NULL;
}

nodoABB* padreNodoABB(TDAabb* arbol, nodoABB* nodo)
{
  if (nodo!=NULL)
    return nodo->padre;
}

int esHojaABB(TDAabb* arbol, nodoABB* nodo)
{
  if (!esABBvacio(arbol))
  {
    if ((nodo->hijoIzquierdo==NULL)&&(nodo->hijoDerecho==NULL))
      return 1;
  }
  return 0;
}

/*--------------- operaciones de recorrido -----------------*/

void recorridoInordenArbolBinarioBusqueda(nodoABB* nodo)
{
  if (nodo!=NULL)
  {
    //hijo izquierdo
    recorridoInordenArbolBinarioBusqueda(nodo->hijoIzquierdo);
    // raiz
    printf("%d ",nodo->dato);
    // hijo derecho
    recorridoInordenArbolBinarioBusqueda(nodo->hijoDerecho);
  }
}

void recorridoInordenABB(TDAabb* arbol)
{
  if (!esABBvacio(arbol))
  {
    printf("INORDEN: ");
    recorridoInordenArbolBinarioBusqueda(arbol->inicio);
    printf("\n");
  }
  else
    printf("El árbol binario está vacío\n");
}

/*--------------- operaciones de búsqueda -----------------*/

/*---- actividad propuesta ----*/
nodoABB* buscarNodoRecursivoABB(nodoABB* nodo, int dato){
  nodoABB* aux;
  if (nodo!=NULL)
  {
    if (nodo->dato==dato)
      return nodo;
    else
    {
      aux=buscarNodoRecursivoABB(nodo->hijoIzquierdo,dato);
      if (aux!=NULL)
        return aux;
      return buscarNodoRecursivoABB(nodo->hijoDerecho,dato);
    }
  }
}
nodoABB* buscarNodoABB(TDAabb* arbol, int dato){
  nodoABB* aux;
  if (!esABBvacio(arbol))
  {
    aux=arbol->inicio;
    return buscarNodoRecursivoABB(aux,dato);
  }
  else
    return NULL;
}

/*--------------- operaciones auxiliares -----------------*/

nodoABB* buscarMenorABB(TDAabb* arbol, nodoABB* nodo)
{
  nodoABB* aux;
  if (!esABBvacio(arbol))
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

/*---- actividad 1 ----*/
int verificacionRecursivaABB(TDAabb* arbol, nodoABB* nodo){
  // retorna falso si el de la derecha es menor o si el de la izq es mayor (asumiendo que no son null)
  if (nodo->hijoIzquierdo != NULL) {
    if (nodo->hijoIzquierdo->dato < nodo->dato) {
      verificacionRecursivaABB(arbol, nodo->hijoIzquierdo);
    }
    else {
      return 0;
    }
  }
  if (nodo->hijoDerecho != NULL) {
    if (nodo->hijoDerecho->dato > nodo->dato) {
      verificacionRecursivaABB(arbol, nodo->hijoDerecho);
    }
    else {
      return 0;
    }
  }
  return 1;
}

int verificarABB(TDAabb* arbol){
  if (arbol->inicio != NULL){
    verificacionRecursivaABB(arbol, arbol->inicio);
  }
  else {printf("El arbol esta vacio\n");}
}

/*--------------- operaciones de actualización -----------------*/

void insertarRaizABB(TDAabb* arbol, int dato)
{
  nodoABB* raiz=(nodoABB*)malloc(sizeof(nodoABB));
  raiz->dato=dato;
  raiz->hijoIzquierdo=NULL;
  raiz->hijoDerecho=NULL;
  raiz->padre=NULL;
  arbol->inicio=raiz;
}

void insertarNodoRecursivoABB(nodoABB* nodo, int dato)
{
  nodoABB* nuevo;

  nuevo=(nodoABB*)malloc(sizeof(nodoABB));
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
      insertarNodoRecursivoABB(nodo->hijoIzquierdo,dato);
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
      insertarNodoRecursivoABB(nodo->hijoDerecho,dato);
    }
  }
}

void insertarNodoABB(TDAabb* arbol, int dato)
{
  if (!esABBvacio(arbol))
  {
    insertarNodoRecursivoABB(arbol->inicio,dato);
  }
  else
    insertarRaizABB(arbol,dato);
}


/*---- actividad 2 ----*/
void eliminarNodoABB(TDAabb* arbol, int dato){
  nodoABB* nodoDato = buscarNodoABB(arbol,dato);
  nodoABB* nodoPadre = nodoDato->padre;

  //Primer caso: El nodo a eliminar es una "hoja".
  if (esHojaABB(arbol,nodoDato)) {
    if (nodoPadre->hijoIzquierdo->dato == dato) {
      nodoPadre->hijoIzquierdo = NULL;
    }
    else if (nodoPadre->hijoDerecho->dato == dato) {
      nodoPadre->hijoDerecho = NULL;
    }
    free(nodoDato); //Liberamos nodoDato, ya que no está "atado" a nada
  }
  //Segundo caso: El nodo no es hoja y tiene SOLO UN hijo, por lo que es posible eliminarlo.
  else if (nodoDato->hijoIzquierdo == NULL || nodoDato->hijoDerecho == NULL) {
    if (nodoPadre->hijoIzquierdo == nodoDato){ //Caso nodoDato sea hijo izquierdo
      if (nodoDato->hijoDerecho != NULL){
        nodoPadre->hijoIzquierdo = nodoDato->hijoDerecho;
      }
      else if (nodoDato->hijoIzquierdo != NULL){
        nodoPadre->hijoIzquierdo = nodoDato->hijoIzquierdo;
      }
    }
    else if (nodoPadre->hijoDerecho == nodoDato){ //Caso nodoDato sea hizo derecho
      if (nodoDato->hijoDerecho != NULL){
        nodoPadre->hijoDerecho = nodoDato->hijoDerecho;
      }
      else if (nodoDato->hijoIzquierdo != NULL){
        nodoPadre->hijoDerecho = nodoDato->hijoIzquierdo;
      }
    }
    free(nodoDato); //Liberamos nodoDato, ya que no está "atado" a nada
  }
  //Tercer caso: El nodo no es hoja y no se puede eliminar de forma "convencional", 
  //se llama la función de forma recursiva, intercambiando los datos de los nodos.
  else {
    nodoABB* aux1 = buscarMenorABB(arbol, nodoDato->hijoDerecho);
    //Intercambio
    int intercambio = nodoDato->dato;
    nodoDato->dato = aux1->dato;
    aux1->dato = intercambio;
    //Llamado recursivo
    eliminarNodoABB(arbol, aux1->dato);
  }
}
