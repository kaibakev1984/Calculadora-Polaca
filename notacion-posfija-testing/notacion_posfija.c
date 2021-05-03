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

bool raiz(int *numero_a, int *resultado) {
  if(!numero_a) return false;
  if(*numero_a < 0) return false;
  *resultado = (int) sqrt(*numero_a);
  return true;
}

bool sumar(int *numero_a, int *numero_b, int *resultado) {
  if(!numero_a || !numero_b) return false;
  *resultado = *numero_b + *numero_a;
  return true;
}

bool restar(int *numero_a, int *numero_b, int *resultado) {
  if(!numero_a || !numero_b) return false;
  *resultado = *numero_b - *numero_a;
  return true;
}

bool dividir(int *numero_a, int *numero_b, int *resultado) {
  if(!numero_a || !numero_b) return false;
  if(*numero_a == 0) return false;
  *resultado = *numero_b / *numero_a;
  return true;
}

bool terciarizar(int *numero_a, int *numero_b, int *numero_c, int *resultado) {
  if(!numero_a || !numero_b || !numero_c) return false;
  *resultado = *numero_c ? *numero_b : *numero_a;
  return true;
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

bool operador_unario(pila_t *pila_numeros, bool operacion(int *, int *)) {
  int *a = (int *)pila_desapilar(pila_numeros);
  int *resultado = calloc(1, sizeof(int));
  if(!operacion(a, resultado)) return false;
  free(a);
  pila_apilar(pila_numeros, resultado);
  return true;
}

bool operador_binario(pila_t *pila_numeros, bool operacion(int *, int *, int *)) {
  int *a = (int *)pila_desapilar(pila_numeros);
  int *b = (int *)pila_desapilar(pila_numeros);
  int *resultado = calloc(1, sizeof(int));
  if(!operacion(a, b, resultado)) return false;
  free(a);
  free(b);
  pila_apilar(pila_numeros, resultado);
  return true;
}

bool operador_ternario(pila_t *pila_numeros, bool operacion(int *, int *, int *, int *)) {
  int *a = (int *)pila_desapilar(pila_numeros);
  int *b = (int *)pila_desapilar(pila_numeros);
  int *c = (int *)pila_desapilar(pila_numeros);
  int *resultado = calloc(1, sizeof(int));
  if(!operacion(a, b, c, resultado)) return false;
  free(a);
  free(b);
  free(c);
  pila_apilar(pila_numeros, resultado);
  return true;
}

bool operar(char **strv, pila_t *pila_numeros) {
  for(size_t i = 0; strv[i]; i++) {
    if(!es_operador(strv[i])) {
      int *numero = calloc(1, sizeof(int));
      *numero = atoi(strv[i]);
      pila_apilar(pila_numeros, numero);
    } else {
      if(!strcmp(strv[i], SUMA)) {
        if(!operador_binario(pila_numeros, sumar)) return false;
      }
      if(!strcmp(strv[i], RESTA)) {
        if(!operador_binario(pila_numeros, restar)) return false;
      }
      if(!strcmp(strv[i], DIVISION)) {
        if(!operador_binario(pila_numeros, dividir)) return false;
      }
      if(!strcmp(strv[i], OPERADOR_TERNARIO)) {
        if(!operador_ternario(pila_numeros, terciarizar)) return false;
      }
      if(!strcmp(strv[i], RAIZ)) {
        if(!operador_unario(pila_numeros, raiz)) return false;
      }
    }
  }
  return true;
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

int *notacion_polaca(char **strv) {
  pila_t *pila_numeros = pila_crear();
  if(!pila_numeros) return NULL;
  int *resultado = calloc(1, sizeof(int));
  if(!resultado) return NULL;
  if(!operar(strv, pila_numeros)) {
    pila_destruir(pila_numeros);
    free(resultado);
    return NULL;
  }
  *resultado = *(int *) pila_ver_tope(pila_numeros); 
   while(!pila_esta_vacia(pila_numeros)) free(pila_desapilar(pila_numeros));
  pila_destruir(pila_numeros);
  return resultado;
}
