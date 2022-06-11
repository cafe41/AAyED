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
//contarHojasAB, función que de forma recursiva cuenta las hojas dentro de un arbol
//DOM: nodoAN X int
//REC: int
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

//numHojasAB, función que "encapsula" a la función contarHojas, no la llama si el arbol es vacío.
//DOM: TDAarbol
//REC: int
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
//eliminarNodoAB, función que borra un nodo con el dato que se especifique, 
//en caso de que sea una hoja se borrará directamente, sino, si tiene un hijo, se le asignará al "abuelo"
//en caso de que el nodoDato (hijo de nodoPadre), tenga dos hijos, no se podrá asignar al "abuelo".
//DOM: TDAarbol X int
//REC: VOID
void eliminarNodoAB(TDAarbolBinario* arbol, int dato){
  nodoArbolBinario* nodoDato = buscarNodoAB(arbol, dato);
  nodoArbolBinario* nodoPadre = nodoDato->padre;

  //Primer caso: El nodo a eliminar es una "hoja".
  if (esHojaAB(nodoDato)) {
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
  //Tercer caso: El nodo no es hoja y tiene dos hijos, no se puede eliminar.
  else { printf("No se puede eliminar el nodo del dato: %d\n", dato); }
}