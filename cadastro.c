#include <stdlib.h>
#include <stdio.h>

#define LIVROS 100 // máximo de livros na biblioteca
#define NOME 20 // máximo de caracteres para nomes
#define TITULO 50 // máximo de caracteres para títulos dos livros


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

// declarando variáveis globais
char user[NOME];
int insere = -1;

typedef struct
{
    int ed; // ano da edição do livro
    int lan; // ano de lançamento do livro
} ano;

typedef struct
{
    char nome[NOME]; // nome da biblioteca
    char titulo[TITULO]; // título do livro
    char autor[NOME]; // nome do autor do livro
    char editora[NOME]; // nome da editora 
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

void EscolhaMenu(int escolha)
{
    switch (escolha)
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
    insere++; // cada vez q a função é chamada a variável é incrementada para salvar as novas informações no array
    printf("Olá, %s! Vamos inserir um novo livro*?\n", user);
    printf("*Só lembrando que esta é uma versão demo, portanto ao encerrar o programa seus dados não ficarão salvos.\n");
    printf("Qual é o título do livro? ");
    //fgets(minhaBiblio[insere].nome, TITULO, stdin); 
    scanf("%s", minhaBiblio[insere].titulo);
    // printf("Qual é o nome do autor? ");
    // scanf("%s", minhaBiblio[insere].autor);
    // printf("Qual é o nome da editora do seu exemplar? ");
    // scanf("%s", minhaBiblio[insere].editora);
    // printf("Qual é o ano de lançamento da edição que você tem? ");
    // scanf("%i", &minhaBiblio[insere].ano.ed);
    // printf("E o ano original de lançamento, da primeira edição, sabe qual é?\nSe não constar ou não souber informar digite 0000. ");
    // scanf("%i", &minhaBiblio[insere].ano.lan);
    // printf("Legal! Já temos informações suficientes!\nVou te reencaminhar para o menu principal, beleza?\n");
    SeparaTopico(2);

}

void Mostrar()
{
    printf("TÍTULO\t\tAUTOR\t\tEDITORA\t\tANO EDIÇÃO\tANO LANÇAMENTO\n0");
    for (int i = 0; i < LIVROS; i++)
    {
        printf("%s\t\t%s\t\t%s\t\t%i\t%i\n", minhaBiblio[i].titulo, minhaBiblio[i].autor, minhaBiblio[i].editora, minhaBiblio[i].ano.ed, minhaBiblio[i].ano.lan);
    }
    SeparaTopico(2);
}

void Buscar()
{
    printf("BUSCANDO LIVROS ESPECÍFICOS\n");
    SeparaTopico(2);
}
