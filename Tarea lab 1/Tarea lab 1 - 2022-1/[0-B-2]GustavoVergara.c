//Tarea 1 del laboratorio
//NOMBRE: GUSTAVO VERGARA
//SECCIÓN: 0-B-2

//Importación de librerías

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

//Variables Globales

//Escribiré los nombres de archivos como variables globales, para ahorrarme problemas de código
const char* archivoEntrada;
const char* archivoSalida;

//Definición de funciones

//bubbleSort, función que ordena con el método de burbuja
//DOM: arreglo X int (n = tamaño del arreglo)
//REC: arreglo "ordenado"
//PD: reciclé esta función del lab S4
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
//leerPrimerNumero, función que lee el primer número del archivo y lo trasnforma en una variable
//DOM: FILE (filename)
//REC: int (n, la cuál se refiere al número de pizzas que hay en el "archivo")
int leerPrimerNumero(){
    FILE *fp;
    fp = fopen ( "Entrada.in", "r" );
    char buffer[100];
    
    fscanf(fp, "%s" ,buffer); //Esto solo lee la primera linea
    int valor = atoi(buffer); //Esto transforma la primera linea de str a int

    fclose ( fp );
    return valor;
}
//leerArchivoPorNumero, función que lee el archivo por cada número dentro de él y lo agrega a una arreglo.
//DOM: FILE (filename) x arreglo
//REC: arreglo con los números del archivo dentro
//PD : reciclé esta función de un lab de métodos de estudio que hice
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
    int f=0;

    while (fscanf(in_file, "%[^\n ] ", file_contents) != EOF) {
        if (f==0){f++;}
        else {
        arreglo[i]=atoi(file_contents);
        i++;
        } 
    }

    fclose(in_file);
    return arreglo;
}
//escribirMovimientos, función que escribe los movimientos al archivo de texto y también los "imprime" por consola
//DOM: str (nombre archivo) X int (m) X int (j) (Posición donde se realizó el movimiento)
//REC: void, pero realiza un print y escribe en un archivo txt
void escribirMovimientos(const char* filename, int j){
    FILE* archivo = fopen(filename, "a");
    printf(" V(%d)->",(j));
    fprintf(archivo,"%d",(j));
    fprintf(archivo,"%s"," ");
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
//sobrescribirArreglo, función que sobrescribe los valores de un arreglo por otros
//DOM: arreglo (quién se sobrescribe) X arreglo (por quién se sobrescribe) X int (desde dónde sobrescribir) X int (Hasta dónde sobrescribir) 
//REC: void
int* sobrescribirArreglo(int* arreglo1, int* arreglo2, int x, int n){
    size_t j=0;
    for (size_t i = x; i < n; i++){
        arreglo1[i]=arreglo2[j];
        j++;
    }
    free(arreglo2); //Liberamos la memoria del "arreglo2"
    return arreglo1;
}
//swapG, función que sobrescribe un arreglo sobre otro
//DOM: arreglo X int (cantidad de carácteres del arreglo) X int (cantidad total de carácteres)
//REC: void
void swapG(int* arreglo, int c, int n){
    int* arreglo2 = (int *) malloc (sizeof(int *)*(n-c));
    int j = 0;
    for (size_t i = n-1; i+1 > c; i=i-1){
        arreglo2[j]=arreglo[i];
        j++;
    }
    arreglo = sobrescribirArreglo(arreglo,arreglo2,c,n);
    free(arreglo2); //Liberamos la memoria del "arreglo2"
    escribirMovimientos(archivoSalida, c+1);
}
//subArreglo, función que divide un arreglo en una forma que sea útil para hacer el swap y sobrescribir 
//DOM: arreglo X int (x, donde inicia nuestro nuevo arreglo) X int (n)
//REC: arreglo
int* subArreglo(int* arreglo, int x, int n){
    int* arregloCorto = (int *) malloc (sizeof(int *)*(n));
    int j = 0;
    for (size_t i = n-1; i+1 > x; i=i-1){
        arregloCorto[j]=arreglo[i];
        j++;
    }
    return arregloCorto;
}
//isOrdenado, función que retorna un 1 si el arreglo está ordenado de mayor a menor, o un 0 si no lo está
//DOM: arreglo x int (n)
//REC: "Boolean" (1 = true, 0 = false)
//PD: Terminé no usando esta función porque era redundante
int isOrdenado(int* arreglo, int n){
    for (size_t i = 0; i < n-1; i++){
        if (arreglo[i] > arreglo[i+1]){
            return 0;
        }
    }
    return 1;
}
//crearListaOrdenada, función que crea una lista ordenada (para no ensuciar funcOrden)
//DOM: arreglo X n (largo arreglo original)
//REC: arreglo
int* crearListaOrdenada(int* arreglo, int n){
    int* listaMayMe = (int *) malloc (sizeof(int *)*n);
    int* arregloC = (int *) malloc (sizeof(int *)*n);
    for (size_t i = 0; i < n; i++){ arregloC[i]=arreglo[i]; }
    arregloC = bubbleSort(arregloC, n);
    for (size_t i = 0; i < n; i++){ listaMayMe[i]=arregloC[n-i-1]; }
    return listaMayMe;
}
//funcOrden, función que en base a varias preguntas, ordena un arreglo al "intercambiar" ciertas partes
//DOM: arreglo X int (n)
//REC: arreglo (ordenado)
int* funcOrden(int* arreglo, int n){
    //Trabajaremos con la lista ordenada, para ver qué número es el siguiente que buscamos ordenar
    int* listaMayMe = crearListaOrdenada(arreglo, n);
    int m = 0; //trabajaremos con un m, que irá recorriendo la lista de mayor a menor
    //El siguiente ciclo se enfocará en ordenar el arreglo:
    while (m != n){ //mientras no hayamos ordenado hasta el último de los valores:
        printf("\nHasta el momento ");
        cicloPrint(arreglo,n);
        if (arreglo[m]==listaMayMe[m]){//si el valor "final" es igual al mayor de los números (hasta m):
            printf("\nEl numero %d esta ordenado\n",listaMayMe[m]);
            m++;
        }
        else {//lo que hace la función es invertir el "que viene" de los números, para luego dar vuelta todo n-1
            for(size_t j = n; j > m; j=j-1){ //recorre la función de j -> n
                if (arreglo[n-1]==listaMayMe[m]){//movimiento 1
                    swapG(arreglo,m,n); //swapG de m a n 
                    cicloPrint(arreglo,n);
                    j=n;
                }
                else if (arreglo[j]==listaMayMe[m]){//movimiento 2
                    int* arregloT=subArreglo(arreglo,n-j,n);
                    printf("\nsi invertimos el arreglo desde %d",listaMayMe[m]); cicloPrint(arregloT,(n-j));
                    arreglo = sobrescribirArreglo(arreglo,arregloT,j,n);
                    escribirMovimientos(archivoSalida, j+1);
                    cicloPrint(arreglo,n);
                    j=n;
                }
            }
        } 
    }
    free(listaMayMe);
    return arreglo;
}

//BLOQUE PRINCIPAL
int main(int argc, char const *argv[]){
    archivoEntrada = argv[1]; if (argc < 3){
        printf("Debe especificar un archivo de Entrada y otro de Salida.\n\n");}
    archivoSalida = argv[2];
    //Leemos el primer número del archivo con la función leerPrimerNumero
    int n = leerPrimerNumero();
    //Creamos un arreglo para ingresar los datos del archivo
    int* arreglo = (int *) malloc (sizeof(int *)*n);
    arreglo = leerArchivoPorNumero(archivoEntrada,arreglo);
    printf("Segun el archivo, la cantidad de pizzas que hay es: %d", n);
    //Reiniciamos el archivo de salida
    FILE* archivo = fopen(archivoSalida, "w");
    //Llamamos a nuestra gran función que ordena el arreglo:
    arreglo = funcOrden(arreglo,n);
    cicloPrint(arreglo, n);
    //No necesitamos el arreglo para el archivo de salida, por lo que es mejor liberarlo
    free(arreglo); 
    //Luego de escribir los movimientos del algoritmo en el archivo de Salida, 
    //terminamos escribiendo un "0" que simboliza el fin
    escribirMovimientos(archivoSalida, 0);
    //Cerramos el archivo abierto y liberamos la memoria que lo contenía.
    fclose(archivo); free(archivo);
    //Fin del programa
    printf("\n\nFin del programa, puede revisar los resultado en el archivo de salida\n");
    return 0;
}