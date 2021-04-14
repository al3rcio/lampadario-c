// Cadastro para uma loja de Lâmpadas

#include <stdio.h>
#include <string.h>

#define ITENS 100 // quantidade máxima de itens no cadastro
#define STRING 20 // quantidade máxima de caracteres para marca ou cor

typedef struct 
{
    char marca[STRING]; // nome da marca da lâmpada
    int v; // tensão -> 127 ou 220
    int w; // potência em watts
    int tipo; // 1 == incandescente / 2 == fluorescente / 3 == LED
    char cor[STRING]; // cor da lâmapada, p. ex.: branca; amarela; vermelha
    int cadastrado; // confirmar cadastro, se o valor for 0, não há cadastro, se for 1, foi cadastrado. 
} lampada;

// declarando funções
void SeparaTopico(int n);
int Menu();
void EscolhaMenu(int menu);
void Inserir();
void Mostrar();
void Buscar();
void BuscaSimples();
void BuscaComposta();
void SeguirBuscando();
lampada ValorBusca(int tipoBusca);
lampada ValorBuscaComposto(int tipoBusca);
int CmpValor(lampada valorMarca, int escolhaBusca);
int CmpValorComposto(lampada cmpValor, int escolhaBusca);
void Finalizar();
void Ajuda();

lampada lampadas[ITENS]; // define variável global do tipo lampada, onde ficaram cadastradas as lâmpadas pelo usuário
int menu = 1; // 1 == programa ativo / 0 == encerrar programa
int insere = -1; // insere vai funcionar como controle de índice do vetor lampadas; 
                 // será incrementado a cada chamada da função Inserir() e 
                 // foi inicializado em -1 para o primeiro cadastro estar na posição 0

int main()
{
    while (menu == 1) // um loop infinito, até que a função Finalizar seja chamada
    {
        EscolhaMenu(Menu()); // o menu é mostrado para o usuário e sua escolha é salva em EscolhaMenu e a partir dali a respectiva função é chamada
    }
    return 0; // retorno da função main do tipo int, sinalizando que tudo ocorreu bem e o programa se encerra
}

int Menu()
{
    int m; // variável criada para armazenar a escolha numérica/de opção do usuário
    printf("####----> MENU LAMPADÁRIO <----####\n");
    printf("Digite ----> 1 <---- para cadastrar uma nova lâmpada\n");
    printf("Digite ----> 2 <---- para mostrar todas as lâmpadas cadastradas\n");
    printf("Digite ----> 3 <---- para procurar por alguma lâmpada específica\n");
    printf("Digite ----> 9 <---- para obter ajuda quanto ao cadastro\n");
    printf("Digite ----> 0 <---- para encerrar este programa\n");
    scanf("%i", &m); // aqui o valor é armazenado conforme escolha do usuário
    return m; // aqui é o retorno da função, do tipo int, que vai ser utilizado na função EscolhaMenu
}

void EscolhaMenu(int escolha)
{
    switch (escolha) // conforme o valor enviado pelo usuário (pré-definido no menu em exibição) o programa escolherá e executará/chamará uma das função abaixo
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
        case 9:
            Ajuda();
            break;
        default:
            printf("Comando inválido.\n");
            break;
    }
}

void Finalizar()
{
    printf("Encerrando...\n");
    menu = 0;
}

void Inserir()
{
    insere++; // esta variável é o guia para a correta inserção dentro do vetor. começa em -1, e é incrementada a cada vez a função inserir é chamada, adicionando no índice 0, 1, 2 etc.
    printf("###----> INSERIR LÂMPADA <----####\n");
    printf("Marca: ");
    scanf("%s", lampadas[insere].marca); // adicionando marca (scanf deixa de registrar a informação depois de um espaço em branco, por isso devem ser utilizadas palavras simples, como informado para o usuário na seção AJUDA)
    printf("Tensão: ");
    scanf("%i", &lampadas[insere].v); // adicionando tensão
    printf("Potência: ");
    scanf("%i", &lampadas[insere].w); // adicionando potência
    printf("Para tipo digite\n\t--> 1 <-- para incandescente\n\t--> 2 <-- para fluorescente\n\t--> 3 <-- para LED\n"); // um pequeno guia para o usuário do padrão/tipo de resposta que o campo exige
    printf("Tipo: ");
    scanf("%i", &lampadas[insere].tipo); // adicionando tipo conforme padrão pré-estabelecido
    printf("Cor: ");
    scanf("%s", lampadas[insere].cor); // adicionando cor (o mesmo vale aqui, sobre scanf dito em MARCA)
    printf("Lâmpada cadastrada com sucesso.\nID ----> %i\n", insere);
    lampadas[insere].cadastrado = 1; // mudar esse valor de 0 para 1 é o que vai servir de guia na hora de mostrar todos e buscar, para somente os cadastrados serem exibidos
}

void Mostrar()
{
    printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
    for (int i = 0; i < ITENS; i++)
    {
        if (lampadas[i].cadastrado == 1) // testando para mostrar somente os itens cadastrados
            printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
    }
}

void Buscar()
{
    int b;
    printf("####----> BUSCAR LÂMPADA(s) <----####\n");
    printf("Digite ----> 1 <---- para realizar uma busca simples (apenas um identificador).\n");
    printf("Digite ----> 2 <---- para realizar uma busca composta (dois identificadores a sua escolha).\n");
    scanf("%i", &b);
    switch (b)
    {
    case 1:
        tipoBuscador = 1;
        BuscaSimples();
        break;
    case 2:
        tipoBuscador = 2;
        BuscaComposta();
    default:
        printf("Comando inválido.\n");
        break;
    }
       
}

void BuscaSimples()
{
    int ma; // variável do marcador
    printf("Digite --> 1 <-- para buscar por MARCA\n");
    printf("Digite --> 2 <-- para buscar por TENSÃO\n");
    printf("Digite --> 3 <-- para buscar por POTÊNCIA\n");
    printf("Digite --> 4 <-- para buscar por TIPO\n");
    printf("Digite --> 5 <-- para buscar por COR\n");
    scanf("%i", &ma);
    
    int buscaCheck;
    switch (ma)
    {
    case 1:
        buscaCheck = CmpValor(ValorBusca(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    case 2:
        buscaCheck = CmpValor(ValorBusca(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    case 3:
        buscaCheck = CmpValor(ValorBusca(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    case 4:
        buscaCheck = CmpValor(ValorBusca(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    case 5:
        buscaCheck = CmpValor(ValorBusca(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    default:
        break;
    }
}

void BuscaComposta()
{
    int ma; // variável do marcador
    printf("Digite --> 0 <-- para buscar por MARCA e TENSÃO\n");
    printf("Digite --> 1 <-- para buscar por MARCA e POTÊNCIA\n");
    printf("Digite --> 2 <-- para buscar por MARCA e TIPO\n");
    printf("Digite --> 3 <-- para buscar por MARCA e COR\n");
    printf("Digite --> 4 <-- para buscar por TENSÃO e POTÊNCIA\n");
    printf("Digite --> 5 <-- para buscar por TENSÃO e TIPO\n");
    printf("Digite --> 6 <-- para buscar por TENSÃO e COR\n");
    printf("Digite --> 7 <-- para buscar por POTÊNCIA e TIPO\n");
    printf("Digite --> 8 <-- para buscar por POTÊNCIA e COR\n");
    printf("Digite --> 9 <-- para buscar por TIPO e COR\n");
    scanf("%i", &ma);
    
    int buscaCheck;
    switch (ma)
    {
    case 0:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 1:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 2:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 3:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 4:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 5:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 6:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    case 7:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 8:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    case 9:
        buscaCheck = CmpValorComposto(ValorBuscaComposto(ma), ma);
        if (buscaCheck == 0)
            printf("Não encontrado / Não consta no lampadário\n");
        break;
    
    default:
        break;
    }
}

lampada ValorBuscaComposto(int tipoBusca)
{
    lampada buscador;
    switch (tipoBusca)
    {
    case 0:
        printf("Digite o nome da marca a ser buscada: ");
        scanf("%s", buscador.marca); 
        printf("Digite o valor de tensão a ser buscado: ");
        scanf("%i", &buscador.v);     
        break;
    
    case 1:
        printf("Digite o nome da marca a ser buscada: ");
        scanf("%s", buscador.marca); 
        printf("Digite o valor de potência a ser buscado: ");
        scanf("%i", &buscador.w);     
        break;

    case 2:
        printf("Digite o nome da marca a ser buscada: ");
        scanf("%s", buscador.marca); 
        printf("Digite o tipo (1, 2 ou 3) da lâmpada a ser buscado: ");
        scanf("%i", &buscador.tipo);     
        break;

    case 3:
        printf("Digite o nome da marca a ser buscada: ");
        scanf("%s", buscador.marca); 
        printf("Digite o nome da cor a ser buscado: ");
        scanf("%s", buscador.cor);     
        break;

    case 4:
        printf("Digite o valor de tensão a ser buscado: ");
        scanf("%i", &buscador.v);   
        printf("Digite o valor de potência a ser buscado: ");
        scanf("%i", &buscador.w);        
        break;

    case 5:
        printf("Digite o valor de tensão a ser buscado: ");
        scanf("%i", &buscador.v);   
        printf("Digite o tipo (1, 2 ou 3) da lâmpada a ser buscado: ");
        scanf("%i", &buscador.tipo);         
        break;

    case 6:
        printf("Digite o valor de tensão a ser buscado: ");
        scanf("%i", &buscador.v);   
        printf("Digite o nome da cor a ser buscado: ");
        scanf("%s", buscador.cor);       
        break;

    case 7:
        printf("Digite o valor de potência a ser buscado: ");
        scanf("%i", &buscador.w);     
        printf("Digite o tipo (1, 2 ou 3) da lâmpada a ser buscado: ");
        scanf("%i", &buscador.tipo);   
        break;

    case 8:
        printf("Digite o valor de potência a ser buscado: ");
        scanf("%i", &buscador.w);     
        printf("Digite o nome da cor a ser buscado: ");
        scanf("%s", buscador.cor);       
        break;

    case 9:
        printf("Digite o tipo (1, 2 ou 3) da lâmpada a ser buscado: ");
        scanf("%i", &buscador.tipo); 
        printf("Digite o nome da cor a ser buscado: ");
        scanf("%s", buscador.cor);          
        break;
    default:
        break;
    }
    return buscador;
}

lampada ValorBusca(int tipoBusca)
{
    lampada buscador;
    switch (tipoBusca)
    {
    case 1:
        printf("Digite o nome da marca a ser buscado: ");
        scanf("%s", buscador.marca);      
        break;
    
    case 2:
        printf("Digite o valor de tensão a ser buscado: ");
        scanf("%i", &buscador.v);
        break;
    
    case 3:
        printf("Digite o valor de potência a ser buscado: ");
        scanf("%i", &buscador.w);
        break;

    case 4:
        printf("Digite o tipo (1, 2 ou 3) da lâmpada a ser buscado: ");
        scanf("%i", &buscador.tipo);
        break;
    
    case 5:
        printf("Digite o nome da cor a ser buscado: ");
        scanf("%s", buscador.cor);
        break;
    default:
        break;
    }
    return buscador;
}

void SeguirBuscando()
{
    int seguir;
    printf("Digite --> 1 <-- para realizar uma nova busca.\n");
    printf("Digite --> 2 <-- para voltar ao menu principal.\n");
    scanf("%i", &seguir);
    if (seguir == 1)
        Buscar();    
}

int CmpValorComposto(lampada cmpValor, int escolhaBusca)
{
    int f = 0;
    int cab = 0;
    switch (escolhaBusca)
    {
    case 0:
        for (int i = 0; i < ITENS; i++)
        {
            if (strcasecmp(cmpValor.marca, lampadas[i].marca) == 0 && cmpValor.v == lampadas[i].v)
            {
                if (cab == 0)
                {
                    printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                    cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 1:
        for (int i = 0; i < ITENS; i++)
        {
            if (strcasecmp(cmpValor.marca, lampadas[i].marca) == 0 && cmpValor.w == lampadas[i].w)
            {
                if (cab == 0)
                {
                    printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                    cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 2:
        for (int i = 0; i < ITENS; i++)
        {
            if (strcasecmp(cmpValor.marca, lampadas[i].marca) == 0 && cmpValor.tipo == lampadas[i].tipo)
            {
                if (cab == 0)
                {
                    printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                    cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 3:
        for (int i = 0; i < ITENS; i++)
        {
            if (strcasecmp(cmpValor.marca, lampadas[i].marca) == 0 && strcasecmp(cmpValor.cor, lampadas[i].cor) == 0)
            {
                if (cab == 0)
                {
                    printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                    cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 4:
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.v == lampadas[i].v && cmpValor.w == lampadas[i].w)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
               
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 5:
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.v == lampadas[i].v && cmpValor.tipo == lampadas[i].tipo)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
               
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 6:
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.v == lampadas[i].v && strcasecmp(cmpValor.cor, lampadas[i].cor) == 0)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
               
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 7: // compara POTÊNCIA E TIPO
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.w == lampadas[i].w && cmpValor.tipo == lampadas[i].tipo)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 8: // compara POTÊNCIA E COR
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.w == lampadas[i].w && strcasecmp(cmpValor.cor, lampadas[i].cor) == 0)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 9: // compara TIPO E COR
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.tipo == lampadas[i].tipo && strcasecmp(cmpValor.cor, lampadas[i].cor) == 0)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }

    default:
        break;
    }
    cab = 0;
    SeguirBuscando();
    return f;
}

int CmpValor(lampada cmpValor, int escolhaBusca)
{
    int f = 0;
    int cab = 0;
    switch (escolhaBusca)
    {
    case 1:
        for (int i = 0; i < ITENS; i++)
        {
            if (strcasecmp(cmpValor.marca, lampadas[i].marca) == 0)
            {
                if (cab == 0)
                {
                    printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                    cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;
    
    case 2:
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.v == lampadas[i].v)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
               
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 3:
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.w == lampadas[i].w)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 4:
        for (int i = 0; i < ITENS; i++)
        {
            if (cmpValor.tipo == lampadas[i].tipo)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }
        break;

    case 5:
        for (int i = 0; i < ITENS; i++)
        {
            if (strcasecmp(cmpValor.cor, lampadas[i].cor) == 0)
            {
                if (cab == 0)
                {
                     printf("MARCA\tTENSÃO\tPOTÊNCIA\tTIPO\tCOR\n"); // cabeçalho da tabela
                     cab = 1;
                }
                printf("%s\t%i\t%i\t\t%i\t%s\n", lampadas[i].marca, lampadas[i].v, lampadas[i].w, lampadas[i].tipo, lampadas[i].cor); // mostrando os itens cadastrados, de acordo com a ordem do cabeçalho
                f++;
            }
        }

    default:
        break;
    }
    cab = 0;
    SeguirBuscando();
    return f;
}

void Ajuda()
{
    int n; // variável criada para testar uma saída direta do usuário da seção AJUDA
    printf("####----> AJUDA CADASTRO <----####\n"); // uma série de printf explicando o funcionamento do cadastro para o usuário a partir de algumas regras pré-estabelecidas pelo programador
    printf("Os itens Marca e Cor devem ser cadastrados somente com uma palavra.\n");
    printf("Para marcas com nome composto, escolha a palavra mais forte e use sempre a mesma para cadastros similares.\n");
    printf("Para cores compostas, escreva com hífen, p. ex.: verde-turquesa; azul-marinho; cinza-chumbo etc\n");
    printf("Para tensão e potência use o valor nominal, em números, nunca escrevendo por extenso ou inserindo letras quaisqer, como V, para tensão, ou P, para potência etc.\n");
    printf("Para o tipo digite o número 1, para incandescente, 2 para fluorescente e 3 para LED\n");
    printf("Digite ----> 1 <---- para voltar ao menu ou ----> 2 <---- para encerrar o programa: ");
    scanf("%i", &n);
    if (n == 2) // testando se o valor informado é 2, se sim, chama a função Finalizar e encerra o programa. é pedido o valor 1 para voltar ao menu por uma convenção, mas nesse caso, em tese, qualquer valor informado diferente de 2 seria o suficiente para voltar ao menu (claro, o usuário final não necessariamente sabe disso, a menos q faça testes. de qualquer forma, não chega a ser um problema, já que o objetivo principal aqui é voltar ao menu)
        Finalizar();        
}

