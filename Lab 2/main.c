#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "funciones.h"
//Grilla *grilla=(Grilla *)malloc(sizeof(Grilla));
int valor = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main (int argc, char* argv[]){

	int c, i, nerror = 0;
	int nValue;
	int LValue;
	int XValue;
	int YValue;
	int bValue;
	double dValue;

	//Lectura de parametros con getopt
	while ((c=getopt(argc, argv, "n:L:X:Y:d:b")) != -1){

		switch(c){
			case ('n'):
				sscanf(optarg, "%d", &nValue);
				break;

			case 'L':
				sscanf(optarg, "%d", &LValue);
				break;

			case 'X':
				sscanf(optarg, "%d", &XValue);
				break;

			case 'Y':
				sscanf(optarg, "%d", &YValue);
				break;

			case 'd':
				sscanf(optarg, "%lf", &dValue);
				break;

			case 'b':
				bValue = 1;
				break;

			case '?':
				if (optopt == 'h'){
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				}
				else if(isprint(optopt)){
					fprintf(stderr, "Opcion Desconocida '-%c'.\n", optopt);
				}
				else{
					fprintf(stderr, "Opcion con caracter desconocido '\\X%x'\n", optopt);
				}
				return 1;
			default:
				abort();
		}
	}

	//Validacion de parametros de entrada
	if (nValue < 1){
		printf("\nNumeros de fotones ingresados menor a dos.");
		nerror++;
	}
	if (LValue <= 1){
		printf("\nDistancia máxima invalida.");
		nerror++;
	}
	if (XValue < 2 || XValue % 2 != 0){
		printf("\nDimensión de X invalida.");
		nerror++;
	}
	if (YValue < 2 || YValue % 2 != 0){
		printf("\nDimensión de Y invalida");
		nerror++;
	}
	//Si se existe al menos un error
	if (nerror != 0){
		printf("\nError\n");
		return 0;
	}

	printf("\n");
	printf("\nCantidad de fotones: %d", nValue);
	printf("\nLargo máximo de recorrido: %d", LValue);
	printf("\nCantidad de casillas horizontales: %d", XValue);
	printf("\nCantidad de casillas verticales: %d", YValue);
	printf("\nDistancia entre casillas : %f", dValue);
	if (bValue==1){
		printf("\nSe imprime la traza");	
	}
	else{
		printf("\nNo se imprime la traza");
	}
	printf("\n\n");

/*-------------------------------------------------------------------------------*/

	//Crear la matriz
	Grilla *grilla = (Grilla*)malloc(sizeof(Grilla));

	crearGrilla(grilla, XValue, YValue, LValue, dValue, bValue);

	grilla->state = (unsigned int*)malloc(nValue * sizeof(unsigned int));

	for(i = 0; i < nValue; i++){
		grilla->state[i] = 0;
	}

	//Se llena la grilla con 0
	llenarGrilla(grilla);

	if(grilla->bValue == 1){
		printf("\n\tCamino de los fotones:\n\n");
	}

	unsigned int state[nValue];

	pthread_t *hilos = (pthread_t*)malloc(nValue * sizeof(pthread_t));

	for(i = 0; i < nValue; i++){
		pthread_create(&hilos[i], NULL, (void *) funcionFoton, grilla);
	}

	for (i = 0; i < nValue; i++){
		pthread_join(hilos[i], NULL);
	}

	crearArchivo(grilla);

	//Liberar memoria
	eliminarGrilla(grilla);

	printf("\n");
	return 0;
}
