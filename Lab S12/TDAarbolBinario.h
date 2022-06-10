#include <stdio.h>
#include <stdlib.h>

/*--------------- estructura de datos -----------------*/

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

TDAarbolBinario* crearArbolBinarioVacio()
{
  TDAarbolBinario* arbolBinario=(TDAarbolBinario*)malloc(sizeof(TDAarbolBinario));
  arbolBinario->inicio=NULL;
  return arbolBinario;
}

int esArbolBinarioVacio(TDAarbolBinario* arbolBinario)
{
  if (arbolBinario->inicio == NULL)
    return 1;
  else
    return 0;
}

/*--------------- operaciones de posicion -----------------*/

//devuelve NULO si el árbol está vacío
nodoArbolBinario* raizAB(TDAarbolBinario* arbol)
{
  if (arbol!=NULL)
    return arbol->inicio;
  return NULL;
}

// devuelve NULO si nodo no existe
nodoArbolBinario* padreNodoAB(TDAarbolBinario* arbol, nodoArbolBinario* nodo)
{
  if (nodo!=NULL)
    return nodo->padre;
}


int esHojaAB(nodoArbolBinario* nodo)
{
  if ((nodo->hijoIzquierdo==NULL)&&(nodo->hijoDerecho==NULL))
    return 1;
  return 0;
}

/*--------------- operaciones de recorrido -----------------*/

/*---- actividad 1 ----*/
//procesar, función que "hace un proceso" a un nodo, la construí para poder cambiar el código y que no colapse.
//DOM: nodoAB
//REC: VOID
void procesar(nodoArbolBinario* nodo){printf("%d ",nodo->dato);}

//recorridoInordenArbolBinario, función que se llama de forma recursiva a si misma para realizar un "proceso" sobre un nodo específico, en orden "En-orden".
//DOM: nodoAB
//REC: VOID (print por consola)
void recorridoInordenArbolBinario(nodoArbolBinario* nodo){
  if (nodo!=NULL) {
    if(esHojaAB(nodo)){
      procesar(nodo);
    }
    else{
      recorridoInordenArbolBinario(nodo->hijoIzquierdo);
      procesar(nodo);
      recorridoInordenArbolBinario(nodo->hijoDerecho);
    }
  }
}

//recorridoInordenAB, función que a partir de un arbol, llama a recorridoInordenArbolBinario de forma recursiva
//DOM: TDAarbol
//REC: VOID (print por consola)
void recorridoInordenAB(TDAarbolBinario* arbol){
  if (!esArbolBinarioVacio(arbol)) {
     recorridoInordenArbolBinario(arbol->inicio);
  }
  else{
    printf(" vacio ");
  }
}

/*---- actividad 2 ----*/
//recorridoPreordenArbolBinario, función que se llama de forma recursiva a si misma para realizar un "proceso" sobre un nodo específico, en orden "Pre-orden".
//DOM: nodoAB
//REC: VOID (print por consola)
void recorridoPreordenArbolBinario(nodoArbolBinario* nodo){
  if (nodo!=NULL) {
    if(esHojaAB(nodo)){
      procesar(nodo);
    }
    else{
      procesar(nodo);
      recorridoPreordenArbolBinario(nodo->hijoIzquierdo);
      recorridoPreordenArbolBinario(nodo->hijoDerecho);
    }
  }
}
//recorridoPreordenAB, función que a partir de un arbol, llama a recorridoPreordenArbolBinario de forma recursiva
//DOM: TDAarbol
//REC: VOID (print por consola)
void recorridoPreordenAB(TDAarbolBinario* arbol){
  if (!esArbolBinarioVacio(arbol)) {
     recorridoPreordenArbolBinario(arbol->inicio);
  }
  else{
    printf(" vacio ");
  }
}


/*---- actividad propuesta ----*/
//recorridoPostordenArbolBinario, función que se llama de forma recursiva a si misma para realizar un "proceso" sobre un nodo específico, en orden "Post-orden".
//DOM: nodoAB
//REC: VOID (print por consola)
void recorridoPostordenArbolBinario(nodoArbolBinario* nodo){
  if (nodo!=NULL) {
    if(esHojaAB(nodo)){
      procesar(nodo);
    }
    else{
      recorridoPostordenArbolBinario(nodo->hijoIzquierdo);
      recorridoPostordenArbolBinario(nodo->hijoDerecho);
      procesar(nodo);
    }
  }
}
//recorridoPostordenAB, función que a partir de un arbol, llama a recorridoPostordenArbolBinario de forma recursiva.
//DOM: TDAarbol
//REC: VOID (print por consola)
void recorridoPostordenAB(TDAarbolBinario* arbol){
  if (!esArbolBinarioVacio(arbol)) {
     recorridoPostordenArbolBinario(arbol->inicio);
  }
  else{
    printf(" vacio ");
  }
}

/*--------------- operaciones auxiliares -----------------*/

/*---- actividad 3 ----*/
int contarHojasAB(nodoArbolBinario* nodo, int contador){
  if (nodo!=NULL) {
    if(esHojaAB(nodo)){
      return 1;
    }
    else{
      return contarHojasAB(nodo->hijoIzquierdo, contador) + contarHojasAB(nodo->hijoDerecho,contador);
    }
  }
  else {
    return contador;
  }
}

int numHojasAB(TDAarbolBinario* arbol){
  int contador = 0;
  if (!esArbolBinarioVacio(arbol)) {
    contador = contarHojasAB(arbol->inicio, contador);
    printf("%d\n",contador);
  }
  else{
    printf("El arbol esta vacio\n");
  }
  return contador;
}


/*--------------- operaciones de búsqueda -----------------*/

nodoArbolBinario* buscarNodoRecursivoAB(nodoArbolBinario* nodo, int dato)
{
  nodoArbolBinario* aux;
  if (nodo!=NULL)
  {
    if (nodo->dato==dato)
      return nodo;
    else
    {
      aux=buscarNodoRecursivoAB(nodo->hijoIzquierdo,dato);
      if (aux!=NULL)
        return aux;
      return buscarNodoRecursivoAB(nodo->hijoDerecho,dato);
    }
  }
}

nodoArbolBinario* buscarNodoAB(TDAarbolBinario* arbol, int dato)
{
  nodoArbolBinario* aux;
  if (!esArbolBinarioVacio(arbol))
  {
    aux=arbol->inicio;
    return buscarNodoRecursivoAB(aux,dato);
  }
  else
    return NULL;
}

/*--------------- operaciones de actualización -----------------*/

void insertarRaizAB(TDAarbolBinario* arbol, int dato)
{
  nodoArbolBinario* raiz=(nodoArbolBinario*)malloc(sizeof(nodoArbolBinario));
  raiz->dato=dato;
  raiz->hijoIzquierdo=NULL;
  raiz->hijoDerecho=NULL;
  raiz->padre=NULL;
  arbol->inicio=raiz;
}

// tipoHijo={0 (izquierdo), 1 (derecho)}
void insertarNodoAB(TDAarbolBinario* arbol, int padre, int dato, int tipoHijo)
{
  nodoArbolBinario* nodoPadre;
  nodoArbolBinario* nuevo;

  if (!esArbolBinarioVacio(arbol))
  {
    //si existe nodoPadre
    nodoPadre=buscarNodoAB(arbol,padre);
    if (nodoPadre!=NULL)
    {
      if (tipoHijo==0)  //hijo izquierdo
      {
        if (nodoPadre->hijoIzquierdo==NULL) //está desocupado
        {
          nuevo=(nodoArbolBinario*)malloc(sizeof(nodoArbolBinario));
          nuevo->dato=dato;
          nuevo->hijoIzquierdo=NULL;
          nuevo->hijoDerecho=NULL;
          nuevo->padre=nodoPadre;
          nodoPadre->hijoIzquierdo=nuevo;
        }
        else
          printf("no se puede insertar %d como hijo izquierdo\n",dato);
      }
      else if (tipoHijo==1)  //hijo derecho
      {
        if (nodoPadre->hijoDerecho==NULL) //está desocupado
        {
          nuevo=(nodoArbolBinario*)malloc(sizeof(nodoArbolBinario));
          nuevo->dato=dato;
          nuevo->hijoIzquierdo=NULL;
          nuevo->hijoDerecho=NULL;
          nuevo->padre=nodoPadre;
          nodoPadre->hijoDerecho=nuevo;
        }
        else
          printf("no se puede insertar %d como hijo derecho\n",dato);
      }
      else
        printf("tipo de hijo incorrecto\n");
    }
    else
      printf("no existe nodo padre\n");
  }
  else
    insertarRaizAB(arbol,dato);
}

/*----- actividad 4 ----*/
nodoArbolBinario* buscarPadreRecursivo(nodoArbolBinario* nodo, int dato){nodoArbolBinario* aux;
  nodoArbolBinario* aux;
  nodoArbolBinario* aux2;
  if (nodo!=NULL){
    if (nodo->dato==dato)
      return nodo;
    else {
      aux = buscarPadreRecursivo(nodo->hijoIzquierdo,dato);
      if (aux->dato==dato) {
        aux2 = buscarPadreRecursivo(nodo->hijoIzquierdo,dato);
        return aux2;
      }
      if (aux!=NULL){
        return aux;
      }
      return buscarPadreRecursivo(nodo->hijoDerecho,dato);
    }
  }
}

nodoArbolBinario* buscarPadreAB(TDAarbolBinario* arbol, int dato){
  nodoArbolBinario* aux;
  if (!esArbolBinarioVacio(arbol))
  {
    aux=arbol->inicio;
    return buscarPadreRecursivo(aux,dato);
  }
  else
    printf("arbol vacio\n");
    return NULL;
}
/*
void eliminarNodoAB(TDAarbolBinario* arbol, int dato){
  nodoArbolBinario* nodoPadre;
  nodoPadre; 
  nodoArbolBinario* nodoDato = buscarNodoAB(arbol, dato);

    if (esHojaAB(nodoPadre)) {
      if (nodoPadre->hijoIzquierdo->dato == dato) {
        nodoPadre->hijoIzquierdo = NULL;
      }
      else if (nodoPadre->hijoDerecho->dato == dato) {
        nodoPadre->hijoDerecho = NULL;
      }
    }

    else {
      
    }

    free(nodoPadre);*/

