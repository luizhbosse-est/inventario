/*
 * Sistema de Inventário para Jogo de Sobrevivência
 * 
 * Este programa implementa duas versões do sistema de inventário:
 * 1. Versão com vetor (lista sequencial)
 * 2. Versão com lista encadeada (estrutura dinâmica)
 * 
 * O objetivo é comparar o desempenho das duas estruturas de dados
 * e demonstrar a eficiência da busca binária em vetores ordenados.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura Item
typedef struct {
    char nome[30];      // Nome do item
    char tipo[20];      // Tipo do item
    int quantidade;     // Quantidade do item
} Item;

// Definição da estrutura No para lista encadeada
typedef struct No {
    Item dados;         // Dados do item
    struct No* proximo; // Ponteiro para o próximo nó
} No;

// Constantes do sistema
#define MAX_ITENS 10
#define TAMANHO_NOME 30
#define TAMANHO_TIPO 20

// Variáveis globais para o vetor
Item inventarioVetor[MAX_ITENS];
int totalItensVetor = 0;
int vetorOrdenado = 0; // Flag para indicar se o vetor está ordenado

// Variáveis globais para a lista encadeada
No* inicioLista = NULL;
int totalItensLista = 0;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// Declaração das funções principais
void exibirMenuPrincipal();
void exibirMenuVetor();
void exibirMenuLista();
void limparBuffer();
void resetarContadores();
void exibirEstatisticas();
void compararDesempenho();
void testeDesempenhoAutomatizado();

// Funções para vetor
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
int buscarSequencialVetor(char* nome);
void ordenarVetor();
int buscarBinariaVetor(char* nome);

// Funções para lista encadeada
void inserirItemLista();
void removerItemLista();
void listarItensLista();
No* buscarSequencialLista(char* nome);
void liberarLista();

/*
 * Função principal do programa
 */
int main() {
    int opcao;
    
    printf("=== SISTEMA DE INVENTÁRIO AVANÇADO - MÓDULO 2 ===\n");
    printf("Comparação entre Vetor e Lista Encadeada\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                // Menu do vetor
                exibirMenuVetor();
                break;
            case 2:
                // Menu da lista encadeada
                exibirMenuLista();
                break;
            case 3:
                // Exibir estatísticas
                exibirEstatisticas();
                break;
            case 4:
                // Comparar desempenho
                compararDesempenho();
                break;
            case 5:
                // Teste automatizado
                testeDesempenhoAutomatizado();
                break;
            case 6:
                // Resetar contadores
                resetarContadores();
                printf("✅ Contadores resetados!\n");
                break;
            case 7:
                printf("Saindo do sistema... Boa sorte na sobrevivência!\n");
                liberarLista(); // Libera memória da lista
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
        
    } while(opcao != 7);
    
    return 0;
}

/*
 * Exibe o menu principal do sistema
 */
void exibirMenuPrincipal() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Gerenciar Inventário com Vetor\n");
    printf("2. Gerenciar Inventário com Lista Encadeada\n");
    printf("3. Exibir Estatísticas de Desempenho\n");
    printf("4. Comparar Desempenho das Estruturas\n");
    printf("5. Executar Teste Automatizado\n");
    printf("6. Resetar Contadores\n");
    printf("7. Sair\n");
    printf("======================\n");
}

/*
 * Limpa o buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Reseta todos os contadores de comparações
 */
void resetarContadores() {
    comparacoesSequencial = 0;
    comparacoesBinaria = 0;
}

/*
 * Exibe estatísticas de desempenho
 */
void exibirEstatisticas() {
    printf("=== ESTATÍSTICAS DE DESEMPENHO ===\n");
    printf("Comparações em Busca Sequencial: %d\n", comparacoesSequencial);
    printf("Comparações em Busca Binária: %d\n", comparacoesBinaria);
    printf("Total de itens no Vetor: %d\n", totalItensVetor);
    printf("Total de itens na Lista: %d\n", totalItensLista);
    printf("Vetor ordenado: %s\n", vetorOrdenado ? "Sim" : "Não");
    
    if (comparacoesSequencial > 0 && comparacoesBinaria > 0) {
        float eficiencia = (float)comparacoesBinaria / comparacoesSequencial * 100;
        printf("Eficiência da busca binária: %.2f%% das comparações da busca sequencial\n", eficiencia);
    }
    printf("==================================\n");
}


/*
 * ========================================
 * FUNÇÕES PARA LISTA ENCADEADA
 * ========================================
 */

/*
 * Exibe o menu da lista encadeada
 */
void exibirMenuLista() {
    int opcao;
    
    do {
        printf("=== INVENTÁRIO COM LISTA ENCADEADA ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Voltar ao menu principal\n");
        printf("=====================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                inserirItemLista();
                break;
            case 2:
                removerItemLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4: {
                char nome[TAMANHO_NOME];
                printf("Digite o nome do item a buscar: ");
                fgets(nome, TAMANHO_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                resetarContadores();
                No* resultado = buscarSequencialLista(nome);
                
                if (resultado != NULL) {
                    printf("✅ Item encontrado!\n");
                    printf("Nome: %s\n", resultado->dados.nome);
                    printf("Tipo: %s\n", resultado->dados.tipo);
                    printf("Quantidade: %d\n", resultado->dados.quantidade);
                } else {
                    printf("❌ Item não encontrado!\n");
                }
                printf("Comparações realizadas: %d\n", comparacoesSequencial);
                break;
            }
            case 5:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        
        printf("\n");
        
    } while(opcao != 5);
}

/*
 * Insere um novo item na lista encadeada
 */
void inserirItemLista() {
    if (totalItensLista >= MAX_ITENS) {
        printf("❌ ERRO: Lista cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    
    // Aloca memória para o novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("❌ ERRO: Falha na alocação de memória!\n");
        return;
    }
    
    printf("=== INSERIR ITEM NA LISTA ===\n");
    
    // Solicita dados do item
    printf("Digite o nome do item: ");
    fgets(novoNo->dados.nome, TAMANHO_NOME, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = 0;
    
    // Verifica se o item já existe
    if (buscarSequencialLista(novoNo->dados.nome) != NULL) {
        printf("⚠️  Item '%s' já existe na lista!\n", novoNo->dados.nome);
        free(novoNo);
        return;
    }
    
    printf("Digite o tipo do item: ");
    fgets(novoNo->dados.tipo, TAMANHO_TIPO, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = 0;
    
    printf("Digite a quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBuffer();
    
    if (novoNo->dados.quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        free(novoNo);
        return;
    }
    
    // Insere no início da lista
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    totalItensLista++;
    
    printf("✅ Item '%s' adicionado à lista com sucesso!\n", novoNo->dados.nome);
    listarItensLista();
}

/*
 * Remove um item da lista encadeada
 */
void removerItemLista() {
    if (inicioLista == NULL) {
        printf("❌ Lista vazia! Não há itens para remover.\n");
        return;
    }
    
    char nome[TAMANHO_NOME];
    printf("=== REMOVER ITEM DA LISTA ===\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, TAMANHO_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    No* atual = inicioLista;
    No* anterior = NULL;
    
    // Busca o item na lista
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            // Item encontrado
            printf("Item encontrado: %s (Tipo: %s, Quantidade: %d)\n", 
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            
            printf("Confirma a remoção? (s/n): ");
            char confirmacao;
            scanf(" %c", &confirmacao);
            limparBuffer();
            
            if (confirmacao == 's' || confirmacao == 'S') {
                // Remove o nó
                if (anterior == NULL) {
                    // Remove o primeiro nó
                    inicioLista = atual->proximo;
                } else {
                    // Remove nó do meio ou fim
                    anterior->proximo = atual->proximo;
                }
                
                free(atual);
                totalItensLista--;
                printf("✅ Item '%s' removido com sucesso!\n", nome);
                listarItensLista();
            } else {
                printf("Remoção cancelada.\n");
            }
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("❌ Item '%s' não encontrado na lista!\n", nome);
}

/*
 * Lista todos os itens da lista encadeada
 */
void listarItensLista() {
    printf("=== INVENTÁRIO DA LISTA ENCADEADA ===\n");
    
    if (inicioLista == NULL) {
        printf("📦 Lista vazia! Nenhum item cadastrado.\n");
        return;
    }
    
    printf("Total de itens: %d/%d\n\n", totalItensLista, MAX_ITENS);
    
    printf("┌─────┬──────────────────────────────┬────────────────────┬────────────┐\n");
    printf("│ Pos │ Nome                         │ Tipo               │ Quantidade │\n");
    printf("├─────┼──────────────────────────────┼────────────────────┼────────────┤\n");
    
    No* atual = inicioLista;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("│ %-3d │ %-28s │ %-18s │ %-10d │\n", 
               posicao, 
               atual->dados.nome, 
               atual->dados.tipo, 
               atual->dados.quantidade);
        atual = atual->proximo;
        posicao++;
    }
    
    printf("└─────┴──────────────────────────────┴────────────────────┴────────────┘\n");
}

/*
 * Busca sequencial na lista encadeada
 */
No* buscarSequencialLista(char* nome) {
    No* atual = inicioLista;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

/*
 * Libera toda a memória da lista encadeada
 */
void liberarLista() {
    No* atual = inicioLista;
    No* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    inicioLista = NULL;
    totalItensLista = 0;
}


/*
 * ========================================
 * FUNÇÕES PARA VETOR
 * ========================================
 */

/*
 * Exibe o menu do vetor
 */
void exibirMenuVetor() {
    int opcao;
    
    do {
        printf("=== INVENTÁRIO COM VETOR ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (sequencial)\n");
        printf("5. Ordenar vetor\n");
        printf("6. Buscar item (binária) - requer vetor ordenado\n");
        printf("7. Voltar ao menu principal\n");
        printf("============================\n");
        printf("Status: %d/%d itens | Ordenado: %s\n", 
               totalItensVetor, MAX_ITENS, vetorOrdenado ? "Sim" : "Não");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                inserirItemVetor();
                break;
            case 2:
                removerItemVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4: {
                char nome[TAMANHO_NOME];
                printf("Digite o nome do item a buscar: ");
                fgets(nome, TAMANHO_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                resetarContadores();
                int indice = buscarSequencialVetor(nome);
                
                if (indice != -1) {
                    printf("✅ Item encontrado na posição %d!\n", indice + 1);
                    printf("Nome: %s\n", inventarioVetor[indice].nome);
                    printf("Tipo: %s\n", inventarioVetor[indice].tipo);
                    printf("Quantidade: %d\n", inventarioVetor[indice].quantidade);
                } else {
                    printf("❌ Item não encontrado!\n");
                }
                printf("Comparações realizadas: %d\n", comparacoesSequencial);
                break;
            }
            case 5:
                ordenarVetor();
                break;
            case 6: {
                if (!vetorOrdenado) {
                    printf("⚠️  ATENÇÃO: O vetor precisa estar ordenado para busca binária!\n");
                    printf("Use a opção 5 para ordenar primeiro.\n");
                    break;
                }
                
                char nome[TAMANHO_NOME];
                printf("Digite o nome do item a buscar: ");
                fgets(nome, TAMANHO_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                resetarContadores();
                int indice = buscarBinariaVetor(nome);
                
                if (indice != -1) {
                    printf("✅ Item encontrado na posição %d!\n", indice + 1);
                    printf("Nome: %s\n", inventarioVetor[indice].nome);
                    printf("Tipo: %s\n", inventarioVetor[indice].tipo);
                    printf("Quantidade: %d\n", inventarioVetor[indice].quantidade);
                } else {
                    printf("❌ Item não encontrado!\n");
                }
                printf("Comparações realizadas: %d\n", comparacoesBinaria);
                break;
            }
            case 7:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        
        printf("\n");
        
    } while(opcao != 7);
}

/*
 * Insere um novo item no vetor
 */
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("❌ ERRO: Vetor cheio! Não é possível adicionar mais itens.\n");
        return;
    }
    
    Item novoItem;
    
    printf("=== INSERIR ITEM NO VETOR ===\n");
    
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, TAMANHO_NOME, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    
    // Verifica se o item já existe
    if (buscarSequencialVetor(novoItem.nome) != -1) {
        printf("⚠️  Item '%s' já existe no vetor!\n", novoItem.nome);
        return;
    }
    
    printf("Digite o tipo do item: ");
    fgets(novoItem.tipo, TAMANHO_TIPO, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;
    
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();
    
    if (novoItem.quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        return;
    }
    
    inventarioVetor[totalItensVetor] = novoItem;
    totalItensVetor++;
    vetorOrdenado = 0; // Marca como não ordenado
    
    printf("✅ Item '%s' adicionado ao vetor com sucesso!\n", novoItem.nome);
    listarItensVetor();
}

/*
 * Remove um item do vetor
 */
void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Vetor vazio! Não há itens para remover.\n");
        return;
    }
    
    char nome[TAMANHO_NOME];
    printf("=== REMOVER ITEM DO VETOR ===\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, TAMANHO_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    int indice = buscarSequencialVetor(nome);
    
    if (indice == -1) {
        printf("❌ Item '%s' não encontrado no vetor!\n", nome);
        return;
    }
    
    printf("Item encontrado: %s (Tipo: %s, Quantidade: %d)\n", 
           inventarioVetor[indice].nome, 
           inventarioVetor[indice].tipo, 
           inventarioVetor[indice].quantidade);
    
    printf("Confirma a remoção? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    limparBuffer();
    
    if (confirmacao == 's' || confirmacao == 'S') {
        // Move todos os elementos uma posição para trás
        for (int i = indice; i < totalItensVetor - 1; i++) {
            inventarioVetor[i] = inventarioVetor[i + 1];
        }
        
        totalItensVetor--;
        vetorOrdenado = 0; // Marca como não ordenado
        
        printf("✅ Item '%s' removido com sucesso!\n", nome);
        listarItensVetor();
    } else {
        printf("Remoção cancelada.\n");
    }
}

/*
 * Lista todos os itens do vetor
 */
void listarItensVetor() {
    printf("=== INVENTÁRIO DO VETOR ===\n");
    
    if (totalItensVetor == 0) {
        printf("📦 Vetor vazio! Nenhum item cadastrado.\n");
        return;
    }
    
    printf("Total de itens: %d/%d | Ordenado: %s\n\n", 
           totalItensVetor, MAX_ITENS, vetorOrdenado ? "Sim" : "Não");
    
    printf("┌─────┬──────────────────────────────┬────────────────────┬────────────┐\n");
    printf("│ Pos │ Nome                         │ Tipo               │ Quantidade │\n");
    printf("├─────┼──────────────────────────────┼────────────────────┼────────────┤\n");
    
    for (int i = 0; i < totalItensVetor; i++) {
        printf("│ %-3d │ %-28s │ %-18s │ %-10d │\n", 
               i + 1, 
               inventarioVetor[i].nome, 
               inventarioVetor[i].tipo, 
               inventarioVetor[i].quantidade);
    }
    
    printf("└─────┴──────────────────────────────┴────────────────────┴────────────┘\n");
}

/*
 * Busca sequencial no vetor
 */
int buscarSequencialVetor(char* nome) {
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(inventarioVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * Ordena o vetor usando Bubble Sort
 */
void ordenarVetor() {
    if (totalItensVetor <= 1) {
        printf("⚠️  Não há itens suficientes para ordenar.\n");
        return;
    }
    
    printf("🔄 Ordenando vetor por nome (Bubble Sort)...\n");
    
    clock_t inicio = clock();
    int trocas = 0;
    
    // Bubble Sort
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(inventarioVetor[j].nome, inventarioVetor[j + 1].nome) > 0) {
                // Troca os elementos
                Item temp = inventarioVetor[j];
                inventarioVetor[j] = inventarioVetor[j + 1];
                inventarioVetor[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    vetorOrdenado = 1;
    
    printf("✅ Vetor ordenado com sucesso!\n");
    printf("Trocas realizadas: %d\n", trocas);
    printf("Tempo de execução: %.6f segundos\n", tempo);
    
    listarItensVetor();
}

/*
 * Busca binária no vetor (requer vetor ordenado)
 */
int buscarBinariaVetor(char* nome) {
    int esquerda = 0;
    int direita = totalItensVetor - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoesBinaria++;
        
        int comparacao = strcmp(inventarioVetor[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio; // Item encontrado
        } else if (comparacao < 0) {
            esquerda = meio + 1; // Busca na metade direita
        } else {
            direita = meio - 1; // Busca na metade esquerda
        }
    }
    
    return -1; // Item não encontrado
}


/*
 * ========================================
 * SISTEMA DE COMPARAÇÃO DE DESEMPENHO
 * ========================================
 */

/*
 * Função para comparar desempenho entre estruturas
 */
void compararDesempenho() {
    printf("=== COMPARAÇÃO DE DESEMPENHO ===\n\n");
    
    // Estatísticas gerais
    printf("📊 ESTATÍSTICAS GERAIS:\n");
    printf("├─ Itens no Vetor: %d/%d\n", totalItensVetor, MAX_ITENS);
    printf("├─ Itens na Lista: %d/%d\n", totalItensLista, MAX_ITENS);
    printf("├─ Vetor ordenado: %s\n", vetorOrdenado ? "Sim" : "Não");
    printf("└─ Memória da Lista: %d bytes alocados\n", totalItensLista * (int)sizeof(No));
    
    printf("\n🔍 COMPARAÇÕES DE BUSCA:\n");
    printf("├─ Busca Sequencial: %d comparações\n", comparacoesSequencial);
    printf("├─ Busca Binária: %d comparações\n", comparacoesBinaria);
    
    if (comparacoesSequencial > 0 && comparacoesBinaria > 0) {
        float eficiencia = (float)comparacoesBinaria / comparacoesSequencial * 100;
        printf("└─ Eficiência da busca binária: %.1f%% das comparações da sequencial\n", eficiencia);
    } else {
        printf("└─ Execute buscas para ver a comparação\n");
    }
    
    printf("\n⚡ ANÁLISE DE COMPLEXIDADE:\n");
    printf("├─ Busca Sequencial (Vetor): O(n) - Linear\n");
    printf("├─ Busca Sequencial (Lista): O(n) - Linear\n");
    printf("├─ Busca Binária (Vetor): O(log n) - Logarítmica\n");
    printf("├─ Ordenação (Bubble Sort): O(n²) - Quadrática\n");
    printf("└─ Inserção (Lista): O(1) - Constante\n");
    
    printf("\n🎯 RECOMENDAÇÕES:\n");
    if (totalItensVetor > 5 || totalItensLista > 5) {
        printf("├─ Para buscas frequentes: Use vetor ordenado + busca binária\n");
        printf("├─ Para inserções frequentes: Use lista encadeada\n");
        printf("└─ Para dados estáticos: Use vetor ordenado\n");
    } else {
        printf("├─ Com poucos itens, a diferença de desempenho é mínima\n");
        printf("└─ Adicione mais itens para ver diferenças significativas\n");
    }
    
    printf("\n================================\n");
}

/*
 * Função para executar teste de desempenho automatizado
 */
void testeDesempenhoAutomatizado() {
    printf("=== TESTE DE DESEMPENHO AUTOMATIZADO ===\n");
    
    // Dados de teste
    char* nomesTeste[] = {
        "AK-47", "Kit Médico", "Munição 7.62", "Bandagem", "Pistola",
        "Granadas", "Colete", "Capacete", "Óculos", "Mochila"
    };
    char* tiposTeste[] = {
        "arma", "cura", "munição", "cura", "arma",
        "explosivo", "proteção", "proteção", "acessório", "equipamento"
    };
    int quantidadesTeste[] = {1, 5, 120, 10, 1, 3, 1, 1, 1, 1};
    
    printf("Inserindo dados de teste...\n");
    
    // Limpa estruturas existentes
    totalItensVetor = 0;
    vetorOrdenado = 0;
    liberarLista();
    resetarContadores();
    
    // Insere dados no vetor
    for (int i = 0; i < 10 && i < MAX_ITENS; i++) {
        strcpy(inventarioVetor[i].nome, nomesTeste[i]);
        strcpy(inventarioVetor[i].tipo, tiposTeste[i]);
        inventarioVetor[i].quantidade = quantidadesTeste[i];
        totalItensVetor++;
    }
    
    // Insere dados na lista
    for (int i = 0; i < 10 && i < MAX_ITENS; i++) {
        No* novoNo = (No*)malloc(sizeof(No));
        if (novoNo != NULL) {
            strcpy(novoNo->dados.nome, nomesTeste[i]);
            strcpy(novoNo->dados.tipo, tiposTeste[i]);
            novoNo->dados.quantidade = quantidadesTeste[i];
            novoNo->proximo = inicioLista;
            inicioLista = novoNo;
            totalItensLista++;
        }
    }
    
    printf("✅ Dados inseridos: %d itens em cada estrutura\n\n", totalItensVetor);
    
    // Teste de busca sequencial no vetor
    printf("🔍 Testando busca sequencial no vetor...\n");
    resetarContadores();
    buscarSequencialVetor("Capacete");
    int compVetor = comparacoesSequencial;
    
    // Teste de busca sequencial na lista
    printf("🔍 Testando busca sequencial na lista...\n");
    resetarContadores();
    buscarSequencialLista("Capacete");
    int compLista = comparacoesSequencial;
    
    // Ordena o vetor e testa busca binária
    printf("🔄 Ordenando vetor...\n");
    ordenarVetor();
    
    printf("🔍 Testando busca binária no vetor...\n");
    resetarContadores();
    buscarBinariaVetor("Capacete");
    int compBinaria = comparacoesBinaria;
    
    // Exibe resultados
    printf("\n📊 RESULTADOS DO TESTE:\n");
    printf("├─ Busca Sequencial (Vetor): %d comparações\n", compVetor);
    printf("├─ Busca Sequencial (Lista): %d comparações\n", compLista);
    printf("└─ Busca Binária (Vetor): %d comparações\n", compBinaria);
    
    printf("\n🏆 VENCEDORES:\n");
    printf("├─ Busca mais eficiente: %s\n", 
           compBinaria < compVetor ? "Busca Binária" : "Busca Sequencial");
    printf("└─ Estrutura mais eficiente para busca sequencial: %s\n",
           compVetor <= compLista ? "Vetor" : "Lista");
    
    printf("\n================================\n");
}
