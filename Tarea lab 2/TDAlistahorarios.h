//Definición de TDAs (o structs)

typedef struct TDA_horario { //Nodo adaptado para contener horarios
   int dia;
   int hora;
   struct TDA_horario* siguiente;
}nodoH;

typedef struct listaHorarios {
  nodoH* inicio;
}TDAlista;


typedef struct TDA_Semana {
  int* lunes;
  int* martes;
  int* miercoles;
  int* jueves;
  int* viernes;
}TDAsemana;

/*------------- operaciones -------------*/

TDAlista* crearListaVacia(){
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->inicio=NULL;
  return lista;
}

int esListaVacia(TDAlista* lista){
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}

void imprimirLista(TDAlista* lista)
{
  if (!esListaVacia(lista))
  {
    nodoH* auxiliar=lista->inicio;
    while (auxiliar!=NULL)
    {
      printf("[%d %d] ",auxiliar->dia,auxiliar->hora);
      auxiliar=auxiliar->siguiente;
    }
    printf("\n");
  }
  else
    printf("La lista está vacía\n");
}

void eliminarInicio(TDAlista* lista)
{
  nodoH* auxiliar;
  if(!esListaVacia(lista))
  {
    auxiliar=lista->inicio;
    lista->inicio=lista->inicio->siguiente;
    free(auxiliar);
  }
}

int obtenerNumeroNodos(TDAlista* lista){
  int i = 0;
  nodoH* auxiliar=lista->inicio;
  while(auxiliar != NULL){
    i = i+1;
    auxiliar = auxiliar->siguiente;
  }
  return i;
}

void insertarInicio(TDAlista* lista, int dato)
{
  nodoH* nuevo = (nodoH*)malloc(sizeof(nodoH));
  nuevo->dia = dato /100;
  nuevo->hora = dato %100;
  nuevo->siguiente = lista->inicio;
  lista->inicio=nuevo;
}

void insertarNodoFinal(TDAlista* lista, int dato){ //dato = numero de 3 dígitos
  nodoH* auxiliar=lista->inicio;
  while(auxiliar->siguiente != NULL){
    auxiliar = auxiliar->siguiente;
  } //Recorremos la lista hasta el "final"
  nodoH* nuevo = (nodoH*)malloc(sizeof(nodoH));
  nuevo->dia = dato /100;
  nuevo->hora = dato %100;
  nuevo->siguiente = NULL;
  auxiliar->siguiente = nuevo;
}

TDAsemana* crearSemana(){ //Se trabaja de 8 a 22hrs (14 hrs en total)
  TDAsemana* lista=(TDAsemana*)malloc(sizeof(TDAsemana));
  lista->lunes = (int *) malloc (sizeof(int *)*14);
  for (size_t i = 0; i < 14; i++){ //Estos ciclos llenan el "dia" de 0
    lista->lunes[i] = 0;
  }
  lista->martes = (int *) malloc (sizeof(int *)*14);
  for (size_t i = 0; i < 14; i++){
    lista->martes[i] = 0;
  }
  lista->miercoles = (int *) malloc (sizeof(int *)*14);
  for (size_t i = 0; i < 14; i++){
    lista->miercoles[i] = 0;
  }
  lista->jueves = (int *) malloc (sizeof(int *)*14);
  for (size_t i = 0; i < 14; i++){
    lista->jueves[i] = 0;
  }
  lista->viernes = (int *) malloc (sizeof(int *)*14);
  for (size_t i = 0; i < 14; i++){
    lista->viernes[i] = 0;
  }
  return lista;
}