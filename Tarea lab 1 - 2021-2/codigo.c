//Importar librerias
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
//Variables globales

//Definición de funciones
int leerPrimerNum(const char* filename){ 
    //Entrada: Archivo de texto, donde el primer número (N) | Salida: Matriz NxN
    FILE *fp;
 	char buffer[100];
 	fp = fopen (filename, "r" );
 	//
 	fscanf(fp, "%s" ,buffer); //Esto solo lee la primera linea
    int valor = atoi(buffer); //Esto transforma la primera linea de str a int
    fclose(fp);

    return valor;
}
//
int* leerPlay(const char* filename, int* listaVacia){ 
    //Entrada: Archivo de texto, donde el primer número (N) | Salida: Matriz NxN
    FILE *fp;
 	const char numGeneros[2], generoElegido[2], duracionMax[20];
 	fp = fopen (filename, "r" );
 	//
 	fscanf(fp, "%s %s %s" ,numGeneros, generoElegido, duracionMax); //Por algún motivo, esto solo lee la primera linea
    int cantGeneros = atoi(numGeneros); //Esto transforma la cantidad de generos a int
    int genero = atoi(generoElegido); //Esto transforma nuestro género a int
    int duracionM=0;
    for (int i = 0, num = 0, horas = 0, minutos = 0, segundos = 0, digito = 0; i < 9; i++){
        if (num==0)//En caso de que estemos en las horas
        {   
            if (duracionMax[i]=='0')
            {
                horas = horas * 10; //si encuentra un 0, multiplicará las horas por 10
            }
            else
            {
                int x = ((int)(generoElegido[i])) - 48;//Esto le da formato de int al char
                horas = horas + (x*3600); //multiplicará el numero por 3600 (una hora)
            }
        }
        else if (num==1)//En caso de estar en miutos
        {
            if (duracionMax[i]=='0')
            {
                minutos = minutos * 10; //si encuentra un 0, multiplicará las los minutos por 10
            }
            else
            {   
                int x = ((int)(generoElegido[i])) - 48; //Esto le da formato de int al char
                minutos = minutos + (x*60); //multiplicará el numero por 60 (un minuto)
            }
        }
        else if (num==2) //En el caso de los segundos
        {
            if (duracionMax[i]=='0') //si nos encontramos un 0
            {
                if (digito==1) //Y es el segundo dígito
                {
                    segundos = segundos * 10; //multiplicará los segundos por 10
                }  
            }
            else
            {
                int x = ((int)(generoElegido[i])) - 48; //Esto le da formato de int al char
                segundos = segundos + x; //sumará los segundos a segundos
            }
            if (digito==1) //si ya es el segundo digito, suma todo a duracionM
            {
                duracionM = duracionM + segundos;
            }
            digito++;
        }
        else if (duracionMax[i]==':')//si el char es :
        {
            if (num==0) //Si estaba en las horas, pasa a los minutos
            {
                duracionM = duracionM + horas;
            }
            else if (num==1) //si estaba en minutos, pasa a segundos
            {
                duracionM = duracionM + minutos;
            }  
            num++;
        }
    }
    fclose(fp);
    
    listaVacia[0]=cantGeneros;
    listaVacia[1]=genero;
    listaVacia[2]=duracionM;printf("\n%d\n",duracionM);

    return listaVacia;
}
//
char** leerArchivoPorLinea(const char* filename, int numLineas){
    //Entrada: nombre del archivo txt | Salida: Una matriz con las lineas
    FILE *in_file = fopen(filename, "r"); 

    struct stat sb;
    stat(filename, &sb);

    char *file_contents = malloc(sb.st_size);
    int i=0;
    int c=0;

    //Esto asigna memoria para las filas de la matriz
    char ** matriz= (char **) malloc (sizeof(char *)*numLineas);
    //Este ciclo crea las columnas
    for(int c=0;c<numLineas;c++){
        matriz[c]=(char *) malloc (sizeof(char *)*numLineas);
    }

    printf("El contenido del archivo es:\n");
    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        if (i==0)
        {i++;
        printf("> %s\n", file_contents);}
        else{
            matriz[c]=file_contents;
            printf("> %s\n", matriz[c]);
            c++;
        }
    }

    fclose(in_file);
    return matriz;
}
//
char* splitStr(char* strLineal){//Entrada: un arreglo de carácteres | Salida: el str dividido en 4
    int c=0; int g=0; int d=0; int a=0; int n=0;
    char* nombreCancion;char* genero;char* duracion;char* artista;
    for (int relleno; n < strlen(strLineal); n++){ 
        if (strLineal[n]==' '){ //Cada vez que encuentre un espacio dividirá el str
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
//

//
char** cicloSplitStr(char** matriz, int N){ //Entrada una matriz y un numero N (numero de lineas de la matriz)
    for (size_t i = 0; i < N; i++){
        matriz[i]=splitStr(matriz[i]);
        printf("%s ",matriz[i][0]);printf("%s ",matriz[i][1]);printf("%s ",matriz[i][2]);printf("%s\n",matriz[i][3]);
    }
    return matriz;
}
//Bloque principal
int main(){
    //Primero, leemos el archivo listado.in con las canciones y su cantidad
    int cantCanciones=leerPrimerNum("listado.in");
    char** archivoTXT=leerArchivoPorLinea("listado.in",cantCanciones);
    //Segundo, leemos el archivo play.in con la cantidad de géneros musicales
    int * listaPlay= (int *) malloc (sizeof(int)*3);
    leerPlay("play.in", listaPlay);
    char** playIn=leerArchivoPorLinea("play.in",listaPlay[0]);
    //Luego, dividimos los str en las matrices para poder usar la información
    cicloSplitStr(archivoTXT, cantCanciones);

    //

    //

    //
    return 0;
}