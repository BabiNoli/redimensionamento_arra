#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo uma estrutura para armazenar o array dinâmico, seu tamanho e capacidade
typedef struct {
    int *dado;       // ponteiro para o array de ints
    int tamanho;        // quantos elementos estão armazenados
    int capacidade;    // capacidade atual
} DynamicArray;

//--------------------------------------------
// Função que cria o array dinâmico
//--------------------------------------------
DynamicArray* createArray(int capacidadeInicial) {
    // Aloca a estrutura em si
    DynamicArray *array = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (!array) {
        printf("Erro ao alocar memoria para DynamicArray.\n");
        exit(1);
    }
    // Aloca espaço para 'capacidadeInicial' inteiros
    array->dado = (int*)malloc(sizeof(int) * capacidadeInicial);
    if (!array->dado) {
        printf("Erro ao alocar memoria para dado.\n");
        free(array);
        exit(1);
    }
    array->tamanho = 0;
    array->capacidade = capacidadeInicial;
    return array;
}

//--------------------------------------------
// Função que realoca o array para o dobro
//--------------------------------------------
void redimensionar(DynamicArray* array) {
    int novaCapacidade = array->capacidade * 2;
    printf("Realocando de %d para %d...\n", array->capacidade, novaCapacidade);

    // realloc realoca o bloco de memória, preservando os dados
    // (ou realoca em outro lugar e copia, mas de forma transparente)
    int *temp = (int*)realloc(array->dado, sizeof(int) * novaCapacidade);
    if (!temp) {
        printf("Erro ao realocar memoria.\n");
        // Em um programa real, poderíamos tentar tratar esse erro
        // mas aqui vamos abortar.
        free(array->dado);
        free(array);
        exit(1);
    }
    array->dado = temp;
    array->capacidade = novaCapacidade;
}

//--------------------------------------------
// Função para inserir um novo valor
//--------------------------------------------
void append(DynamicArray* array, int valor) {
    // Se atingimos a capacidade, precisamos redimensionar
    if (array->tamanho == array->capacidade) {
        redimensionar(array);
    }
    // Armazena o valor e incrementa o tamanho
    array->dado[array->tamanho] = valor;
    array->tamanho++;
}

//--------------------------------------------
// Função para imprimir o array
//--------------------------------------------
void printArray(DynamicArray* array) {
    printf("Posições preenchidas %d, capacidade = %d: ", array->tamanho, array->capacidade);
    for (int i = 0; i < array->tamanho; i++) {
        printf("%d ", array->dado[i]);
    }
    printf("\n");
}


int main() {
    int capacidadeInicial;
    printf("Digite a capacidade inicial do array: ");
    scanf("%d", &capacidadeInicial);

    // Cria o array dinâmico
    DynamicArray* array = createArray(capacidadeInicial);

    // Loop de inserções
    while (1) {
        char buffer[50];
        printf("Digite um valor para adicionar (ou 'sair'): ");
        scanf("%s", buffer);

        // Se o usuário digitar 'sair', encerramos
        if (strcmp(buffer, "sair") == 0) {
            break;
        }

        // Converte a string para inteiro
        int valor = atoi(buffer);

        // Faz append ao array
        append(array, valor);

        // Mostra estado atual do array
        printArray(array);
    }

    // imprimir o array final fora do loop
    printf("Array final:\n");
    printArray(array);

    // Libera a memória
    free(array->dado); // primeiro liberamos o bloco de ints
    free(array);       // depois liberamos a estrutura

    return 0;
}
