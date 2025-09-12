/*
 * Sistema de Torre de Fuga - Módulo 3
 * 
 * Sistema avançado de organização de componentes para montagem de torre de fuga.
 * Implementa múltiplos algoritmos de ordenação, busca binária otimizada e
 * análise de desempenho em tempo real.
 * 
 * Algoritmos implementados:
 * - Bubble Sort (ordenação por nome)
 * - Insertion Sort (ordenação por tipo)
 * - Selection Sort (ordenação por prioridade)
 * - Busca Binária (busca por nome em array ordenado)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Componente
typedef struct {
    char nome[30];      // Nome do componente (ex: "chip central")
    char tipo[20];      // Tipo (ex: "controle", "suporte", "propulsão")
    int prioridade;     // Prioridade de 1 a 10
} Componente;

// Constantes do sistema
#define MAX_COMPONENTES 20
#define TAMANHO_NOME 30
#define TAMANHO_TIPO 20

// Variáveis globais
Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;
int ordenadoPorNome = 0;    // Flag para indicar se está ordenado por nome
int ordenadoPorTipo = 0;    // Flag para indicar se está ordenado por tipo
int ordenadoPorPrioridade = 0; // Flag para indicar se está ordenado por prioridade

// Contadores de comparações
int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;
int comparacoesBusca = 0;

// Declaração das funções principais
void exibirMenuPrincipal();
void cadastrarComponente();
void mostrarComponentes();
void limparBuffer();
void resetarContadores();
void exibirEstatisticas();

// Funções de ordenação
void bubbleSortNome(Componente arr[], int n);
void insertionSortTipo(Componente arr[], int n);
void selectionSortPrioridade(Componente arr[], int n);

// Função de busca
int buscaBinariaPorNome(Componente arr[], int n, char nome[]);

// Funções de medição e análise
double medirTempo(void (*algoritmo)(Componente[], int), Componente arr[], int n);
void compararAlgoritmos();
void iniciarMontagem();
void testarBuscas();

/*
 * Função principal do programa
 */
int main() {
    int opcao;
    
    printf("=== SISTEMA DE TORRE DE FUGA - MÓDULO 3 ===\n");
    printf("Sistema Avançado de Organização de Componentes\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                if (totalComponentes == 0) {
                    printf("❌ Nenhum componente cadastrado!\n");
                } else {
                    printf("🔄 Ordenando por nome (Bubble Sort)...\n");
                    resetarContadores();
                    double tempo = medirTempo(bubbleSortNome, torre, totalComponentes);
                    ordenadoPorNome = 1;
                    ordenadoPorTipo = 0;
                    ordenadoPorPrioridade = 0;
                    printf("✅ Ordenação concluída!\n");
                    printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoesBubble, tempo);
                    mostrarComponentes();
                }
                break;
            case 3:
                if (totalComponentes == 0) {
                    printf("❌ Nenhum componente cadastrado!\n");
                } else {
                    printf("🔄 Ordenando por tipo (Insertion Sort)...\n");
                    resetarContadores();
                    double tempo = medirTempo(insertionSortTipo, torre, totalComponentes);
                    ordenadoPorNome = 0;
                    ordenadoPorTipo = 1;
                    ordenadoPorPrioridade = 0;
                    printf("✅ Ordenação concluída!\n");
                    printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoesInsertion, tempo);
                    mostrarComponentes();
                }
                break;
            case 4:
                if (totalComponentes == 0) {
                    printf("❌ Nenhum componente cadastrado!\n");
                } else {
                    printf("🔄 Ordenando por prioridade (Selection Sort)...\n");
                    resetarContadores();
                    double tempo = medirTempo(selectionSortPrioridade, torre, totalComponentes);
                    ordenadoPorNome = 0;
                    ordenadoPorTipo = 0;
                    ordenadoPorPrioridade = 1;
                    printf("✅ Ordenação concluída!\n");
                    printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoesSelection, tempo);
                    mostrarComponentes();
                }
                break;
            case 5: {
                if (!ordenadoPorNome) {
                    printf("⚠️  ATENÇÃO: Para busca binária, os componentes devem estar ordenados por nome!\n");
                    printf("Use a opção 2 para ordenar por nome primeiro.\n");
                    break;
                }
                
                char nomeBusca[TAMANHO_NOME];
                printf("=== BUSCA DO COMPONENTE-CHAVE ===\n");
                printf("Digite o nome do componente-chave: ");
                fgets(nomeBusca, TAMANHO_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                
                resetarContadores();
                clock_t inicio = clock();
                int indice = buscaBinariaPorNome(torre, totalComponentes, nomeBusca);
                clock_t fim = clock();
                double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                
                if (indice != -1) {
                    printf("🎯 COMPONENTE-CHAVE ENCONTRADO!\n");
                    printf("Nome: %s\n", torre[indice].nome);
                    printf("Tipo: %s\n", torre[indice].tipo);
                    printf("Prioridade: %d\n", torre[indice].prioridade);
                    printf("Posição: %d\n", indice + 1);
                } else {
                    printf("❌ Componente-chave não encontrado!\n");
                }
                printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoesBusca, tempo);
                break;
            }
            case 6:
                mostrarComponentes();
                break;
            case 7:
                compararAlgoritmos();
                break;
            case 8:
                exibirEstatisticas();
                break;
            case 9:
                iniciarMontagem();
                break;
            case 10:
                testarBuscas();
                break;
            case 11:
                printf("Saindo do sistema... Boa sorte na fuga!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
        
    } while(opcao != 11);
    
    return 0;
}

/*
 * Exibe o menu principal do sistema
 */
void exibirMenuPrincipal() {
    printf("=== MENU PRINCIPAL ===\n");
    printf("1. Cadastrar componente\n");
    printf("2. Ordenar por nome (Bubble Sort)\n");
    printf("3. Ordenar por tipo (Insertion Sort)\n");
    printf("4. Ordenar por prioridade (Selection Sort)\n");
    printf("5. Buscar componente-chave (Busca Binária)\n");
    printf("6. Exibir componentes\n");
    printf("7. Comparar algoritmos\n");
    printf("8. Exibir estatísticas\n");
    printf("9. Iniciar montagem da torre\n");
    printf("10. Testar buscas (Sequencial vs Binária)\n");
    printf("11. Sair\n");
    printf("======================\n");
    printf("Status: %d/%d componentes | Ordenado: %s\n", 
           totalComponentes, MAX_COMPONENTES,
           ordenadoPorNome ? "Nome" : (ordenadoPorTipo ? "Tipo" : (ordenadoPorPrioridade ? "Prioridade" : "Não")));
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
    comparacoesBubble = 0;
    comparacoesInsertion = 0;
    comparacoesSelection = 0;
    comparacoesBusca = 0;
}


/*
 * Cadastra um novo componente no sistema
 */
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("❌ ERRO: Limite máximo de componentes atingido (%d)!\n", MAX_COMPONENTES);
        return;
    }
    
    Componente novoComponente;
    
    printf("=== CADASTRAR COMPONENTE ===\n");
    
    // Solicita o nome do componente
    printf("Digite o nome do componente: ");
    fgets(novoComponente.nome, TAMANHO_NOME, stdin);
    novoComponente.nome[strcspn(novoComponente.nome, "\n")] = 0;
    
    // Verifica se o componente já existe
    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(torre[i].nome, novoComponente.nome) == 0) {
            printf("⚠️  Componente '%s' já existe!\n", novoComponente.nome);
            return;
        }
    }
    
    // Solicita o tipo do componente
    printf("Digite o tipo do componente (controle/suporte/propulsão/outros): ");
    fgets(novoComponente.tipo, TAMANHO_TIPO, stdin);
    novoComponente.tipo[strcspn(novoComponente.tipo, "\n")] = 0;
    
    // Solicita a prioridade
    do {
        printf("Digite a prioridade (1-10): ");
        scanf("%d", &novoComponente.prioridade);
        limparBuffer();
        
        if (novoComponente.prioridade < 1 || novoComponente.prioridade > 10) {
            printf("❌ ERRO: Prioridade deve estar entre 1 e 10!\n");
        }
    } while (novoComponente.prioridade < 1 || novoComponente.prioridade > 10);
    
    // Adiciona o componente ao array
    torre[totalComponentes] = novoComponente;
    totalComponentes++;
    
    // Marca como não ordenado
    ordenadoPorNome = 0;
    ordenadoPorTipo = 0;
    ordenadoPorPrioridade = 0;
    
    printf("✅ Componente '%s' cadastrado com sucesso!\n", novoComponente.nome);
    mostrarComponentes();
}

/*
 * Exibe todos os componentes cadastrados
 */
void mostrarComponentes() {
    printf("=== COMPONENTES DA TORRE ===\n");
    
    if (totalComponentes == 0) {
        printf("📦 Nenhum componente cadastrado!\n");
        printf("Use a opção 1 para cadastrar componentes.\n");
        return;
    }
    
    printf("Total: %d/%d componentes\n", totalComponentes, MAX_COMPONENTES);
    printf("Ordenação atual: %s\n\n", 
           ordenadoPorNome ? "Por Nome (Bubble Sort)" : 
           (ordenadoPorTipo ? "Por Tipo (Insertion Sort)" : 
           (ordenadoPorPrioridade ? "Por Prioridade (Selection Sort)" : "Sem ordenação")));
    
    // Cabeçalho da tabela
    printf("┌─────┬──────────────────────────────┬────────────────────┬────────────┐\n");
    printf("│ Pos │ Nome                         │ Tipo               │ Prioridade │\n");
    printf("├─────┼──────────────────────────────┼────────────────────┼────────────┤\n");
    
    // Lista todos os componentes
    for (int i = 0; i < totalComponentes; i++) {
        printf("│ %-3d │ %-28s │ %-18s │ %-10d │\n", 
               i + 1, 
               torre[i].nome, 
               torre[i].tipo, 
               torre[i].prioridade);
    }
    
    printf("└─────┴──────────────────────────────┴────────────────────┴────────────┘\n");
    
    // Estatísticas por tipo
    printf("\n=== ESTATÍSTICAS POR TIPO ===\n");
    int contadores[4] = {0}; // controle, suporte, propulsão, outros
    
    for (int i = 0; i < totalComponentes; i++) {
        if (strstr(torre[i].tipo, "controle") != NULL) {
            contadores[0]++;
        } else if (strstr(torre[i].tipo, "suporte") != NULL) {
            contadores[1]++;
        } else if (strstr(torre[i].tipo, "propulsão") != NULL || 
                   strstr(torre[i].tipo, "propulsao") != NULL) {
            contadores[2]++;
        } else {
            contadores[3]++;
        }
    }
    
    printf("🎛️  Controle: %d componentes\n", contadores[0]);
    printf("🔧 Suporte: %d componentes\n", contadores[1]);
    printf("🚀 Propulsão: %d componentes\n", contadores[2]);
    printf("⚙️  Outros: %d componentes\n", contadores[3]);
}

/*
 * Exibe estatísticas de desempenho
 */
void exibirEstatisticas() {
    printf("=== ESTATÍSTICAS DE DESEMPENHO ===\n");
    printf("Total de componentes: %d/%d\n", totalComponentes, MAX_COMPONENTES);
    printf("\n📊 COMPARAÇÕES POR ALGORITMO:\n");
    printf("├─ Bubble Sort (Nome): %d comparações\n", comparacoesBubble);
    printf("├─ Insertion Sort (Tipo): %d comparações\n", comparacoesInsertion);
    printf("├─ Selection Sort (Prioridade): %d comparações\n", comparacoesSelection);
    printf("└─ Busca Binária: %d comparações\n", comparacoesBusca);
    
    printf("\n🎯 STATUS DE ORDENAÇÃO:\n");
    printf("├─ Ordenado por Nome: %s\n", ordenadoPorNome ? "✅ Sim" : "❌ Não");
    printf("├─ Ordenado por Tipo: %s\n", ordenadoPorTipo ? "✅ Sim" : "❌ Não");
    printf("└─ Ordenado por Prioridade: %s\n", ordenadoPorPrioridade ? "✅ Sim" : "❌ Não");
    
    printf("\n⚡ COMPLEXIDADE DOS ALGORITMOS:\n");
    printf("├─ Bubble Sort: O(n²) - Quadrática\n");
    printf("├─ Insertion Sort: O(n²) pior caso, O(n) melhor caso\n");
    printf("├─ Selection Sort: O(n²) - Quadrática\n");
    printf("└─ Busca Binária: O(log n) - Logarítmica\n");
    
    printf("==================================\n");
}


/*
 * ========================================
 * ALGORITMOS DE ORDENAÇÃO
 * ========================================
 */

/*
 * Bubble Sort - Ordenação por nome (alfabética)
 * Complexidade: O(n²)
 * Compara elementos adjacentes e os troca se estiverem fora de ordem
 */
void bubbleSortNome(Componente arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0; // Flag para otimização
        
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesBubble++; // Conta cada comparação
            
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                // Troca os elementos
                Componente temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = 1;
            }
        }
        
        // Se não houve trocas, o array já está ordenado
        if (!trocou) {
            break;
        }
    }
}

/*
 * Insertion Sort - Ordenação por tipo (alfabética)
 * Complexidade: O(n²) no pior caso, O(n) no melhor caso
 * Insere cada elemento na posição correta em relação aos elementos já ordenados
 */
void insertionSortTipo(Componente arr[], int n) {
    for (int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;
        
        // Move elementos maiores que a chave uma posição à frente
        while (j >= 0) {
            comparacoesInsertion++; // Conta cada comparação
            
            if (strcmp(arr[j].tipo, chave.tipo) > 0) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        
        arr[j + 1] = chave;
    }
}

/*
 * Selection Sort - Ordenação por prioridade (numérica)
 * Complexidade: O(n²)
 * Encontra o menor elemento e o coloca na posição correta
 */
void selectionSortPrioridade(Componente arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indiceMenor = i;
        
        // Encontra o elemento com menor prioridade
        for (int j = i + 1; j < n; j++) {
            comparacoesSelection++; // Conta cada comparação
            
            if (arr[j].prioridade < arr[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        
        // Troca o elemento atual com o menor encontrado
        if (indiceMenor != i) {
            Componente temp = arr[i];
            arr[i] = arr[indiceMenor];
            arr[indiceMenor] = temp;
        }
    }
}

/*
 * Função para medir tempo de execução de algoritmos de ordenação
 */
double medirTempo(void (*algoritmo)(Componente[], int), Componente arr[], int n) {
    // Cria uma cópia do array para não afetar o original durante a medição
    Componente copia[MAX_COMPONENTES];
    for (int i = 0; i < n; i++) {
        copia[i] = arr[i];
    }
    
    clock_t inicio = clock();
    algoritmo(copia, n); // Executa o algoritmo na cópia
    clock_t fim = clock();
    
    // Copia o resultado de volta para o array original
    for (int i = 0; i < n; i++) {
        arr[i] = copia[i];
    }
    
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/*
 * Função para comparar todos os algoritmos de ordenação
 */
void compararAlgoritmos() {
    if (totalComponentes < 2) {
        printf("❌ É necessário ter pelo menos 2 componentes para comparar algoritmos!\n");
        return;
    }
    
    printf("=== COMPARAÇÃO DE ALGORITMOS DE ORDENAÇÃO ===\n");
    printf("Testando com %d componentes...\n\n", totalComponentes);
    
    // Salva o estado original
    Componente original[MAX_COMPONENTES];
    for (int i = 0; i < totalComponentes; i++) {
        original[i] = torre[i];
    }
    
    // Testa Bubble Sort
    printf("🔵 BUBBLE SORT (por nome):\n");
    resetarContadores();
    double tempoBubble = medirTempo(bubbleSortNome, torre, totalComponentes);
    printf("├─ Comparações: %d\n", comparacoesBubble);
    printf("└─ Tempo: %.6f segundos\n\n", tempoBubble);
    
    // Restaura estado original
    for (int i = 0; i < totalComponentes; i++) {
        torre[i] = original[i];
    }
    
    // Testa Insertion Sort
    printf("🟢 INSERTION SORT (por tipo):\n");
    resetarContadores();
    double tempoInsertion = medirTempo(insertionSortTipo, torre, totalComponentes);
    printf("├─ Comparações: %d\n", comparacoesInsertion);
    printf("└─ Tempo: %.6f segundos\n\n", tempoInsertion);
    
    // Restaura estado original
    for (int i = 0; i < totalComponentes; i++) {
        torre[i] = original[i];
    }
    
    // Testa Selection Sort
    printf("🟡 SELECTION SORT (por prioridade):\n");
    resetarContadores();
    double tempoSelection = medirTempo(selectionSortPrioridade, torre, totalComponentes);
    printf("├─ Comparações: %d\n", comparacoesSelection);
    printf("└─ Tempo: %.6f segundos\n\n", tempoSelection);
    
    // Restaura estado original
    for (int i = 0; i < totalComponentes; i++) {
        torre[i] = original[i];
    }
    
    // Análise comparativa
    printf("📊 ANÁLISE COMPARATIVA:\n");
    
    // Algoritmo mais rápido
    if (tempoBubble <= tempoInsertion && tempoBubble <= tempoSelection) {
        printf("🏆 Algoritmo mais rápido: Bubble Sort\n");
    } else if (tempoInsertion <= tempoBubble && tempoInsertion <= tempoSelection) {
        printf("🏆 Algoritmo mais rápido: Insertion Sort\n");
    } else {
        printf("🏆 Algoritmo mais rápido: Selection Sort\n");
    }
    
    // Algoritmo com menos comparações
    if (comparacoesBubble <= comparacoesInsertion && comparacoesBubble <= comparacoesSelection) {
        printf("🎯 Menos comparações: Bubble Sort (%d)\n", comparacoesBubble);
    } else if (comparacoesInsertion <= comparacoesBubble && comparacoesInsertion <= comparacoesSelection) {
        printf("🎯 Menos comparações: Insertion Sort (%d)\n", comparacoesInsertion);
    } else {
        printf("🎯 Menos comparações: Selection Sort (%d)\n", comparacoesSelection);
    }
    
    printf("\n💡 RECOMENDAÇÕES:\n");
    printf("├─ Para dados quase ordenados: Insertion Sort\n");
    printf("├─ Para dados pequenos: Qualquer algoritmo\n");
    printf("├─ Para dados grandes: Considere algoritmos O(n log n)\n");
    printf("└─ Para busca frequente: Ordene primeiro, depois use busca binária\n");
    
    printf("=============================================\n");
    
    // Reseta flags de ordenação
    ordenadoPorNome = 0;
    ordenadoPorTipo = 0;
    ordenadoPorPrioridade = 0;
}


/*
 * ========================================
 * BUSCA BINÁRIA E SISTEMA DE MONTAGEM
 * ========================================
 */

/*
 * Busca Binária - Busca por nome em array ordenado
 * Complexidade: O(log n)
 * Requer que o array esteja ordenado por nome
 */
int buscaBinariaPorNome(Componente arr[], int n, char nome[]) {
    int esquerda = 0;
    int direita = n - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoesBusca++; // Conta cada comparação
        
        int comparacao = strcmp(arr[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio; // Componente encontrado
        } else if (comparacao < 0) {
            esquerda = meio + 1; // Busca na metade direita
        } else {
            direita = meio - 1; // Busca na metade esquerda
        }
    }
    
    return -1; // Componente não encontrado
}

/*
 * Sistema de montagem da torre de fuga
 */
void iniciarMontagem() {
    printf("=== SISTEMA DE MONTAGEM DA TORRE ===\n");
    
    if (totalComponentes == 0) {
        printf("❌ Nenhum componente cadastrado para montagem!\n");
        return;
    }
    
    printf("🏗️  Iniciando processo de montagem da torre de fuga...\n\n");
    
    // Verifica se há componentes de todos os tipos necessários
    int temControle = 0, temSuporte = 0, temPropulsao = 0;
    
    for (int i = 0; i < totalComponentes; i++) {
        if (strstr(torre[i].tipo, "controle") != NULL) temControle = 1;
        if (strstr(torre[i].tipo, "suporte") != NULL) temSuporte = 1;
        if (strstr(torre[i].tipo, "propulsão") != NULL || 
            strstr(torre[i].tipo, "propulsao") != NULL) temPropulsao = 1;
    }
    
    printf("📋 VERIFICAÇÃO DE COMPONENTES ESSENCIAIS:\n");
    printf("├─ Sistema de Controle: %s\n", temControle ? "✅ Disponível" : "❌ Ausente");
    printf("├─ Sistema de Suporte: %s\n", temSuporte ? "✅ Disponível" : "❌ Ausente");
    printf("└─ Sistema de Propulsão: %s\n", temPropulsao ? "✅ Disponível" : "❌ Ausente");
    
    if (!temControle || !temSuporte || !temPropulsao) {
        printf("\n⚠️  ATENÇÃO: Componentes essenciais estão faltando!\n");
        printf("A torre pode não funcionar corretamente.\n");
    }
    
    // Busca por componente-chave
    printf("\n🔍 BUSCA DO COMPONENTE-CHAVE:\n");
    
    if (!ordenadoPorNome) {
        printf("⚠️  Para localizar o componente-chave, é necessário ordenar por nome primeiro.\n");
        printf("Deseja ordenar agora? (s/n): ");
        
        char resposta;
        scanf(" %c", &resposta);
        limparBuffer();
        
        if (resposta == 's' || resposta == 'S') {
            printf("🔄 Ordenando componentes por nome...\n");
            resetarContadores();
            double tempo = medirTempo(bubbleSortNome, torre, totalComponentes);
            ordenadoPorNome = 1;
            ordenadoPorTipo = 0;
            ordenadoPorPrioridade = 0;
            printf("✅ Ordenação concluída em %.6f segundos\n", tempo);
        } else {
            printf("❌ Montagem cancelada. Ordene os componentes e tente novamente.\n");
            return;
        }
    }
    
    char componenteChave[TAMANHO_NOME];
    printf("Digite o nome do componente-chave para ativar a torre: ");
    fgets(componenteChave, TAMANHO_NOME, stdin);
    componenteChave[strcspn(componenteChave, "\n")] = 0;
    
    resetarContadores();
    clock_t inicio = clock();
    int indiceChave = buscaBinariaPorNome(torre, totalComponentes, componenteChave);
    clock_t fim = clock();
    double tempoBusca = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    if (indiceChave == -1) {
        printf("❌ FALHA NA MONTAGEM!\n");
        printf("Componente-chave '%s' não encontrado.\n", componenteChave);
        printf("Comparações realizadas: %d | Tempo: %.6f segundos\n", comparacoesBusca, tempoBusca);
        return;
    }
    
    printf("🎯 COMPONENTE-CHAVE LOCALIZADO!\n");
    printf("Nome: %s\n", torre[indiceChave].nome);
    printf("Tipo: %s\n", torre[indiceChave].tipo);
    printf("Prioridade: %d\n", torre[indiceChave].prioridade);
    printf("Localizado em %.6f segundos com %d comparações\n", tempoBusca, comparacoesBusca);
    
    // Simulação da montagem
    printf("\n🏗️  INICIANDO MONTAGEM...\n");
    printf("┌─ Fase 1: Instalando base de suporte...\n");
    printf("├─ Fase 2: Conectando sistemas de controle...\n");
    printf("├─ Fase 3: Ativando propulsão...\n");
    printf("├─ Fase 4: Inserindo componente-chave...\n");
    printf("└─ Fase 5: Teste final dos sistemas...\n");
    
    printf("\n🚀 TORRE DE FUGA MONTADA COM SUCESSO!\n");
    printf("🎉 Parabéns! Você conseguiu escapar da ilha!\n");
    
    // Relatório final
    printf("\n📊 RELATÓRIO FINAL DA MISSÃO:\n");
    printf("├─ Componentes utilizados: %d\n", totalComponentes);
    printf("├─ Algoritmo de ordenação: Bubble Sort\n");
    printf("├─ Comparações na busca: %d\n", comparacoesBusca);
    printf("├─ Tempo de busca: %.6f segundos\n", tempoBusca);
    printf("└─ Status da missão: ✅ SUCESSO\n");
    
    printf("=======================================\n");
}

/*
 * Função para testar desempenho da busca binária vs sequencial
 */
void testarBuscas() {
    if (totalComponentes == 0) {
        printf("❌ Nenhum componente cadastrado para teste!\n");
        return;
    }
    
    printf("=== TESTE DE DESEMPENHO: BUSCA SEQUENCIAL vs BINÁRIA ===\n");
    
    // Garante que está ordenado por nome para busca binária
    if (!ordenadoPorNome) {
        printf("🔄 Ordenando por nome para habilitar busca binária...\n");
        bubbleSortNome(torre, totalComponentes);
        ordenadoPorNome = 1;
    }
    
    // Escolhe um componente aleatório para buscar
    int indiceAleatorio = rand() % totalComponentes;
    char nomeBusca[TAMANHO_NOME];
    strcpy(nomeBusca, torre[indiceAleatorio].nome);
    
    printf("Testando busca pelo componente: '%s'\n\n", nomeBusca);
    
    // Teste de busca sequencial
    printf("🔍 BUSCA SEQUENCIAL:\n");
    int comparacoesSeq = 0;
    clock_t inicioSeq = clock();
    
    int encontradoSeq = -1;
    for (int i = 0; i < totalComponentes; i++) {
        comparacoesSeq++;
        if (strcmp(torre[i].nome, nomeBusca) == 0) {
            encontradoSeq = i;
            break;
        }
    }
    
    clock_t fimSeq = clock();
    double tempoSeq = ((double)(fimSeq - inicioSeq)) / CLOCKS_PER_SEC;
    
    printf("├─ Resultado: %s\n", encontradoSeq != -1 ? "Encontrado" : "Não encontrado");
    printf("├─ Comparações: %d\n", comparacoesSeq);
    printf("└─ Tempo: %.6f segundos\n\n", tempoSeq);
    
    // Teste de busca binária
    printf("🎯 BUSCA BINÁRIA:\n");
    resetarContadores();
    clock_t inicioBin = clock();
    int encontradoBin = buscaBinariaPorNome(torre, totalComponentes, nomeBusca);
    clock_t fimBin = clock();
    double tempoBin = ((double)(fimBin - inicioBin)) / CLOCKS_PER_SEC;
    
    printf("├─ Resultado: %s\n", encontradoBin != -1 ? "Encontrado" : "Não encontrado");
    printf("├─ Comparações: %d\n", comparacoesBusca);
    printf("└─ Tempo: %.6f segundos\n\n", tempoBin);
    
    // Comparação
    printf("📊 COMPARAÇÃO:\n");
    printf("├─ Redução de comparações: %.1f%%\n", 
           (1.0 - (double)comparacoesBusca / comparacoesSeq) * 100);
    printf("├─ Speedup: %.1fx mais rápida\n", 
           tempoSeq > 0 ? tempoSeq / tempoBin : 1.0);
    printf("└─ Vencedor: %s\n", 
           comparacoesBusca < comparacoesSeq ? "Busca Binária" : "Busca Sequencial");
    
    printf("=============================================\n");
}