#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int codigo[100];          // codigos dos produtos
char nome[100][30];       // nomes dos produtos
char categoria[100][30];  // categorias dos produtos
float preco[100];         // precos dos produtos
int quantidade[100];      // quantidades em estoque
int total = 0;            // quantidade de produtos cadastrados
int proximoId = 1;        // proximo ID automatico (nunca reutiliza IDs excluidos)

void limparBuffer() {
    int c;
    c = getchar();                          // le um caractere
    while (c != '\n' && c != EOF) {         // ate o fim da linha
        c = getchar();
    }
}

float lerPreco() {
    char texto[20];
    int i;

    scanf("%s", texto);                     // le o preco como texto
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') {              // troca virgula por ponto
            texto[i] = '.';
        }
    }
    limparBuffer();
    return atof(texto);                     // converte para numero
}

void salvar() {
    FILE *arq;
    int i;

    arq = fopen("mercado.txt", "w");        // abre para escrita
    if (arq == NULL) {
        printf("Erro no arquivo\n");
        return;
    }
    fprintf(arq, "%d\n", proximoId);        // 1a linha: proximo ID (guarda os excluidos)
    for (i = 0; i < total; i++) {           // grava um produto por linha
        fprintf(arq, "%d %s %s %.2f %d\n", codigo[i], nome[i], categoria[i], preco[i], quantidade[i]);
    }
    fclose(arq);
}

void carregar() {
    FILE *arq;

    total = 0;
    proximoId = 1;
    arq = fopen("mercado.txt", "r");        // abre para leitura
    if (arq == NULL) {                      // arquivo nao existe:
        salvar();                           // cria o arquivo vazio automaticamente
        return;
    }
    fscanf(arq, "%d", &proximoId);          // le o proximo ID salvo
    while (total < 100 && fscanf(arq, "%d %s %s %f %d", &codigo[total], nome[total], categoria[total], &preco[total], &quantidade[total]) == 5) {
        total++;
    }
    fclose(arq);
}

// Mostra em tabela os produtos cujos indices estao em idx[] (nao altera o arquivo)
void tabela(int idx[], int n) {
    int i;

    if (n == 0) {
        printf("Nenhum produto encontrado.\n");
        return;
    }
    printf("\n%-5s %-20s %-15s %10s %5s\n", "ID", "Nome", "Categoria", "Preco", "Qtd");
    printf("----------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-5d %-20s %-15s %10.2f %5d\n", codigo[idx[i]], nome[idx[i]], categoria[idx[i]], preco[idx[i]], quantidade[idx[i]]);
    }
}

void listar() {
    int idx[100], i;

    for (i = 0; i < total; i++) {           // todos os indices, na ordem do arquivo
        idx[i] = i;
    }
    tabela(idx, total);
}

// Retorna 1 se ja existe outro produto com esse nome (ignora o indice "ignorar")
int nomeExiste(char *n, int ignorar) {
    int i;

    for (i = 0; i < total; i++) {
        if (i != ignorar && strcmp(nome[i], n) == 0) {
            return 1;
        }
    }
    return 0;
}

void inserir() {
    char novoNome[30];

    if (total >= 100) {
        printf("Lista cheia!\n");
        return;
    }
    printf("Digite o nome (sem espacos): ");
    scanf("%s", novoNome);
    limparBuffer();
    if (nomeExiste(novoNome, -1)) {         // verifica duplicata
        printf("Esse produto ja existe!\n");
        return;
    }
    strcpy(nome[total], novoNome);
    codigo[total] = proximoId++;            // ID automatico
    printf("Digite a categoria (sem espacos): ");
    scanf("%s", categoria[total]);
    limparBuffer();
    printf("Digite o preco: ");
    preco[total] = lerPreco();
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade[total]);
    limparBuffer();

    total++;
    salvar();
    printf("Produto inserido com ID %d!\n", codigo[total - 1]);
}

void alterar() {
    int busca, i;
    char novoNome[30];

    printf("Digite o ID do produto que quer alterar: ");
    scanf("%d", &busca);
    limparBuffer();

    for (i = 0; i < total; i++) {
        if (codigo[i] == busca) {
            printf("Novo nome (sem espacos): ");
            scanf("%s", novoNome);
            limparBuffer();
            if (nomeExiste(novoNome, i)) {  // nome ja usado por outro produto
                printf("Esse nome ja existe!\n");
                return;
            }
            strcpy(nome[i], novoNome);
            printf("Nova categoria: ");
            scanf("%s", categoria[i]);
            limparBuffer();
            printf("Novo preco: ");
            preco[i] = lerPreco();
            printf("Nova quantidade: ");
            scanf("%d", &quantidade[i]);
            limparBuffer();
            salvar();
            printf("Produto alterado!\n");
            return;
        }
    }
    printf("ID nao encontrado.\n");
}

void excluir() {
    int busca, i, j;

    printf("Digite o ID do produto que quer excluir: ");
    scanf("%d", &busca);
    limparBuffer();

    for (i = 0; i < total; i++) {
        if (codigo[i] == busca) {
            for (j = i; j < total - 1; j++) {   // puxa os proximos uma posicao
                codigo[j] = codigo[j + 1];
                strcpy(nome[j], nome[j + 1]);
                strcpy(categoria[j], categoria[j + 1]);
                preco[j] = preco[j + 1];
                quantidade[j] = quantidade[j + 1];
            }
            total--;
            salvar();                       // proximoId continua o mesmo (ID excluido nao volta)
            printf("Produto excluido!\n");
            return;
        }
    }
    printf("ID nao encontrado.\n");
}

// tipo 1 = busca por nome, tipo 2 = busca por categoria
void buscar(int tipo) {
    char termo[30];
    int idx[100], n = 0, i;

    printf(tipo == 1 ? "Digite o nome (ou parte): " : "Digite a categoria (ou parte): ");
    scanf("%s", termo);
    limparBuffer();
    for (i = 0; i < total; i++) {
        // strstr verifica se o termo aparece dentro do texto
        if (strstr(tipo == 1 ? nome[i] : categoria[i], termo) != NULL) {
            idx[n++] = i;                   // guarda o indice encontrado
        }
    }
    tabela(idx, n);
}

// Bubble Sort por nome: ordena so os indices, o arquivo nao muda
void ordenar() {
    int idx[100], i, j, aux;

    for (i = 0; i < total; i++) {
        idx[i] = i;
    }
    for (i = 0; i < total - 1; i++) {           // passadas
        for (j = 0; j < total - 1 - i; j++) {   // compara vizinhos
            if (strcmp(nome[idx[j]], nome[idx[j + 1]]) > 0) {
                aux = idx[j];                   // troca de posicao
                idx[j] = idx[j + 1];
                idx[j + 1] = aux;
            }
        }
    }
    tabela(idx, total);
}

void comprar() {
    int busca, qtd, i;

    printf("Digite o ID do produto que quer comprar: ");
    scanf("%d", &busca);
    limparBuffer();

    for (i = 0; i < total; i++) {
        if (codigo[i] == busca) {
            printf("Quantidade a comprar: ");
            scanf("%d", &qtd);
            limparBuffer();
            if (qtd <= 0 || qtd > quantidade[i]) {  // valida a quantidade
                printf("Quantidade invalida ou estoque insuficiente (estoque: %d).\n", quantidade[i]);
                return;
            }
            quantidade[i] = quantidade[i] - qtd;    // diminui do estoque
            salvar();
            printf("Compra realizada! Total: R$ %.2f\n", qtd * preco[i]);
            return;
        }
    }
    printf("ID nao encontrado.\n");
}

int main() {
    int opcao;

    carregar();                             // carrega dados (cria o arquivo se nao existir)

    do {
        printf("\nMercadinho UNICID\n");
        printf("1 - Listar produtos\n");
        printf("2 - Inserir produto\n");
        printf("3 - Alterar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Buscar por nome\n");
        printf("6 - Buscar por categoria\n");
        printf("7 - Listar ordenado por nome (Bubble Sort)\n");
        printf("8 - Comprar produto\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {                    // escolhe a acao conforme a opcao
            case 1: listar(); break;
            case 2: inserir(); break;
            case 3: alterar(); break;
            case 4: excluir(); break;
            case 5: buscar(1); break;       // busca por nome
            case 6: buscar(2); break;       // busca por categoria
            case 7: ordenar(); break;
            case 8: comprar(); break;
            case 0: printf("Sair\n"); break;
            default: printf("Opcao nao encontrada\n");
        }
    } while (opcao != 0);

    return 0;
}
