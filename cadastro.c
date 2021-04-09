#include <stdlib.h>
#include <stdio.h>

#define LIVROS 100
#define STRING 50 

typedef struct
{
    char titulo[STRING]; // título do livro
    char autor[STRING]; // nome do autor do livro
    int anoEd; // ano da edição do livro
    int anoLan; // ano de lançamento do livro
} biblioteca;
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
