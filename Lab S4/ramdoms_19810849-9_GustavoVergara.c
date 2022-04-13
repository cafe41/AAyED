//Lab semana 4
//NOMBRE: GUSTAVO VERGARA
//SECCIÓN: 0-B-2

//Importación de librerías
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
//Variables globales

//Definición de funciones
//numerosAleatorios, función que recibe ciertos valores y entrega un arreglo con números random 
//DOM: int (n) X int (min) X int (max) donde n es argv1, min es argv2 y max es argv3, 
//REC: arreglo con n números, el cual contiene números randoms
int* numerosAleatorios(int n, int min, int max){
    int* arreglo;
    arreglo = (int *) malloc (sizeof(int *)*n);
    for(size_t i = 0; i < n; i++){
        arreglo[i]= rand() % (max-min+1) + min; //numero random entre min y max
    }
    return arreglo;
}
//bubbleSort, función que ordena con el método de burbuja
//DOM: arreglo X int (n = tamaño del arreglo)
//REC: arreglo "ordenado"
int* bubbleSort(int* arreglo, int n){
    for(size_t i = n; i > 1; i=i-1){
        for(size_t j = 0; j < i-1; j++){
            if (arreglo[j] > arreglo[j+1]) {
                int vIzq = arreglo[j]; //Variable izquierda = valor izq.
                //Se intercambian:
                arreglo[j] = arreglo[j+1]; // intercambiamos izquierdo con derecho
                arreglo[j+1] = vIzq; // intercambiamos derecho con izq.
            }
        }
        n=n-1;
    }
    return arreglo;
}
//cicloPrint, función que imprime un arreglo
//DOM: arreglo X int (largo del arreglo (n))
//REC: print del arreglo
void cicloPrint(int* arreglo, int n){
    for(size_t i = 0; i < n; i++){
        if (n==1) {
            printf("\nel arreglo es: (%d)\n", arreglo[i]);
        }
        else if (i==0) {
            printf("\nel arreglo es: (%d, ", arreglo[i]);
        }
        else if (i==n-1){
            printf("%d) \n", arreglo[i]);
        }
        else {
        printf("%d, ", arreglo[i]);
        }
    }
}
//cicloWrite, función que escribe los "prints" anteriores en un archivo de texto
//DOM: arreglo X int (n = largo del arreglo) X int (ordenado? 0=false, 1=true) 
//REC: archivo de texto con lo escrito encima
//IMPORTANTE: AL FINAL NO USÉ ESTA FUNCIÓN, YA QUE NO PEDÍAN ESCRIBIR LA LISTA DENTRO DEL ARCHIVO
void cicloWrite(int* arreglo, int n, int ordenado, FILE * fptr){
    if (ordenado==0) {
        for(size_t i = 0; i < n; i++){
            if (n==1) {
                //"\nel arreglo ordenado es: (arreglo[i])\n";
                fprintf(fptr,"%s","el arreglo sin ordenar es: (");
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",")\n");
            }
            else if (i==0) {
                //"\nel arreglo ordenado es: (arreglo[i], "
                fprintf(fptr,"%s","el arreglo sin ordenar es: (");
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",", ");
            }
            else if (i==n-1){
                //"arreglo[i]) \n"
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",") \n");
            }
            else {
                //"arreglo[i], "
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",", ");
            }
        }
    }
    else if (ordenado==1) {
        for(size_t i = 0; i < n; i++){
            if (n==1) {
                //"\nel arreglo ordenado es: (arreglo[i])\n";
                fprintf(fptr,"%s","el arreglo ordenado es: (");
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",")\n");
            }
            else if (i==0) {
                //"\nel arreglo ordenado es: (arreglo[i], "
                fprintf(fptr,"%s","el arreglo ordenado es: (");
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",", ");
            }
            else if (i==n-1){
                //"arreglo[i]) \n"
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",") \n");
            }
            else {
                //"arreglo[i], "
                fprintf(fptr,"%d",arreglo[i]);
                fprintf(fptr,"%s",", ");
            }
        }
    } 
}
//BLOQUE PRINCIPAL
int main(int argc, char const *argv[]){
    clock_t bbSortI, bbSortF;
    //Declaramos los argumentos como variables:
    int cantNum = atoi(argv[1]);
    int min; int max;
    //Si no se especifica un mínimo o máximo, estos serán 0 y 1000
    if (argc==2){
        min = 0;
        max = 1000;
    } 
    else if (argc==3) {
        min = atoi(argv[2]);
        max = 1000;
    }
    else {
        min = atoi(argv[2]);
        max = atoi(argv[3]);
    }
    //Llamamos a la función numerosAleatorios para crear un arreglo con números randoms.
    int* listaR=numerosAleatorios(cantNum,min,max);
    //Abrimos el archivo en el cual escribiremos los resultados:
    FILE * fptr;
    fptr = fopen ("lab4-orden.out", "a");
    //Llamamos la función cicloPrint para imprimir la función antes de ser ordenada, con un ciclo.
    printf("\nSIN ORDENAR");
    cicloPrint(listaR, cantNum);
    //Llamamos a la función bubbleSort, para que ordene el arreglo con el método burbuja.
    //Además, llamaremos a la función clock para medir el tiempo, ya que como vimos en el LAB anterior, es más precisa que time()
    bbSortI=clock();
    bubbleSort(listaR, cantNum);
    bbSortF=clock();
    //Lo escribimos en el archivo
    fprintf(fptr,"%s","BubbleSort ");
    fprintf(fptr,"%d",cantNum);
    fprintf(fptr,"%s"," ");
    fprintf(fptr,"%f",(double)(bbSortF-bbSortI)/CLOCKS_PER_SEC);
    fprintf(fptr,"%s","\n");
    //"Printeamos" el tiempo que demoró a través de la consola
    printf("\n");
	printf("bubbleSort iterativo de %d valores\n",cantNum);
	printf("clock_t bubbleSort:  %f\n",(double)(bbSortF-bbSortI)/CLOCKS_PER_SEC);
    //Llamamos a la función cicloPrint para que imprima la función con un ciclo.
    printf("\nORDENADO");
    cicloPrint(listaR, cantNum);
    //Cerramos el archivo
    fclose(fptr);
    return 0;
}