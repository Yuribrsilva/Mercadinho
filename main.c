#include <stdio.h>
#include <stdlib.h>

int codigo[100];
char nome[100][30];
float preco[100];
int quantidade[100];
int total = 0;

// Joga fora o que sobrou digitado na linha (evita o scanf "pular" a proxima pergunta)
void limparBuffer() {
    int c;
    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

// Le o preco como texto, troca virgula por ponto e converte para numero
float lerPreco() {
    char texto[20];
    int i;

    scanf("%s", texto);
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') {
            texto[i] = '.';
        }
    }
    limparBuffer();
    return atof(texto);
}

void salvar() {
    FILE *arq;
    int i;

    arq = fopen("mercado.txt", "w");
    if (arq == NULL) {
        printf("Erro no arquivo\n");
        return;
    }

    for (i = 0; i < total; i++) {
        fprintf(arq, "%d %s %.2f %d\n", codigo[i], nome[i], preco[i], quantidade[i]);
    }

    fclose(arq);
}

void carregar() {
    FILE *arq;

    total = 0;
    arq = fopen("mercado.txt", "r");
    if (arq == NULL) {
        return;
    }

    while (fscanf(arq, "%d %s %f %d", &codigo[total], nome[total], &preco[total], &quantidade[total]) != EOF) {
        total++;
    }

    fclose(arq);
}

void criarArquivo() {
    total = 0;
    salvar();
    printf("Arquivo criado vazio!\n");
}

void listar() {
    int i;

    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nProdutos\n");
    for (i = 0; i < total; i++) {
        printf("Codigo: %d\n", codigo[i]);
        printf("Nome: %s\n", nome[i]);
        printf("Preco: R$ %.2f\n", preco[i]);
        printf("Quantidade: %d\n\n", quantidade[i]);
    }
}

void inserir() {
    int novoCodigo, i;

    if (total >= 100) {
        printf("Lista cheia!\n");
        return;
    }

    printf("Digite o codigo: ");
    scanf("%d", &novoCodigo);
    
    for (i = 0; i < total; i++) {
        if (codigo[i] == novoCodigo) {
            printf("Esse codigo ja existe!\n");
            return;
        }
    }

    codigo[total] = novoCodigo;
    printf("Digite o nome (sem espacos): ");
    scanf("%s", nome[total]);
    limparBuffer();
    printf("Digite o preco: ");
    preco[total] = lerPreco();
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade[total]);
    limparBuffer();

    total++;
    salvar();
    printf("Produto inserido!\n");
}

void alterar() {
    int busca, i;
    int achou = 0;

    printf("Digite o codigo do produto que quer alterar: ");
    scanf("%d", &busca);

    for (i = 0; i < total; i++) {
        if (codigo[i] == busca) {
            achou = 1;
            printf("Novo nome (sem espacos): ");
            scanf("%s", nome[i]);
            limparBuffer();
            printf("Novo preco: ");
            preco[i] = lerPreco();
            printf("Nova quantidade: ");
            scanf("%d", &quantidade[i]);
            limparBuffer();

            salvar();
            printf("Produto alterado!\n");
        }
    }

    if (achou == 0) {
        printf("Codigo nao encontrado.\n");
    }
}

int main() {
    int opcao;

    carregar();

    do {
        printf("\nMercadinho UNICID\n");
        printf("1 - Criar arquivo vazio\n");
        printf("2 - Listar produtos\n");
        printf("3 - Inserir produto\n");
        printf("4 - Alterar produto\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            criarArquivo();
        } else if (opcao == 2) {
            listar();
        } else if (opcao == 3) {
            inserir();
        } else if (opcao == 4) {
            alterar();
        } else if (opcao == 0) {
            printf("Sair\n");
        } else {
            printf("Opcao não encontrada\n");
        }
    } while (opcao != 0);

    return 0;
}