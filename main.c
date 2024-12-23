#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define clear() printf("\033[H\033[J")

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

// Enum para representar as unidades de tempo
typedef enum {
	SEGUNDOS,
	MINUTOS,
	HORAS
} unidade_tempo;

// constantes que auxiliam na representação das unidades de memória e tempo
const char *nomeUnidade[] = {"Bit(s)", "Byte(s)", "KB", "MB", "GB", "TB"};
const char *nomeUnidadeTempo[] = {"segundo(s)", "minuto(s)", "hora(s)"};



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
            *kelvin = *celsius + 273.15f;
            printf("\nTemperatura em Kelvin: %.2f\n", *kelvin);
            break;
        case 2:
            printf("\nDigite a temperatura em Celsius: ");
            scanf("%f", celsius);
            *fahrenheit = *celsius * 1.8f + 32;
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


void converterVelocidade() {
    int opcao;
    float velocidadeInicial = 0.0f;
    int unidadeFinal = 0;
    printf("\nSelecione a Unidade da Velocidade Atual:\n1 - Km/h\n2 - M/s\n3 - Mph\n");
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            printf("\nDigite a velocidade em Km/h:\n");
            scanf("%f", &velocidadeInicial);
            printf("\nSelecione a Unidade de Velocidade Destino:\n1 - M/s\n2 - Mph\n");
            scanf("%d", &unidadeFinal);
            if (unidadeFinal == 1) {
                printf("\nA velocidade em M/s é: %f", (velocidadeInicial / 3.6));
            } else if (unidadeFinal == 2) {
                printf("\nA velocidade em Mph é: %f", (velocidadeInicial / 1.609));
            } else {
                printf("\nOpção inválida!\n");
            }
            break;
        case 2:
            printf("\nDigite a velocidade em M/s:\n");
            scanf("%f", &velocidadeInicial);
            printf("\nSelecione a Unidade de Velocidade Destino:\n1 - Km/h\n2 - Mph\n");
            scanf("%d", &unidadeFinal);
            if (unidadeFinal == 1) {
                printf("\nA velocidade em Km/h é: %f", (velocidadeInicial * 3.6));
            } else if (unidadeFinal == 2) {
                printf("\nA velocidade em Mph é: %f", (velocidadeInicial * 2.23694));
            } else {
                printf("\nOpção inválida!\n");
            }
            break;
        case 3:
            printf("\nDigite a velocidade em Mph:\n");
            scanf("%f", &velocidadeInicial);
            printf("\nSelecione a Unidade de Velocidade Destino:\n1 - Km/h\n2 - M/s\n");
            scanf("%d", &unidadeFinal);
            if (unidadeFinal == 1) {
                printf("\nA velocidade em Km/h é: %f", (velocidadeInicial * 1.609));
            } else if (unidadeFinal == 2) {
                printf("\nA velocidade em M/s é: %f", (velocidadeInicial / 2.23694));
            } else {
                printf("\nOpção inválida!\n");
            }
            break;
        default:
            printf("\nOpção inválida!\n");
    }
}


// Função para conversão de unidades de tempo
double converter_tempo(double valor, unidade_tempo unidade_origem, unidade_tempo unidade_destino) {
    if (valor < 0) {
        fprintf(stderr, "Erro: Medida de tempo  não pode ser negativa.\n");
        return -1;
    }
    switch (unidade_origem) {
        case SEGUNDOS:
            switch (unidade_destino) {
                case SEGUNDOS: return valor;
                case MINUTOS: return valor / 60.0;
                case HORAS: return valor / 3600.0;
            }
            break;
        case MINUTOS:
            switch (unidade_destino) {
                case SEGUNDOS: return valor * 60;
                case MINUTOS: return valor;
                case HORAS: return valor / 60.0;
            }
            break;
        case HORAS:
            switch (unidade_destino) {
                case SEGUNDOS: return valor * 3600;
                case MINUTOS: return valor * 60;
                case HORAS: return valor;
            }
            break;
    }
    fprintf(stderr, "Erro: Combinação de unidades inválida.\n");
    return -1;
}

// Função para conversão de Watts, kwatts e cv
void converter_potencia(int opc, double valor){

    double valorW, valorkW, valorHP; //Valores em diferentes escalas


    // opc1 define qual o tipo de conversão que deseja
    printf("Aqui está sua medida em diferentes unidades:\n");

    switch (opc)
    {
        case 1: // Valor dado está em watts

           valorW = valor;
           valorkW = valor / 1000.0;
           valorHP = valor / 735.5;

            break;

        case 2: // Valor dado está em kwatts

            valorW = valor * 1000.0;
            valorkW = valor;
            valorHP = valorW / 735.5;          
           
            break;

        case 3: // Valor dado está em Horse Power
            
            valorW = valor * 735.5;
            valorkW = valorW /1000.0;
            valorHP = valor;

            break;
    }

     printf("\n%.lf W\n", valorW);   
     printf("%.2lf kW\n", valorkW);
     printf("%.2lf cv\n", valorHP);

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
    int unidade_origem_mem, unidade_destino_mem;

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

	// Conversão de tempo
	double valor_tempo;
    int origem_temp, destino_temp;

    printf("Digite a medida de tempo: ");
    if (scanf("%lf", &valor_tempo) != 1) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    printf("Digite a unidade de origem (0: segundos, 1: minutos, 2: horas): ");
    if (scanf("%d", &origem_temp) != 1 || origem_temp < 0 || origem_temp > 2) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    printf("Digite a unidade de destino (0: segundos, 1: minutos, 2: horas): ");
    if (scanf("%d", &destino_temp) != 1 || destino_temp < 0 || destino_temp > 2) {
        fprintf(stderr, "Erro: Entrada inválida.\n");
        return 1;
    }

    double resultado_tempo = converter_tempo(valor_tempo, origem_temp, destino_temp);
    if (resultado_tempo != -1) {
        printf("Resultado tempo: %lf %s em %s são %lf %s \n", valor_tempo, nomeUnidadeTempo[origem_temp], nomeUnidadeTempo[destino_temp], resultado_tempo, nomeUnidadeTempo[destino_temp]);
    }


    // Conversão de temperatura
    float celsius = 0.0f, fahrenheit = 0.0f, kelvin = 0.0f;
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

    //conversor de potênca
    double potencia;
    int opc_p = 0;
    
     do {
        printf("\nBem-vindo ao conversor de potência! O seu valor está em qual das escalas abaixo:\n");
        printf("1 - Watts\n2 - Kilowatts\n3 - Cavalos-vapor (Horse Power!)\n4 - Não quero fazer esta conversão\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc_p);

        if (opc_p == 1 || opc_p == 2 || opc_p == 3) {
            printf("Digite o valor numérico:\n");
            scanf("%lf", &potencia); 

            converter_potencia(opc_p, potencia); 
        } else if (opc_p != 4) {
            printf("Opção Inválida!\n");
        }
    } while (opc_p != 4);

    return 0;
}
#include <stdio.h>

void menu() {
    printf("=== Conversor de Unidades de Área ===\n");
    printf("1. Metros quadrados para centímetros quadrados\n");
    printf("2. Centímetros quadrados para metros quadrados\n");
    printf("3. Metros quadrados para milímetros quadrados\n");
    printf("4. Milímetros quadrados para metros quadrados\n");
    printf("5. Metros quadrados para quilômetros quadrados\n");
    printf("6. Quilômetros quadrados para metros quadrados\n");
    printf("7. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;
    double valor, resultado;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor em metros quadrados: ");
                scanf("%lf", &valor);
                resultado = valor * 10000; // 1 m² = 10,000 cm²
                printf("%.2lf metros quadrados equivalem a %.2lf centímetros quadrados.\n\n", valor, resultado);
                break;

            case 2:
                printf("Digite o valor em centímetros quadrados: ");
                scanf("%lf", &valor);
                resultado = valor / 10000; // 1 cm² = 0.0001 m²
                printf("%.2lf centímetros quadrados equivalem a %.2lf metros quadrados.\n\n", valor, resultado);
                break;

            case 3:
                printf("Digite o valor em metros quadrados: ");
                scanf("%lf", &valor);
                resultado = valor * 1000000; // 1 m² = 1,000,000 mm²
                printf("%.2lf metros quadrados equivalem a %.2lf milímetros quadrados.\n\n", valor, resultado);
                break;

            case 4:
                printf("Digite o valor em milímetros quadrados: ");
                scanf("%lf", &valor);
                resultado = valor / 1000000; // 1 mm² = 0.000001 m²
                printf("%.2lf milímetros quadrados equivalem a %.2lf metros quadrados.\n\n", valor, resultado);
                break;

            case 5:
                printf("Digite o valor em metros quadrados: ");
                scanf("%lf", &valor);
                resultado = valor / 1000000; // 1 m² = 0.000001 km²
                printf("%.2lf metros quadrados equivalem a %.6lf quilômetros quadrados.\n\n", valor, resultado);
                break;

            case 6:
                printf("Digite o valor em quilômetros quadrados: ");
                scanf("%lf", &valor);
                resultado = valor * 1000000; // 1 km² = 1,000,000 m²
                printf("%.6lf quilômetros quadrados equivalem a %.2lf metros quadrados.\n\n", valor, resultado);
                break;

            case 7:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n\n");
        }
    } while (opcao != 7);

    return 0;
}
