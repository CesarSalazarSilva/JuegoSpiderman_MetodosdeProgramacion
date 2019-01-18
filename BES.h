#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>



int tamanio;
//BES
//------------------------------------------------------------------------------------------------------------------------------------------------------------
/*Funcion que recibe al archivo de la ciudad codificado para procesar el segmento de las filas
Entrada: puntero a un archivo/tamanio de la ciudad
Salida: matriz con las filas mostradas en el archivo*/
int ** procesarFilas(FILE * archivo, int tamanio){

	int ** filas;
	filas = (int**)malloc(sizeof(int*)*tamanio);

	//aqui se guarda la parte de las filas como matriz de enteros
	int i, j, cantEdif, cantEdifFila;
	for(i=0; i<tamanio; i++){

		//se guarda el primer numero de las filas para saber cuantos edificios hay
		fscanf(archivo, "%d ", &cantEdif);
		filas[i] = (int*)malloc(sizeof(int)*(tamanio+1));
		filas[i][0] = cantEdif;

		//creacion de la matriz de las filas
		cantEdifFila = 0;
		for(j=1; j<cantEdif+1; j++){
			 fscanf(archivo, "%d ", &filas[i][j]);
			 cantEdifFila++;
		}
	}

	int prueba;
	//parte para probar filas, cambiar el numero para no imprmir
	prueba = 1;
	if (prueba == 0){
		printf("--------------------\nPrueba Filas\n");
		for(i=0; i<tamanio; i++){
			printf("fila %d: ", i);
			for(j=0; j<tamanio+1; j++){
				printf("%d ", filas[i][j]);
			}
			printf("\n");
		}
		printf("--------------------\n");
	}

	return filas;
}

/*Funcion que procesa la segunda mitad del archivo, las partes de las columnas, 
y separa los 2 datos que entrega en 2 matrices.
Entrada: puntero a un archivo/tamanio de la ciudad/matriz de los numeros de cada edificio a rellenar/
matriz que indica cuantos edificios seguidos hay, a rellenar
Salida: void*/ 
void procesarColumnas(FILE * archivo, int tamanio, int ** colNumeros, int ** colEdifSeguidos){

	int i, j, k, aux, edifTotal;
	edifTotal = 0;
	char linea[tamanio*4+2];
	for(i=0; i < tamanio; i++){
		colNumeros[i] = (int*)malloc(sizeof(int)*tamanio);
		colEdifSeguidos[i] = (int*)malloc(sizeof(int)*tamanio);

		fgets(linea, tamanio*4+2, archivo);

		//caso de columna vacia
		if (linea[0] == '0'){
			colNumeros [i][0] = 0;
			colEdifSeguidos[i][0] = 0;
		}
		else{
			for(j=0; j < tamanio*2; j+=2){
				//caso en que solo haya 1 edificio en la columna
				if(j==0 && linea[1] != '-'){
					//truco para transformar un char del 0 al 9 en int
					aux = linea[0] - '0';
					colEdifSeguidos[i][0] = aux;
					aux = linea[2] - '0';
					colNumeros[i][0] = aux;
				}
				//caso para contar cuantos edificios seguidos hay
				else if (linea[j+1] == '-' || (j>0 && linea[j-1] == '-')){
					aux = linea[j] - '0';
					colEdifSeguidos[i][j/2] = aux;
					edifTotal += aux;

					//aqui se procesa la parte de los numeros de los edificios, para hacerlo solo 1 vez por col
					//primero se verifica que se este en el ultimo numero con guion
					if ((j>0 && linea[j-1] == '-') && (linea[j+1] == ' ')){
						//aqui se guardan los numeros de cada edificio
						for (k=0; k<edifTotal; k++){
							aux = linea[2*k+j+2] - '0';
							colNumeros[i][k] = aux;
						}
						//aqui se rellena el resto con ceros
						for (k = tamanio-1; k >= edifTotal; k--){
							colNumeros[i][k] = 0;
						}
					}

				}
				//ahora se rellena el resto con ceros para dejar una matriz cuadrada sin vacios
				else{
					colEdifSeguidos[i][j/2] = 0;
				}
			}
			edifTotal = 0;
		}
	}
	//parte para probar colNumeros, cambiar el numero para no imprmir
	int prueba;
	prueba = 1;
	if (prueba == 0){
		printf("--------------------\nPrueba colNumeros\n");
		for(i=0; i<tamanio; i++){
			for(j=0; j<tamanio; j++){
				printf("%d ", colNumeros[i][j]);
			}
			printf("\n");
		}
	printf("--------------------\n");
	}
	//parte para probar colEdifSeguidos , cambiar el numero para no imprmir
	prueba = 1;
	if (prueba == 0){
		printf("--------------------\nPrueba colEdifSeguidos\n");
		for(i=0; i<tamanio; i++){
			for(j=0; j<tamanio; j++){
				printf("%d ", colEdifSeguidos[i][j]);
			}
			printf("\n");
		}
	printf("--------------------\n");
	}
	return;
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


	//****se creara el espacio de soluciones aqui****
	//procesamiento de las filas
	int ** filas;
	filas = procesarFilas(archPuntero, *tamanio);

	//procesamiento de las columnas
	int ** colNumeros;
	int ** colEdifSeguidos;
	colNumeros = (int**)malloc(sizeof(int*)*(*tamanio));
	colEdifSeguidos = (int**)malloc(sizeof(int*)*(*tamanio));
	procesarColumnas(archPuntero, *tamanio, colNumeros, colEdifSeguidos);
	fclose(archPuntero);

	//creacion de tadas las ciudades posibles
	int *** ciudadesPosibles = (int***)malloc(sizeof(int**)*1000); 
	//RECORDAR: ver si se puede calcular esto en vez de dejar un numero al ojo

	int i, j;
		/*
	for (i = 0; i<*tamanio; i++){
		//creacion de una ciudad posible
		int ** ciudadesPosibles = (int**)malloc(sizeof(int*)*(*tamanio)); 
		for(j = 0; j< )
		if (colNumeros[i])
	}
*/
	//MATRIZ FAKEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
	//------------------------------------------------------------------------------------------------------------------------------
	//salida temporal para que corra el programa
	int** salidaWIP = (int**)malloc(sizeof(int*)*10);
	int Matris[10][10] ={
		{0,0,1,2,1,1,0,0,0,0},
		{0,0,0,2,1,0,0,0,0,0},
		{0,0,1,2,0,0,0,0,0,0},
		{0,0,0,1,1,1,2,1,0,0},
		{0,0,0,0,0,1,1,0,0,0},
		{0,0,0,1,2,1,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0},
		{0,0,1,2,2,0,0,0,0,0},
		{0,0,0,1,3,3,2,0,0,0},
		{0,0,0,0,2,2,0,0,0,0}
		};

	for (i=0; i<10; i++){
		salidaWIP[i] = (int*)malloc(sizeof(int)*10);
		for(j=0; j<10; j++){
			salidaWIP[i][j] = Matris[i][j];
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------
	//liberacion de memoria de la matriz con la primera mitad del texto
	//pofa no lo olvides xd
	for(i=0; i<*tamanio; i++){
		free(filas[i]);
	}
	free(ciudadesPosibles);
	free(filas);
	fclose(archPuntero);
	return salidaWIP;
}



//------------------------------------------------------------------------------------------------------------------------------------------------------------


int * crearconjuntosolucion(int tamano){
	int*lista = (int*)malloc(sizeof(int)*tamano);
	return lista;
}
