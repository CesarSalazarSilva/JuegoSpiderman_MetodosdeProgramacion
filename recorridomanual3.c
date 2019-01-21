int tamanio;


//Función que genera una estampa de tiempo para cada acción exitosa que haga el usuario en el recorrido manual y la imprime en un archivo de registro.
//Entrada: String de la acción.
//Salida: Archivo con todas las acciones exitosas del recorrido manual con su correspondiente estampa de tiempo

void timestamp(char * movimiento){
    FILE * fp;
    fp=fopen("userLog.txt", "a");
    time_t tiempo; 
    tiempo=time(NULL); //Se toma el tiempo actual
    fprintf(fp,"\n%s",asctime( localtime(&tiempo) ) );
    fprintf(fp,"\n%s", movimiento);
    fclose(fp);
}

//Función que reescribe la ciudad actual del usuario en un archivo nuevo.
//Entrada: Direccion del archivo nuevo, matriz que contiene el mapa.
//Salida: Confirmación de la correcta copia de la ciudad en el archivo nuevo.

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
	printf("El archivo se actualizó correctamente \n");
	fclose(archivoRecorrido);
}		


//Función que imprime la matriz de la ciudad actual.
//Entrada: Matriz que contiene el mapa de la ciudad.
//Salida: Matriz impresa por pantalla.

void imprimeCiudad(int** matrz){
	for (int i=0; i<tamanio; i++){
		for(int j=0; j<tamanio; j++){
			printf("%d\t", matrz[i][j]);
		}
		printf("\n");
	}
}

//Función que verifica si la entrada proporcionada por el usuario es un número o no.
//Entrada: Caracter ingresado por el usuario.
//Salida: Valor booleano, 1 en caso de ser un numero, 0 en caso de ser una letra u otro caracter.

int verificaNumero(char * input){
	if (isdigit(input)){
		return 1;
	}else{
		return 0;
	}
}

//Función que verifica los alrededores del jugador, ya que de estar encerrado entre ceros, pierde el juego.
//Entrada: Matriz que contiene la ciudad, fila y columna de la posicion a analizar.
//Salida: Valor "booleano", 1 de estar rodeado de ceros, 0 en caso contrario.

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
		

//Funcion que ejecuta el recorrido manual de un juego nuevo.
//Entrada: Matriz que contiene el mapa de la ciudad obtenido por BES.
//Salida: Opciones por pantalla para que el usuario interactue.

void juegoNuevo(int** matrizCiudad){
	//Primero se lee la matriz de la ciudad generada
	int caracter, fila, columna, verificador, aux;
	int contadorEdificios=0;
	char * inputDireccion;
	inputDireccion="recorridoUsuario.txt";
	char opcion, filaInput, columnaInput;
	for (int i=0;i<tamanio;i++){
		for (int j=0;j<tamanio;j++){
			caracter = matrizCiudad[i][j];
			contadorEdificios=contadorEdificios+caracter;
		}
	}
	//Luego se copia en el archivo que llevará el progreso del jugador registrando su última jugada
	copiaCiudad(inputDireccion, matrizCiudad);
	imprimeCiudad(matrizCiudad);
	do{
		printf("Ingrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa distintos a '0' :\n");
		printf("Ingrese el numero de fila:\n");
		scanf("%c", &filaInput);
		while(verificaNumero(filaInput)==0){
			printf("\nPor favor ingresa un número, no una letra o caracter:");
			scanf("%c", &filaInput);
		}
		printf("Ingrese el numero de columna:\n");
		scanf("%c", &columnaInput);
		while(verificaNumero(columnaInput)==0){
			printf("\nPor favor ingresa un número, no una letra o caracter:");
			scanf("%c", &columnaInput);
		}
		fila=atoi(filaInput);
		columna=atoi(columnaInput);
		fila= fila-1;
		columna= columna-1;
		if (fila>tamanio || fila<0 || columna >tamanio || columna <0){
			printf("\nError, por favor ingrese un número válido.");
		}else if(matrizCiudad[fila][columna]==0){
			printf("\nError, por favor no ingreses coordenadas donde hayan ceros.");
		}else{
			do{
				contadorEdificios= contadorEdificios-1;
				aux= matrizCiudad[fila][columna];
				matrizCiudad[fila][columna]=aux-1;
				imprimeCiudad(matrizCiudad);
				printf( "\n   5. Arriba.");
        		printf( "\n   2. Abajo.");
        		printf( "\n   3. Derecha.");
            	printf( "\n   1. Izquierda. ");
				printf( "\n   6. Salir. ");
				printf( "\n   Seleccione un movimiento:");
           		scanf( "%c", &opcion);
				if (opcion>6 || opcion<1){
					printf("\nError al recibir su decisión, por favor ingrese un movimiento válido.");
				}else{
					while(opcion!=6){
						switch(opcion){
							case '5':
								if(fila-1<0){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra acción(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
									scanf("%c", &opcion);
								}else{
									fila= fila-1;
									int aux1= matrizCiudad[fila][columna];
									if(aux1==0){
										fila=fila+1;
										printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
										printf("\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
										break;
									}else{
										aux1= aux1-1;
										contadorEdificios= contadorEdificios-1;
										matrizCiudad[fila][columna]= aux1;
										copiaCiudad(inputDireccion, matrizCiudad);
										timestamp("Arriba");
										imprimeCiudad(matrizCiudad);
										verificador= verificar(matrizCiudad, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}
									}
								}
							case '2':
								if (fila+1>9){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra acción(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
									scanf("%c", &opcion);
								}else{
									fila= fila+1;
									int aux2= matrizCiudad[fila][columna];
									if(aux2==0){
										fila=fila-1;
										printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
										printf("\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
										break;
									}else{
										aux2= aux2-1;
										contadorEdificios= contadorEdificios-1;
										matrizCiudad[fila][columna]= aux2;
										copiaCiudad(inputDireccion, matrizCiudad);
										timestamp("Abajo");
										imprimeCiudad(matrizCiudad);
										verificador= verificar(matrizCiudad, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}
									}	
								}
							case '3':
								if(columna+1>9){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra acción(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
									scanf("%c", &opcion);
								}else{
									columna= columna+1;
									int aux3= matrizCiudad[fila][columna];
									if(aux3==0){
										columna=columna-1;
										printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
										printf("\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
										break;
									}else{
										aux3= aux3-1;
										contadorEdificios= contadorEdificios-1;
										matrizCiudad[fila][columna]= aux3;
										copiaCiudad(inputDireccion, matrizCiudad);
										timestamp("Derecha");
										imprimeCiudad(matrizCiudad);
										verificador= verificar(matrizCiudad, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}
									}	
								}
							case '1':
								if(columna-1<0){
									printf("\nHas salido de los bordes de la ciudad!");
									printf("\nIngresa otra acción(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
									scanf("%c", &opcion);
								}else{
									columna= columna-1;
									int aux4= matrizCiudad[fila][columna];
									if(aux4==0){
										columna=columna-1;
										printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
										printf("\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
										printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
										break;
									}else{
										aux4= aux4-1;
										contadorEdificios= contadorEdificios-1;
										matrizCiudad[fila][columna]= aux4;
										copiaCiudad(inputDireccion, matrizCiudad);
										timestamp("Izquierda");
										imprimeCiudad(matrizCiudad);
										verificador= verificar(matrizCiudad, fila, columna);
										if (verificador == 1 && contadorEdificios !=0){
											printf("\nHas quedado encerrado! GAME OVER.\n");
											exit(0);
										}else if(verificador==1 && contadorEdificios == 0){
											printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
											exit(0);
										}else{
											printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}
									}
								}
						}
					}
				}
			}
			while(opcion>6 || opcion<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
		}
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
	char opcion, filaInput, columnaInput;
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
	do{
		printf("\nIngrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa distintos a '0' :\n");
		printf("Ingrese el número de fila:\n");
		scanf("%c", &filaInput);
		while(verificaNumero(filaInput)==0){
			printf("\nPor favor ingresa un número, no una letra o caracter:");
			scanf("%c", &filaInput);
		}
		printf("Ingrese el numero de columna:\n");
		scanf("%c", &columnaInput);
		while(verificaNumero(columnaInput)==0){
			printf("\nPor favor ingresa un número, no una letra o caracter:");
			scanf("%c", &columnaInput);
		}
		fila= atoi(filaInput);
		columna=atoi(columnaInput);
		fila= fila-1;
		columna= columna-1;
		if (fila>tamanio || fila<0 || columna> tamanio || columna<0){
			printf("\nError, por favor ingrese un numero valido");
		}else if(matriz[fila][columna]==0){
			printf("\nError, por favor no ingreses coordenadas donde hayan ceros.");
		}else{
				do{
					contadorEdificios= contadorEdificios-1;
					aux= matriz[fila][columna];
					matriz[fila][columna]=aux-1;
					imprimeCiudad(matriz);
					printf( "\n   5. Arriba.");
        			printf( "\n   2. Abajo.");
        			printf( "\n   3. Derecha.");
            		printf( "\n   1. Izquierda. ");
					printf( "\n   6. Salir. ");
					printf( "\n   Seleccione un movimiento:");
           			scanf( "%c", &opcion);


					if (opcion>6 || opcion<1){
						printf("\nError al recibir su decision, por favor ingrese un valor entre 1 y 5.");
					}else{
						while(opcion!=6){
							switch(opcion){
								case '5':
									if(fila-1<0){
										printf("\nHas salido de los bordes de la ciudad!");
										printf("\nIngresa otra acción(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
									}else{
										fila= fila-1;
										int aux1= matriz[fila][columna];
										if(aux1==0){
											fila=fila+1;
											printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
											printf("\n Su ubicacion actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}else{
											aux1= aux1-1;
											contadorEdificios= contadorEdificios-1;
											matriz[fila][columna]= aux1;
											copiaCiudad(inputDireccion, matriz);
											timestamp("Arriba");
											imprimeCiudad(matriz);
											verificador= verificar(matriz, fila, columna);
											if (verificador == 1 && contadorEdificios !=0){
												printf("\nHas quedado encerrado! GAME OVER.\n");
												exit(0);
											}else if(verificador==1 && contadorEdificios == 0){
												printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
												exit(0);
											}else{
												printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
												printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
												scanf("%c", &opcion);
												break;
											}
										}						
									}
								case '2':
									if (fila+1>9){
										printf("\nHas salido de los bordes de la ciudad!");
										printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
									}else{
										fila= fila+1;
										int aux2= matriz[fila][columna];
										if(aux2==0){
											fila=fila-1;
											printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
											printf("\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}else{
											aux2= aux2-1;
											contadorEdificios= contadorEdificios-1;
											matriz[fila][columna]= aux2;
											copiaCiudad(inputDireccion, matriz);
											timestamp("Abajo");
											imprimeCiudad(matriz);
											verificador= verificar(matriz, fila, columna);
											if (verificador == 1 && contadorEdificios !=0){
												printf("\nHas quedado encerrado! GAME OVER.\n");
												exit(0);
											}else if(verificador==1 && contadorEdificios == 0){
												printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
												exit(0);
											}else{
												printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
												printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
												scanf("%c", &opcion);
												break;
											}
										}
									}	
								case '3':
									if (columna+1>9){
										printf("\nHas salido de los bordes de la ciudad!");
										printf("\nIngresa otra acción(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
									}else{
										columna= columna+1;
										int aux3= matriz[fila][columna];
										if(aux3==0){
											columna=columna-1;
											printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
											printf("\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}else{
											aux3= aux3-1;
											contadorEdificios= contadorEdificios-1;
											matriz[fila][columna]= aux3;
											copiaCiudad(inputDireccion, matriz);
											timestamp("Derecha");
											imprimeCiudad(matriz);
											verificador= verificar(matriz, fila, columna);
											if (verificador == 1 && contadorEdificios !=0){
												printf("\nHas quedado encerrado! GAME OVER.\n");
												exit(0);
											}else if(verificador==1 && contadorEdificios == 0){
												printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
												exit(0);
											}else{
												printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
												printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
												scanf("%c", &opcion);
												break;
											}
										}
								}
								case '1':
									if (columna-1<0){
										printf("\nHas salido de los bordes de la ciudad!");
										printf("\nIngresa otra accion(5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
										scanf("%c", &opcion);
									}else{
										columna= columna-1;
										int aux4= matriz[fila][columna];
										if(aux4==0){
											columna=columna+1;
											printf("\nMovimiento inválido! Recuerda moverte por donde hayan números distintos a cero.");
											printf("\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
											printf("\nIngrese otra acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
											scanf("%c", &opcion);
											break;
										}else{
											aux4= aux4-1;
											contadorEdificios= contadorEdificios-1;
											matriz[fila][columna]= aux4;
											copiaCiudad(inputDireccion, matriz);
											timestamp("Izquierda");
											imprimeCiudad(matriz);
											verificador= verificar(matriz, fila, columna);
											if (verificador == 1 && contadorEdificios !=0){
												printf("\nHas quedado encerrado! GAME OVER.\n");
												exit(0);
											}else if(verificador==1 && contadorEdificios == 0){
												printf("\nFelicitaciones, has capturado a todos los malhechores!\n");
												exit(0);
											}else{
												printf( "\n Su ubicación actual es [%d] [%d]", fila+1, columna+1);
												printf("\nIngrese su siguiente acción (5.Arriba, 2.Abajo, 3. Derecha, 1. Izquierda, 6. Salir");
												scanf("%c", &opcion);
												break;
											}
										}
									}
							}
						}
					}	
				}
				while(opcion>6 || opcion<1); //En caso de ingresar valores no validos, no se ejecuta ninguna accion
			}
		}
		fclose(archivoJuegoAnterior);
	}
}

//Función que recibe la matriz de la ciudad actual, y da la opcion al usuario de hacer el recorrido manual.
//Entrada: Matriz que contiene la ciudad obtenida del BES.
//Salida: Menú que da las opciones de empezar un juego nuevo o continuar uno anterior.

void recorridoManual(int ** matrizCiudad){
	int decision;
	//Entrando a la función, pregunta si continua con el mapa anterior o empieza uno nuevo
	do{
		printf( "\n   1. Continuar Juego Anterior.");
        printf( "\n   2. Juego Nuevo.");
        printf( "\n   3. Salir.");
        printf( "\n   Introduzca opcion (1-3): ");
        scanf( "%c", &decision);
        switch(decision){
        	case '1': 
				printf("\nRecuperando Juego Anterior...");
				juegoAnterior();	

           	case '2': 
				printf("\nIniciando Juego Nuevo...");
				juegoNuevo(matrizCiudad);
        }
	}
}
