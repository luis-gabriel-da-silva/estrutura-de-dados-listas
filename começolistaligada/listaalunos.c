#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max 50
#define inv -1
#define maxdisciplinas 5

typedef int Matricula;

typedef char Disciplina[50];

typedef struct
{
    Matricula matricula;
    Disciplina disciplina[maxdisciplinas];
    char Nome_Aluno[100];
    int qtdDisciplinas;
} Aluno;

typedef struct
{
    Aluno r;
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
bool Inserir_Elemento_Ordenado(Lista *L, Aluno r);
int Obtencao_do_NO(Lista *L);
bool Excluir_Elemento_Lista(Lista *L, Matricula ch);
void Devolver_No_Disponivel_Lista(Lista *L, int i);
void Reinicializar_Lista(Lista *L);
void Busca_Por_Nome(Lista *L, char ch[]);
void Busca_Disciplina(Lista *L, char ch[]);
int Limite_Alunos(Lista *L, char ch[]);
void Inserir_Disciplina(Aluno *a, char disciplina[]);

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
    printf("\t ===== Lista ===== \n");
    while (i != inv)
    {
        printf("Nº matrícula: ");
        printf("%d \n", L->V[i].r.matricula);
        printf("Nome: ");
        printf("%s \n", L->V[i].r.Nome_Aluno);
        printf("Disciplinas: ");
        for (int j = 0; j < L->V[i].r.qtdDisciplinas; j++)
        {
            printf("%s - ", L->V[i].r.disciplina[j]);
        }
        printf("\n ------------------ \n");
        i = L->V[i].proximo;
    }
    printf("\n\n");
}

void Busca_Por_Nome(Lista *L, char ch[])
{
    int i = L->inicio;
    bool encontrou = false;

    while (i != inv)
    {

        if (strcmp(L->V[i].r.Nome_Aluno, ch) == 0)
        {
            printf("Nº matrícula: %d\n", L->V[i].r.matricula);
            printf("Nome: %s\n", L->V[i].r.Nome_Aluno);
            printf("Disciplinas: ");
            for (int j = 0; j < L->V[i].r.qtdDisciplinas; j++)
            {
                printf("%s - ", L->V[i].r.disciplina[j]);
            }
            encontrou = true;
        }
        i = L->V[i].proximo;
    }
    if (!encontrou)
    {
        printf("Aluno não encontrado\n");
    }
}

void Busca_Disciplina(Lista *L, char ch[])
{
    int i = L->inicio;
    bool encontrou = false;

    while (i != inv)
    {
        for (int j = 0; j < L->V[i].r.qtdDisciplinas; j++)
        {
            if (strcmp(L->V[i].r.disciplina[j], ch) == 0)
            {
                printf("Nº matrícula: %d\n", L->V[i].r.matricula);
                printf("Nome: %s\n", L->V[i].r.Nome_Aluno);
                encontrou = true;
                break;
            }
        }

        i = L->V[i].proximo;
    }

    if (!encontrou)
    {
        printf("Nenhum aluno encontrado\n");
    }
}

int Limite_Alunos(Lista *L, char ch[])
{
    int i = L->inicio;
    int contador = 0;
    while (i != inv)
    {
        for (int j = 0; j < L->V[i].r.qtdDisciplinas; j++)
        {
            if (strcmp(L->V[i].r.disciplina[j], ch) == 0)
                contador++;
        }
        i = L->V[i].proximo;
    }
    return contador;
}

void Inserir_Disciplina(Aluno *a, char disciplina[])
{
    if (a->qtdDisciplinas < 5)
    {
        strcpy(a->disciplina[a->qtdDisciplinas], disciplina);
        a->qtdDisciplinas++;
    }
    else
    {
        printf("Quantidade de disciplina excedidas!\n");
    }
}

bool Inserir_Elemento_Ordenado(Lista *L, Aluno r)
{
    if (L->disponivel == inv)
        return false;
    int anterior = inv;
    int i = L->inicio;
    Matricula mat = r.matricula;
    while (i != inv && L->V[i].r.matricula < mat)
    {
        anterior = i;
        i = L->V[i].proximo;
    }
    if (i != inv && L->V[i].r.matricula == mat)
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

bool Excluir_Elemento_Lista(Lista *L, Matricula ch)
{
    int anterior = inv;
    int i = L->inicio;
    while (i != inv && L->V[i].r.matricula < ch)
    {
        anterior = i;
        i = L->V[i].proximo;
    }
    if (i == inv || L->V[i].r.matricula != ch)
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
    Aluno r;
    Matricula matricula;

    Iniciar_Lista(&L);

    do
    {
        printf("\n===== MENU =====\n");
        printf("1 - Inserir Aluno\n");
        printf("2 - Excluir Aluno por matrícula\n");
        printf("3 - Buscar por aluno\n");
        printf("4 - Buscar por disciplina\n");
        printf("5 - Imprimir lista\n");
        printf("6 - Numero de Alunos\n");
        printf("7 - Reinicializar lista\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            printf("Digite a matricula: ");
            scanf("%d", &r.matricula);
            printf("Digite o nome: ");
            scanf(" %[^\n]", r.Nome_Aluno);

            r.qtdDisciplinas = 0;

            int n;
            char disciplina[50];

            printf("Quantas disciplinas? ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++)
            {
                printf("Digite a disciplina: ");
                scanf(" %[^\n]", disciplina);

                if (Limite_Alunos(&L, disciplina) < 10)
                {
                    Inserir_Disciplina(&r, disciplina);
                }
                else
                {
                    printf("Disciplina cheia!\n");
                }
            }

            if (Inserir_Elemento_Ordenado(&L, r))
                printf("Inserido com sucesso!\n");
            else
                printf("Erro ao inserir (lista cheia ou matricula repetida)\n");
            break;
        }
        case 2:
            printf("Digite a matricula para remover: ");
            scanf("%d", &matricula);

            if (Excluir_Elemento_Lista(&L, matricula))
                printf("Removido com sucesso!\n");
            else
                printf("Elemento nao encontrado!\n");
            break;

        case 3:
        {
            char aluno[100];
            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]", aluno);
            Busca_Por_Nome(&L, aluno);
            break;
        }
        case 4:
        {
            char disciplina[50];

            printf("Digite a disciplina: ");
            scanf(" %[^\n]", disciplina);

            Busca_Disciplina(&L, disciplina);
            break;
        }
        case 5:

            Imprimir_Lista(&L);
            break;

        case 6:
            printf("Total de elementos: %d\n", Numero_Elementos(&L));
            break;

        case 7:
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
