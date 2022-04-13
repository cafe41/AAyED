// Lab semana 2  
// Fibonacci _time _clock

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	int num=0;
	int fiboi=0;
	int fibor=0;
	time_t tiniIt, tfinIt, tiniRe, tfinRe;
	clock_t ciniIt, cfinIt, ciniRe, cfinRe;
	
	num=atoi(argv[1]);
	
	tiniIt=time(NULL);
	//fiboi=llamada a funcion iterativa
	tfinIt=time(NULL);
	
	printf("time_t iterativo\n");
	printf("Fib Iterativo secuencia %d : %d\n",num, fiboi); 
	printf("time_t iterativo:  %f\n",difftime(tfinIt, tiniIt));

	tiniRe=time(NULL);
	//fibor=llamada a funcion recursiva
	tfinRe=time(NULL);

	printf("time_t recursivo\n");
	printf("Fib Recursivo secuencia %d : %d\n",num, fibor); 
	printf("time_t recursivo:  %f\n",difftime(tfinRe, tiniRe));
	
	ciniIt=clock();
	//fiboi=llamada a funcion iterativa
	cfinIt=clock();
		
	ciniRe=clock();
	//fibor=llamada a funcion recursiva
	cfinRe=clock();
	
	printf("clock_t iterativo\n");
	printf("Fib Iterativo secuencia %d : %d\n",num, fiboi); 
	printf("clock_t iterativo:  %f\n",(double)(cfinIt-ciniIt)/CLOCKS_PER_SEC);
	
	printf("clock_t recursivo\n");
	printf("Fib Recursivo secuencia %d : %d\n",num, fibor); 
	printf("clock_t recursivo:  %f\n",(double)(cfinRe-ciniRe)/CLOCKS_PER_SEC);
	
	
	return 0;	
}
