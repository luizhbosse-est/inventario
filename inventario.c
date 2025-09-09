/*
 * Sistema de Inventário para Jogo de Sobrevivência
 * Este programa implementa um sistema de inventário que simula uma mochila
 * virtual para um jogo de sobrevivência. O jogador pode cadastrar, remover,
 * listar e buscar itens em sua mochila.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da estrutura Item para representar os itens do inventário
typedef struct {
    char nome[30];      // Nome do item (ex: "AK-47", "Kit Médico")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;     // Quantidade do item no inventário
} Item;

// Constantes do sistema
#define MAX_ITENS 10
#define TAMANHO_NOME 30
#define TAMANHO_TIPO 20

// Variáveis globais
Item inventario[MAX_ITENS];  // Vetor para armazenar os itens
int totalItens = 0;          // Contador de itens no inventário

// Declaração das funções
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer();

/*
 * Função principal do programa
 * Controla o fluxo principal através de um menu interativo
 */
int main() {
    int opcao;
    
    printf("=== SISTEMA DE INVENTÁRIO - JOGO DE SOBREVIVÊNCIA ===\n");
    printf("Bem-vindo ao seu sistema de mochila virtual!\n\n");
    
    // Loop principal do programa
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Saindo do sistema... Boa sorte na sobrevivência!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
        
    } while(opcao != 5);
    
    return 0;
}

/*
 * Exibe o menu principal do sistema
 */
void exibirMenu() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Cadastrar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item\n");
    printf("5. Sair\n");
    printf("=====================\n");
}

/*
 * Limpa o buffer de entrada para evitar problemas com scanf
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/*
 * Função para inserir um novo item no inventário
 * Verifica se há espaço disponível e solicita os dados do item
 */
void inserirItem() {
    // Verifica se o inventário está cheio
    if (totalItens >= MAX_ITENS) {
        printf("❌ ERRO: Inventário cheio! Não é possível adicionar mais itens.\n");
        printf("Remova alguns itens antes de adicionar novos.\n");
        return;
    }
    
    Item novoItem;
    
    printf("=== CADASTRAR NOVO ITEM ===\n");
    
    // Solicita o nome do item
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, TAMANHO_NOME, stdin);
    // Remove a quebra de linha do fgets
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    
    // Verifica se o item já existe
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, novoItem.nome) == 0) {
            printf("⚠️  Item '%s' já existe no inventário!\n", novoItem.nome);
            printf("Quantidade atual: %d\n", inventario[i].quantidade);
            printf("Deseja aumentar a quantidade? (s/n): ");
            
            char resposta;
            scanf(" %c", &resposta);
            limparBuffer();
            
            if (resposta == 's' || resposta == 'S') {
                int quantidadeAdicional;
                printf("Digite a quantidade a adicionar: ");
                scanf("%d", &quantidadeAdicional);
                limparBuffer();
                
                if (quantidadeAdicional > 0) {
                    inventario[i].quantidade += quantidadeAdicional;
                    printf("✅ Quantidade atualizada! Total: %d\n", inventario[i].quantidade);
                    listarItens();
                } else {
                    printf("❌ Quantidade inválida!\n");
                }
            }
            return;
        }
    }
    
    // Solicita o tipo do item
    printf("Digite o tipo do item (arma/munição/cura/ferramenta): ");
    fgets(novoItem.tipo, TAMANHO_TIPO, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;
    
    // Solicita a quantidade
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();
    
    // Valida a quantidade
    if (novoItem.quantidade <= 0) {
        printf("❌ ERRO: Quantidade deve ser maior que zero!\n");
        return;
    }
    
    // Adiciona o item ao inventário
    inventario[totalItens] = novoItem;
    totalItens++;
    
    printf("✅ Item '%s' adicionado com sucesso!\n", novoItem.nome);
    
    // Lista os itens após a inserção
    listarItens();
}


/*
 * Função para remover um item do inventário
 * Busca o item pelo nome e o remove, reorganizando o vetor
 */
void removerItem() {
    if (totalItens == 0) {
        printf("❌ Inventário vazio! Não há itens para remover.\n");
        return;
    }
    
    char nomeItem[TAMANHO_NOME];
    
    printf("=== REMOVER ITEM ===\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeItem, TAMANHO_NOME, stdin);
    nomeItem[strcspn(nomeItem, "\n")] = 0;
    
    // Busca o item no inventário
    int indiceItem = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(inventario[i].nome, nomeItem) == 0) {
            indiceItem = i;
            break;
        }
    }
    
    // Verifica se o item foi encontrado
    if (indiceItem == -1) {
        printf("❌ Item '%s' não encontrado no inventário!\n", nomeItem);
        return;
    }
    
    // Exibe informações do item a ser removido
    printf("Item encontrado:\n");
    printf("Nome: %s\n", inventario[indiceItem].nome);
    printf("Tipo: %s\n", inventario[indiceItem].tipo);
    printf("Quantidade: %d\n", inventario[indiceItem].quantidade);
    
    // Confirma a remoção
    printf("Tem certeza que deseja remover este item? (s/n): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    limparBuffer();
    
    if (confirmacao != 's' && confirmacao != 'S') {
        printf("Remoção cancelada.\n");
        return;
    }
    
    // Remove o item reorganizando o vetor
    for (int i = indiceItem; i < totalItens - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    
    totalItens--;
    
    printf("✅ Item '%s' removido com sucesso!\n", nomeItem);
    
    // Lista os itens após a remoção
    listarItens();
}


/*
 * Função para listar todos os itens do inventário
 * Exibe uma tabela formatada com todos os itens cadastrados
 */
void listarItens() {
    printf("=== INVENTÁRIO ATUAL ===\n");
    
    if (totalItens == 0) {
        printf("📦 Inventário vazio! Nenhum item cadastrado.\n");
        printf("Use a opção 1 para adicionar itens.\n");
        return;
    }
    
    printf("Total de itens: %d/%d\n\n", totalItens, MAX_ITENS);
    
    // Cabeçalho da tabela
    printf("┌─────┬──────────────────────────────┬────────────────────┬────────────┐\n");
    printf("│ Nº  │ Nome                         │ Tipo               │ Quantidade │\n");
    printf("├─────┼──────────────────────────────┼────────────────────┼────────────┤\n");
    
    // Lista todos os itens
    for (int i = 0; i < totalItens; i++) {
        printf("│ %-3d │ %-28s │ %-18s │ %-10d │\n", 
               i + 1, 
               inventario[i].nome, 
               inventario[i].tipo, 
               inventario[i].quantidade);
    }
    
    printf("└─────┴──────────────────────────────┴────────────────────┴────────────┘\n");
    
    // Estatísticas por tipo
    printf("\n=== ESTATÍSTICAS POR TIPO ===\n");
    int contadores[4] = {0}; // arma, munição, cura, outros
    
    for (int i = 0; i < totalItens; i++) {
        if (strstr(inventario[i].tipo, "arma") != NULL) {
            contadores[0]++;
        } else if (strstr(inventario[i].tipo, "munição") != NULL || 
                   strstr(inventario[i].tipo, "municao") != NULL) {
            contadores[1]++;
        } else if (strstr(inventario[i].tipo, "cura") != NULL) {
            contadores[2]++;
        } else {
            contadores[3]++;
        }
    }
    
    printf("🔫 Armas: %d itens\n", contadores[0]);
    printf("🔸 Munições: %d itens\n", contadores[1]);
    printf("💊 Cura: %d itens\n", contadores[2]);
    printf("🔧 Outros: %d itens\n", contadores[3]);
}


/*
 * Função para buscar um item específico no inventário
 * Implementa busca sequencial pelo nome do item
 */
void buscarItem() {
    if (totalItens == 0) {
        printf("❌ Inventário vazio! Não há itens para buscar.\n");
        return;
    }
    
    char nomeBusca[TAMANHO_NOME];
    
    printf("=== BUSCAR ITEM ===\n");
    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, TAMANHO_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    printf("\nRealizando busca sequencial...\n");
    
    // Busca sequencial no inventário
    int encontrado = 0;
    int posicao = -1;
    
    for (int i = 0; i < totalItens; i++) {
        // Busca exata
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            posicao = i;
            break;
        }
    }
    
    if (encontrado) {
        printf("✅ Item encontrado!\n\n");
        printf("=== DETALHES DO ITEM ===\n");
        printf("Posição no inventário: %d\n", posicao + 1);
        printf("Nome: %s\n", inventario[posicao].nome);
        printf("Tipo: %s\n", inventario[posicao].tipo);
        printf("Quantidade: %d\n", inventario[posicao].quantidade);
        
        // Verifica se é um item crítico (baixa quantidade)
        if (inventario[posicao].quantidade <= 5) {
            printf("⚠️  ATENÇÃO: Quantidade baixa! Considere reabastecer.\n");
        }
        
    } else {
        printf("❌ Item '%s' não encontrado no inventário.\n", nomeBusca);
        
        // Busca por similaridade (busca parcial)
        printf("\nBuscando itens similares...\n");
        int encontrouSimilar = 0;
        
        for (int i = 0; i < totalItens; i++) {
            if (strstr(inventario[i].nome, nomeBusca) != NULL) {
                if (!encontrouSimilar) {
                    printf("Itens similares encontrados:\n");
                    encontrouSimilar = 1;
                }
                printf("- %s (Tipo: %s, Quantidade: %d)\n", 
                       inventario[i].nome, 
                       inventario[i].tipo, 
                       inventario[i].quantidade);
            }
        }
        
        if (!encontrouSimilar) {
            printf("Nenhum item similar encontrado.\n");
        }
    }
}
