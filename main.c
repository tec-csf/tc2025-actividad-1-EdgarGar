//Edgar Adrian Garcia Villegas
//A01021730

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructuras
typedef struct {
	char* nombre;
	char* apellidos;
	int edad;
	char* telefono;
} persona;

typedef struct {
	int id;
	persona* p;
} cama;

//funciones 
int agregarCamas(cama** camas, int** disponibles, int totalCamas, int* totalDisponibles, int n);
void agregarPersona(cama* camas, int id, int maxLen);
int agregarDisponible(int** disponibles, int id, int total);
int encontrarDisponible(int** disponibles, int* total);

int buscarCama(int total);
void imprimirCama(cama* camas, int id);
void listarPersonas(cama* camas, int total);

void altaPersona(cama* camas, int id, int** disponibles, int* totalDisponibles);
void liberarCamas(cama* camas, int total);
char* obtenerDatos(char* str, int maxLen);

int main() {
	int numInicial, maxLen, totalCamas = 0, totalDisponibles = 0, opcion, id;
	printf("---------Bienvenido al Registro Hospitalario--------------");
	//Se ingresa una cadena maxima para reservar un cierto espacio de memoria
	printf("\nTamaño maximo del nombre: ");
	scanf("%d", &maxLen);
	printf("Número inicial de camas: ");
	scanf("%d", &numInicial);

	cama* camas = NULL;
	int* disponibles = NULL;
	totalCamas = agregarCamas(&camas, &disponibles, totalCamas, &totalDisponibles, numInicial);

	//Menu 
	do {
		printf("\n1. Incorporar persona\n2. Buscar cama\n3. Dar de alta a la persona\n4. Lista de personas\n5. Ver camas disponibles\n0. Salir \nSelecciona una opcion: ");
		scanf("%d", &opcion);
		getchar();

		switch(opcion) {
			case 1:
				if (totalDisponibles == 0) {
					printf("Se agregaron nuevas camas :) ...\n");
					totalCamas = agregarCamas(&camas, &disponibles, totalCamas, &totalDisponibles, 5);
				}
				id = encontrarDisponible(&disponibles, &totalDisponibles);
				agregarPersona(camas, id, maxLen);
				break;
			case 2:
				id = buscarCama(totalCamas);
				if (id != -1)
					imprimirCama(camas, id);
				break;
			case 3:
				id = buscarCama(totalCamas);
				if (id != -1)
					altaPersona(camas, id, &disponibles, &totalDisponibles);
				break;
			case 4:
				listarPersonas(camas, totalCamas);
				break;
			case 5:
				printf("Camas disponibles: %d\nCamas ocupadas: %d\n", totalDisponibles, totalCamas - totalDisponibles);
				break;
			case 0:
				break;
			default:
				printf("Opción no válida\n");
		}
	} while (opcion != 0);

	liberarCamas(camas, totalCamas);
	free(disponibles);
	free(camas);
	return 0;
}

//Agregacion de camas
int agregarCamas(cama** camas, int** disponibles, int totalCamas, int* totalDisponibles, int n) {
	*camas = realloc(*camas, (totalCamas+n) * sizeof(cama));
	cama *c, *end = *camas + totalCamas + n;

	for (c = *camas + totalCamas; c < end; ++c) {
		c->id = ++totalCamas;
		c->p = NULL;
		*totalDisponibles = agregarDisponible(disponibles, c->id, *totalDisponibles);
	}
	return totalCamas;
}

//Agregar persona nuevo
void agregarPersona(cama* camas, int id, int maxLen) {
	printf("Cama %d\n", id);
	cama* c = camas + id - 1;

	c->p = (persona*) malloc(sizeof(persona));
	c->p->nombre = (char*) malloc(maxLen * sizeof(char));
	c->p->apellidos = (char*) malloc(maxLen * sizeof(char));
	c->p->telefono = (char*) malloc(maxLen * sizeof(char));

	printf("Nombre: ");
	obtenerDatos(c->p->nombre, maxLen);
	printf("Apellidos: ");
	obtenerDatos(c->p->apellidos, maxLen);
	printf("Edad: ");
	scanf("%d", &c->p->edad);
	getchar();
	printf("Teléfono: ");
	obtenerDatos(c->p->telefono, maxLen);
}

//Agregar
int agregarDisponible(int** disponibles, int id, int total) {
	*disponibles = realloc(*disponibles, (total + 1) * sizeof(int));
	*(*disponibles + total) = id;
	return total + 1;
}

//Busqueda de Disponibilidad
int encontrarDisponible(int** disponibles, int* total) {
	int id = *(*disponibles + --(*total));
	*disponibles = realloc(*disponibles, *total * sizeof(int));
	return id;
}

//Busqueda de Cama
int buscarCama(int total) {
	int id;	
	printf("ID de la cama: ");
	scanf("%d", &id);
	getchar();

	if (id >= 1 && id <= total)
		return id;
	else {
		printf("No hay una cama con ese ID\n");
		return -1;
	}
}

//Datos de la cama
void imprimirCama(cama* camas, int id) {
	cama* c = camas + id - 1;
	if (c->p)
		printf("La persona: %s %s, %d años, Tel: %s\n", c->p->nombre, c->p->apellidos, c->p->edad, c->p->telefono);
	else
		printf("Cama disponible\n");
}

//Lista de los personas 
void listarPersonas(cama* camas, int total) {
	cama* c;
	for (c = camas; c < camas + total; ++c) {
		if (c->p)
			printf("Cama %d -> persona: %s %s, %d años, Tel: %s\n", c->id, c->p->nombre, c->p->apellidos, c->p->edad, c->p->telefono);
	}
}

//Datos de persona dado de alto
void altaPersona(cama* camas, int id, int** disponibles, int* totalDisponibles) {
	cama* c = camas + id - 1;
	free(c->p->nombre);
	free(c->p->apellidos);
	free(c->p->telefono);
	free(c->p);
	c->p = NULL;

	*totalDisponibles = agregarDisponible(disponibles, id, *totalDisponibles);
	printf("La Persona fue dado de alta\n");
}

//Liberacion de camas
void liberarCamas(cama* camas, int total) {
	cama* c;
	for (c = camas; c < camas + total; ++c) {
		if (c->p) {
			free(c->p->nombre);
			free(c->p->apellidos);
			free(c->p->telefono);
			free(c->p);
		}
	}
}

//Obtencion de cadenas
char* obtenerDatos(char* str, int maxLen) {
	fgets(str, maxLen, stdin);
	*(str + strcspn(str, "\n")) = 0;
	return 0;
}
