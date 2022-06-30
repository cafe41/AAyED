#include <stdio.h>
#include <stdlib.h>
#include "TDAaAVL.h"

int main() {
	//Primero, asignamos memoria y nodos al arbol para crearlo:
	TDAarbolAVL* arbolAVL=crearAVLVacio();
	insertarNodoAVL(arbolAVL,20);
	insertarNodoAVL(arbolAVL,5);
	insertarNodoAVL(arbolAVL,10);
	insertarNodoAVL(arbolAVL,15);
	insertarNodoAVL(arbolAVL,12);
	recorridoInordenAVL(arbolAVL);
	printf("\n");

	//Chequeamos el balance de cada nodo 
	//(La posición de los nodos la conseguí a base de ensayo y error)
	printf("Chequeo de balances (1 = true, 0 = false)\n"); int esBalanceado;
	//Balance para 20
	esBalanceado = esBalanceadoNodoAVL(arbolAVL,arbolAVL->inicio);
	printf("Esta balanceado el nodo? R: %d\n\n",esBalanceado);
	//Balance para 5
	esBalanceado = esBalanceadoNodoAVL(arbolAVL,arbolAVL->inicio->hijoIzquierdo);
	printf("Esta balanceado el nodo? R: %d\n\n",esBalanceado);
	//Balance para 10
	esBalanceado = esBalanceadoNodoAVL(arbolAVL,arbolAVL->inicio->hijoIzquierdo->hijoDerecho);
	printf("Esta balanceado el nodo? R: %d\n\n",esBalanceado);
	//Balance para 15
	esBalanceado = esBalanceadoNodoAVL(arbolAVL,arbolAVL->inicio->hijoIzquierdo->hijoDerecho->hijoDerecho);
	printf("Esta balanceado el nodo? R: %d\n\n",esBalanceado);
	//Balance para 12
	esBalanceado = esBalanceadoNodoAVL(arbolAVL,
					arbolAVL->inicio->hijoIzquierdo->hijoDerecho->hijoDerecho->hijoIzquierdo);
	printf("Esta balanceado el nodo? R: %d\n\n",esBalanceado);

	recorridoInordenAVL(arbolAVL);printf("\n");

	//Balanceos
	while (esBalanceadoNodoAVL(arbolAVL,arbolAVL->inicio) != 1){//Mientras el arbolAVL no esté balanceado:
		recuperarBalanceAVL(arbolAVL,arbolAVL->inicio->hijoIzquierdo->hijoDerecho->
		hijoDerecho->hijoIzquierdo); //Recorrerá hasta el nodo más bajo (caso específico)
	}
	printf("El arbol esta balanceado\n");
	
	printf("\n");recorridoInordenAVL(arbolAVL);


	printf("\nFIN\n");
	return 0;
}


