#include<stdio.h>
#include<stdlib.h>

int Matriz[15][15] =
{
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,1,1,1,1,1,0,1,1,1,1,1,0},
{0,1,0,1,1,0,0,0,0,0,0,0,1,0,0},
{0,1,0,1,1,1,1,1,0,1,1,0,1,0,1},
{0,1,0,1,1,0,1,1,0,1,1,0,1,0,1},
{0,1,0,1,0,0,0,0,0,1,1,0,1,0,1},
{0,0,0,1,0,1,1,1,1,1,1,0,0,0,1},
{1,1,1,1,0,1,1,1,1,1,1,0,1,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
{1,0,1,1,1,0,1,1,1,0,1,0,1,0,1},
{1,0,1,1,1,0,0,1,1,0,1,0,1,0,1},
{1,1,1,0,0,1,0,0,1,0,0,0,0,0,1},
{0,1,1,1,0,1,1,0,1,0,1,1,0,1,1},
{0,0,0,0,0,1,1,2,1,0,1,1,0,1,1}
};

typedef struct estado estado;

struct estado{
    int idx;
    int idy;
    int contenido;
    int idax;
    int iday;
    char dedondeviene;
};

estado crearEstado(int idx, int idy, int idax, int iday,char dedondeviene){

    estado nuevoEstado;
    nuevoEstado.idx = idx;
    nuevoEstado.idy = idy;
    nuevoEstado.contenido = Matriz[idy][idx];
    nuevoEstado.idax = idax;
    nuevoEstado.iday = iday;
    nuevoEstado.dedondeviene = dedondeviene;

    return nuevoEstado;
}

estado *agregarEstado(estado * lista, int * largolista, estado estadoaAgregar){
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

estado * eliminarEstado(estado * lista, int *largolista){
    estado * nuevaLista = (estado *)malloc(sizeof(estado)*(*largolista-1));
    for (int i = 1 ; i < *largolista ; ++i){
        nuevaLista[i-1] = lista[i];
    }
    *largolista -= 1;
    free(lista);
    return nuevaLista;
}


int revisarN(int x, int y){
    if(Matriz[y-1][x] == 0 || Matriz[y-1][x] == 2){
        return 1;
    }
    return 0;
}
int revisarS(int x, int y){
    if (Matriz[y+1][x] == 0 || Matriz[y+1][x] == 2){
        return 1;
    }
    return 0;
}
int revisarE(int x, int y){
    if (Matriz[y][x+1] == 0 || Matriz[y][x+1] == 2){
        return 1;
    }
    return 0;
}
int revisarO(int x, int y){
    if (Matriz[y][x-1] == 0 || Matriz[y][x-1] == 2){
        return 1;
    }
    return 0;
}

int revisarExistencia(estado estadoporrevisar, estado * Lista, int largolista){
    for (int i = 0; i < largolista; ++i){
        if ((estadoporrevisar.idx == Lista[i].idx) && (estadoporrevisar.idy == Lista[i].idy)){
            return 1;
        }
    }
    return 0;
}
int anterior(estado * lista,int largolista,int x, int y){
    for (int i = 0; i < largolista; ++i){
        if((lista[i].idx == x) && (lista[i].idy == y)){
            return i;
        }
    }

}

void mostrarsolucion(estado * lista, int ultimo,int ultimo2, int largolista){
    printf("\n He procesado el Laberinto, te entregare los pasos a seguir para encontrar la primera salida, \n sigue el los pasos de abajo hacia arriba : ");
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
        ultimo = anterior(lista,largolista,lista[ultimo].idax,lista[ultimo].iday);
    }
    printf("\n Este es el inicio I(0,0) la instruccion de arriba te llevará a la salida !! \n");
}
   

int main(){
   
    int canAbiertos = 0;
    int canCerrados = 0;
    estado * abiertos = (estado *)malloc(sizeof(estado)*canAbiertos);
    estado * cerrados = (estado *)malloc(sizeof(estado)*canCerrados);
    estado inicial = crearEstado(0,0,0,0,'I');
    abiertos = agregarEstado(abiertos,&canAbiertos,inicial);


    while(canAbiertos>0){

        estado eActual = abiertos[0];

        if (eActual.idy != 0){
            if (revisarN(eActual.idx,eActual.idy) == 1){
                estado nuevoestado = crearEstado(eActual.idx,eActual.idy-1,eActual.idx,eActual.idy,'S');
                //Revisamos si esta en Abiertos
                if (revisarExistencia(nuevoestado,abiertos,canAbiertos)==0 && revisarExistencia(nuevoestado,cerrados,canCerrados)==0){

                    abiertos = agregarEstado(abiertos,&canAbiertos,nuevoestado);
                }
            }
        }
        if(eActual.idy != 14){
            if (revisarS(eActual.idx,eActual.idy) == 1){
                estado nuevoestado = crearEstado(eActual.idx,eActual.idy+1,eActual.idx,eActual.idy,'N');
                if (revisarExistencia(nuevoestado,abiertos,canAbiertos)==0 && revisarExistencia(nuevoestado,cerrados,canCerrados)==0){
                   
                    abiertos = agregarEstado(abiertos,&canAbiertos,nuevoestado);
                }
            }
        }
        if (eActual.idx != 14){
            if (revisarE(eActual.idx,eActual.idy) == 1){
                estado nuevoestado = crearEstado(eActual.idx+1,eActual.idy,eActual.idx,eActual.idy,'O');
                if (revisarExistencia(nuevoestado,abiertos,canAbiertos)==0 && revisarExistencia(nuevoestado,cerrados,canCerrados)==0){
                   
                    abiertos = agregarEstado(abiertos,&canAbiertos,nuevoestado);
                }
            }
        }
        if (eActual.idx != 0){
            if (revisarO(eActual.idx,eActual.idy) == 1){
                estado nuevoestado = crearEstado(eActual.idx-1,eActual.idy,eActual.idx,eActual.idy,'E');
                if (revisarExistencia(nuevoestado,abiertos,canAbiertos)==0 && revisarExistencia(nuevoestado,cerrados,canCerrados)==0){
                   
                    abiertos = agregarEstado(abiertos,&canAbiertos,nuevoestado);
                }
            }
        }

        cerrados = agregarEstado(cerrados,&canCerrados,eActual);
        abiertos = eliminarEstado(abiertos,&canAbiertos);

        if(eActual.contenido == 2){

            printf("Acabo de encontrar una salida, te diré como llegar a ella !! \n");
            mostrarsolucion(cerrados,canCerrados-1,canCerrados-1,canCerrados);
            // Del estado ultimo recorrer hasta el prmero
            return 0;
        }

    }


}

