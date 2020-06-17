Introducción
============

Esta es una implementación de cómo leer un archivo
por entrada estándar. Las implementaciones para, y
guarda acá, para imprimir líneas del archivo de texto
**oper.txt** (o sea, imprimir con un ***printf*** 
cada línea de dicho archivo) ya están dadas.

Solo queda de tu parte, implementar la función
***calculadora_polaca***, que recibirá una línea,
a la cuál le vas a tener que hacer el correspondiente
***split*** para poder trabajarla.

ComponentesDentroDeEstaCarpeta
==============================
Al descomprimir la carpeta, tendrás lo siguiente:
1. oper.txt
2. calculadora_polaca.txt
3. makefile

¿Qué hace lo que te mandés?
===========================
Si haces ***make run***, vas a estar imprimiendo 
todas las líneas del archivo oper.txt

¿Qué Es lo que tengo que hacer?
===============================
Vas a tener que editar el archivo ***calculadora_polaca.c***,
SOLO lo que esta dentro del bloque:
~~~~
/*************Editame**********************/ 

	printf("%s\n", str);

/*************Fin Editame ****************/
~~~~ 

RecetasMakefile
================
Para agilizar las cosas, te dejé implementada varias recetas
para que vayas probando directamente:
***make run*** es para que corras el programa
***make valgrind*** es para ver si no perdiste memoria
***make clear*** MUY IMPORTANTE, para limpiar los ejecutables
		y los *.o que se van a ir creando

Algunas Aclaraciones
====================
Vas a ver una función extraña llamada ***str_crear***.
Lo que va a hacer es pedir memoria para poder leer las líneas
de tu archivo. Sin importar la implementación, ya hace todo
lo que necesitas, que es obtener la línea de tu archivo.

Es importante destacar los 2 free que aparecen (uno dentro del
while y otro fuera) que son necesarios por estar pidiendo memoria
para obtener las líneas. 

Esta implementación no tiene agregada ***pila.h*** por lo que vas a
tener que agregarla, dentro de la carpeta, incluyendo sus primitivas en ***pila.c***

Con esta implementación en el ***makefile***, vas a ver que
hay una variable llamada OBJ, son los que van a crear nuestros
*.o. Cuando vayas a agregar un nuevo archivo <nombre_archivo>.c,
en donde dice OBJ vas a agregar <nombre_archivo>.o. En tu caso, 
que vas a usar la pila, vas a agregar en OBJ pila.o. Te debería
quedar de esta forma (en el archivo makefile):

~~~~
OBJ = calculadora_polaca.o pila.o
~~~~

NOTA 1: En el tp vas a estar haciedo uso de "*.o", pero no te va a
importar por ahora, pero es importante que sepas que existe, porque
vas a hacer uso de los mismos en el ***deps.mk*** que vas a entregar
junto con el tp.

NOTA 2: ¡¡Fuerza!!
