#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Enum para representar as unidades de comprimento
typedef enum {
    METROS,
    CENTIMETROS,
    MILIMETROS
} unidade_comprimento;

// Enum para representar as unidades de memória
typedef enum {
    Bits,   // valor como inteiro = 0
    Bytes,  // valor como inteiro = 1
    KB,     // 2
    MB,     // 3
    GB,     // 4
    TB      // 5
} unidade_memoria;

// constante que auxilia na representação das unidades de memória
const char *nomeUnidade[] = {"Bit(s)", "Byte(s)", "KB", "MB", "GB", "TB"};


// Função de conversão de comprimento
double converter_comprimento(double valor, unidade_comprimento unidade_origem, unidade_comprimento unidade_destino) {
    if (valor < 0) {
        fprintf(stderr, "Erro: Valor de comprimento não pode ser negativo.\n");
        return -1;
    }
    switch (unidade_origem) {
        case METROS:
            switch (unidade_destino) {
                case METROS: return valor;
                case CENTIMETROS: return valor * 100;
                case MILIMETROS: return valor * 1000;
            }
            break;
        case CENTIMETROS:
            switch (unidade_destino) {
                case METROS: return valor / 100.0; //Notei a falta do .0 aqui para garantir precisão de double
                case CENTIMETROS: return valor;
                case MILIMETROS: return valor * 10;
            }
            break;
        case MILIMETROS:
            switch (unidade_destino) {
                case METROS: return valor / 1000.0; //Notei a falta do .0 aqui para garantir precisão de double
                case CENTIMETROS: return valor / 10.0; //Notei a falta do .0 aqui para garantir precisão de double
                case MILIMETROS: return valor;
            }
            break;
    }
    fprintf(stderr, "Erro: Combinação de unidades inválida.\n");
    return -1;
}

// Função de conversão de memória
double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final) {
    if (valor < 0) return -1; // Indica erro

    double resultado = valor;
    int expoente = unidade_origem - unidade_final;

    // Ajusta para bits se necessário (1 byte = 8 bits)
    if (unidade_final == Bits) resultado *= 8;
    if (unidade_origem == Bits) resultado *= 0.125;


    // Aplica a conversão baseada em 1000
    if (expoente != 0) resultado *= pow(1024, expoente); // Corrigido para usar 1024 (potências de 2) para KB, MB, GB, etc.

    return resultado;
}


// Função para conversão de temperatura
void converterTemperatura(int opcao, float *celsius, float *kelvin, float *fahrenheit) {
    switch (opcao) {
        case 1:
            printf("\nDigite a temperatura em Celsius: ");
            scanf("%f", celsius);
            *kelvin = *celsius + 273.15;
            printf("\nTemperatura em Kelvin: %.2f\n", *kelvin);
            break;
        case 2:
            printf("\nDigite a temperatura em Celsius: ");
            scanf("%f", celsius);
            *fahrenheit = *celsius * 1.8 + 32;
            printf("\nTemperatura em Fahrenheit: %.2f\n", *fahrenheit);
            break;
        // Adicione os outros casos de conversão de temperatura aqui...
        case 7:
            printf("Fim do programa...\n");
            break;
        default:
            printf("Opção inválida!\n");
    }
}


int main() {
    system("chcp 65001 > null"); // Só para acentuação

    // Conversão de comprimento
    double valor_comprimento;
    int origem_comp, destino_comp;

    printf("Digite o valor de comprimento: ");
    if (scanf("%lf", &valor_comprimento) != 1) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    printf("Digite a unidade de origem (0: metros, 1: centímetros, 2: milímetros): ");
    if (scanf("%d", &origem_comp) != 1 || origem_comp < 0 || origem_comp > 2) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    printf("Digite a unidade de destino (0: metros, 1: centímetros, 2: milímetros): ");
    if (scanf("%d", &destino_comp) != 1 || destino_comp < 0 || destino_comp > 2) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    double resultado_comprimento = converter_comprimento(valor_comprimento, origem_comp, destino_comp);
    if (resultado_comprimento != -1) {
        printf("Resultado comprimento: %.2lf\n", resultado_comprimento);
    }


    // Conversão de memória
    double valor_memoria;
    int opcao_mem, unidade_origem_mem, unidade_destino_mem;

    printf("Digite o valor de memória: ");
    if (scanf("%lf", &valor_memoria) != 1 || valor_memoria < 0) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    printf("Unidade de origem (0: Bits, 1: Bytes, 2: KB, 3: MB, 4: GB, 5: TB): ");
    if (scanf("%d", &unidade_origem_mem) != 1 || unidade_origem_mem < 0 || unidade_origem_mem > 5) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    printf("Unidade de destino (0: Bits, 1: Bytes, 2: KB, 3: MB, 4: GB, 5: TB): ");
    if (scanf("%d", &unidade_destino_mem) != 1 || unidade_destino_mem < 0 || unidade_destino_mem > 5) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    double resultado_memoria = converter_memoria(valor_memoria, unidade_origem_mem, unidade_destino_mem);
    if (resultado_memoria != -1) {
        printf("Resultado memória: %.2lf %s\n", resultado_memoria, nomeUnidade[unidade_destino_mem]);
    }



    // Conversão de temperatura
    float celsius = 0.0, fahrenheit = 0.0, kelvin = 0.0;
    int opcao_temp;
    do {
        printf("\nConverter:\n"
               "1 - Celsius para Kelvin\n"
               "2 - Celsius para Fahrenheit\n"
               "3 - Kelvin para Celsius\n"
               "4 - Kelvin para Fahrenheit\n"
               "5 - Fahrenheit para Celsius\n"
               "6 - Fahrenheit para Kelvin\n"
               "7 - Sair\n");
        scanf("%d", &opcao_temp);
        converterTemperatura(opcao_temp, &celsius, &kelvin, &fahrenheit);
    } while (opcao_temp != 7);

    return 0;
}