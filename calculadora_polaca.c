#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char *str_crear(char *linea, size_t capacidad){
	char *str = malloc(capacidad * sizeof(char));
	if(!str) return NULL;
	strtok(linea, "\n");
	strcpy(str, linea);
	return str;
}

int main(int argc, const char *argv[]){
	/* Esto es por si nos pasan solo el ejecutable..
	 * pero no el archivo oper.txt*/
	if(argc != 1){
		fprintf(stderr, "%s\n", "Cantidad de parametros erronea");
		return 1;
	}

	/* Líneas necesarias para usar getline */
	char *linea = NULL;
	size_t capacidad;
	ssize_t leidos;
	while((leidos = getline(&linea, &capacidad, stdin )) != -1) {
		char *str = str_crear(linea, capacidad);
		/******************Editame***********************/
		
		printf("%s\n", str);

		/******************Fin Editame******************/
		free(str);
	}
	free(linea);
	return 0;
}
