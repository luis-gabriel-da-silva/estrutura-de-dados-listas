#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>

typedef int Tipo_Chave;
typedef struct
{
    Tipo_Chave chave;
    char nome[100];
} Registro;

typedef struct Aux_Elemento
{
    Registro r;
    struct Aux_Elemento *proximo;
} Elemento;

typedef Elemento *PONT; // Ptr ponteiro
typedef struct
{
    PONT inicio;
} Lista;

void Inicializar_Lista(Lista *L)
{
    L->inicio = NULL;
}

int Tamanho(Lista *L)
{
    PONT aux = L->inicio;
    int tam = 0;
    while (aux != NULL)
    {
        tam++;
        aux = aux->proximo;
    }
    return tam;
}

void Imprimir_Lista(Lista *L)
{
    PONT aux = L->inicio;
    while (aux != NULL)
    {
        printf("Matricula: %d | Nome: %s\n", aux->r.chave, aux->r.nome);
        aux = aux->proximo;
    }
    printf("\n\n");
}

PONT Busca_Sequencial(Lista *L, Tipo_Chave ch)
{
<<<<<<< HEAD
    PONT posicao = L->inicio; // cria auxilair
    while (posicao != NULL)   // enquanto não acaba
    {
        if (posicao->r.chave == ch) // se posição igual chave
        {
            printf("Matrícula: %d", posicao->r.chave);
            printf("Nome: %s", posicao->r.nome); // print
            return posicao;                      // retorna a posição
        }
        posicao = posicao->proximo; // passa para o proximo
    }
    return NULL; // n deu certo retorna null
=======
    PONT posicao = L->inicio; // faz um auxiliar
    while (posicao != NULL) // enquanto o auxiliar for diferente de nulo
    {
        if (posicao->r.chave == ch) // se o campo chave do registro for igual a chave passada por parametro
        {
            printf("Matrícula: %d", posicao->r.chave); 
            printf("Nome: %s", posicao->r.nome);
            return posicao; // retorna o endereço do elemento encontrado
        }
        posicao = posicao->proximo; // avança para o próximo elemento
    }
    return NULL; // se chegar aqui, é porque não encontrou o elemento, então retorna NULL
>>>>>>> 944749dc0107505328d0deeb2ad0687b343f9ce5
}

PONT Busca_Sequencial_Aux(Lista *L, Tipo_Chave ch, PONT *anterior) // função de busca sequencial auxiliar, recebe um ponteiro para a lista, a chave a ser buscada e um ponteiro para o elemento anterior
{
<<<<<<< HEAD
    *anterior = NULL;                                 // passa o anterior como null
    PONT atual = L->inicio;                           // aponta para o inicio o atual
    while ((atual != NULL) && (atual->r.chave != ch)) // se atual n for null e nem chave ser igual a chave
    {
        *anterior = atual;      // anterior vira atual
        atual = atual->proximo; // atual vira proximo
    }
    if ((atual != NULL) && (atual->r.chave == ch)) // se atual for igual a chave
        return atual;                              // retorna atual
    return NULL;                                   // se n retorna null
=======
    *anterior = NULL; // anterior é um ponteiro para o elemento anterior, começa como NULL
    PONT atual = L->inicio; // atual é um ponteiro para o elemento atual, começa no início da lista
    while ((atual != NULL) && (atual->r.chave != ch)) // enquanto o atual for diferente de NULL e a chave do registro do atual for diferente da chave buscada
    {
        *anterior = atual; // ponteiro de anterior recebe o endereço do atual
        atual = atual->proximo; // atual avança para o próximo elemento
    }
    if ((atual != NULL) && (atual->r.chave == ch)) // se o atual for diferente de NULL e a chave do registro do atual for igual à chave buscada
        return atual; // retorna o endereço do elemento encontrado
    return NULL; // se chegar aqui, é porque não encontrou o elemento, então retorna NULL
>>>>>>> 944749dc0107505328d0deeb2ad0687b343f9ce5
}

bool Inserir_Elemento_Lista(Lista *L, Registro r) // função para inserir um elemento na lista, recebe um ponteiro para a lista e um registro a ser inserido
{
    Tipo_Chave ch = r.chave;                    // denomina chave como ch
    PONT anterior, i;                           // cria os pont
    i = Busca_Sequencial_Aux(L, ch, &anterior); // retorna se existe, anterior e atual
    if (i != NULL)
        return false;                   // se for diferente de null retorna false
    i = (PONT)malloc(sizeof(Elemento)); // aloca na memória o elemento
    i->r = r;                           // aloca os dados em r
    if (anterior == NULL)               // se anterior for null
    {
        i->proximo = L->inicio;
        L->inicio = i; // bota no inicio
    }
    else
    {
        i->proximo = anterior->proximo; // se não i aponta para o proximo do anterior
        anterior->proximo = i;          // e anterior aponta para o i
    }
    return true; // return true se alocou
}

bool Excluir_Elemento_Lista(Lista *L, Tipo_Chave ch)
{
    PONT anterior, i;
    i = Busca_Sequencial_Aux(L, ch, &anterior); // busca se existe
    if (i == NULL)                              // se n existe retorna false
        return false;
    if (anterior == NULL)
        L->inicio = i->proximo; // se anterior null o inicio vira o proximo do inicio antigo
    else
        anterior->proximo = i->proximo; // se n o anterior aponta para o proximo do i
    free(i);                            // libera espaço do i
    return true;                        // retorna true
}

void Reinicializar_Lista(Lista *L)
{
    PONT aux = L->inicio; // cria auxiliar
    while (aux != NULL)   // enquanto n acaba
    {
        PONT limpar = aux;  // limpar vira aux
        aux = aux->proximo; // aux vai pro proximo
        free(limpar);       // libera o atual
    }
    L->inicio = NULL; // inicio aponta para null
}

bool Excluir_pela_Matricula_Busca_Binaria(Lista *L, Tipo_Chave ch)
{
    PONT anterior = NULL;
    PONT atual = L->inicio; // inicializa

    while (atual != NULL && atual->r.chave < ch) // enquanto n acabar e chave menor q chave passada
    {
        anterior = atual;
        atual = atual->proximo; // armazena anterior em atual e passa para o proximo
    }

    if (atual == NULL || atual->r.chave != ch)
        return false; // se atual diferenter q chave passada, retorna false

    if (anterior == NULL)
    {
        L->inicio = atual->proximo; // se o anterior for null o inicio aponta para o proximo
    }
    else
    {
        anterior->proximo = atual->proximo; // se não o anterior aponta para o próximo do atual
    }
    free(atual); // exclui atual
    return true; // returna true
}

bool Inserir_Ordenadamente_pelo_numero_chamada_Lista(Lista *L, Registro r)
{
    {
        PONT novo = (PONT)malloc(sizeof(Elemento)); // aloca elemento
        novo->r = r;                                // coloca os dados no elemento

        // lista vazia ou menor que o primeiro
        if (L->inicio == NULL || r.chave < L->inicio->r.chave) // se inicio aponta para null e chave menor q o inicio da lista
        {
            novo->proximo = L->inicio; // novo aponta para inicio
            L->inicio = novo;          // inicio vira novo
            return true;               // encerra com sucesso
        }

        PONT atual = L->inicio; // atual aponta para inicio

        // encontra posição
        while (atual->proximo != NULL && atual->proximo->r.chave < r.chave)
        { // enquanto atual n aponta para o null e o proximo de atual é menor que o novo
            atual = atual->proximo;
        }

        // insere
        novo->proximo = atual->proximo; // novo aponta para o proximo do atual
        atual->proximo = novo;          // proximo do atual vira novo

        return true;
    }
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Lista L;
    char op;
    int opcao = 0;
    Registro a;

    Inicializar_Lista(&L);

    do
    {
        printf("1- Criar Lista de alunos: \n");
        printf("2- Inserir aluno na lista: \n");
        printf("3- Imprimir a lista: \n");
        printf("4- Inserir aluno ordenadamente: \n");
        printf("5- Excluir aluno pela matricula: \n");
        printf("6- Buscar aluno pela matricula: \n");
        printf("0- Sair\n");

        printf("Digite a opção: ");
        scanf("%d", &opcao);

        printf("\n==================================\n");

        switch (opcao)
        {
        case 1:
            Inicializar_Lista(&L);
            break;

        case 2:
            do
            {
                printf("\nDigite a matricula do aluno: ");
                scanf("%d", &a.chave);

                printf("Digite o nome do aluno: ");
                scanf(" %[^\n]", a.nome);

                Inserir_Elemento_Lista(&L, a);

                printf("Deseja continuar? (s/n): ");
                scanf(" %c", &op);

            } while (op != 'n');
            break;

        case 3:
            Imprimir_Lista(&L);
            break;

        case 4:
            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]", a.nome);

            printf("Digite a matricula: ");
            scanf("%d", &a.chave);

            Inserir_Ordenadamente_pelo_numero_chamada_Lista(&L, a);
            break;

        case 5:
            printf("Digite a matricula para excluir: ");
            scanf("%d", &a.chave);

            Excluir_pela_Matricula_Busca_Binaria(&L, a.chave);
            break;

        case 6:
        {
            printf("Digite a matricula: ");
            scanf("%d", &a.chave);

            PONT res = Busca_Sequencial(&L, a.chave);

            if (res == NULL)
                printf("Aluno não encontrado\n");

            break;
        }

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida\n");
        }

        printf("\n==================================\n\n");

    } while (opcao != 0);

    return 0;
}