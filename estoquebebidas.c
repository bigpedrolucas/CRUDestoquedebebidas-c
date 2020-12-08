#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Tema: BAR
// Tipo: CADASTRO DE ESTOQUE

// Variáveis globais
int i;
int pos = 0;
int tam = 100;

// Estrutura
typedef struct {
    char tipo[20];
    char nome[50];
    float valor;
    int quantidade;
} bebidas;

bebidas bebida[100]; // Vetor estrutura global

// Declaração de todas as funções
void lerarquivo();
void inserir();
void alterar();
void pesqpornome();
void remover();
void listartodos();

// Arquivos
FILE* arq; // Modo "a+"
FILE* arqleitura; // Modo "r"
FILE* arqw; // modo "w"

// FUNÇÃO PRINCIPAL
int main(void) {

    setlocale(LC_ALL, "Portuguese"); // Definindo o idioma dos arquivos, a fim de aceitar caracteres especiais

    lerarquivo(); // Chamamento da função que lê o arquivo antes de executar todo o programa para o usuário

    int op; // Variável local de opção numérica do menu

    printf("\n------ CADASTRO DE ESTOQUE - PEDRO BEBIDAS LTDA ------\n\n");
    printf("1 - Inserir produto\n");
    printf("2 - Alterar parâmetro(s)\n");
    printf("3 - Pesquisar por nome\n");
    printf("4 - Remover produto\n");
    printf("5 - Listar produtos\n");
    printf("0 - Sair\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", &op);
    getchar();

    switch(op) {
        case 1:
            inserir(); break;
        case 2:
            alterar(); break;
        case 3:
            pesqpornome(); break;
        case 4:
            remover(); break;
        case 5:
            listartodos(); break;
        case 0:
            break;
        default:
            printf("\nErro. Verifique se digitou a opção correta!\n"); main(); break;
    }
    return 0;
}

// FUNÇÃO DE LEITURA DOS REGISTROS EXISTENTES
void lerarquivo() {

    setlocale(LC_ALL, "Portuguese");

    arqleitura = fopen("estoque.txt", "r"); // Abertura de arquivo de leitura

    // Leitura dos registros existentes
    for(i=0; i<100; i++) {

        fgets(bebida[i].tipo, 20, arqleitura);
        bebida[i].tipo[strlen(bebida[i].tipo) - 1] = '\0';

        fgets(bebida[i].nome, 50, arqleitura);
        bebida[i].nome[strlen(bebida[i].nome) - 1] = '\0';

        fscanf(arqleitura, "%f", &bebida[i].valor);

        fscanf(arqleitura, "%d", &bebida[i].quantidade);

        // A função "inserir" não irá usar a última posição lida, já que ela está ocupada.
        // logo, a posição a ser preenchida pelo cadastro é a última (i) + 1
        pos = i+1;

        if (fgetc(arqleitura) == EOF) break;
    }
    fclose(arqleitura); // Fechamento do arquivo
}

// FUNÇÃO INSERIR DADOS
void inserir(void) {

    setlocale(LC_ALL, "Portuguese");

    int op; // Variável local de opção numérica
    char escolha[5]; //Variável local de escolha

    printf("\n------ INSERIR PRODUTO ------\n\n");

    printf("1 - Cerveja / 2 - Cachaça / 3 - Vodca / 4 - Vinho / 5 - Whisky / 0 - Voltar\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", &op);
    getchar();

    // Cadastro por seleção no menu
    switch(op) {
        case 1:
            strcpy(bebida[pos].tipo, "Cerveja"); break;
        case 2:
            strcpy(bebida[pos].tipo, "Cachaça"); break;
        case 3:
            strcpy(bebida[pos].tipo, "Vodca"); break;
        case 4:
            strcpy(bebida[pos].tipo, "Vinho"); break;
        case 5:
            strcpy(bebida[pos].tipo, "Whisky"); break;
        case 0:
            main(); return; break;
        default:
            printf("\nErro. Verifique se digitou a opção correta!");
            inserir(); return; break;
        }
    // Cadastro manual
    printf("Digite o nome do produto: ");
    fgets(bebida[pos].nome, 50, stdin);
    bebida[pos].nome[strlen(bebida[pos].nome) - 1] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &bebida[pos].quantidade);
    getchar();

    printf("Digite o preco do produto: R$ ");
    scanf("%f", &bebida[pos].valor);
    getchar();

    // Abrindo arquivo para escrevêr os registros
    arq = fopen("estoque.txt", "a+");

    fprintf(arq, "%s\n", bebida[pos].tipo);
    fprintf(arq, "%s\n", bebida[pos].nome);
    fprintf(arq, "%.2f\n", bebida[pos].valor);
    fprintf(arq, "%d\n", bebida[pos].quantidade);
    fclose(arq); // Fechamento do arquivo

    printf("\nCadastro concluido.\nDeseja cadastrar outro produto? (sim/nao): ");
    scanf("%s", &escolha);

    if (strcmp(escolha, "sim") == 0) {
        pos++; // Adiciona mais uma posição a ser preenchida pelo inserir
        inserir();
    }
    if (strcmp(escolha, "nao") == 0) {
        main(); // Retorna à função principal
    }

    return;
}

// FUNÇÃO 3
void alterar() {

    setlocale(LC_ALL, "Portuguese");

    arq = fopen("estoque.txt", "r+");

    int op1; // Variável local de opção 1
    int op2; // Variável local de opção 2
    int escolha; // Variável local de escolha. Volta ao menu ou a função alterar

    printf("\n------ ALTERAR PARÂMETROS ------\n\n");
    printf("Digite a posição do produto ou aperte 0 para voltar: ");
    scanf("%d", &op1);
    getchar();

    if (op1 > pos-1) {
        printf("\nPosição inválida ou inexistente. Tente novamente!\n");
        alterar();
        return;
    }
    if (op1 == 0) {
        main();
        return;
    }

    op1--; // Decremento da opção numérica, uma vez que, para humanos, não existe posição zero, mas para a máquina sim.
            // Se digito 4, a posição real é 3.

    for (i=0; i<pos; i++) {
        if (i == op1) {
            printf("\nTipo: %s\n", bebida[i].tipo);
            printf("Nome: %s\n", bebida[i].nome);
            printf("Valor: R$ %.2f\n", bebida[i].valor);
            printf("Quantidade: %d\n\n", bebida[i].quantidade);
            break;
        }
    }

    char resposta[5]; // Variável local

    printf("Esse é o produto correto? (sim/nao): ");
    scanf("%s", &resposta);

    if (strcmp(resposta, "nao") == 0) {
        alterar(); // Chama novamente a função, em caso de resposta negativa. Se sim, continua.
        return;
    }

    printf("\n1 - Tipo / 2 - Nome / 3 - Quantidade / 4 - Valor\n\n");
    printf("Escolha um parâmetro: ");
    scanf("%d", &op2);
    getchar();

    // Escolha do parâmetro a ser alterado, as alterações e a exibição do item alterado.
    switch(op2) {
        case 1:
            printf("Insira o tipo: ");
            fgets(bebida[op1].tipo, 20, stdin);
            bebida[op1].tipo[strlen(bebida[op1].tipo) - 1] = '\0';

            printf("Alterações salvas com sucesso!\n");
            printf("\nTipo: %s\n", bebida[op1].tipo);
            printf("Nome: %s\n", bebida[op1].nome);
            printf("Valor: R$ %.2f\n", bebida[op1].valor);
            printf("Quantidade: %d\n\n", bebida[op1].quantidade);
            break;
        case 2:
            printf("Digite o nome do produto: ");
            fgets(bebida[op1].nome, 50, stdin);
            bebida[op1].nome[strlen(bebida[op1].nome) - 1] = '\0';

            printf("Alterações salvas com sucesso!\n");
            printf("\nTipo: %s\n", bebida[op1].tipo);
            printf("Nome: %s\n", bebida[op1].nome);
            printf("Valor: R$ %.2f\n", bebida[op1].valor);
            printf("Quantidade: %d\n\n", bebida[op1].quantidade);
            break;
        case 3:
            printf("Digite a quantidade: ");
            scanf("%d", &bebida[op1].quantidade);
            getchar();

            printf("Alterações salvas com sucesso!\n");
            printf("\nTipo: %s\n", bebida[op1].tipo);
            printf("Nome: %s\n", bebida[op1].nome);
            printf("Valor: R$ %.2f\n", bebida[op1].valor);
            printf("Quantidade: %d\n\n", bebida[op1].quantidade);
            break;
        case 4:
            printf("Digite o preco do produto: R$ ");
            scanf("%f", &bebida[op1].valor);
            getchar();

            printf("Alterações salvas com sucesso!\n");
            printf("\nTipo: %s\n", bebida[op1].tipo);
            printf("Nome: %s\n", bebida[op1].nome);
            printf("Valor: R$ %.2f\n", bebida[op1].valor);
            printf("Quantidade: %d\n\n", bebida[op1].quantidade);
            break;
        default:
            printf("Verifique se digitou os dados corretamente!\n");
            alterar();
            return;
            break;
    }

        // Gravação das alterações no arquivo
        arq = fopen("estoque.txt", "w+");

        pos  = pos - 1; // Tirando a posição vazia que seria preenchida pelo "inserir"

        for (i=0; i<pos; i++) {
            fprintf(arq, "%s\n", bebida[i].tipo);
            fprintf(arq, "%s\n", bebida[i].nome);
            fprintf(arq, "%.2f\n", bebida[i].valor);
            fprintf(arq, "%d\n", bebida[i].quantidade);
        }

        fclose(arq);

        printf("Para voltar ao menu, digite 0. Para fazer novas alterações, digite 1: ");
        scanf("%d", &escolha);
        getchar();

        if (escolha == 0) {
            main();
            return;
        }
        if (escolha == 1) {
            alterar();
            return;
        }

    return;
}

// FUNÇÃO 4
void pesqpornome() {

    setlocale(LC_ALL, "Portuguese");

    char produto[50]; // Variável local que armazena o nome do produto
    int op;
    int existe; // Variável local para verificar existencia do produto. Caso não exista, Uma mensagem de erro será mostrada.

    printf("\n------ PESQUISAR PRODUTO ------\n\n");

    printf("Digite o nome do produto a ser procurado ou digite \"voltar\" para ir ao menu: ");
    fgets(produto, 50, stdin);
    produto[strlen(produto) - 1] = '\0';

    if (strcmp(produto, "voltar") == 0) {
        main();
        return;
    }

    // Laço para procurar o produto e, se achar, exibí-lo
    for (i=0; i<pos; i++) {
        if (strcmp(bebida[i].nome, produto) == 0) {
            existe = 1;
            printf("\nProduto encontrado:\n\n");
            printf("Tipo: %s\n", bebida[i].tipo);
            printf("Nome: %s\n", bebida[i].nome);
            printf("Valor: R$ %.2f\n", bebida[i].valor);
            printf("Quantidade: %d\n\n", bebida[i].quantidade);
            break;
        }
    }

    if(existe == 0) printf("Verifique se digitou os dados corretamente!\n");

    printf("Para voltar ao menu, aperte 0. Para fazer uma nova busca, aperte 1: ");
    scanf("%d", &op);
    getchar();

    if (op == 0) {
        main();
        return;
    }
    if (op == 1) {
        pesqpornome();
        return;
    }

    return;
}

// FUNÇÃO REMOVER
void remover() {

    char produto[50];
    char escolha[5];
    char op;
    int existe; // Variável que verifica a existência do produto. Se não existir, uma mensagem de erro será retornada
                // e a função será chamada novamente.

    printf("\n------ EXCLUIR PRODUTO ------\n\n");

    printf("Digite o nome do produto ou digite \"voltar\" para ir ao menu: ");
    fgets(produto, 50, stdin);
    produto[strlen(produto) - 1] = '\0';

    if (strcmp(produto, "voltar") == 0) {
        main();
        return;
    }

    for (i=0; i<pos; i++) {
        if (strcmp(bebida[i].nome, produto) == 0) {
            existe = 1;
            printf("Tipo: %s\n", bebida[i].tipo);
            printf("Nome: %s\n", bebida[i].nome);
            printf("Valor: R$ %.2f\n", bebida[i].valor);
            printf("Quantidade: %d\n\n", bebida[i].quantidade);
            break;
        }
    }
    if (existe == 0) {
        printf("Produto não encontrado. Tente novamente!\n");
        remover();
        return;
    }

    printf("Deseja excluir esse produto? (sim/nao): ");
    scanf("%s", &escolha);

    if (strcmp(escolha, "sim") == 0) {
        bebida[i].tipo[0] = '\0'; // Marcação do produto a ser excluído, a fim dele não ser gravado
        printf("Produto excluído com sucesso!");
    }
    if (strcmp(escolha, "nao") == 0) {
        printf("\n\nPara voltar ao menu, aperte 0. Para fazer uma nova busca, aperte 1: ");
        scanf("%d", &op);
        getchar();

        if (op == 0) {
        main();
        return;
    }
        if (op == 1) {
        remover();
        return;
        }
    }

    arqw = fopen("estoque.txt", "w");

    pos--; // Posição extra que não foi usada pelo inserir sendo decrementada

    for (i=0; i<pos; i++) {
        if (bebida[i].tipo[0] != '\0') {
            fprintf(arqw, "%s\n", bebida[i].tipo);
            fprintf(arqw, "%s\n", bebida[i].nome);
            fprintf(arqw, "%.2f\n", bebida[i].valor);
            fprintf(arqw, "%d\n", bebida[i].quantidade);
        }
    }
    fclose(arqw); // Fechamento do arquivo

    printf("\n\nPara voltar ao menu, aperte 0. Para fazer uma nova busca, aperte 1: ");
    scanf("%d", &op);
    getchar();

    if (op == 0) {
        main();
        return;
    }
    if (op == 1) {
        remover();
        return;
    }
    return;
}

// FUNÇÃO 6
void listartodos() {

    int op;
    pos--; // Decremento da posição que está disponível para a função "inserir" usar ou não

    for (i=0; i<pos; i++) {
        printf("\n--- POSIÇÃO %d ---\n", i+1);
        printf("Tipo: %s\n", bebida[i].tipo);
        printf("Nome: %s\n", bebida[i].nome);
        printf("Valor: R$ %.2f\n", bebida[i].valor);
        printf("Quantidade: %d\n\n", bebida[i].quantidade);
        if (bebida[i].tipo == NULL) break;
    }

    printf("Aperte 0 para retornar ao menu: ");
    scanf("%d", &op);
    getchar();
    
    if (op == 0) main();
}
