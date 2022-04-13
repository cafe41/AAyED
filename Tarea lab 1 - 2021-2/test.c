#include <string.h>
#include <stdlib.h>
#include <stdio.h>
char* splitStr(char* strLineal){//Entrada: un arreglo de carácteres | Salida: el str dividido en 4
    int c=0; int g=0; int d=0; int a=0; int n=0;
    char* nombreCancion;char* genero;char* duracion;char* artista;
    for (int relleno; n < strlen(strLineal); n++){ 
        if (strLineal[n]==" "){ //Cada vez que encuentre un espacio dividirá el str
            if (c==0){ //El primero es desde el inicio hasta n (n es el numero del ciclo)
                char *nombreCancion = malloc(n * sizeof(char));
                memcpy(nombreCancion, strLineal, n * sizeof(int));
                c=1; // C cambia a 1, para que no divida por cancion denuevo
            }
            else if (g==0){ //El segundo es un str de 1 caracter, con el numero del género
                char *genero = malloc(1 * sizeof(char));
                memcpy(genero, strLineal + n, 1 * sizeof(int));
                g=1; //G cambia a 1, para que no se divida por género denuevo
            }
            else if (d==0){ //El tercero es un str de 4 caracteres, con la duración de la canción 0:00
            //PD: se espera que ninguna dure más de 10 minutos
                char *duracion = malloc(4 * sizeof(char));
                memcpy(duracion, strLineal + n, 4 * sizeof(int));
                d=1; //D cambia a 1, para que no se divida por duración denuevo
            }
            else if (a==0){ //El cuarto es el nombre del artista, con cierto tamaño específico
                //El tamaño del arreglo será el tamaño total del arreglo a cortar - el lugar donde se encontró el espacio
                int tamano= strlen(strLineal) - n;
                char *artista = malloc(tamano * sizeof(char));
                memcpy(artista, strLineal + n, tamano * sizeof(int));
                a=1; //A cambia a 1 para que no se divida por el artista denuevo
            }
        }
    }
    //Agregamos todo al arreglo
    strLineal[0]=nombreCancion[0];
    strLineal[1]=genero[0];
    strLineal[2]=duracion[0];
    strLineal[3]=artista[0];

    return strLineal;
}

char* splitStr2(char* strLineal, int N){
    for (size_t i = 0; i < N; i++){
        char* Arreglo = (char *) malloc (sizeof(char *)*4);
        for (size_t i = 0; i < strlen(strLineal); i++){
            if (strLineal[i]!=' ')
            {
                Arreglo = Arreglo + strLineal[i];
            }
            else if (strLineal[i]==' ')
            {
                /* code */
            }

        }
    }
    

}

int main(int argc, char const *argv[])
{
    int c=0;

    //Esto asigna memoria para las filas de la matriz
    char ** matriz= (char **) malloc (sizeof(char *)*4);
    //Este ciclo crea las columnas
    for(int c=0;c<36;c++){
        matriz[c]=(char *) malloc (sizeof(char *)*36);
    }

    char* A=(char *) malloc (sizeof(char *)*36);
    A[0]="Rude 4 3:44 MAGIC!";
    matriz[0]=A[0];

    splitStr(A);
    printf(A[0]);
    printf(A[1]);
    printf(A[2]);
    printf(A[3]);


    return 0;
}
