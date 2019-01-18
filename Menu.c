#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include "BEE.h"
#include "BES.h"
#include "Inverso.h"
#include "recorridomanual.h"

int tamanio;

int main(){
	int ** ciudad,** inicio;
	int * iniSol;
	int ver,i,aux;
	char desicion,a;
	printf("Estoy decodificando el archivo...\n\n");
	ciudad = generarCiudad("entrada.txt", &tamanio);
	
	do{
		system("clear");
		printf("\n ------------------------------------------------------------- \n");
		printf("|                                                             |\n");
		printf("|                         MENU                                |\n");
		printf("|                                                             |\n");
		printf("| 0. Salir del juego.                                         |\n");
		printf("| 1. Verificar existencia de solución en ciudad.              |\n");
		printf("| 2. Mostrar solución y archivo solución.                     |\n");
		printf("| 3. Recorrido manual.                                        |\n");
		printf("| 4. Codificar una ciudad.                                    |\n");
		printf("|                                                             |\n");
		printf(" ------------------------------------------------------------- \n");
		printf("Seleccione lo que quiere hacer: ");
		scanf("%c", &desicion);
		printf("\n");

		switch(desicion) {
			case '0'  :
				system("clear");
				printf("Game Over.\n");
				//liberacion de la memoria usada por la Matriz
				for(i=0; i<10; i++){//CAMBIAR EL 5 CUADNO LA CIUDAD SE DEVUELVA BIEN
					free(ciudad[i]);
				}
				free(ciudad);
				exit(0);

		    case '1'  :
		    	system("clear");
		    	printf("\n Verificando existencia de solucion en el la ciudad entregada ...\n\n");
		    	aux = 0;
				inicio = IniciosPosibles(ciudad,&aux,tamanio,tamanio);
				iniSol = crearconjuntosolucion(aux);
				for (int i = 0; i < aux; ++i){
					if(BEE(ciudad,tamanio,tamanio,inicio[i][0],inicio[i][1],0) == 1){
						iniSol[i]=1; 
					}else{
						iniSol[i]=0;
					}
				}
				ver = 0;
				for (i = 0; i < aux; ++i){
					if (iniSol[i] == 1){
						ver+=1;
						printf("\n Hay solucion en : %d,%d \n",inicio[i][0]+1,inicio[i][1]+1);
					}					
				}
				if (ver==0){
					printf("\n No hay solucion\n");
				}	
				printf("Presione Enter para continuar \n");
				getchar();
				getchar();
		    	break; 

		    case '2'  :
		    	system("clear");
				aux = 0;
				inicio = IniciosPosibles(ciudad,&aux,tamanio,tamanio);
				iniSol = crearconjuntosolucion(aux);
				for (int i = 0; i < aux; ++i){
					if(BEE(ciudad,tamanio,tamanio,inicio[i][0],inicio[i][1],1) == 1){
						iniSol[i]=1; 
					}else{
						iniSol[i]=0;
					}
				}
				ver = 0;
				for (i = 0; i < aux; ++i){
					if (iniSol[i] == 1){
						ver+=1;
						printf("\n Hay solucion en : %d,%d \n",inicio[i][0]+1,inicio[i][1]+1);
					}					
				}
				if (ver==0){
					printf("\n No hay solucion\n");
				}			
				printf("Presione Enter para continuar \n");
				getchar();
				getchar();
		    	break; 

		    case '3'  :
		    	system("clear");
		    	printf("Estoy preparando tu juego.\n\n");
		    	recorridoManual(ciudad);
		    	printf("Presione Enter para continuar \n");
				getchar();
				getchar();
		    	break; 

		    case '4'  :
		    	system("clear");
		      	printf("Creando el archivo con la ciudad codificada.\n\n");
		      	Inverso(ciudad,tamanio);
		      	printf("Presione Enter para continuar \n");
				getchar();
				getchar();
		      	break; 

			default :
				system("clear"); 
				printf("Por favor ingrese una opción válida.");
				printf("Presione Enter para continuar \n");
				getchar();
				getchar();
				break;
		}

	}while(desicion != '0' );
	return 0;
}