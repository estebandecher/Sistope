#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

//Variables Globales



int main (int argc, char* argv[]){

	int c;

	int nValue=0;
	int LValue=0;
	int XValue=0;
	int YValue=0;
	int dValue=0;
	int bValue=0;


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
				sscanf(optarg, "%d", &dValue);
				break;

			case 'b':
				//sscanf(optarg, "%d", &bValue);
				bValue=1; 
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
	

	printf("\nn: %d",nValue);
	printf("\nL: %d",LValue);
	printf("\nX: %d",XValue);
	printf("\nY: %d",YValue);
	printf("\nd: %d",dValue);
	printf("\nb: %d\n",bValue);


	return 0;
}
