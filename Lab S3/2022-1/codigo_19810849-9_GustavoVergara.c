// Lab semana 3  
// Fibonacci _time _clock

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Función recursiva de fibonacci
int fiboRecursiva(int n){
    if (n==0){
        return 0;
    }
    if (n==1){
        return 1;
    }
	return fiboRecursiva(n-1) + fiboRecursiva(n-2); //Si no me equivoco, su O(2^n)
}
//Función iterativa de fibonacci
int fiboIterativa(int n){ //"hasta x=num"
	int fibonacci = 0;
	int fibonacci2 = 1; 
	int temp = 0;
	for(int i = 0; i < n; i++){
		temp = fibonacci;
		fibonacci = fibonacci2;
		fibonacci2 = fibonacci2 + temp;
	}
	return fibonacci; //O(n), T()= 3 + 3n 
}
//
int main(int argc, char *argv[]){
	int num=0;
	int fiboi=0;
	int fibor=0;
	time_t tiniIt, tfinIt, tiniRe, tfinRe;
	clock_t ciniIt, cfinIt, ciniRe, cfinRe;
	
	num=atoi(argv[1]);
	
	tiniIt=time(NULL);
	fiboi=fiboIterativa(num);
	tfinIt=time(NULL);
	
	printf("time_t iterativo\n");
	printf("Fib Iterativo secuencia %d : %d\n",num, fiboi); 
	printf("time_t iterativo:  %f\n",difftime(tfinIt, tiniIt));

	tiniRe=time(NULL);
	fibor=fiboRecursiva(num);
	tfinRe=time(NULL);

	printf("time_t recursivo\n");
	printf("Fib Recursivo secuencia %d : %d\n",num, fibor); 
	printf("time_t recursivo:  %f\n",difftime(tfinRe, tiniRe));
	
	ciniIt=clock();
	fiboi=fiboIterativa(num);
	cfinIt=clock();
		
	ciniRe=clock();
	fibor=fiboRecursiva(num);
	cfinRe=clock();
	
	printf("clock_t iterativo\n");
	printf("Fib Iterativo secuencia %d : %d\n",num, fiboi); 
	printf("clock_t iterativo:  %f\n",(double)(cfinIt-ciniIt)/CLOCKS_PER_SEC);
	
	printf("clock_t recursivo\n");
	printf("Fib Recursivo secuencia %d : %d\n",num, fibor); 
	printf("clock_t recursivo:  %f\n",(double)(cfinRe-ciniRe)/CLOCKS_PER_SEC);
	
	return 0;	
	//Podemos comprobar que clock_t es mucho más preciso que time_t, que simplemente nos da un entero, mientras clock nos da un decimal
}
