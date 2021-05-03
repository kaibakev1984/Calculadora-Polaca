#include <stdio.h>
#include "notacion_posfija.h"
#include "testing.h"
#include "strutil.h"

void pruebas_operaciones_notacion_posfija() {
   printf("--------------------------------------------------\n");
   printf("PRUEBAS OPERACIONES NOTACIÓN POSFIJA\n");
   printf("--------------------------------------------------\n");

   char *str_1 = "5 3 +";
   char *str_2 = "5 3 -";
   char *str_3 = "5 3 /";
   char *str_4 = "3 5 8 + +";
   char *str_5 = "3 5 8 + -";
   char *str_6 = "3 5 - 8 +";
   char *str_7 = "1 -1 0 ?";
   char *str_8 = "5 sqrt";

   char **strv_1 = split(str_1, ' ');
   char **strv_2 = split(str_2, ' ');
   char **strv_3 = split(str_3, ' ');
   char **strv_4 = split(str_4, ' ');
   char **strv_5 = split(str_5, ' ');
   char **strv_6 = split(str_6, ' ');
   char **strv_7 = split(str_7, ' ');
   char **strv_8 = split(str_8, ' ');

   print_test("5 3 + --> 8", 8 == notacion_posfija(strv_1));
   print_test("5 3 - --> 2", 2 == notacion_posfija(strv_2));
   print_test("5 3 / --> 1", 1 == notacion_posfija(strv_3));
   print_test("3 5 8 + + --> 16", 16 == notacion_posfija(strv_4));
   print_test("3 5 8 + - --> -10", -10 == notacion_posfija(strv_5));
   print_test("3 5 - 8 + --> 6", 6 == notacion_posfija(strv_6));
   print_test("1 -1 0 ? --> -1", -1 == notacion_posfija(strv_7));
   print_test("5 sqrt --> 2", 2 == notacion_posfija(strv_8));

   free_strv(strv_1);
   free_strv(strv_2);
   free_strv(strv_3);
   free_strv(strv_4);
   free_strv(strv_5);
   free_strv(strv_6);
   free_strv(strv_7);
   free_strv(strv_8);
}

void pruebas_formato_valido() {
   printf("--------------------------------------------------\n");
   printf("PRUEBAS FORMATO VALIDO\n");
   printf("--------------------------------------------------\n");

   char *str_1 = "5 3 +";
   char *str_2 = "5 3 -";
   char *str_3 = "5 3 /";
   char *str_4 = "3 5 8 + +";
   char *str_5 = "3 5 8 + -";
   char *str_6 = "3 5 - 8 +";
   char *str_7 = "1 -1 0 ?";
   char *str_8 = "2 2 + +";
   char *str_9 = "0 1 ?";
   char *str_10 = "5 sqrt";

   char **strv_1 = split(str_1, ' ');
   char **strv_2 = split(str_2, ' ');
   char **strv_3 = split(str_3, ' ');
   char **strv_4 = split(str_4, ' ');
   char **strv_5 = split(str_5, ' ');
   char **strv_6 = split(str_6, ' ');
   char **strv_7 = split(str_7, ' ');
   char **strv_8 = split(str_8, ' ');
   char **strv_9 = split(str_9, ' ');
   char **strv_10 = split(str_10, ' ');

   print_test("5 3 + es correcto", validar_notacion_posfija(strv_1));
   print_test("5 3 - es correcto", validar_notacion_posfija(strv_2));
   print_test("5 3 / es correcto", validar_notacion_posfija(strv_3));
   print_test("3 5 8 + + es correcto", validar_notacion_posfija(strv_4));
   print_test("3 5 8 + - es correcto", validar_notacion_posfija(strv_5));
   print_test("3 5 - 8 + es correcto", validar_notacion_posfija(strv_6));
   print_test("1 -1 0 ? es correcto", validar_notacion_posfija(strv_7));
   print_test("2 2 + + no es correcto", !validar_notacion_posfija(strv_8));
   print_test("0 1 ? no es correcto", !validar_notacion_posfija(strv_9));
   print_test("5 sqrt no es correcto", validar_notacion_posfija(strv_10));

   free_strv(strv_1);
   free_strv(strv_2);
   free_strv(strv_3);
   free_strv(strv_4);
   free_strv(strv_5);
   free_strv(strv_6);
   free_strv(strv_7);
   free_strv(strv_8);
   free_strv(strv_9);
   free_strv(strv_10);
}

void pruebas_notacion_posfija() {
  pruebas_operaciones_notacion_posfija();
  pruebas_formato_valido();
}
