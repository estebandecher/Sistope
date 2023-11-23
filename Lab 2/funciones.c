#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "funciones.h"

//Funcion para determinar a que casilla corresponde cierta posicion en X
int posXGrilla(Grilla *grilla, double ubicacionX){

	double xLimit;

	xLimit = grilla->XValue * (grilla->delta / 2) * -1;

	int x = 0;

	while (x < grilla->XValue){
		//Si la ubicacion es menor al limite
		if (ubicacionX < xLimit){
			return -1;
		}
		else if ((ubicacionX >= grilla->casilla[x][0].uppperLimit) && (ubicacionX < grilla->casilla[x][0].lowerLimit)){
			return x;
		}
		x++;
	}
	return -2;
}

//Funcion para determinar a que casilla corresponde cierta posicion en Y
int posYGrilla(Grilla *grilla, double ubicacionY){

	double yLimit;

	yLimit = grilla->YValue * (grilla->delta / 2) * -1;
	int y = 0;

	while (y < grilla->YValue){
		//Si la ubicacion es menor al limite
		if (ubicacionY < yLimit){
			return -1;
		}
		else if ((ubicacionY >= grilla->casilla[0][y].leftLimit) && (ubicacionY < grilla->casilla[0][y].rigthLimit)){
			return y;
		}
		y++;
	}
	return -2;
}

//Funcion para crear la grilla
void crearGrilla(Grilla *grilla, int XValue, int YValue, int LValue, float dValue, int bValue){

	int i = 0;
	//asignando valores
	grilla->XValue = XValue;
	grilla->YValue = YValue;
	grilla->LValue = LValue;
	grilla->delta = dValue;
	grilla->bValue = bValue;

	//Memoria por filas
	grilla->casilla = (casilla**)malloc(XValue * sizeof(casilla*));
	//Asignar memoria a matriz por columna
	for (i = 0; i < XValue; i++){
		grilla->casilla[i] = (casilla*)malloc(YValue * sizeof(casilla));
	}
}

//Funcion que libera memoria de la grilla
void eliminarGrilla(Grilla *grilla){
	int i = 0, j = 0;
	//casilla *ptrAux=grilla->casilla[i][j];
	//ptrAux=grilla->casilla[i][j];
	for (i = 0; i < grilla->XValue; i++){
		free(grilla->casilla[i]);
	}
	free(grilla);
}

//Se llena la grilla
//se asigna energia
//se asignan limites superiores e inferiores
void llenarGrilla(Grilla *grilla){

	int i = 0, j = 0, z = 0;
	double xLimit;
	double yLimit;

	yLimit = grilla->YValue * (grilla->delta / 2) * -1;
	xLimit = grilla->XValue * (grilla->delta / 2) * -1;

	for (i = 0; i < grilla->XValue; i++){
		for ( j = 0; j < grilla->YValue; j++){
			//energia
			grilla->casilla[i][j].energy = 0;
			//limites superiores
			grilla->casilla[i][j].leftLimit = yLimit;
			grilla->casilla[i][j].uppperLimit = xLimit;
			//sumando delta
			//xLimit=xLimit+grilla->delta;
			yLimit = yLimit + grilla->delta;
			//limites superiores
			grilla->casilla[i][j].rigthLimit = yLimit;
			grilla->casilla[i][j].lowerLimit = xLimit + grilla->delta;

			z++;
		}
		yLimit = grilla->YValue * (grilla->delta / 2) * -1;
		xLimit = xLimit + grilla->delta;
	}
}

// Se crea el archivo de salida
void crearArchivo(Grilla *grilla){

	int i = 0, j = 0;

	FILE *fp = fopen("salida.txt", "w");

	for (i = 0; i < grilla->XValue; i++){
		for (j = 0; j < grilla->YValue; j++){
			fprintf(fp, "< %d\t[%d][%d]>\n", grilla->casilla[i][j].energy, i, j);
		}
	}

	fclose(fp);

}

//Funcion para calcular el largo del movimiento
double getRandomLarge(unsigned int *mystate){
	double r;
	double l;
	r = ((double)rand_r(mystate)) / RAND_MAX;
	l = log(1 - r) * -1;
	return l;
}

//Funcion para obtener el modulo del vector unitario
double getModulo(int randX, int randY){

	int modulo;
	int zum = pow(randX, 2) + pow(randY, 2);
	modulo = sqrt(zum);

	return modulo;
}

//Funcion de la hebra
void funcionFoton(void *arg){

	Grilla *grilla = (Grilla *) arg;

	//Distancia recorrida foton
	double l = 0.0;
	//Posicion inicial foton
	double posXActual = 0.0;
	double posYActual = 0.0;

	//Variable para saber si foton se encuentra dentro de grilla
	int fuera = 0;

	//Vector
	int vectorX;
	int vectorY;
	//Probabilidad
	int probabilidadSigno;

	//Vector Modulo
	double modulo;
	double unitarioX;
	double unitarioY;

	//Largo de recorrido
	double largo;

	//Distancia a recorrer por el foton
	double distanciaX;
	double distanciaY;

	//Posicion casilla
	int posX;
	int posY;

	//Probabilidad de liberar energia
	int probabilidadAccion;



  // Se asgina un estado para cada hebra en particular,
	// así aumenta el poder del random y es más Variable.
	unsigned int *estado = grilla->state;
  *estado = time(NULL) ^ getpid();

	//Mientras el largo recorrido
	while (l < grilla->LValue && fuera != 1){

		//Vector en x
		vectorX = rand_r(estado) % (grilla->XValue / 2) + 1;
		probabilidadSigno = rand_r(estado) % 100;
		if (probabilidadSigno < 50){
			vectorX = vectorX * -1;
		}

		//Vector en y
		vectorY = rand_r(estado) % (grilla->YValue / 2) + 1;
		probabilidadSigno = rand_r(estado) % 100;
		if (probabilidadSigno < 50){
			vectorY = vectorY * -1;
		}

		//Vector Unitario
		modulo = getModulo(vectorX,vectorY);
		unitarioX = vectorX / modulo;
		unitarioY = vectorY / modulo;

		//Largo de recorrido
		largo = getRandomLarge(estado);

		//Distancia a recorrer por el foton
		distanciaX = largo * unitarioX;
		distanciaY = largo * unitarioY;

		//Nueva ubicacion del foton
		posXActual = posXActual + distanciaX;
		posYActual = posYActual + distanciaY;

		//Establecer en que casilla se encuentra el foton
		posX = posXGrilla(grilla, posXActual);
		posY = posYGrilla(grilla, posYActual);

		pthread_mutex_lock(&mutex);

		//Ver si el vector se escapa de la grilla
		if((posX >= 0) && (posY >= 0)){
			if(grilla->bValue == 1){
				printf("\tSoy el foton con valor: %u.\n", (unsigned int)pthread_self());
				printf("\tMe muevo con largo l: %f.\n",  largo);
				printf("\tLLegando a la casilla [%d][%d] de la grilla.\n", posX, posY);
				printf("\tCuyo valor superior es %f, su valor inferior es %f,\n",
								grilla->casilla[posX][posY].uppperLimit,
								grilla->casilla[posX][posY].lowerLimit);
				printf("\tsu limite izquierdo es %f y su limite derecho es %f\n",
								grilla->casilla[posX][posY].leftLimit,
								grilla->casilla[posX][posY].rigthLimit);
			}
			//Determinar si se hace absorcion o ...
			probabilidadAccion = rand_r(estado) % 100;
			if (probabilidadAccion < 50){
				//Agregar energia
				grilla->casilla[posX][posY].energy = grilla->casilla[posX][posY].energy + 1;
				if(grilla->bValue == 1){
					printf("\tDonde realizo uno absorcion, dejando en esa casilla un valor de energia: %d.\n\n", grilla->casilla[posX][posY].energy);
				}
			}
			else{
				if(grilla->bValue == 1){
					printf("\tDonde realizo uno difusion.\n\n");
				}
			}
			//Aumentar la cantidad de distancia recorrida
			l = l + largo;
		}
		else{
			fuera = 1;
			if(grilla->bValue == 1){
				printf("\tSoy el foton con valor: %u.\n", (unsigned int)pthread_self());
				printf("\tMe muevo con largo l: %f.\n", l);
				printf("\tPero me salgo de la grilla.\n\n");
			}
		}
		pthread_mutex_unlock(&mutex);

		sleep(0);
	}

	//Si ya se recorrio la distancia maxima
	//Hace un evento de absorcion
	pthread_mutex_lock(&mutex);
	//Establecer en que casilla se encuentra el foton
	posX = posXGrilla(grilla, posXActual);
	posY = posYGrilla(grilla, posYActual);
	grilla->casilla[posX][posY].energy = grilla->casilla[posX][posY].energy + 1;
	pthread_mutex_unlock(&mutex);

}
