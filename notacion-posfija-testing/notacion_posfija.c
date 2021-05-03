#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "notacion_posfija.h"
#include "pila.h"
#include "cola.h"

#define SUMA "+"
#define RESTA "-"
#define DIVISION "/"
#define RAIZ "sqrt"
#define OPERADOR_TERNARIO "?"

int raiz(int *numero_a) {
  return (int) sqrt(*numero_a);
}

int sumar(int *numero_a, int *numero_b) {
  return *numero_b + *numero_a;
}

int restar(int *numero_a, int *numero_b) {
  return *numero_b - *numero_a;
}

int dividir(int *numero_a, int *numero_b) {
  return *numero_b / *numero_a;
}

int terciarizar(int *numero_a, int *numero_b, int *numero_c) {
  return *numero_c ? *numero_b : *numero_a;
}

bool es_operador(char *str) {
  return !strcmp(str, SUMA) || !strcmp(str, RESTA) || !strcmp(str, DIVISION) || !strcmp(str, OPERADOR_TERNARIO) || !strcmp(str, RAIZ);
}

bool operador_es_binario(char *str) {
  return !strcmp(str, SUMA) || !strcmp(str, RESTA) || !strcmp(str, DIVISION);
}

bool operador_es_ternario(char *str) {
  return !strcmp(str, OPERADOR_TERNARIO);
}

bool validar_notacion_posfija(char **strv) {
  int count = 0;
  for(size_t i = 0; strv[i]; i++) {
    if(!es_operador(strv[i])) {
      count++;
    } else {
      if(operador_es_binario(strv[i])) {
        if(count < 2) {
          return false;
        } else {
          count--;
        }
      } else if(operador_es_ternario(strv[i])) {
        if(count < 3) {
          return false;
        } else {
          count -= 2;
        }
      }
    } 
  }
  return true;
}

void operador_unario(pila_t *pila_numeros, int operacion(int *)) {
  int *a = (int *)pila_desapilar(pila_numeros);
  int *resultado = calloc(1, sizeof(int));
  *resultado = operacion(a);
  free(a);
  pila_apilar(pila_numeros, resultado);
}

void operador_binario(pila_t *pila_numeros, int operacion(int *, int *)) {
  int *a = (int *)pila_desapilar(pila_numeros);
  int *b = (int *)pila_desapilar(pila_numeros);
  int *resultado = calloc(1, sizeof(int));
  *resultado = operacion(a, b);
  free(a);
  free(b);
  pila_apilar(pila_numeros, resultado);
}

void operador_ternario(pila_t *pila_numeros, int operacion(int *, int *, int *)) {
  int *a = (int *)pila_desapilar(pila_numeros);
  int *b = (int *)pila_desapilar(pila_numeros);
  int *c = (int *)pila_desapilar(pila_numeros);
  int *resultado = calloc(1, sizeof(int));
  *resultado = operacion(a, b, c);
  free(a);
  free(b);
  free(c);
  pila_apilar(pila_numeros, resultado);
}

void operar(char **strv, pila_t *pila_numeros) {
  for(size_t i = 0; strv[i]; i++) {
    if(!es_operador(strv[i])) {
      int *numero = calloc(1, sizeof(int));
      *numero = atoi(strv[i]);
      pila_apilar(pila_numeros, numero);
    } else {
      if(!strcmp(strv[i], SUMA)) {
        operador_binario(pila_numeros, sumar);
      }
      if(!strcmp(strv[i], RESTA)) {
        operador_binario(pila_numeros, restar);
      }
      if(!strcmp(strv[i], DIVISION)) {
        operador_binario(pila_numeros, dividir);
      }
      if(!strcmp(strv[i], OPERADOR_TERNARIO)) {
        operador_ternario(pila_numeros, terciarizar);
      }
      if(!strcmp(strv[i], RAIZ)) {
        operador_unario(pila_numeros, raiz);
      }
    }
  }
}

int notacion_posfija(char **strv) {
  pila_t *pila_numeros = pila_crear();
  operar(strv, pila_numeros);
  int resultado = *(int *) pila_ver_tope(pila_numeros);
  while(!pila_esta_vacia(pila_numeros)) {
    free(pila_desapilar(pila_numeros));
  }
  pila_destruir(pila_numeros);
  return resultado;
}

