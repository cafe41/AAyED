#include <stdio.h>
#include <stdlib.h>

/*----------------- estructura de datos -----------------*/

typedef struct nodoHashAbierto{
    int dato;
    struct nodoHashAbierto* siguiente;
}nodoHash;

typedef struct TDAtablaCerrada{
    int tamano;
    int* llaves;
    int* datos;
}TDAtablaHashCerrada;

/*----------------- operaciones de creación -----------------*/

//constructor tabla hash cerrada
//DOM: int
//REC: arreglo de ints
TDAtablaHashCerrada* crearHashCerrada(int largoArreglo){
    //Asignamos memoria
    TDAtablaHashCerrada* tabla = (TDAtablaHashCerrada*)malloc(sizeof(TDAtablaHashCerrada));
    tabla->tamano = largoArreglo;
    tabla->llaves = (int *) malloc (sizeof(int) * largoArreglo);
    tabla->datos = (int *) malloc (sizeof(int) * largoArreglo);
    
    //Rellenamos ambos arreglos con "-1"
    for(int i = 0; i < largoArreglo; i++){
        tabla->llaves[i] = -1;  
        tabla->datos[i] = -1;
    }

    return tabla;
}

//constructor tabla hash abierta

/*----------------- operaciones de tablaHashCerrada -----------------*/

//funcionHash, funcion que entrega una posición en base a una función que se aplica a la llave.
//DOM: int
//REC: int
int funcionHash(int llave){
    int pos = ((4* llave) + 3) % 7;
    return pos;
}

//insertarHashCerrado, función que inserta un dato
//DOM: TDAtablaHashCerrada X int X int
//REC: void
void insertarHashCerrado(TDAtablaHashCerrada* tabla, int llave, int dato){
    int pos = funcionHash(llave);
    int agregado = 0;
    int vuelta = 0;
    
    while(agregado == 0){
        if (tabla->llaves[pos]==-1 && tabla->datos[pos]==-1) {
            tabla->llaves[pos] = llave;
            tabla->datos[pos] = dato;
            agregado = 1;
        }
        else { //Si el espacio que se intenta rellenar está lleno:
            if (pos < tabla->tamano) {//Si la tabla no está en su final, la pos pasa a ser pos+1
                pos = pos + 1;
            }
            else {//Sino, pasa denuevo al 0 y se cuenta una vuelta.
                pos = 0;
                vuelta = vuelta + 1;
            }
            //En caso de que de más de una vuelta a la tabla hash y no logre escribir el dato.
            if (vuelta > 1) {
                agregado = 1;
                printf("La tabla esta llena, no se puede agregar");
            }
        }
    }
}

//buscarHashCerrado, función que busca un dato en la tabla hash
//DOM: TDAtablaHashCerrada X int
//REC: void
void buscarHashCerrado(TDAtablaHashCerrada* tabla, int llave){
    int pos = funcionHash(llave);
    int encontrado = 0; int vuelta = 0;
    
    while(encontrado == 0){//Mientras no se encuentre el elemento aún
        if (tabla->llaves[pos]==llave) {
            printf("\nLlave encontrada:\nLlave = %d\nDato = %d\n", tabla->llaves[pos], tabla->datos[pos]);
            encontrado = 1;
        }
        else { //Si el espacio que se intenta rellenar está lleno:
            if (pos < tabla->tamano) {//Si la tabla no está en su final, la pos pasa a ser pos+1
                pos = pos + 1;
            }
            else {//Sino, pasa denuevo al 0 y se cuenta una vuelta.
                pos = 0;
                vuelta = vuelta + 1;
            }
            //En caso de que de más de una vuelta a la tabla hash y no logre encontrar el dato.
            if (vuelta > 1) {
                encontrado = 1;
                printf("\nLa tabla no posee la llave que busca\n");
            }
        }
    }
}

//eliminarHashCerrado, función que elimina un dato de la tabla hash (lo reemplaza por -1)
//DOM: TDAtablaHashCerrada X int
//REC: void
void eliminarHashCerrado(TDAtablaHashCerrada* tabla, int llave){
    int pos = funcionHash(llave);
    int eliminado = 0; int vuelta = 0;
    
    while(eliminado == 0){
        if (tabla->llaves[pos]==llave) {
            tabla->llaves[pos] = -1;
            tabla->datos[pos]  = -1;
            eliminado = 1;
        }
        else { //Si el espacio que se intenta eliminar no es la llave que buscamos:
            if (pos < tabla->tamano) {//Si la tabla no está en su final, la pos pasa a ser pos+1
                pos = pos + 1;
            }
            else {//Sino, pasa denuevo al 0 y se cuenta una vuelta.
                pos = 0;
                vuelta = vuelta + 1;
            }
            //En caso de que de más de una vuelta a la tabla hash y no logre escribir el dato.
            if (vuelta > 1) {
                eliminado = 1;
                printf("El elemento no se encuentra en la tabla");
            }
        }
    }
}

//imprimirArreglo,función que imprime un arreglo, llamada por mostrarTablaHashCerrado
//DOM: int* (arreglo de int)
//REC: void (print por consola)
void imprimirArreglo(int* arreglo, int largo){
    for(size_t i = 0; i < largo; i++){
            if (largo==1) {
                if (arreglo[i] == -1){
                    printf("[  ]\n");
                }
                else{printf("[%d]\n", arreglo[i]);}
            }
            else if (i==0) {
                if (arreglo[i] == -1){
                    printf("[  , ");
                }
                else{printf("[%d, ", arreglo[i]);}
            }
            else if (i==largo-1){
                if (arreglo[i] == -1){
                    printf("  ]\n");
                }
                else{printf("%d]\n", arreglo[i]);}
            }
            else {
                if (arreglo[i] == -1){
                    printf("  , ");
                }
                else{printf("%d, ", arreglo[i]);}
            }
        }
}
//mostrarTablaHashCerrado, función que muestra nuestra tabla cerrada
//DOM: TDAtablaHashCerrada
//REC: void (sin embargo, imprime cosas por consola)
void mostrarTablaHashCerrado(TDAtablaHashCerrada* tabla){
    if(tabla != NULL){
        printf("Nuesta Tabla Hash Cerrada es:\n");
        //mostrarLlaves:
        printf("Llaves: ");
        imprimirArreglo(tabla->llaves,tabla->tamano);
        //mostarDatos:
        printf("Datos:  ");
        imprimirArreglo(tabla->datos,tabla->tamano);
    }
    else{printf("La tabla esta vacia\n");}
}