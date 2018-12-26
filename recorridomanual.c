#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Función que reescribe la ciudad actual del usuario en un archivo nuevo
void copiaCiudad(char * dirMapaNuevo, int** mapa){
	FILE *archivoRecorrido;
	archivoRecorrido= fopen(dirMapaNuevo, "w");
	for (int i=0; i< 10; i++){
		for (int j=0; j< 10; j++){
			fprintf(archivoRecorrido, "%d",mapa[i][j]);
			fprintf(archivoRecorrido, " ");
		}
	fprintf(archivoRecorrido, "\n");
	}
	printf("El archivo se actualizo correctamente");
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
		switch (decision){
			while (decision != 3){
           			case '1': 
					

           			case '2': 
					//Primero se lee la matriz de la ciudad generada
					FILE * archivoOrigen;
					char * dirMapa= "home\\mapaCiudad.txt";
					archivoOrigen= fopen(dirMapa, "r");
					int caracter, fila, columna;
					int contadorEdificios=0;
					char * inputDireccion;
					int opcion;
					if (archivoOrigen==NULL){	
						printf("Error con el archivo de ciudad, cerrando programa...");		
						exit(1);
					}
					int ** matriz= (int**)malloc(sizeof(int*)*10);//ojo acá, es solo porque me falta la variable global
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
					copiaCiudad("home\\recorridoUsuario.txt", matriz);
					imprimeCiudad(matriz);
					printf("Ingrese las coordenadas del punto [fila][columna] de donde quiere partir, considere que solo puede partir en aquellos puntos del mapa iguales a '0' :\n");
					printf("Ingrese el numero de fila:\n");
					scanf("%d", &fila);
					printf("Ingrese el numero de columna:\n");
					scanf("%d", &fila);
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
								if (opcion > 5 || opcion < 1){
									printf("Error al recibir su decision, por favor ingrese un valor entre 1 y 5.");
								}else{
									while (opcion != 5 ){
										switch(opcion){
											case '1':
												fila= fila-1;
												int aux1= matriz[fila][columna];
												if (fila<0){
													printf("Se ha salido de los bordes de la ciudad.");
												}else if(aux1!= 0){
														aux1= aux1-1;
														contadorEdificios= contadorEdificios-1;
														matriz[fila][columna]= aux1;
														copiaCiudad("home\\recorridoUsuario.txt", matriz);
														imprimeCiudad(matriz);
														printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste ");
														//////////////////////////quedé aca/////////////////////////////////////////////////////
														scanf("%d", &opcion);
														
												}else if (aux1==0){
													printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste ");
														scanf("%d", &opcion);
												}
											case '2':
												fila= fila+1;
												int aux2= matriz[fila][columna];
												if (fila>9){
													printf("Se ha salido de los bordes de la ciudad.");
												}else if(aux2!= 0){
														aux2= aux2-1;
														contadorEdificios= contadorEdificios-1;
														matriz[fila][columna]= aux2;
														printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
														scanf("%d", &opcion);
												}else if (aux2==0){
													printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
														scanf("%d", &opcion);
												}	
											case '3':
												columna= columna+1;
												int aux3= matriz[fila][columna];
												if (columna>9){
													printf("Se ha salido de los bordes de la ciudad.");
												}else if(aux3!= 0){
														aux3= aux3-1;
														contadorEdificios= contadorEdificios-1;
														matriz[fila][columna]= aux3;
														printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
														scanf("%d", &opcion);
												}else if (aux3==0){
													printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
														scanf("%d", &opcion);
												}
											case '4': 
												columna= columna-1;
												int aux4= matriz[fila][columna];
												if (columna<0){
													printf("Se ha salido de los bordes de la ciudad.");
												}else if(aux4!= 0){
														aux4= aux4-1;
														contadorEdificios= contadorEdificios-1;
														matriz[fila][columna]= aux4;
														printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
														scanf("%d", &opcion);
												}else if (aux4==0){
													printf("Ingrese su siguiente accion (1.Norte, 2.Sur, 3. Este, 4. Oeste, 5. Salir");
														scanf("%d", &opcion);
												}	
					

					
                      			
         }

    } while ( opcion != '4' );

 

	fclose(archivoOrigen);


	/* Programa: Menú de opciones (Solución 3) */

int main(){
   
    return 0;
}
	
	

