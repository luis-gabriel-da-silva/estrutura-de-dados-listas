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
        printf(" %d ", aux->r.chave);
        aux = aux->proximo;
    }
    printf("\n\n");
}

PONT Busca_Sequencial(Lista *L, Tipo_Chave ch)
{
    PONT posicao = L->inicio;
    while (posicao != NULL)
    {
        if (posicao->r.chave == ch)
            return posicao;
        posicao = posicao->proximo;
    }
    return NULL;
}

PONT Busca_Sequencial_Aux(Lista *L, Tipo_Chave ch, PONT *anterior)
{
    *anterior = NULL;
    PONT atual = L->inicio;
    while ((atual != NULL) && (atual->r.chave == ch))
    {
        *anterior = atual;
        atual = atual->proximo;
    }
    if ((atual != NULL) && (atual->r.chave == ch))
        return atual;
    return NULL;
}

bool Inserir_Elemento_Lista(Lista *L, Registro r)
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
    return false;
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

Inserir_Ordenadamente_pelo_numero_chamada_Lista(Lista *L, Registro r);
Excluir_pela_Matricula_Busca_Binaria(Lista *L, Registro r);

int main()
{
    setlocale(LC_ALL, "");
    Lista L;
    char sair, op;
    int opcao = 0;
    Tipo_Chave h;
    Registro a;

    Inicializar_Lista(&L);
    do
    {
        printf("1- Criar Lista de alunos: \n");
        printf("2- Inserir aluno na lista: \n");
        printf("3- Imprimir a lista: \n");
        printf("4- Inserir aluno ordenadamente pelo n�mero da matricula na lista: \n");
        printf("5- Excluir aluno pela busca binaria usando a matricula: \n");
        printf("Digite a op��o: \n");
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
                Inserir_Elemento_Lista(&L, a);
                printf("\nDeseja digitar mais elementos: ");
                fflush(stdin);
                scanf("%c", &op);
            } while (op != 'n');
            break;

        case 3:
            Imprimir_Lista(&L);
            break;

        case 4:
            printf("Digite o nome do aluno: ");
            scanf("%s", a.nome);
            printf("Digite a matricula do aluno: ");
            scanf("%d", &a.chave);
            Inserir_Ordenadamente_pelo_numero_chamada_Lista(&L, a);
            break;
        case 5:
            printf("Digite a matricula do aluno que deseja excluir: ");
            scanf("%d", &a.chave);
            Excluir_pela_Matricula_Busca_Binaria(&L, a);
        }
        printf("\n\n==================================\n\n");
        fflush(stdin);
        printf("Deseja sair do programa (s/n): \n");
        scanf("%c", &sair);
        printf("\n\n==================================\n\n");
    } while (sair != 's');
    return 0;
}