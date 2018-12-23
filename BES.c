#include <stdio.h>
#include <stdlib.h>

/*Funcion recursiva que le suma 1 a la combinacion actual, al menos que se llegue a su limite, en tal caso
se cambia a 0 y aplica la misma funcion a la sigiuente linea, recursivamente
Entrada: arreglo de enteros con los limites de las combinaciones, arreglo de enteros con la combinacion actual,
         entero con el tamanio de la ciudad, y un entero con la posicion actual*/
void sigCombinacion(int * combFinal, int * combActual, int tamanio, int pos){
	//caso base: el numero de la pos actual aun no llega al limite de combinaciones
	if(combFinal[pos]-1 != combActual[pos]){
		combActual[pos] += 1;
		return;
	}
	//caso recursivo: el numero de la pos actual llega a su limite, se cambia a cero y se pasa a la siguiente linea
	else{
		//primero se verifica si ya se llego al final
		if (combActual[tamanio-1] == combFinal[tamanio-1]) return;
		combActual[pos] = 0;
		//se pasa a la siguiente linea
		sigCombinacion(combFinal, combActual, tamanio, pos+1);
		return;
	}
}

/*Funcion que recibe al archivo de la ciudad codificado para procesar el segmento de las filas,
crea una matriz con los numeros y una lista de cada combinacion de cada fila
Entrada: puntero a un archivo/puntero suma total de las combinaciones/tamanio de la ciudad/lista con cada combinaicon de cada fila
Salida: matriz de enteros con las los mismos numeros de la parte de filas del archivo*/
int ** procesarFilas(FILE * archivo, double * combTotales, int cantidad, int *listCombinaciones){

	int ** filas;
	filas = (int**)malloc(sizeof(int*)*cantidad);

	//aqui se guarda la parte de las filas como matriz de enteros
	int i, j, avanzar, espaciosLibres, cantBloqEdif, cantEdifFila, combinaciones;
	avanzar = 0;
	*combTotales = 1;

	for(i=0; i<cantidad; i++){
		//se guarda el primer numero de las filas para saber cuantos bloques de edificios hay
		fscanf(archivo, "%d ", &cantBloqEdif);
		printf ("Prueba cant edificios: <%d>\n", cantBloqEdif);
		filas[i] = (int*)malloc(sizeof(int)*(cantBloqEdif+1));
		filas[i][0] = cantBloqEdif;

		//creacion de la matriz de las filas
		cantEdifFila = 0;
		for(j=1; j<cantBloqEdif+1; j++){
			 fscanf(archivo, "%d ", &filas[i][j]);
			 printf("Prueba n edif: <%d>\n", filas[i][j]);
			 cantEdifFila++;
		}

		//un cero de sobra para que se sepa cuando se termina de leer las filas
		filas[i][cantidad] = 0;

		//se calculan las combinaciones posibles de edificios por fila
		espaciosLibres = cantidad - cantEdifFila;
		//como siempre es 1 bloque de edificios seguidos, las posibles combinaciones son bastante simples:
		combinaciones = espaciosLibres+1;
		//editamos los valores de la lista de combinaciones (si, tambien cambian en las otras funciones)
		listCombinaciones[i] = combinaciones;
		//se calcula la suma total de combinaciones a hacer
		*combTotales *= combinaciones;
		printf("combinaciones de la fila: %d\n\n", listCombinaciones[i]);
	}
	printf("COMINACIONES TOTALES: %f\n", *combTotales);

	return filas;

}

//funcion que genera la matriz de la ciudad a partir de un archivo (usando busqueda en espacio de soluciones)
//Entrada: nombre del archivo y puntero del entero representando el tamanio de la ciudad
//Salida: matriz con la ciudad en el formato pedido por el enunciado
int ** generarCiudad(char * nombreArchivo, int *tamanio){
	FILE *archPuntero;
	archPuntero = fopen(nombreArchivo, "r");

	//se aborta la funcion si el archivo no se encuentra
	if (archPuntero == NULL){
		printf("Error abriendo archivo, ejecutando con ciudad vacia.\n");
		int** vacio = (int**)malloc(sizeof(int*));
		vacio[0] = (int*)malloc(sizeof(int));
		vacio[0][0] = 0;
		return vacio;
	}

	//se guarda el primer numero del archivo
	//ojo que el espacio en "%d " es importante para pasar a la siguiente linea
	fscanf(archPuntero, "%d ", tamanio);
	printf("tamanio de ciudad: %dx%d\n", *tamanio, *tamanio);


	//se creara el espacio de soluciones aqui
	//procesamiento de las filas
	int ** filas;
	double combTotales;
	int * listCombinaciones = (int*)malloc(sizeof(int)*(*tamanio));
	filas = procesarFilas(archPuntero, &combTotales, *tamanio, listCombinaciones);

	//lista que parte con ceros y representa cada combinacion de cada ciudad
	int * listCombinacionActual = (int*)malloc(sizeof(int)*(*tamanio));
	double i;
	for(i = 0; i<*tamanio; i++)	listCombinacionActual[i] = 0;

	//creacion de tadas las ciudades posibles
	int *** ciudadesPosibles = (int***)malloc(sizeof(int**)*combTotales);
	int j, k, escrituraFilas, posFilas;


	//variable con la posicion a leer de la matriz de filas
	posFilas = 1;
	//variable que dira que escribir en la fila de las ciudades
	//0: escribir ceros, 1: escribir los edificios, 2: escribir ceros
	escrituraFilas = 0;
	//ciudades
	for(i = 0; i<combTotales; i++){
		//printf("ciudad numero %d\n", i);
		ciudadesPosibles[i] = (int**)malloc(sizeof(int*)*(*tamanio));
		printf("TAATATAT\n");
		//1 ciudad
		for(j = 0; j < *tamanio; j++){
			ciudadesPosibles[i][j] = (int*)malloc(sizeof(int)*(*tamanio));
			//1 fila de 1 ciudad
			for (k = 0; k < *tamanio; k++){

				if (k == listCombinacionActual[j])
					escrituraFilas = 1;

				if (escrituraFilas == 0) {
					ciudadesPosibles[i][j][k] = 0;
				}

				if (escrituraFilas == 1){
					if (filas[j][posFilas] == 0)
						escrituraFilas = 2;
					else{
						ciudadesPosibles[i][j][k] = filas[j][posFilas];
						posFilas++;
					}
				}

				if (escrituraFilas == 2)
					ciudadesPosibles[i][j][k] = 0;
				
				
				printf("%d ", ciudadesPosibles[i][j][k]);
			}
			escrituraFilas = 0;
			posFilas = 1;
			printf("\n");
		}
		//esta funcion hace que se pase a la siguiente combinatoria
		sigCombinacion(listCombinaciones, listCombinacionActual, *tamanio, 0);
		printf("\n");
	}


	//salida temporal para que corra el programa, una matriz 5x5 rellena con 0-24 en orden
	int** salidaWIP = (int**)malloc(sizeof(int*)*5);
	int numero;
	numero=0;
	printf("Matriz:\n");
	for (i=0; i<5; i++){
		salidaWIP[i] = (int*)malloc(sizeof(int)*5);
		for(j=0; j<5; j++){
			salidaWIP[i][j] = numero;
			printf("%d ", salidaWIP[i][j]);
			numero++;
		}
		printf("\n");
	}

	//liberacion de memoria de la matriz con la primera mitad del texto
	//pofa no lo olvides xd
	for(i=0; i<*tamanio; i++){
		free(filas[i]);
	}
	for (i=0; i<1000; i++){
		for (j = 0; j < *tamanio; ++j){
			free(ciudadesPosibles[i][j]);
		}
		free(ciudadesPosibles[i]);
	}
	free(ciudadesPosibles);
	free(filas);
	fclose(archPuntero);
	return salidaWIP;
}


int main(){
	int ** ciudad;
	int tamanio;
	ciudad = generarCiudad("entrada.txt", &tamanio);
	printf("COSA en main: <%d>\n", ciudad[0][0]);
	
	//liberacion de la memoria usada por la matriz
	int i;
	for(i=0; i<5; i++){//CAMBIAR EL 5 CUADNO LA CIUDAD SE DEVUELVA BIEN
		free(ciudad[i]);
	}
	free(ciudad);

	return 0;

}

//no olvidar:
//arreglar el 5 del ultimo free