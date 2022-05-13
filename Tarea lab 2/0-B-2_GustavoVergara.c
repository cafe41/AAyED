//Tarea 2 del laboratorio
//NOMBRE: GUSTAVO VERGARA
//SECCIÓN: 0-B-2

//Importación de librerías

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "TDAlistahorarios.h" //TDA propio, adjuntado en el .zip

//Variables Globales

//Escribiré los nombres de archivos como variables globales, para ahorrarme problemas de código
const char* archivoEntrada; //Entrada.in
const char* archivoSalida;  //Salida.out
int n; //Cantidad de elementos en Entrada.in

//Definición de funciones

//leerArchivoPorNumero, función que lee el archivo por cada número dentro de él y lo agrega a una arreglo.
//DOM: FILE (filename) x arreglo
//REC: arreglo con los números del archivo dentro
//PD : reciclada de la tarea anterior, editada para leer todo
int* leerArchivoPorNumero(const char* filename, int* arreglo){ 
    FILE *in_file = fopen(filename, "r");
    if (!in_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sb.st_size);
    int i=0;

    while (fscanf(in_file, "%[^\n ] ", file_contents) != EOF) {
        arreglo[i]=atoi(file_contents);
        i++;
    }

    fclose(in_file);
    return arreglo;
}
//cantidadNumerosArchivo, función que lee el archivo por cada número dentro de él y lo agrega a una arreglo.
//DOM: const char* (filename)
//REC: cantidad de elementos en el archivo
//PD : edit de la función leerArchivoPorNumero
int cantidadNumerosArchivo(const char* filename){ 
    FILE *in_file = fopen(filename, "r");
    if (!in_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sb.st_size);
    int i=0;

    while (fscanf(in_file, "%[^\n ] ", file_contents) != EOF) {
        if (strlen(file_contents) == 3) {i++;}
    }

    fclose(in_file);
    return i;
}
//printArreglo, función que imprime un arreglo
//DOM: arreglo X int (largo del arreglo (n))
//REC: print del arreglo
void printArreglo(int* arreglo, int n){
    for(size_t i = 0; i < n; i++){
        if (n==1) {
            printf("el arreglo es: (%d)\n", arreglo[i]);
        }
        else if (i==0) {
            printf("el arreglo es: (%d, ", arreglo[i]);
        }
        else if (i==n-1){
            printf("%d) \n", arreglo[i]);
        }
        else {
        printf("%d, ", arreglo[i]);
        }
    }
}
//arregloToListaH, función que pasa los elementos de un arreglo a una lista enlazada
//DOM: arreglo X listaEnlazada
//REC: listaEnlazada
TDAlista* arregloToListaH(int* arreglo, TDAlista* listaE){
    for (size_t i = 0; i < n; i++){
        if (i==0) {insertarInicio(listaE,arreglo[i]);}
        else {insertarNodoFinal(listaE,arreglo[i]);}
    }
    return listaE;
}
//organizarSemana, esto organiza lo que hay en una lista, a un TDA_Semana
//DOM: listaE, semana
//REC: semana
TDAsemana* organizarSemana(TDAlista* listaE, TDAsemana* semana){
    nodoH* auxiliar = listaE->inicio;
    int dif; int x;
    for (size_t i = 0; i < n; i++){ //ciclo para recorrer la listaEnlazada
        if (i%2 == 0){//si es un valor par (o 0):  
            dif = auxiliar->siguiente->hora - auxiliar->hora;
            for (size_t j = 0; j < dif; j++){ //Este ciclo cambiará todas las horas que se trabajen por 1s (el arreglo está lleno de 0s)
                if (auxiliar->dia == 1){
                    x = auxiliar->hora + j - 8;
                    semana->lunes[x] = 1; //caso lunes
                }
                else if (auxiliar->dia == 2){
                    x = auxiliar->hora + j - 8;
                    semana->martes[x] = 1; //caso martes
                }
                else if (auxiliar->dia == 3){
                    x = auxiliar->hora + j - 8;
                    semana->miercoles[x] = 1; //caso miercoles
                }
                else if (auxiliar->dia == 4){
                    x = auxiliar->hora + j - 8;
                    semana->jueves[x] = 1; //caso jueves
                }
                else if (auxiliar->dia == 5){
                    x = auxiliar->hora + j - 8;
                    semana->viernes[x] = 1; //caso viernes
                }
            }
        }
        auxiliar = auxiliar->siguiente; 
    }
    return semana;
}
//horariosFaltantes, esta función recibe una semana y retorna los horarios que falta cubrir de la semana, como lista enlazada
//DOM: semana X listaEnlazada
//REC: listaEnlazada
TDAlista* horariosFaltantes(TDAsemana* semana, TDAlista* listaE){
    nodoH* auxiliar; int a = 0; int b = 0; //para la "ventana", a es el inicio y b el final
    for (size_t i = 0; i < 14; i++){//ciclo lunes
        if (a == 0){ 
            if (semana->lunes[i] == 0){ //si encuentra un 0 en el horario
                a = i + 8; //donde inicia el 
                if (i+1 == 14 || semana->lunes[i+1] == 1){ //si encuentra un 1 luego del 0
                    b = i + 8;
                    //Hay un error al insertar un nodo al final en una lista vacía
                    if (listaE->inicio == NULL){insertarInicio(listaE,(100+a));}
                    else {insertarNodoFinal(listaE,(100+a));} 
                    insertarNodoFinal(listaE,(100+b+1)); 
                    a = 0;
                }
            }
        }
        else {
            if (i+1 == 14 || semana->lunes[i+1] == 1){ //si encuentra un 1 luego del 0
                b = i + 8;
                if (listaE->inicio == NULL){insertarInicio(listaE,(100+a));}
                else {insertarNodoFinal(listaE,(100+a));}
                insertarNodoFinal(listaE,(100+b+1));
                a = 0;
            }  
        }
        
    }
    for (size_t i = 0; i < 14; i++){//ciclo martes
        if (a == 0){ 
            if (semana->martes[i] == 0){ //si encuentra un 0 en el horario
                a = i + 8; //donde inicia el 
                if (i+1 == 14 || semana->martes[i+1] == 1){ //si encuentra un 1 luego del 0
                    b = i + 8;
                    if (listaE->inicio == NULL){insertarInicio(listaE,(200+a));}
                    else {insertarNodoFinal(listaE,(200+a));}
                    insertarNodoFinal(listaE,(200+b+1));
                    a = 0;
                }
            }
        }
        else {
            if (i+1 == 14 || semana->martes[i+1] == 1){ //si encuentra un 1 luego del 0
                b = i + 8;
                if (listaE->inicio == NULL){insertarInicio(listaE,(200+a));}
                else {insertarNodoFinal(listaE,(200+a));}
                insertarNodoFinal(listaE,(200+b+1));
                a = 0;
            }  
        }
    }
    for (size_t i = 0; i < 14; i++){//ciclo miercoles
        if (a == 0){
            if (semana->miercoles[i] == 0){ //si encuentra un 0 en el horario
                a = i + 8; //donde inicia el 
                if (i+1 == 14 || semana->miercoles[i+1] == 1){ //si encuentra un 1 luego del 0
                    b = i + 8;
                    if (listaE->inicio == NULL){insertarInicio(listaE,(300+a));}
                    else {insertarNodoFinal(listaE,(300+a));}
                    insertarNodoFinal(listaE,(300+b+1));
                    a = 0;
                }
            }
        }
        else {
            if (i+1 == 14 || semana->miercoles[i+1] == 1){ //si encuentra un 1 luego del 0
                b = i + 8;
                if (listaE->inicio == NULL){insertarInicio(listaE,(300+a));}
                else {insertarNodoFinal(listaE,(300+a));}
                insertarNodoFinal(listaE,(300+b+1));
                a = 0;
            }  
        }
    }
    for (size_t i = 0; i < 14; i++){//ciclo jueves
        if (a == 0){
            if (semana->jueves[i] == 0){ //si encuentra un 0 en el horario
                a = i + 8; //donde inicia el 
                if (i+1 == 14 || semana->jueves[i+1] == 1){ //si encuentra un 1 luego del 0
                    b = i + 8;
                    if (listaE->inicio == NULL){insertarInicio(listaE,(400+a));}
                    else {insertarNodoFinal(listaE,(400+a));}
                    insertarNodoFinal(listaE,(400+b+1));
                    a = 0;
                }
            }
        }
        else {
            if (i+1 == 14 || semana->jueves[i+1] == 1){ //si encuentra un 1 luego del 0
                b = i + 8;
                if (listaE->inicio == NULL){insertarInicio(listaE,(400+a));}
                else {insertarNodoFinal(listaE,(400+a));}
                insertarNodoFinal(listaE,(400+b+1));
                a = 0;
            }  
        }
    }
    for (size_t i = 0; i < 14; i++){//ciclo viernes
        if (a == 0){
            if (semana->viernes[i] == 0){ //si encuentra un 0 en el horario
                a = i + 8; //donde inicia el 
                if (i+1 == 14 || semana->viernes[i+1] == 1){ //si encuentra un 1 luego del 0
                    b = i + 8;
                    if (listaE->inicio == NULL){insertarInicio(listaE,(500+a));}
                    else {insertarNodoFinal(listaE,(500+a));}
                    insertarNodoFinal(listaE,(500+b+1));
                    a = 0;
                }
            }
        }
        else {
            if (i+1 == 14 || semana->viernes[i+1] == 1){ //si encuentra un 1 luego del 0
                b = i + 8;
                if (listaE->inicio == NULL){insertarInicio(listaE,(500+a));}
                else {insertarNodoFinal(listaE,(500+a));}
                insertarNodoFinal(listaE,(500+b+1));
                a = 0;
            }  
        }
    }
    return listaE;
}
//escribirHorarios, función que escribe la lista enlazada como un archivo de salida.out
//DOM: listaEnlazada
//REC: archivoSalida.out
void escribirHorarios(TDAlista* listaE){
    nodoH* auxiliar = listaE->inicio;
    int cNodos = obtenerNumeroNodos(listaE);
    FILE* archivo = fopen(archivoSalida, "w");
    for (size_t i = 0; i < cNodos; i++){
        if (i%2 == 0){
            fprintf(archivo,"%d",((auxiliar->dia*100)+auxiliar->hora));
            fprintf(archivo,"%s"," ");
            fprintf(archivo,"%d",((auxiliar->siguiente->dia*100)+auxiliar->siguiente->hora));
            if(i!=cNodos-2){fprintf(archivo,"%s","\n");} //Para no entregar el archivo.out con un /n de más.
        }
        auxiliar = auxiliar->siguiente;
    }
    fclose(archivo);
}
//imprimirHorario, función que escribe el horario de una forma estética, por consola
//Dom: semana
//Rec: VOID
void imprimirHorario(TDAsemana* semana){
    //HORAS
    printf ("DIA        | 8 | 9 | 10| 11| 12| 13| 14| 15| 16| 17| 18| 19| 20| 21|\n");
    //LUNES
    printf ("LUNES:     |");
    for(size_t i = 0; i < 14; i++){
        if (i == 13){printf(" %d |\n", semana->lunes[i]);}
        else {printf(" %d |", semana->lunes[i]);}
    }
    //MARTES
    printf ("MARTES:    |");
    for(size_t i = 0; i < 14; i++){
        if (i == 13){printf(" %d |\n", semana->martes[i]);}
        else {printf(" %d |", semana->martes[i]);}
    }
    //MIERCOLES
    printf ("MIERCOLES: |");
    for(size_t i = 0; i < 14; i++){
        if (i == 13){printf(" %d |\n", semana->miercoles[i]);}
        else {printf(" %d |", semana->miercoles[i]);}
    }
    //JUEVES
    printf ("JUEVES:    |");
    for(size_t i = 0; i < 14; i++){
        if (i == 13){printf(" %d |\n", semana->jueves[i]);}
        else {printf(" %d |", semana->jueves[i]);}
    }
    //VIERNES
    printf ("VIERNES:   |");
    for(size_t i = 0; i < 14; i++){
        if (i == 13){printf(" %d |\n", semana->viernes[i]);}
        else {printf(" %d |", semana->viernes[i]);}
    }
}
//BLOQUE PRINCIPAL
int main(int argc, char const *argv[]){
    //Declaramos los argumentos como archivo de entrada y salida
    archivoEntrada = argv[1];
    if (argc < 3){printf("Debe especificar un archivo de Entrada y otro de Salida.\n\n");}
    archivoSalida = argv[2];
    //Definimos n como la cantidad de numeros en el archivo
    n = cantidadNumerosArchivo(archivoEntrada);
    //Creamos un arreglo para ingresar los datos del archivo
    int* arreglo = (int *) malloc (sizeof(int *)*n);
    leerArchivoPorNumero(archivoEntrada,arreglo);
    //Pasamos lo del arreglo a una lista enlazada, con "nodos de horario"
    TDAlista* listaE = crearListaVacia();
    arregloToListaH(arreglo,listaE);
    printf("la lista enlazada con los horarios que hay es:\n");imprimirLista(listaE);
    //Pasamos lo del arreglo dinámico a una "semana" (struct con dias laborales de 14 horas)
    TDAsemana* semana = crearSemana();
    organizarSemana(listaE,semana);
    imprimirHorario(semana);
    //Pasamos los horarios que faltan a una lista enlazada
    TDAlista* horariosF = crearListaVacia();
    horariosF = horariosFaltantes(semana,horariosF);
    printf("la lista enlazada con los horarios que faltan es:\n");imprimirLista(horariosF);
    //Escribimos los horarios faltantes en un archivo de salida
    escribirHorarios(horariosF);
    //Liberamos la memoria de las listas o arreglos sin usar
    free(arreglo); free(listaE); free(horariosF);
    //Fin del programa
    printf("\nFin del programa, puede revisar los resultados en el archivo de salida\n");
    return 0;
}