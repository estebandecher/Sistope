#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


int main (int argc ,char* argv[]){

	printf("\n");

	int pidPadre = atoi(argv[1]);
	int signalSIGUSR1Counter = atoi(argv[2]);

	//Se aumenta la cantidad de veces que se ha ejecutado esta llamada
	signalSIGUSR1Counter++;

	//Se retorna el contador	
	return signalSIGUSR1Counter;
}
