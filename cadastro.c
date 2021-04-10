#include <stdlib.h>
#include <stdio.h>

#define LIVROS 100
#define STRING 50 

// declarando funções
void BemVindx();
void SeparaTopico(int n);
void NomeandoBiblioteca();
int Menu();
void EscolhaMenu(int menu);
void Inserir();
void Mostrar();
void Buscar();
void Finalizar();

char user[STRING];

typedef struct
{
    int ed; // ano da edição do livro
    int lan; // ano de lançamento do livro
} ano;

typedef struct
{
    char nome[STRING]; // nome da biblioteca
    char titulo[STRING]; // título do livro
    char autor[STRING]; // nome do autor do livro
    char editora[STRING]; // nome da editora 
    ano ano; // ano da edição e do lançamento original
} biblioteca;

biblioteca minhaBiblio[LIVROS];
int menu = 1;

int main()
{
    BemVindx();
    SeparaTopico(1);
    NomeandoBiblioteca();
    SeparaTopico(1);
    while (menu == 1)
        EscolhaMenu(Menu());  
    return 0;    
}

void BemVindx()
{
    printf("Olá, você! Como quer ser chamado? \n");
    scanf("%s", user);
    printf("Bem-vindx, %s!\n", user);
}

void SeparaTopico(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("################\n");
    }
}

void NomeandoBiblioteca()
{
    printf("Como você gostaria de chamar a sua biblioteca, %s?\n", user);
    scanf("%s", minhaBiblio->nome);
    printf("Excelente escolha, %s!\n\tVoilá.......... %s!\n", user, minhaBiblio->nome);
}

int Menu()
{
    int m;
    printf("Então, %s, o que você gostaria de fazer agora?\n", user);
    printf("Bom... claro... dentro do meu possível!\n");
    printf("Digite ->1<- para inserir um novo livro!\n");
    printf("Digite ->2<- para mostrar todos os livros da incrível %s!\n", minhaBiblio->nome);
    printf("Digite ->3<- para procurar algum livro específico!\n");
    printf("E se você quiser encerrar por aqui é só digitar ->0<-\n");
    scanf("%i", &m);
    return m;
}

void EscolhaMenu(int menu)
{
    switch (menu)
    {
        case 0:
            Finalizar();
            break;
        case 1:
            Inserir();
            break;
        case 2:
            Mostrar();
            break;
        case 3:
            Buscar();
            break;
        default:
            printf("Opa, %s! O valor informado não é válido, hein... Vou fingir que nada aconteceu e te mostrar o menu mais uma vez, beleza?\n", user);
            break;
    }
}

void Finalizar()
{
    printf("Tchau, %s!\n", user);
    menu = 0;
}

void Inserir()
{
    // todo
    printf("INSERINDO LIVROS\n");
    SeparaTopico(2);
}

void Mostrar()
{
    // todo
    printf("MOSTRANDO TODOS OS LIVROS\n");
    SeparaTopico(2);
}

void Buscar()
{
    printf("BUSCANDO LIVROS ESPECÍFICOS\n");
    SeparaTopico(2);
}
