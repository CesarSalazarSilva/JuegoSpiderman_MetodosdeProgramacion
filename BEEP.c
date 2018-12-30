#include<stdio.h>
#include<stdlib.h>

int Matriz[10][10] ={
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

int fila = 10;
int columna = 10;
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
	int arreglo[10][10];
	int px;
	int py;
	int contenido;
	char dedondeviene;
};

//Funcion Crear Estado
//Entrada : id actual del estado a crear, id del estado del que viene , posicionx,posiciony en este estado, mapa anterior
//Salida : Estado 
estado CrearEstado(int * idn, int idAnteriorn, int pxn, int pyn,char dedondevienen, int Matrizanteriorn[10][10] ){
	estado nuevoEstado;
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

//Funcion agregar estado a un arreglo
//Entrada : el estado a agregar y el puntero de lista a añadir ese estado mas su tamaño
//Salida : lista nueva con el estado agregado
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

//Funcion que borra el primer estado en la lista
//Entrada :
//Salida :
estado *BorrarEstado(estado *lista,int * largolista){
	estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*largolista-1));
    for (int i = 1 ; i < *largolista ; ++i){
        nuevaLista[i-1] = lista[i];
    }
    *largolista -= 1;
    free(lista);
    return nuevaLista;
}

//Conjunto de funciones que revisan si exite un moviento a la direccion señalada en el nombre de la funcion
//Entrada
//Salida respectivamente un booleano 1 si exite movimiento posible, 0 para lo contrario 
int revisarN(estado EstadoActual){
	// Retorna que si hay movimiento
	if (EstadoActual.py > 0){
		if(EstadoActual.arreglo[EstadoActual.py-1][EstadoActual.px] != 0 ){
	        return 1;
	    }
	}
	// Retorna que no hay moviento  
    return 0;
}
int revisarS(estado EstadoActual){
	if (EstadoActual.py < fila-1){
		if (EstadoActual.arreglo[EstadoActual.py+1][EstadoActual.px] != 0){
	        return 1;
		}
    }
    return 0;
}
int revisarE(estado EstadoActual){
    if (EstadoActual.px < columna-1){
    	if (EstadoActual.arreglo[EstadoActual.py][EstadoActual.px+1] != 0){
	        return 1;
    	}
    }
    return 0;
}
int revisarO(estado EstadoActual){
    if (EstadoActual.px > 0){
    	if (EstadoActual.arreglo[EstadoActual.py][EstadoActual.px-1] != 0){
	        return 1;
    	} 
    }
    return 0;
}

//Funcion que revisa si el estado actual puede seguir moviendose
//Entrada : el estado actual, lista de movimientos abiertos.
//Salida : si tiene movimientos posibles
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

//Funcion que revisa si el estado actual contiene la solucion final
//Entrada : el estado actual.
//Salida : si tiene movimientos posibles
int EncontroSolucionFinal(estado EstadoActual){
	for (int i = 0; i < fila; ++i){
		for (int j = 0; j < columna; ++j){
			if (EstadoActual.arreglo[i][j] != 0){
				return 0;
			}
		}
	}
	return 1;
}

//Funcion busca la posicion de un estado que da origen al estado tenido en un arreglo.
//Entrada : Una arreglo de estados, el largo de ese arreglo y el estado a buscar su predecesor
//Salida : Un entero que es la posicion en el arreglo del estado predecesor del estado entregado
int Anterior(estado * lista,int largolista,estado Estadofinal){
    for (int i = 0; i<largolista ; ++i){
        if((lista[i].id == Estadofinal.idAnterior)){
        	if (lista[i].px == ConversionX(Estadofinal) && lista[i].py == ConversionY(Estadofinal)){
        		return i;
        	}
            
        }
    }
}

//Funcion que entrega un arreglo con la solucion de pasos a seguir 
//Entrada : El estado final lista estados Cerrados para buscar el camino a devolver  
//Salida : un arreglo con las instruciones para salir 

void mostrarsolucion(char ultimoMovimiento,estado * lista, int largolista, estado Estadofinal){
	if (ultimoMovimiento == 'N'){
		printf("\n Ve hacia el : Sur");
	}
	if (ultimoMovimiento == 'S'){
		printf("\n Ve hacia el : Norte");
	}
	if (ultimoMovimiento == 'O'){
		printf("\n Ve hacia el : Este");
	}
	if (ultimoMovimiento == 'E'){
		printf("\n Ve hacia el : Oeste");
	}

	int ultimo = Anterior(lista,largolista,Estadofinal);

    while(lista[ultimo].dedondeviene != 'I'){
        if (lista[ultimo].dedondeviene == 'N'){
            printf("\n Ve hacia el : Sur");
        }
        if (lista[ultimo].dedondeviene == 'S'){
            printf("\n Ve hacia el : Norte");
        }
        if (lista[ultimo].dedondeviene == 'E'){
            printf("\n Ve hacia el : Oeste");
        }
        if (lista[ultimo].dedondeviene == 'O'){
            printf("\n Ve hacia el : Este");
        }
        ultimo = Anterior(lista,largolista,lista[ultimo]);
    }
    printf("\n Este es el inicio I(0,5) la instruccion de arriba te llevará a la salida !! \n");
}

//Revisa si el estado a Analizar contiene 2 conjuntos separados de edificios 
//Entrada : Un estado a analizar
//Salida : Un booleano, 1 para cuando exista 2 conjuntos separados, 0 para un estado que solo tenga un unico 
//conjunto a recorrer
int DiscriminarEstados(estado EAR){
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

	//revisamos la lista que exista una secuencia 1-0-1 en filas
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
	//revisamos la lista que exista una secuencia 1-0-1 en columnas
	for (int i = 0; i < columna-1; ++i){
		if (i<columna-4){
			if (auxC[i]==1 &&auxC[i+1]==0 && auxC[i+2]==1){
				return 1;
			}
		
		}
	}

	return 0;
}

//Funcion que entrega las posiciones validas para iniciar 
//Entrada : un arreglo el cual representa la ciudad
//Salida : un arreglo con las posiciones validas para iniciar en la fila superior que contenga edificos
int ** IniciosPosibles(int arreglo[fila][columna], int * aux){
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


int BEE(int Matriz[fila][columna],int fila,int columna, int posicionIX,int posicionIY){
	int canAbiertos = 0;
    int canCerrados = 0;
    //LEA lista estados abiertos
    estado * LEA = (estado *)malloc(sizeof(estado)*canAbiertos);
    //LER lista estados recorridos
    estado * LER = (estado *)malloc(sizeof(estado)*canCerrados);
    //Se crea el estado inicial 
    estado inicial = CrearEstado(&correlativo,posicionIX,posicionIY,0,'I',Matriz);
    //Agregamos a la lista de los estados 
    LEA = AgregarEstado(LEA,&canAbiertos,inicial);
    printf("El Estado  Inicial es : \n");
			for (int i = 0; i < fila; ++i){
				for (int j = 0; j < columna; ++j){
					printf(" %d," ,inicial.arreglo[i][j]);
				}
				printf("\n");
			}
	printf("----------------------------------------------\n");
	
	while(canAbiertos > 0){
		estado eActual = LEA[0];
		//Revisamos si este estado contiene la solucion, es decir deja el mapa en 0 
		//No borramos este estado para que no acuse luego que no encontramos solucion
		if (EncontroSolucionFinal(LEA[0]) == 1){
			//Muestra la solucion 
			//Devolver pasos para salir 
			printf("El Arreglo quedo como : \n");
			for (int i = 0; i < fila; ++i){
				for (int j = 0; j < columna; ++j){
					printf(" %d," ,eActual.arreglo[i][j]);
				}
				printf("\n");
			}
			printf("Llegué mi rey !!!!!\n");
			printf("----------------------------------------------\n");
			mostrarsolucion(eActual.dedondeviene,LER,canCerrados,eActual);
			return 1;
		}
		correlativo+=1;
		if (revisarN(eActual) == 1){
			//Creamos un estado nuevo al norte del actual copiando el mapa anterior restando una a la llegada
			estado norte = CrearEstado(&correlativo,eActual.id,eActual.px,eActual.py-1,'S',eActual.arreglo);
			if(DiscriminarEstados(norte)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,norte);
			}
		}
		if (revisarS(eActual) == 1){
			//Creamos un estado nuevo 
			estado sur = CrearEstado(&correlativo,eActual.id,eActual.px,eActual.py+1,'N',eActual.arreglo);
			if(DiscriminarEstados(sur)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,sur);
			}
		}
		if (revisarO(eActual) == 1){
			//Creamos un estado nuevo 
			estado oeste = CrearEstado(&correlativo,eActual.id,eActual.px-1,eActual.py,'E',eActual.arreglo);
			if(DiscriminarEstados(oeste)==0){
				//Agregamos el Estado a ListaEstadoAbierto
				LEA = AgregarEstado(LEA,&canAbiertos,oeste);
			}
		}
		if (revisarE(eActual) == 1){
			//Creamos un estado nuevo 
			estado este = CrearEstado(&correlativo,eActual.id,eActual.px+1,eActual.py,'O',eActual.arreglo);
			if(DiscriminarEstados(este)==0){
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
		printf("No encontré solucion, generarlo de otro punto \n");
		return 0 ; 
	}
}

int main(){
	int aux = 0;
	int ** inicio = IniciosPosibles(Matriz,&aux);

	for (int i = 0; i < aux; ++i){
		printf("%d , ", inicio[i][0]);
		printf("%d\n", inicio[i][1]);
	}

	printf("---------------------------------\n" );
	printf("La matriz inicial es : \n");
			for (int i = 0; i < fila; ++i){
				for (int j = 0; j < columna; ++j){
					printf(" %d," ,Matriz[i][j]);
				}
				printf("\n");
			}
		printf("----------------------------------------------\n");

	for (int i = 0; i < aux; ++i){
		if(BEE(Matriz,fila,columna,inicio[i][0],inicio[i][1])){
			return 0;
		}
	}
}