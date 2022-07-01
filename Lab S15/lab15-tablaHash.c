#include <stdio.h>
#include <stdlib.h>
#include "TDAtablaHash.h"

int main() {
	//Instanciamos la tablaHashCerrada
	TDAtablaHashCerrada* tablita = crearHashCerrada(7);

	//Aplicamos las operaciones que nos piden:
	//En el insertar se repite el dato y la llave, pues en el ejemplo solo nos dan uno
	//Y la entrada de la función "insertarHashCerrado" está definida como un arbol, un dato y una llave.
	insertarHashCerrado(tablita,30,30); //a)
	insertarHashCerrado(tablita,43,43); //b)
	insertarHashCerrado(tablita,11,11); //c)
	insertarHashCerrado(tablita,16,16); //d)
	insertarHashCerrado(tablita,51,51); //e)
	eliminarHashCerrado(tablita,16);    //f)
	insertarHashCerrado(tablita,47,47); //g)
	insertarHashCerrado(tablita,21,21); //h)
	eliminarHashCerrado(tablita,47);    //i)
	eliminarHashCerrado(tablita,11);    //j)
	insertarHashCerrado(tablita,17,17); //k)
	eliminarHashCerrado(tablita,21);    //l)

	//Mostramos la tabla resultante:
	mostrarTablaHashCerrado(tablita);

	return 0;
}


