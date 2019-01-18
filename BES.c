#include <stdio.h>
#include <stdlib.h>

//definición de variable global
int tamanio;


/*Funcion recursiva que le suma 1 a la combinacion actual, al menos que se llegue a su limite, en tal caso
se cambia a 0 y aplica la misma funcion a la sigiuente linea, recursivamente
Entrada: arreglo de enteros con los limites de las combinaciones, arreglo de enteros con la combinacion actual,
         entero con el tamanio de la ciudad, un entero con la posicion actual,
         y un entero que indica con que columna debe partir el espacio solucion*/
void sigCombinacion(int * combFinal, int * combActual, int tamanio, int pos, int colInicial){
	//caso base: el numero de la pos actual aun no llega al limite de combinaciones
	if(combFinal[pos]-1 != combActual[pos]){
		combActual[pos] += 1;
		return;
	}
	//caso recursivo: el numero de la pos actual llega a su limite, se cambia a cero y se pasa a la siguiente linea
	else{
		//primero se verifica si ya se llego al final
		if (combActual[tamanio-1] == combFinal[tamanio-1]) return;
		combActual[pos] = colInicial;
		//se pasa a la siguiente linea
		sigCombinacion(combFinal, combActual, tamanio, pos+1, colInicial);
		return;
	}
}

/* Funcion que calcula el factorial de un entero positivo
Entrada: un numero entero
Salida: el factorial de la entrada*/
double factorial(int a){
    int i;
    double resultado = 1;
    if (a>0){
        for (i=1; i<=a; ++i){
            resultado *= i;
        }
    }
    return resultado;
}


/* Funcion que calcula las posibles combinaciones de b elementos en a espacios ordenados
Entrada: numeros a y b que se quieren combinar de la manera "a sobre b"
Salida: numero entero con el resultado de dicha combinacion*/
int combinaciones(int a, int b){
    int resultado;
    /*resultado = a!/(b!(a-b)!*/
    double numerador, denominador;
    numerador = factorial(a);
    denominador = factorial(b)*factorial(a-b);
    resultado = numerador/denominador;
    return resultado;
}

/*Funcion que recibe al archivo de la ciudad codificado para procesar el segmento de las filas
Entrada: puntero a un archivo/tamanio de la ciudad
Salida: matriz con las filas mostradas en el archivo*/
int ** procesarFilas(FILE * archivo, long int * combTotales, int tamanio, int *listCombinaciones){

	int ** filas;
	filas = (int**)malloc(sizeof(int*)*tamanio);
	*combTotales = 1;

	//aqui se guarda la parte de las filas como matriz de enteros
	int i, j, cantEdif, cantEdifFila, espaciosLibres, combinaciones;

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
		for(j = cantEdif+1; j<tamanio+1; j++){
			filas[i][j] = 0;
		}

		//se calculan las combinaciones posibles de edificios por fila
		espaciosLibres = tamanio - cantEdifFila;
		//como siempre es 1 bloque de edificios seguidos, las posibles combinaciones son bastante simples:
		combinaciones = espaciosLibres+1;
		//editamos los valores de la lista de combinaciones (si, tambien cambian en las otras funciones)
		listCombinaciones[i] = combinaciones;
		//se calcula la suma total de combinaciones a hacer
		*combTotales *= combinaciones;
		//printf("combinaciones de la fila: %d\n\n", listCombinaciones[i]);
	}

	int prueba;
	//parte para probar filas, cambiar el numero para no imprmir
	prueba = 0;
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
			for (j=0; j < tamanio; j++){
				colNumeros [i][j] = 0;
				colEdifSeguidos[i][j] = 0;
			}
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
	prueba = 0;
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
	prueba = 0;
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

/*Función que mejora la posición de partida de la lista de combinaciones y la lista de combinación actual,
además asigna una variable que recuerda la columna de la que se debe partir la combinatoria
Entrada: lista de combinaciones finales, lista de combinación actual, matriz de restricción de columnas, entero col
Salida: void*/
void mejorarComb(int * combFinal, int * combPartida, int ** restriccion, int *primeraCol, int *ultimaCol, int tamanio){
	int probarFunc = 1;
	int i;

	if(probarFunc == 0){
		printf("-----------------------PRE FUNCION-----------------------\n");
		printf("Comb Actual:\n");
		for(i = 0; i<tamanio; i++){
			printf("%d ", combPartida[i]);
		}
		printf("\nComb Final:\n");
		for(i = 0; i<tamanio; i++){
			printf("%d ", combFinal[i]);
		}
	}

	printf("\n");
	//caso para la columna de la que empieza
	*primeraCol = 0;
	if (restriccion[0][0] == 0){
		for(i = 1; i<tamanio; i++){
			if(restriccion[i][0] != 0){
				*primeraCol = i;
				i = tamanio;

			}
		}
	}
	else *primeraCol = 0;
	for(i = 0; i<tamanio; i++){
		combPartida[i] = *primeraCol;
	}
	//caso para la columna final
	*ultimaCol = 0;
	if(restriccion[tamanio-1][0] == 0){
		for(i = tamanio-1; i>=0; i--){
			if(restriccion[i][0] != 0){
				*ultimaCol = i;
				i = -1;
			}
		}
	}
	else *ultimaCol = tamanio-1;
	for(i = 0; i<tamanio; i++){
		combFinal[i] -= tamanio + - 1 - *ultimaCol;
	}

	if(probarFunc == 0){
		printf("-----------------------POST FUNCION----------------------\n");
		printf("primeraCol: <%d>\n", *primeraCol);
		printf("posFinal: <%d>\n", *ultimaCol);
		printf("Comb Actual:\n");
		for(i = 0; i<tamanio; i++){
			printf("%d ", combPartida[i]);
		}
		printf("\nComb Final:\n");
		for(i = 0; i<tamanio; i++){
			printf("%d ", combFinal[i]);
		}
		printf("\n");
	}
	return;
}

/*Función que verifica si ya se procesaron todas las ciudades posibles
Entrada: matriz con una ciudad, tamanio de la ciudad, columna final
Salida: 0 si se llegó a la última combinación, 1 en el caso contrario*/
int verificarFinComb(int ** ciudad, int tamanio, int ultimaCol){
	int i;
	int fin = 0;
	for(i = 0; i < tamanio; i++){
		if (ciudad[i][ultimaCol] == 0){
			fin = 1;
			i = tamanio; 
		}
	}
	//caso en que se llega a la ultima combinacion
	if (fin == 0){
		return 1;
	}
	//caso en que aun no se llega al final
	else {
		return 0;
	}
}

/*Función que verifica si la ciudad es válida usando las condiciones de edificios seguidos que cada columna tiene
*/
int verifCiudadValidaCol(int ** ciudadActual, int ** restriccion, int tamanio){
	//primero se hace una copia de la ciudad actual editarla
	int ** ciudadCopia = (int**)malloc(sizeof(int*)*tamanio);
	int i, j;

	for(i = 0; i<tamanio; i++){
		ciudadCopia[i] = (int*)malloc(sizeof(int)*tamanio);
		for(j = 0; j<tamanio; j++){
			ciudadCopia[i][j] = ciudadActual[i][j];
		}
	}

	//valida = 0 para ciudad válida, valida = 1 para ciudad inválida
	int valida = 0;
	int seguidos, contadorEdifSeg;
	//r = restricción, c = ciudad
	int ri, rj, ci, cj;
	for(ri = 0; ri < tamanio; ri++){
		for(rj = 0; rj < tamanio; rj++){
			seguidos = restriccion[ri][rj];
			contadorEdifSeg = 0;
			//aquí se revisará si la ciudad es válida con el "seguidos"
			for(ci = 0; ci<tamanio; ci++){
				//printf("filaR, colR, colC, seguidos, contadorEdifSeg: %d %d %d %d %d ", ri, rj ,ci, seguidos, contadorEdifSeg);
				//printf("ciudadCopia[ci][ri]:  %d\n", ciudadCopia[ci][ri]);
				//ri = columna actual de la ciudad
				//si la columna tiene restricción de vacía, se omite
				if(seguidos == 0){
					ci = tamanio; 
					rj = tamanio;
					break;
				}
				//se revisan ahora los edificios seguidos
				else{
					if(ciudadCopia[ci][ri] != 0){
						contadorEdifSeg += 1;
					}
					else if(ciudadCopia[ci][ri] == 0 && contadorEdifSeg !=0){
						//los edificios seguidos que deberían haber no calzan conlas restricciones
						if (seguidos!=contadorEdifSeg){
							valida = 1;
							ri = tamanio;
							rj = tamanio;
							ci = tamanio;
						}
						//se pasa a la siguiente restricción y se reinicia el contador de edificios seguidos
						ci = tamanio;
						contadorEdifSeg = 0;
						break;
					}
				}
				//se borra el edificio ya que ya fue procesado y así no estorbará en la siguiente iteración
				ciudadCopia[ci][ri] = 0;


			}

			//si ya se leyó un cero, pasamos a la siguiente fila inmediatamente para ahorrar procesos
			if (seguidos == 0) rj == tamanio;

		}
	}


	//liberación de memoria de la copia
	for(i = 0; i<tamanio; i++){
		free(ciudadCopia[i]);
	}
	free(ciudadCopia);
	//caso en que la ciudad no es invalidada
	if (valida == 0){
		return valida;
	}
	//caso en que la ciudad SI ES inválida
	else return valida;
}

/*Función que genera la matriz de la ciudad a partir de un archivo (usando busqueda en espacio de soluciones)
Entrada: nombre del archivo y puntero del entero representando el tamanio de la ciudad
Salida: matriz con la ciudad en el formato pedido por el enunciado*/
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


	//procesamiento de las filas
	int ** filas;
	long int combTotales;
	int * listCombinaciones = (int*)malloc(sizeof(int)*(*tamanio));
	filas = procesarFilas(archPuntero, &combTotales, *tamanio, listCombinaciones);

	//procesamiento de las columnas
	int ** colNumeros;
	int ** colEdifSeguidos;
	colNumeros = (int**)malloc(sizeof(int*)*(*tamanio));
	colEdifSeguidos = (int**)malloc(sizeof(int*)*(*tamanio));
	procesarColumnas(archPuntero, *tamanio, colNumeros, colEdifSeguidos);
	fclose(archPuntero);

	//----ESPACIO SOLUCIÓN----
	//lista que parte con ceros y representa cada combinacion de cada ciudad
	int * listCombinacionActual = (int*)malloc(sizeof(int)*(*tamanio));
	long int i;
	for(i = 0; i<*tamanio; i++)	listCombinacionActual[i] = 0;

	//funcion para que se ignoren las columnas de ceros en el espacio solucion
	int primeraColUsar, ultimaColUsar;
	mejorarComb(listCombinaciones, listCombinacionActual, colNumeros, &primeraColUsar, &ultimaColUsar, *tamanio);

	//creacion de tadas las ciudades posibles
	int *** ciudadesPosibles = (int***)malloc(sizeof(int**)*1000); 
	//RECORDAR: ver si se puede calcular esto en vez de dejar un numero al ojo

	int j, escrituraFilas;
	//este contador avanza solo cuando la ciudad actual se verifica válida usando las pista de columnas
	int contador = 0;
	int primeraVez = 0;
	//variable con la posicion a leer de la matriz de filas
	int posFilas = 1;
		
	do{

		//si la ciudad actual no es válida, se sobreescribirá ya que este contador no avanzará
		if (primeraVez != 0 && verifCiudadValidaCol(ciudadesPosibles[contador], colEdifSeguidos, *tamanio) == 0){
			contador++;
		}

		printf("ciudad numero: %d\n", contador);
		ciudadesPosibles[contador] = (int**)malloc(sizeof(int*)*(*tamanio));
		//1 ciudad
		for(i = 0; i < *tamanio; i++){
			ciudadesPosibles[contador][i] = (int*)malloc(sizeof(int)*(*tamanio));
			if (primeraVez == 0){
				for(j = 0; j<*tamanio; j++){
					ciudadesPosibles[contador][i][j] = 0;
				}
			}
			//1 fila de 1 ciudad
			for (j = 0; j < *tamanio; j++){

				//para verificar si se debe seguir escribiendo ceros
				if (j == listCombinacionActual[i])
					escrituraFilas = 1;
				//donde se escriben los ceros a la izquierda de la fila
				if (escrituraFilas == 0)
					ciudadesPosibles[contador][i][j] = 0;	
				//donde se escriben los numeros de los edificios en la fila
				if (escrituraFilas == 1){
					if (filas[i][posFilas] == 0)
						escrituraFilas = 2;
					else{
						ciudadesPosibles[contador][i][j] = filas[i][posFilas];
						posFilas++;
					}
				}
				//donde se escriben los ceros a la derecha de la fila
				if (escrituraFilas == 2)
					ciudadesPosibles[contador][i][j] = 0;


				//printf("%d ", ciudadesPosibles[contador][i][j]);
			}
			escrituraFilas = 0;
			posFilas = 1;
			//printf("\n");
		}
		//esta funcion hace que se pase a la siguiente combinatoria
		sigCombinacion(listCombinaciones, listCombinacionActual, *tamanio, 0, primeraColUsar);
		//printf("\n");
		primeraVez = 1;

	}while(verificarFinComb(ciudadesPosibles[contador], *tamanio, ultimaColUsar) == 0);

	printf("Prueba espacio soluciones:\n");
	int k;
	for(i = 0; i <= contador; i++){
		for(j = 0; j<*tamanio; j++){
			for(k = 0; k<*tamanio; k++){
				printf("%d ", ciudadesPosibles[i][j][k]);
			}
		printf("\n");
		}
	printf("\n\n");
	}

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

	//liberacion de memoria de la matriz con la primera mitad del texto
	//pofa no lo olvides xd
	for(i=0; i<*tamanio; i++){
		free(filas[i]);
	}
	free(ciudadesPosibles);
	free(filas);

	fclose(archPuntero);

	printf("PRUEBA VERFCIUDADVALIDACOL\n");
	int caca;
	caca = verifCiudadValidaCol(salidaWIP, colEdifSeguidos, *tamanio);
	printf("Resultado: <%d>\n\n", caca);

	return salidaWIP;
}


int main(){
	int ** ciudad;
	ciudad = generarCiudad("entrada.txt", &tamanio);

	printf("Prueba salida ciudad en main:\n");
	int i, j;
	for(i = 0; i < tamanio; i++){
		for(j = 0; j < tamanio; j++){
			printf("%d ", ciudad[i][j]);
		}
		printf("\n");
	}


	//liberacion de la memoria usada por la matriz
	for(i=0; i<10; i++){//CAMBIAR EL 10 CUADNO LA CIUDAD SE DEVUELVA BIEN
		free(ciudad[i]);
	}
	free(ciudad);

	return 0;

}

//no olvidar:
//arreglar el 10 del ultimo free