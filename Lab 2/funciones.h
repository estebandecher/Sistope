#ifndef FUNCIONES_H
#define FUNCIONES_H

typedef struct{
	//Dato energia
	int energy;
	//Datos de limites
	double leftLimit;
	double rigthLimit;
	double uppperLimit;
	double lowerLimit;
	//Datos de posicion
	int posX;
	int posY;
}casilla;

//Estructura matriz
typedef struct{
	//Dato energia
	casilla ** casilla;
	//Datos tamaño matriz
	int XValue;
	int YValue;
	int LValue;
	double delta;
	unsigned int *state;
	int bValue;
}Grilla;

//Grilla *grilla=(Grilla *)malloc(sizeof(Grilla));
int valor;

pthread_mutex_t mutex;

//Funcion para determinar a que casilla corresponde cierta posicion en X
int posXGrilla(Grilla *grilla, double ubicacionX);

//Funcion para determinar a que casilla corresponde cierta posicion en Y
int posYGrilla(Grilla *grilla, double ubicacionY);

//Funcion para crear la grilla
void crearGrilla(Grilla *grilla, int XValue, int YValue, int LValue, float dValue, int bValue);

//Funcion que libera memoria de la grilla
void eliminarGrilla(Grilla *grilla);

//Se llena la grilla
//se asigna energia
//se asignan limites superiores e inferiores
void llenarGrilla(Grilla *grilla);

// Se crea el archivo de salida
void crearArchivo(Grilla *grilla);

//Funcion para calcular el largo del movimiento
double getRandomLarge(unsigned int *mystate);

//Funcion de la hebra
void funcionFoton(void *arg);

#endif
