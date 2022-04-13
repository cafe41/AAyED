#include <stdio.h>
#include <stdlib.h>

int* numerosAleatorios(int n, int x, int y){
	
	int arr[n];
	int i = 0;
	int num;
	while(i < n){
		num = (rand() % (y - x + 1)) + x;
		arr[i] = num;
		i = i + 1;
	}
	
	i = 0;
	while(i < n){
		printf("%i ", arr[i]);
		i = i + 1;
	}
    return arr;
}

void bubbleSort(int* arreglo, int num){
    for (int i = 0; i < num; i++)
    {
        /* code */
    }
    
}

int main(int argc, char* argv[]){
	
    int x = 0;
    int y = 1000;
    int n = atoi(argv[1]);
    if (argc==3){
		x = atoi(argv[2]);
		y = atoi(argv[3]);
		}	
	
	int* numRandom = numerosAleatorios(n, x, y);

    bubbleSort(numRandom, n);
	
	return 0;
}