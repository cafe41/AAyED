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
//DOM: str (nombre archivo) X arreglo X m (Posición donde se realizó el movimiento)
//REC: void, pero realiza un print y escribe en un archivo txt
void escribirMovimientos(const char* filename, int m, int j){
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
//DOM: arreglo (quién se sobrescribe) X arreglo (por quién se sobrescribe) X int (Hasta dónde sobrescribir) X int (dónde va nuestra m)
//REC: void
int* sobrescribirArreglo(int* arreglo1, int* arreglo2, int n, int m){
    size_t j=0;
    for (size_t i = m; i < n; i++){
        arreglo1[i]=arreglo2[j];
        j++;
    }
    return arreglo1;
}
//swapG, función que invierte las posiciones de un arreglo
//DOM: arreglo X int (cantidad de carácteres del arreglo) X int (cantidad total de carácteres del arreglo)
//REC: void
void swapG(int* arreglo, int m, int n){
    int* arreglo2 = (int *) malloc (sizeof(int *)*m);
    for (size_t i = 0; i < m; i++){
        arreglo2[i]=arreglo[m-i-1];
    }
    arreglo = sobrescribirArreglo(arreglo,arreglo2,m,0);
    escribirMovimientos(archivoSalida, m, n);
}
//subArreglo, función que divide un arreglo en una forma que sea útil para hacer el swap y sobrescribir 
//DOM: arreglo X int (x, donde inicia nuestro nuevo arreglo) X int (n)
//REC: arreglo
int* subArreglo(int* arreglo, int x, int n){
    int* arregloCorto = (int *) malloc (sizeof(int *)*(n-x));
    for (size_t i = 0; i < (n-x); i++){
        arregloCorto[i]=arreglo[i+x];
        printf("POS: %d, el numero a agregar es: %d, ",i+x,arreglo[i+x]);
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
    printf("\nlistaMayMe:");cicloPrint(listaMayMe,n);
    int m = 0; //trabajaremos con un m, que irá recorriendo la lista de mayor a menor
    //El siguiente ciclo se enfocará en ordenar el arreglo:
    while (m != n){ //mientras no hayamos ordenado hasta el último de los valores:
        printf("\nHasta el momento ");
        cicloPrint(arreglo,n);
        printf("y nuestro m es: %d\n",m);
        if (arreglo[m]==listaMayMe[m]){//si el valor "final" es igual al mayor de los números (hasta m):
            printf("\nEl numero %d esta ordenado, le sumamos 1 a m\n",listaMayMe[m]);
            m++;
        }
        else {//lo que hace la función es invertir el "que viene" de los números, para luego dar vuelta todo n-1
            for(size_t j = 0; j < n; j++){ //recorre la función de j -> n
                if (arreglo[m]==listaMayMe[m]){//movimiento 1
                    printf("\naplicamos un swap 1:"); swapG(arreglo,m+1,n-m); //swapG de 0 a m
                    cicloPrint(arreglo,n);
                    j=n;
                }
                else if (arreglo[j]==listaMayMe[m]){//movimiento 2
                    //Realmente, desconozco el por qué todo tiene que ser j+1
                    int* arregloT=subArreglo(arreglo,j+1,n);
                    printf("arregloT:"); cicloPrint(arregloT,(n));
                    printf("\naplicamos un swap 2:"); swapG(arregloT,n-m,m+1);
                    printf("arregloT swappeado:"); cicloPrint(arregloT,(n-m));
                    arreglo = sobrescribirArreglo(arreglo,arregloT,n,m);
                    cicloPrint(arreglo,n);
                    j=n;
                }
            }
        } 
    }
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
    fclose(archivo);
    return 0;
}
