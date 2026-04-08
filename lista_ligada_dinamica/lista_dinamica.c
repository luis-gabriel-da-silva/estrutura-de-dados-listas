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
}

PONT Busca_Sequencial_Aux(Lista *L, Tipo_Chave ch, PONT *anterior) // função de busca sequencial auxiliar, recebe um ponteiro para a lista, a chave a ser buscada e um ponteiro para o elemento anterior
{
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
}

bool Inserir_Elemento_Lista(Lista *L, Registro r) // função para inserir um elemento na lista, recebe um ponteiro para a lista e um registro a ser inserido
{
    Tipo_Chave ch = r.chave;
    PONT anterior, i;
    i = Busca_Sequencial_Aux(L, ch, &anterior);
    if (i != NULL)
        return false;
    i = (PONT)malloc(sizeof(Elemento));
    i->r = r;
    if (anterior == NULL)
    {
        i->proximo = L->inicio;
        L->inicio = i;
    }
    else
    {
        i->proximo = anterior->proximo;
        anterior->proximo = i;
    }
    return true;
}

bool Excluir_Elemento_Lista(Lista *L, Tipo_Chave ch)
{
    PONT anterior, i;
    i = Busca_Sequencial_Aux(L, ch, &anterior);
    if (i == NULL)
        return false;
    if (anterior == NULL)
        L->inicio = i->proximo;
    else
        anterior->proximo = i->proximo;
    free(i);
    return true;
}

void Reinicializar_Lista(Lista *L)
{
    PONT aux = L->inicio;
    while (aux != NULL)
    {
        PONT limpar = aux;
        aux = aux->proximo;
        free(limpar);
    }
    L->inicio = NULL;
}

bool Excluir_pela_Matricula_Busca_Binaria(Lista *L, Tipo_Chave ch)
{
    PONT anterior = NULL;
    PONT atual = L->inicio;

    while (atual != NULL && atual->r.chave < ch)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL || atual->r.chave < ch)
        return false;

    if (anterior == NULL)
    {
        L->inicio = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    return true;
}

bool Inserir_Ordenadamente_pelo_numero_chamada_Lista(Lista *L, Registro r)
{
    {
        PONT novo = (PONT)malloc(sizeof(Elemento));
        novo->r = r;

        // lista vazia ou menor que o primeiro
        if (L->inicio == NULL || r.chave < L->inicio->r.chave)
        {
            novo->proximo = L->inicio;
            L->inicio = novo;
            return true;
        }

        PONT atual = L->inicio;

        // encontra posição
        while (atual->proximo != NULL && atual->proximo->r.chave < r.chave)
        {
            atual = atual->proximo;
        }

        // insere
        novo->proximo = atual->proximo;
        atual->proximo = novo;

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