#include <stdio.h>
#include <stdlib.h>

#define STRING 50

typedef struct 
{
    char nome[STRING];
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    int seg;
} data;

typedef struct 
{
    char sala[STRING]; // nome da sala que a chave abre
    int retirou; // bool para saber se está no claviculário. 0 == está && 1 == não está / retirada
    data dataRetirou;
    data dataDevolveu;
} clavi;