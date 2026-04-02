#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 50
#define inv -1

typedef int Tipo_Chave;

typedef struct
{
    Tipo_Chave chave;
} Registro;

typedef struct
{
    Registro r;
    int proximo;
} Elemento;

typedef struct
{
    Elemento V[max];
    int inicio;
    int disponivel;
} Lista;

void Iniciar_Lista(Lista *L);
int Numero_Elementos(Lista *L);
int Busca_Sequencial_Ordenada(Lista *L, Tipo_Chave ch);
bool Inserir_Elemento_Ordenado(Lista *L, Registro r);
int Obtencao_do_NO(Lista *L);
bool Excluir_Elemento_Lista(Lista *L, Tipo_Chave ch);
void Devolver_No_Disponivel_Lista(Lista *L, int i);
void Reinicializar_Lista(Lista *L);

void Iniciar_Lista(Lista *L)
{
    int i;
    for (i = 0; i < max - 1; i++)
        L->V[i].proximo = i + 1;
    L->V[max - 1].proximo = inv;
    L->inicio = inv;
    L->disponivel = 0;
}

int Numero_Elementos(Lista *L)
{
    int i = L->inicio;
    int tamanho = 0;
    while (i != inv)
    {
        tamanho++;
        i = L->V[i].proximo;
    }
    return tamanho;
}

void Imprimir_Lista(Lista *L)
{
    int i = L->inicio;
    printf("\t Lista \n");
    while (i != inv)
    {
        printf(" %d ", L->V[i].r.chave);
        i = L->V[i].proximo;
    }
    printf("\n\n");
}

int Busca_Sequencial_Ordenada(Lista *L, Tipo_Chave ch)
{
    int i = L->inicio;
    while (i != inv && L->V[i].r.chave < ch)
        i = L->V[i].proximo;
    if (i != inv && L->V[i].r.chave == ch)
        return i;
    else
        return inv;
}

bool Inserir_Elemento_Ordenado(Lista *L, Registro r)
{
    if (L->disponivel == inv)
        return false;
    int anterior = inv;
    int i = L->inicio;
    Tipo_Chave ch = r.chave;
    while (i != inv && L->V[i].r.chave < ch)
    {
        anterior = i;
        i = L->V[i].proximo;
    }
    if (i != inv && L->V[i].r.chave == ch)
        return false;
    i = Obtencao_do_NO(L);
    L->V[i].r = r;
    if (anterior == inv)
    {
        L->V[i].proximo = L->inicio;
        L->inicio = i;
    }
    else
    {
        L->V[i].proximo = L->V[anterior].proximo;
        L->V[anterior].proximo = i;
    }
    return true;
}

int Obtencao_do_NO(Lista *L)
{
    int resultado = L->disponivel;
    if (L->disponivel != inv)
        L->disponivel = L->V[L->disponivel].proximo;
    return resultado;
}

bool Excluir_Elemento_Lista(Lista *L, Tipo_Chave ch)
{
    int anterior = inv;
    int i = L->inicio;
    while (i != inv && L->V[i].r.chave < ch)
    {
        anterior = i;
        i = L->V[i].proximo;
    }
    if (i == inv || L->V[i].r.chave != ch)
        return false;
    if (anterior == inv)
        L->inicio = L->V[i].proximo;
    else
        L->V[anterior].proximo = L->V[i].proximo;
    Devolver_No_Disponivel_Lista(L, i);
    return true;
}

void Devolver_No_Disponivel_Lista(Lista *L, int i)
{
    L->V[i].proximo = L->disponivel;
    L->disponivel = i;
}

void Reinicializar_Lista(Lista *L)
{
    Iniciar_Lista(L);
}

int main()
{
    Lista L;
    int opcao;
    Registro r;
    Tipo_Chave chave;

    Iniciar_Lista(&L);

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Excluir elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Imprimir lista\n");
        printf("5 - Numero de elementos\n");
        printf("6 - Reinicializar lista\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite a chave: ");
            scanf("%d", &r.chave);

            if (Inserir_Elemento_Ordenado(&L, r))
                printf("Inserido com sucesso!\n");
            else
                printf("Erro ao inserir (lista cheia ou chave repetida)\n");
            break;

        case 2:
            printf("Digite a chave para remover: ");
            scanf("%d", &chave);

            if (Excluir_Elemento_Lista(&L, chave))
                printf("Removido com sucesso!\n");
            else
                printf("Elemento nao encontrado!\n");
            break;

        case 3:
        {
            printf("Digite a chave para buscar: ");
            scanf("%d", &chave);

            int pos = Busca_Sequencial_Ordenada(&L, chave);

            if (pos != inv)
                printf("Elemento encontrado na posicao %d\n", pos);
            else
                printf("Elemento nao encontrado!\n");
            break;
        }

        case 4:
            Imprimir_Lista(&L);
            break;

        case 5:
            printf("Total de elementos: %d\n", Numero_Elementos(&L));
            break;

        case 6:
            Reinicializar_Lista(&L);
            printf("Lista reinicializada!\n");
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
