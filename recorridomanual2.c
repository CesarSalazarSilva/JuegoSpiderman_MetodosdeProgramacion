#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Función que reescribe la ciudad actual del usuario en un archivo nuevo
void copiaCiudad(char * dirMapaNuevo, int** mapa){
	FILE * archivoRecorrido;
	archivoRecorrido= fopen(dirMapaNuevo, "w");
	for (int i=0; i< 10; i++){
		for (int j=0; j< 10; j++){
			fprintf(archivoRecorrido, "%d",mapa[i][j]);
			fprintf(archivoRecorrido, " ");
		}
	fprintf(archivoRecorrido, "\n");
	}
	printf("El archivo se actualizo correctamente \n");
	fclose(archivoRecorrido);
}		


//Función que imprime la matriz de la ciudad actual
void imprimeCiudad(int** matrz){
	for (int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			printf("%d\t", matrz[i][j]);
		}
		printf("\n");
	}
}


//Función que verifica los alrededores del jugador, ya que de estar encerrado entre ceros, pierde el juego.

int verificar(int ** matriz, int fila, int columna){
	int respuesta=0;
	if (fila-1<0){
		if ((matriz[fila+1][columna]==0) && (matriz[fila][columna+1]==0) && (matriz[fila][columna-1]==0)){
			respuesta= 1;
		}
	}else if(fila+1> 9){
		if ((matriz[fila-1][columna]==0) && (matriz[fila][columna+1]==0) && (matriz[fila][columna-1]==0)){
			respuesta= 1;
		}
	}else if(columna+1> 9){
		if ((matriz[fila-1][columna]==0) && (matriz[fila+1][columna]==0) && (matriz[fila][columna-1]==0)){
			respuesta= 1;
		}
	}else if (columna-1<0){
		if ((matriz[fila-1][columna]==0) && (matriz[fila+1][columna]==0) && (matriz[fila][columna+1]==0)){
			respuesta= 1;
		}
	}else{
		if((matriz[fila-1][columna]==0) && (matriz[fila+1][columna]==0) && (matriz[fila][columna-1]==0) && (matriz[fila][columna+1]==0));
	}
	return respuesta;
}
		

//Funcion que ejecuta el recorrido manual de un juego nuevo

void juegoNuevo(){
		//Primero se lee la matriz de la ciudad generada
	FILE * archivoOrigen;
	char * dirMapa;
	dirMapa= "mapaCiudad.txt";
	int caracter, fila, columna, verificador, aux;
	int contadorEdificios=0;
	char * inputDireccion;
	inputDireccion="recorridoUsuario.txt";
	int opcion;
	archivoOrigen= fopen(dirMapa, "r");
	if (archivoOrigen==NULL){
		printf("Error con el archivo de ciudad, cerrando programa...");
		exit(1);
	}
	int**matriz= (int**)malloc(sizeof(int*)*10);//ojo acá, es solo porque me falta la variable global
	for (int i=0;i<10;i++){
		matriz[i]=(int*)malloc(sizeof(int)*10);
	}
	for (int i=0;i<10;i++){
		for (int j=0;j<10;){
			caracter = fgetc(archivoOrigen);
			if (caracter!=32 && caracter != 10){
				caracter=caracter-48;
				contadorEdificios= contadorEdificios + caracter;
				matriz[i][j]=caracter;
				j++;
			}
		}
		caracter=fgetc(archivoOrigen);
	}
	//Luego se copia en el archivo que llevará el progreso del jugador registrando su última jugada
	copiaCiudad(inputDireccion, matriz);
	imprimeCiudad(matriz);
	printf("Ingrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa distintos a '0' :\n");
	printf("Ingrese el numero de fila:\n");
	scanf("%d", &fila);
	printf("Ingrese el numero de columna:\n");
	scanf("%d", &columna);
	fila= fila-1;
	columna= columna-1;
	if (fila>10 || fila<0 || columna >10 || columna <0){
		printf("Error, por favor ingrese un numero valido");
	}else{
		do{
			printf( "\n   1. Norte.");
        	printf( "\n   2. Sur.");
        	printf( "\n   3. Este.");
            printf( "\n   4. Oeste. ");
			printf( "\n   5. Salir. ");
			printf( "\n   Seleccione un movimiento (1-5)");
           	scanf( "%d", &opcion);
			contadorEdificios= contadorEdificios-1;
			aux= matriz[fila][columna];
			matriz[fila][columna]=aux-1;
			if (opcion>5 || opcion<1){
				printf("Error al recibir su decision, por favor ingrese un valor entre 1 y 5.");
			}else{
				while(opcion!=5){
					switch(opcion){
						case 1:
							if(fila-1<0){
								printf("Has salido de los bordes de la ciudad!");
								printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								fila= fila-1;
								int aux1= matriz[fila][columna];
								aux1= aux1-1;
								contadorEdificios= contadorEdificios-1;
								matriz[fila][columna]= aux1;
								copiaCiudad(inputDireccion, matriz);
								imprimeCiudad(matriz);
								verificador= verificar(matriz, fila, columna);
								if (verificador == 1 && contadorEdificios !=0){
									printf("Has quedado encerrado! GAME OVER.");
									exit(0);
								}else if(verificador==1 && contadorEdificios == 0){
									printf("Felicitaciones, has capturado a todos los malhechores!");
									exit(0);
								}else{
									printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}
							}
						case 2:
							if (fila+1>9){
								printf("Has salido de los bordes de la ciudad!");
								printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								fila= fila+1;
								int aux2= matriz[fila][columna];
								aux2= aux2-1;
								contadorEdificios= contadorEdificios-1;
								matriz[fila][columna]= aux2;
								copiaCiudad(inputDireccion, matriz);
								imprimeCiudad(matriz);
								verificador= verificar(matriz, fila, columna);
								if (verificador == 1 && contadorEdificios !=0){
									printf("Has quedado encerrado! GAME OVER.");
									exit(0);
								}else if(verificador==1 && contadorEdificios == 0){
									printf("Felicitaciones, has capturado a todos los malhechores!");
									exit(0);
								}else{
									printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}
							}
						case 3:
							if(columna+1>9){
								printf("Has salido de los bordes de la ciudad!");
								printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								columna= columna+1;
								int aux3= matriz[fila][columna];
								aux3= aux3-1;
								contadorEdificios= contadorEdificios-1;
								matriz[fila][columna]= aux3;
								copiaCiudad(inputDireccion, matriz);
								imprimeCiudad(matriz);
								verificador= verificar(matriz, fila, columna);
								if (verificador == 1 && contadorEdificios !=0){
									printf("Has quedado encerrado! GAME OVER.");
									exit(0);
								}else if(verificador==1 && contadorEdificios == 0){
									printf("Felicitaciones, has capturado a todos los malhechores!");
									exit(0);
								}else{
									printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}
							}
						case 4:
							if(columna-1<0){
								printf("Has salido de los bordes de la ciudad!");
								printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								columna= columna-1;
								int aux4= matriz[fila][columna];
								aux4= aux4-1;
								contadorEdificios= contadorEdificios-1;
								matriz[fila][columna]= aux4;
								copiaCiudad(inputDireccion, matriz);
								imprimeCiudad(matriz);
								verificador= verificar(matriz, fila, columna);
								if (verificador == 1 && contadorEdificios !=0){
									printf("Has quedado encerrado! GAME OVER.");
									exit(0);
								}else if(verificador==1 && contadorEdificios == 0){
									printf("Felicitaciones, has capturado a todos los malhechores!");
									exit(0);
								}else{
									printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}
							}

					}
				}
			}
		}
		while(opcion>5 || opcion<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
	}
	fclose(archivoOrigen);
}


//Funcion que permite hacer el recorrido manual con una partida guardada anteriormente
void juegoAnterior(){
	//Primero se lee la matriz de la ciudad guardada en el juego anterior
	FILE * archivoJuegoAnterior;
	int caracter, fila, columna, verificador, aux;
	int contadorEdificios=0;
	char * inputDireccion;
	inputDireccion="recorridoUsuario.txt";
	int opcion;
	archivoJuegoAnterior= fopen(inputDireccion, "r");
	if (archivoJuegoAnterior==NULL){
		printf("No has iniciado ningun juego anteriormente, cerrando programa...");		
		exit(1);
	}
	int ** matriz= (int**)malloc(sizeof(int*)*10);//ojo acá, es solo porque me falta la variable global
	for (int i=0;i<10;i++){
		matriz[i]=(int*)malloc(sizeof(int)*10);
	}
	for (int i=0;i<10;i++){
		for (int j=0;j<10;){
			caracter = fgetc(archivoJuegoAnterior);
			if (caracter!=32 && caracter != 10){
				caracter=caracter-48;
				contadorEdificios= contadorEdificios + caracter;
				matriz[i][j]=caracter;
				j++;
			}
		}
		caracter=fgetc(archivoJuegoAnterior);
	}
	//Luego se copia en el archivo que llevará el progreso del jugador registrando su última jugada
	copiaCiudad(inputDireccion, matriz);
	imprimeCiudad(matriz);
	printf("Ingrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa distintos a '0' :\n");
	printf("Ingrese el numero de fila:\n");
	scanf("%d", &fila);
	printf("Ingrese el numero de columna:\n");
	scanf("%d", &columna);
	fila= fila-1;
	columna= columna-1;
	if (fila>10 || fila<0 || columna> 10 || columna<0){
		printf("Error, por favor ingrese un numero valido");
	}else{
		if (matriz[fila][columna] != 0){
			printf("Error, por favor ingrese una coordenada que corresponda a un '0' en el mapa");
		}else{
			do{
				printf( "\n   1. Norte.");
        		printf( "\n   2. Sur.");
        		printf( "\n   3. Este.");
            	printf( "\n   4. Oeste. ");
				printf( "\n   5. Salir. ");
				printf( "\n   Seleccione un movimiento (1-5)");
           		scanf( "%d", &opcion);
				contadorEdificios= contadorEdificios-1;
				aux= matriz[fila][columna];
				matriz[fila][columna]=aux-1;
				if (opcion>5 || opcion<1){
					printf("Error al recibir su decision, por favor ingrese un valor entre 1 y 5.");
				}else{
					while(opcion!=5){
						switch(opcion){
							case 1:
								if(fila-1<0){
									printf("Has salido de los bordes de la ciudad!");
									printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									fila= fila-1;
									int aux1= matriz[fila][columna];
									aux1= aux1-1;
									contadorEdificios= contadorEdificios-1;
									matriz[fila][columna]= aux1;
									copiaCiudad(inputDireccion, matriz);
									imprimeCiudad(matriz);
									verificador= verificar(matriz, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("Has quedado encerrado! GAME OVER.");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("Felicitaciones, has capturado a todos los malhechores!");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}
							case 2:
								if (fila+1>9){
									printf("Has salido de los bordes de la ciudad!");
									printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									fila= fila+1;
									int aux2= matriz[fila][columna];
									aux2= aux2-1;
									contadorEdificios= contadorEdificios-1;
									matriz[fila][columna]= aux2;
									copiaCiudad(inputDireccion, matriz);
									imprimeCiudad(matriz);
									verificador= verificar(matriz, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("Has quedado encerrado! GAME OVER.");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("Felicitaciones, has capturado a todos los malhechores!");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}
							case 3:
								if (columna+1>9){
									printf("Has salido de los bordes de la ciudad!");
									printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									columna= columna+1;
									int aux3= matriz[fila][columna];
									aux3= aux3-1;
									contadorEdificios= contadorEdificios-1;
									matriz[fila][columna]= aux3;
									copiaCiudad(inputDireccion, matriz);
									imprimeCiudad(matriz);
									verificador= verificar(matriz, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("Has quedado encerrado! GAME OVER.");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("Felicitaciones, has capturado a todos los malhechores!");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}
							case 4:
								if (columna-1<0){
									printf("Has salido de los bordes de la ciudad!");
									printf("Ingresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									columna= columna-1;
									int aux4= matriz[fila][columna];
									aux4= aux4-1;
									contadorEdificios= contadorEdificios-1;
									matriz[fila][columna]= aux4;
									copiaCiudad(inputDireccion, matriz);
									imprimeCiudad(matriz);
									verificador= verificar(matriz, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("Has quedado encerrado! GAME OVER.");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("Felicitaciones, has capturado a todos los malhechores!");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}

						}
					}
				}

			}
			while(opcion>5 || opcion<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
		}
	}
	fclose(archivoJuegoAnterior);
}

//Función que recibe la matriz de la ciudad actual, y da la opcion al usuario de hacer el recorrido manual
void recorridoManual(){
	int decision;
	//Entrando a la función, pregunta si continua con el mapa anterior o empieza uno nuevo
	do{
		printf( "\n   1. Continuar Juego Anterior.");
        printf( "\n   2. Juego Nuevo.");
        printf( "\n   3. Salir.");
        printf( "\n   Introduzca opcion (1-3): ");
        scanf( "%d", &decision);
        switch(decision){
        	case 1: 
				printf("Recuperando Juego Anterior...");
				juegoAnterior();	

           	case 2: 
				printf("Iniciando Juego Nuevo...");
				juegoNuevo();
        }
	}
	while(decision>3 || decision<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
}

int main(){
	recorridoManual();
}