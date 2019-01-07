#include <stdio.h>
#include <stdlib.h>


int tamanio;
//Función que reescribe la ciudad actual del usuario en un archivo nuevo
void copiaCiudad(char * dirMapaNuevo, int** mapa){
	FILE * archivoRecorrido;
	archivoRecorrido= fopen(dirMapaNuevo, "w");
	for (int i=0; i< tamanio; i++){
		for (int j=0; j< tamanio; j++){
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
	for (int i=0; i<tamanio; i++){
		for(int j=0; j<tamanio; j++){
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

void juegoNuevo(int** matrizCiudad){
	//Primero se lee la matriz de la ciudad generada
	int caracter, fila, columna, verificador, aux;
	int contadorEdificios=0;
	char * inputDireccion;
	inputDireccion="recorridoUsuario.txt";
	int opcion;
	for (int i=0;i<tamanio;i++){
		for (int j=0;j<tamanio;j++){
			caracter = matrizCiudad[i][j];
			contadorEdificios=contadorEdificios+caracter;
			//printf("%d",matrizCiudad[i][j]);
		}
	}
	//Luego se copia en el archivo que llevará el progreso del jugador registrando su última jugada
	copiaCiudad(inputDireccion, matrizCiudad);
	imprimeCiudad(matrizCiudad);
	printf("Ingrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa distintos a '0' :\n");
	printf("Ingrese el numero de fila:\n");
	scanf("%d", &fila);
	printf("Ingrese el numero de columna:\n");
	scanf("%d", &columna);
	fila= fila-1;
	columna= columna-1;
	if (fila>tamanio || fila<0 || columna >tamanio || columna <0){
		printf("Error, por favor ingrese un numero valido");
	}else{
		do{
			contadorEdificios= contadorEdificios-1;
			aux= matrizCiudad[fila][columna];
			matrizCiudad[fila][columna]=aux-1;
			imprimeCiudad(matrizCiudad);
			printf( "\n   1. Norte.");
        	printf( "\n   2. Sur.");
        	printf( "\n   3. Este.");
            printf( "\n   4. Oeste. ");
			printf( "\n   5. Salir. ");
			printf( "\n   Seleccione un movimiento (1-5)");
           	scanf( "%d", &opcion);
			if (opcion>5 || opcion<1){
				printf("\nError al recibir su decision, por favor ingrese un valor entre 1 y 5.");
			}else{
				while(opcion!=5){
					switch(opcion){
						case 1:
							if(fila-1<0){
								printf("\nHas salido de los bordes de la ciudad!");
								printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								fila= fila-1;
								int aux1= matrizCiudad[fila][columna];
								if(aux1==0){
									fila=fila+1;
									printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
									printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}else{
									aux1= aux1-1;
									contadorEdificios= contadorEdificios-1;
									matrizCiudad[fila][columna]= aux1;
									copiaCiudad(inputDireccion, matrizCiudad);
									imprimeCiudad(matrizCiudad);
									verificador= verificar(matrizCiudad, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("\nHas quedado encerrado! GAME OVER.\n");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}
							}
						case 2:
							if (fila+1>9){
								printf("\nHas salido de los bordes de la ciudad!");
								printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								fila= fila+1;
								int aux2= matrizCiudad[fila][columna];
								if(aux2==0){
									fila=fila-1;
									printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
									printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}else{
									aux2= aux2-1;
									contadorEdificios= contadorEdificios-1;
									matrizCiudad[fila][columna]= aux2;
									copiaCiudad(inputDireccion, matrizCiudad);
									imprimeCiudad(matrizCiudad);
									verificador= verificar(matrizCiudad, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("\nHas quedado encerrado! GAME OVER.\n");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}	
							}
						case 3:
							if(columna+1>9){
								printf("\nHas salido de los bordes de la ciudad!");
								printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								columna= columna+1;
								int aux3= matrizCiudad[fila][columna];
								if(aux3==0){
									columna=columna-1;
									printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
									printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}else{
									aux3= aux3-1;
									contadorEdificios= contadorEdificios-1;
									matrizCiudad[fila][columna]= aux3;
									copiaCiudad(inputDireccion, matrizCiudad);
									imprimeCiudad(matrizCiudad);
									verificador= verificar(matrizCiudad, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("\nHas quedado encerrado! GAME OVER.\n");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}
							}
						case 4:
							if(columna-1<0){
								printf("\nHas salido de los bordes de la ciudad!");
								printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
								scanf("%d", &opcion);
							}else{
								columna= columna-1;
								int aux4= matrizCiudad[fila][columna];
								if(aux4==0){
									columna=columna-1;
									printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
									printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
									printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
									break;
								}else{
									aux4= aux4-1;
									contadorEdificios= contadorEdificios-1;
									matrizCiudad[fila][columna]= aux4;
									copiaCiudad(inputDireccion, matrizCiudad);
									imprimeCiudad(matrizCiudad);
									verificador= verificar(matrizCiudad, fila, columna);
									if (verificador == 1 && contadorEdificios !=0){
										printf("\nHas quedado encerrado! GAME OVER.\n");
										exit(0);
									}else if(verificador==1 && contadorEdificios == 0){
										printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
										exit(0);
									}else{
										printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}
								}
							}

					}
				}
			}
		}
		while(opcion>5 || opcion<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
	}
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
		printf("\nNo has iniciado ningun juego anteriormente, cerrando programa...");		
		exit(1);
	}
	int ** matriz= (int**)malloc(sizeof(int*)*tamanio);
	for (int i=0;i<tamanio;i++){
		matriz[i]=(int*)malloc(sizeof(int)*tamanio);
	}
	for (int i=0;i<tamanio;i++){
		for (int j=0;j<tamanio;){
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
	printf("\nIngrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa distintos a '0' :\n");
	printf("Ingrese el numero de fila:\n");
	scanf("%d", &fila);
	printf("Ingrese el numero de columna:\n");
	scanf("%d", &columna);
	fila= fila-1;
	columna= columna-1;
	if (fila>tamanio || fila<0 || columna> tamanio || columna<0){
		printf("\nError, por favor ingrese un numero valido");
	}else{
		if (matriz[fila][columna] != 0){
			printf("\nError, por favor ingrese una coordenada que corresponda a un '0' en el mapa");
		}else{
			do{
				contadorEdificios= contadorEdificios-1;
				aux= matriz[fila][columna];
				matriz[fila][columna]=aux-1;
				imprimeCiudad(matriz);
				printf( "\n   1. Norte.");
        		printf( "\n   2. Sur.");
        		printf( "\n   3. Este.");
            	printf( "\n   4. Oeste. ");
				printf( "\n   5. Salir. ");
				printf( "\n   Seleccione un movimiento (1-5)");
           		scanf( "%d", &opcion);


				if (opcion>5 || opcion<1){
					printf("\nError al recibir su decision, por favor ingrese un valor entre 1 y 5.");
				}else{
					while(opcion!=5){
						switch(opcion){
							case 1:
								if(fila-1<0){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									fila= fila-1;
									int aux1= matriz[fila][columna];
									if(aux1==0){
										fila=fila+1;
										printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
										printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}else{
										aux1= aux1-1;
										contadorEdificios= contadorEdificios-1;
										matriz[fila][columna]= aux1;
										copiaCiudad(inputDireccion, matriz);
										imprimeCiudad(matriz);
										verificador= verificar(matriz, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
											scanf("%d", &opcion);
											break;
										}
									}						
								}
							case 2:
								if (fila+1>9){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									fila= fila+1;
									int aux2= matriz[fila][columna];
									if(aux2==0){
										fila=fila-1;
										printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
										printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}else{
										aux2= aux2-1;
										contadorEdificios= contadorEdificios-1;
										matriz[fila][columna]= aux2;
										copiaCiudad(inputDireccion, matriz);
										imprimeCiudad(matriz);
										verificador= verificar(matriz, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
											scanf("%d", &opcion);
											break;
										}
									}
								}
							case 3:
								if (columna+1>9){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									columna= columna+1;
									int aux3= matriz[fila][columna];
									if(aux3==0){
										columna=columna-1;
										printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
										printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}else{
										aux3= aux3-1;
										contadorEdificios= contadorEdificios-1;
										matriz[fila][columna]= aux3;
										copiaCiudad(inputDireccion, matriz);
										imprimeCiudad(matriz);
										verificador= verificar(matriz, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
											scanf("%d", &opcion);
											break;
										}
									}
								}
							case 4:
								if (columna-1<0){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra accion(1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
									scanf("%d", &opcion);
								}else{
									columna= columna-1;
									int aux4= matriz[fila][columna];
									if(aux4==0){
										columna=columna+1;
										printf("\nMovimiento invalido! Recuerda moverte por donde hayan numeros distintos a cero.");
										printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
										scanf("%d", &opcion);
										break;
									}else{
										aux4= aux4-1;
										contadorEdificios= contadorEdificios-1;
										matriz[fila][columna]= aux4;
										copiaCiudad(inputDireccion, matriz);
										imprimeCiudad(matriz);
										verificador= verificar(matriz, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
											scanf("%d", &opcion);
											break;
										}
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
void recorridoManual(int ** matrizCiudad){
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
				printf("\nRecuperando Juego Anterior...");
				juegoAnterior();	

           	case 2: 
				printf("\nIniciando Juego Nuevo...");
				juegoNuevo(matrizCiudad);
        }
	}
	while(decision>3 || decision<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
}

//BEE
//--------------------------------------------------------------------------------------------------------------------
int correlativo = 0;

//Creamos un Structure con :
//id del estado
//id de donde viene 
//mapa actual con el estado cambiado 
//posicion de x del estado (Posicion x de Spiderman en ese estado)
//posicion de y del estado (Posicion y de Spiderman en ese estado)
//contenido del estado 
typedef struct estado estado;
struct estado{
	int id;
	int idAnterior;
	int ** arreglo;
	int px;
	int py;
	int contenido;
	char dedondeviene;
};

//Funcion que crea un estado
//Entrada : Id actual del estado a crear, id del estado del que viene , posicionx, posiciony en este estado, mapa anterior.
//Salida  : Estado nuevo en base a los parametros entregados. 
estado CrearEstado(int * idn, int idAnteriorn, int pxn, int pyn,char dedondevienen, int ** Matrizanteriorn, int fila, int columna ){
	estado nuevoEstado;
	nuevoEstado.arreglo =  (int**)malloc(sizeof(int*)*fila);
	for (int i = 0; i < fila; ++i){
		nuevoEstado.arreglo[i]=(int*)malloc(sizeof(int)*columna);
	}
	nuevoEstado.id = *idn;
	nuevoEstado.idAnterior = idAnteriorn;
	nuevoEstado.px = pxn;
	nuevoEstado.py = pyn;
	nuevoEstado.dedondeviene = dedondevienen;
	for (int i = 0; i < fila; ++i){
		for (int j = 0; j < columna; ++j){
			nuevoEstado.arreglo[i][j] = Matrizanteriorn[i][j];
		}
	}
	nuevoEstado.arreglo[pyn][pxn] -=1;
	return nuevoEstado;
};

//Funcion agregar un estado a un arreglo.
//Entrada : El estado a agregar, la lista a la que se va a añadir ese estado y su tamaño.
//Salida  : Lista nueva con el estado agregado.
estado *AgregarEstado(estado * lista, int * largolista, estado estadoaAgregar){
    estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*largolista+1));
    if (*largolista != 0){
        for (int i = 0; i < *largolista; ++i){
            nuevaLista[i]=lista[i];
        }
    }
    nuevaLista[*largolista] = estadoaAgregar;
    *largolista += 1;
    free(lista);
    return nuevaLista;
}

//Funcion que borra el primer estado de un arreglo
//Entrada : Lista a eliminar el primer elemento y el largo de respectivo arreglo.
//Salida  : Arreglo pero sin su primer elemento.
estado *BorrarEstado(estado *lista,int * largolista){
	estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*largolista-1));
    for (int i = 1 ; i < *largolista ; ++i){
        nuevaLista[i-1] = lista[i];
    }
    *largolista -= 1;
    free(lista);
    return nuevaLista;
}

//Conjunto de funciones que revisan si exite un moviento posible a la direccion señalada en el nombre de la funcion.
//Entrada : Un estado a evaluar.
//Salida  : Respectivamente un booleano 1 si exite movimiento posible en esa direccion, 0 para lo contrario.
int revisarN(estado EstadoActual, int fila, int columna){
	// Retorna que si hay movimiento
	if (EstadoActual.py > 0){
		if(EstadoActual.arreglo[EstadoActual.py-1][EstadoActual.px] != 0 ){
	        return 1;
	    }
	}
	// Retorna que no hay moviento  
    return 0;
}
int revisarS(estado EstadoActual, int fila, int columna){
	if (EstadoActual.py < fila-1){
		if (EstadoActual.arreglo[EstadoActual.py+1][EstadoActual.px] != 0){
	        return 1;
		}
    }
    return 0;
}
int revisarE(estado EstadoActual, int fila, int columna){
    if (EstadoActual.px < columna-1){
    	if (EstadoActual.arreglo[EstadoActual.py][EstadoActual.px+1] != 0){
	        return 1;
    	}
    }
    return 0;
}
int revisarO(estado EstadoActual, int fila, int columna){
    if (EstadoActual.px > 0){
    	if (EstadoActual.arreglo[EstadoActual.py][EstadoActual.px-1] != 0){
	        return 1;
    	} 
    }
    return 0;
}

//Funcion que transforma la posicion de un estado a su antecesor, en relacion de dondev viene.
//Entrada : Un estado.
//Salida  : La posicion en X e Y rescpectivo al nombre de la funcion del estado de donde viene.
int ConversionX(estado EstadoActual){
	if (EstadoActual.dedondeviene == 'O'){
		return EstadoActual.px-1; 
	}
	if (EstadoActual.dedondeviene == 'E'){
		return EstadoActual.px+1;
	}
	else{
		return EstadoActual.px;
	}
}
int ConversionY(estado EstadoActual){
	if (EstadoActual.dedondeviene == 'S'){
		return EstadoActual.py+1; 
	}
	if (EstadoActual.dedondeviene == 'N'){
		return EstadoActual.py-1;
	}
	else{
		return EstadoActual.py;
	}
}

//Funcion que revisa si la matriz de un estado contiene la solucion final.
//Entrada : Un estado.
//Salida  : Un booleano, cero si tiene algun edificion con un numero distinto de 0; 1 si ya todo está en cero.
int EncontroSolucionFinal(estado EstadoActual, int fila, int columna){
	for (int i = 0; i < fila; ++i){
		for (int j = 0; j < columna; ++j){
			if (EstadoActual.arreglo[i][j] != 0){
				return 0;
			}
		}
	}
	return 1;
}

//Funcion busca la posicion de un estado que da origen al estado que estamos revisando en un arreglo.
//Entrada : Una arreglo de estados, el largo de ese arreglo y el estado a buscar su predecesor.
//Salida  : Un entero que es la posicion en el arreglo del estado predecesor del estado entregado.
int Anterior(estado * lista,int largolista,estado Estadofinal){
    for (int i = 0; i<largolista ; ++i){
        if((lista[i].id == Estadofinal.idAnterior)){
        	if (lista[i].px == ConversionX(Estadofinal) && lista[i].py == ConversionY(Estadofinal)){
        		return i;
        	}  
        }
    }
}

//Funcion que entrega un arreglo con la solucion de pasos a seguir.
//Entrada : El arreglo de los estados cerrados para buscar el camino a devolver y el estado Final.  
//Salida  : Un arreglo con las instruciones para salir.
char * mostrarsolucion(estado * lista, int largolista, estado Estadofinal){
	int contador = 0;
	char * Solucion = (char*)malloc(contador*sizeof(char));
	if (Estadofinal.dedondeviene == 'N'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'S';
		contador+= 1;
	}
	if (Estadofinal.dedondeviene == 'S'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'N';
		contador+= 1;
	}
	if (Estadofinal.dedondeviene == 'O'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'E';
		contador+= 1;
	}
	if (Estadofinal.dedondeviene == 'E'){
		Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
		Solucion[contador] = 'O';
		contador+= 1;
	}
	int ultimo = Anterior(lista,largolista,Estadofinal);
    while(lista[ultimo].dedondeviene != 'I'){
        if (lista[ultimo].dedondeviene == 'N'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'S';
			contador+= 1;
        }
        if (lista[ultimo].dedondeviene == 'S'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'N';
			contador+= 1;
        }
        if (lista[ultimo].dedondeviene == 'E'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'O';
			contador+= 1;
        }
        if (lista[ultimo].dedondeviene == 'O'){
        	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
			Solucion[contador] = 'E';
			contador+= 1;
        }
        ultimo = Anterior(lista,largolista,lista[ultimo]);
    }
    FILE * archivo;

    archivo = fopen("Salida.txt","w");
    Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
	Solucion[contador] = lista[ultimo].py+ '0';
	contador+= 1;
	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
	Solucion[contador] = lista[ultimo].px+ '0';
	contador+= 1;
	Solucion = (char*)realloc(Solucion,(contador+1)*sizeof(int*));
	Solucion[contador] = 'I';
	contador+= 1;

    char parD = '(';
    char parI = ')';
    char esp = ' ';
    char com = ',';
    fwrite(&Solucion[contador-1],sizeof(char),1,archivo);
    fwrite(&parD,sizeof(char),1,archivo);
    fwrite(&Solucion[contador-2],sizeof(char),1,archivo);
    fwrite(&com,sizeof(char),1,archivo);
    fwrite(&Solucion[contador-3],sizeof(char),1,archivo);
    fwrite(&parI,sizeof(char),1,archivo);
    fwrite(&esp,sizeof(char),1,archivo);

    for (int i = contador-4; -1 < i; --i)
    {
    	fwrite(&Solucion[i],sizeof(char),1,archivo);
    	fwrite(&com,sizeof(char),1,archivo);
    }

    fclose(archivo);
}

//Revisa si el estado a Analizar contiene 2 conjuntos separados de edificios para asi ignorar estos casos dado que no hay solucion para ellos.
//Entrada : Un estado a analizar.
//Salida  : Un booleano, 1 para cuando exista 2 conjuntos separados, 0 para un estado que solo tenga un unico conjunto a recorrer.
int DiscriminarEstados(estado EAR, int fila, int columna){
	int auxA = 0;
	int auxF[fila];
	for (int i = 0; i < fila-1; ++i){
		auxA = 0;
		for (int j = 0; j < columna-1; ++j){
			if (EAR.arreglo[i][j] != 0){
				auxA = 1;
			} 
		}
		auxF[i] = auxA;
	}
	//Revisamos la lista que exista una secuencia 1-0-1 en filas.
	for (int i = 0; i < fila-1; ++i){
		if (i<fila-4){
			if (auxF[i]==1 && auxF[i+1]==0 && auxF[i+2]==1){
				return 1;
			}
		}
	}
	int auxB = 0;
	int auxC[columna];
	for (int i = 0; i < fila-1; ++i){
		auxB = 0;
		for (int j = 0; j < columna-1; ++j){
			if (EAR.arreglo[j][i] != 0){
				auxB = 1;
			} 
		}
		auxC[i] = auxB;
	}
	//Revisamos la lista que exista una secuencia 1-0-1 en columnas.
	for (int i = 0; i < columna-1; ++i){
		if (i<columna-4){
			if (auxC[i]==1 &&auxC[i+1]==0 && auxC[i+2]==1){
				return 1;
			}
		}
	}
	return 0;
}

//Funcion que entrega las posiciones validas para iniciar.
//Entrada : Un arreglo, el cual representa la ciudad.
//Salida  : Un arreglo con las posiciones validas para iniciar en la fila superior que contenga edificos.
int ** IniciosPosibles(int ** arreglo, int * aux, int fila, int columna){
	int ** comienzosPosibles =  (int**)malloc(sizeof(int*)*1);
    comienzosPosibles[0]=(int*)malloc(sizeof(int)*2);
	for (int i = 0; i < fila; ++i){
		for (int j = 0; j < columna; ++j){
			if (arreglo[i][j] != 0){
				comienzosPosibles[*aux][0]= i;
				comienzosPosibles[*aux][1]= j;
				*aux+=1;
                comienzosPosibles = (int**)realloc(comienzosPosibles,(*aux+1)*sizeof(int*));
                comienzosPosibles[*aux]=(int*)malloc(sizeof(int)*2);
			}
		}
		if(*aux != 0){
			return comienzosPosibles;
		}
	}
}

//Funcion que realiza la Busqueda en Espacio de Estados.
//Entrada : La matriz a recorrer, las filas de la matriz, las columnas , la posicion inicial en x y la posicion inicial en "y" para comenzar a recorrer.
//Salida  : Un booleano con 1 si encontró la forma de recorrer y dejar todo en cero, de lo contrario un 0.
int BEE(int ** Matriz,int fila,int columna, int posicionIX,int posicionIY){
	int canAbiertos = 0;
    int canCerrados = 0;
    //LEA lista estados abiertos
    estado * LEA = (estado *)malloc(sizeof(estado)*canAbiertos);
    //LER lista estados recorridos
    estado * LER = (estado *)malloc(sizeof(estado)*canCerrados);
    //Se crea el estado inicial 
    estado inicial = CrearEstado(&correlativo,posicionIX,posicionIY,0,'I',Matriz,fila,columna);
    //Agregamos a la lista de los estados 
    LEA = AgregarEstado(LEA,&canAbiertos,inicial);
	while(canAbiertos > 0){
		estado eActual = LEA[0];
		//Revisamos si este estado contiene la solucion, es decir deja el mapa en 0 
		//No borramos este estado para que no acuse luego que no encontramos solucion
		if (EncontroSolucionFinal(LEA[0],fila,columna) == 1){
			//Muestra la solucion 
			//Devolver pasos para salir
			mostrarsolucion(LER,canCerrados,eActual);

			//Liberar Toda la memoria almacenada
			return 1;
		}
		correlativo+=1;
		if (revisarN(eActual,fila,columna) == 1){
			//Creamos un estado nuevo al norte del actual copiando el mapa anterior restando una a la llegada
			estado norte = CrearEstado(&correlativo,eActual.id,eActual.px,eActual.py-1,'S',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(norte,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,norte);
			}
		}
		if (revisarS(eActual,fila,columna) == 1){
			//Creamos un estado nuevo 
			estado sur = CrearEstado(&correlativo,eActual.id,eActual.px,eActual.py+1,'N',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(sur,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,sur);
			}
		}
		if (revisarO(eActual,fila,columna) == 1){
			//Creamos un estado nuevo 
			estado oeste = CrearEstado(&correlativo,eActual.id,eActual.px-1,eActual.py,'E',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(oeste,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,oeste);
			}
		}
		if (revisarE(eActual,fila,columna) == 1){
			//Creamos un estado nuevo 
			estado este = CrearEstado(&correlativo,eActual.id,eActual.px+1,eActual.py,'O',eActual.arreglo,fila,columna);
			if(DiscriminarEstados(este,fila,columna)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,este);
			}
		}
		//Borramos este estado de Abiertos y lo agregamos a cerrados y aumentamos el contador de cerrados en 
		LER = AgregarEstado(LER,&canCerrados,eActual);
		LEA = BorrarEstado(LEA,&canAbiertos);
	}
	//Condicion que no encontramos solucion 
	if(canAbiertos == 0){
		printf("No encontré solucion con el inicio en %d,%d lo generaré en otro punto \n", posicionIY,posicionIX);
		return 0 ; 
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------


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
		{0,0,0,2,99,0,0,0,0,0},
		{0,0,1,2,0,0,999,0,0,0},
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


int main(){
	int ** ciudad;
	int ver, i;
	int aux;
	int * iniSol;
	int ** inicio;
	printf("Estoy decodificando el archivo...\n\n");
	ciudad = generarCiudad("entrada.txt", &tamanio);
	int desicion;
	do{
		printf("\n ------------------------------------------------------------- \n");
		printf("|                                                             |\n");
		printf("|                         MENU                                |\n");
		printf("|                                                             |\n");
		printf("| 0. Salir del juego.                                         |\n");
		printf("| 1. Verificar existencia de solución en ciudad.              |\n");
		printf("| 2. Entrega de archivo solución.                             |\n");
		printf("| 3. Recorrido manual.                                        |\n");
		printf("| 4. Codificar una ciudad.                                    |\n");
		printf("|                                                             |\n");
		printf(" ------------------------------------------------------------- \n");
		printf("Seleccione lo que quiere hacer: ");
		scanf("%d", &desicion);
		printf("\n");

		switch(desicion) {
			case 0  :
				printf("Game Over.\n");
				//liberacion de la memoria usada por la Matriz
				for(i=0; i<10; i++){//CAMBIAR EL 5 CUADNO LA CIUDAD SE DEVUELVA BIEN
					free(ciudad[i]);
				}
				free(ciudad);
				exit(0);
		    case 1  :
		    	printf("Verifico si hay solucion con el mapa entregado.\n\n");
		    	break; /* optional */
		    case 2  :
				aux = 0;
				inicio = IniciosPosibles(ciudad,&aux,tamanio,tamanio);
				iniSol = crearconjuntosolucion(aux);
				for (int i = 0; i < aux; ++i){
					if(BEE(ciudad,tamanio,tamanio,inicio[i][0],inicio[i][1]) == 1){
						iniSol[i]=1; 
					}else{
						iniSol[i]=0;
					}
				}
				ver = 0;
				for (i = 0; i < aux; ++i){
					if (iniSol[i] == 1){
						ver+=1;
						printf("Hay solucion e : %d,%d \n",inicio[i][0],inicio[i][1]);
					}					
				}

				if (ver==0){
					printf("No hay solucion\n");
				}				


	
		    	break; /* optional */
		    case 3  :
		    	printf("Estoy preparando tu juego.\n\n");
		    	recorridoManual(ciudad);
		    	break; /* optional */

		    case 4  :
		      	printf("Estoy Devolviendo el Inverso.\n\n");
		      	break; /* optional */
		   /* you can have any number of case statements */
			default : 
				printf("Por favor ingrese una opción válida.");
				break;
		}

	}while(desicion != 0 );
	return 0;
}
