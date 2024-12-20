#include <stdio.h>
#include <stdlib.h>

// Enum para representar as unidades de comprimento
typedef enum {
  METROS,
  CENTIMETROS,
  MILIMETROS
} unidade_comprimento;

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
        case METROS: return valor / 100;
        case CENTIMETROS: return valor;
        case MILIMETROS: return valor * 10;
      }
      break;
    case MILIMETROS:
      switch (unidade_destino) {
        case METROS: return valor / 1000;
        case CENTIMETROS: return valor / 10;
        case MILIMETROS: return valor;
      }
      break;
  }

  fprintf(stderr, "Erro: Combinação de unidades inválida.\n");
  return -1;
}

// Função para conversão de temperatura
void temp(int a, float C, float K, float F) {
  switch (a) {
    case 1:
      printf("\nDigite a temperatura em Celsius: ");
      scanf("%f", &C);
      K = C + 273.15;
      printf("\nTemperatura em Kelvin: %.2f", K);
      break;
    case 2:
      printf("\nDigite a temperatura em Celsius: ");
      scanf("%f", &C);
      F = C * 1.8 + 32;
      printf("\nTemperatura em Fahrenheit: %.2f", F);
      break;
    case 3:
      printf("\nDigite a temperatura em Kelvin: ");
      scanf("%f", &K);
      C = K - 273.15;
      printf("\nTemperatura em Celsius: %.2f", C);
      break;
    case 4:
      printf("\nDigite a temperatura em Kelvin: ");
      scanf("%f", &K);
      F = (K - 273.15) * 1.8 + 32;
      printf("\nTemperatura em Fahrenheit: %.2f", F);
      break;
    case 5:
      printf("\nDigite a temperatura em Fahrenheit: ");
      scanf("%f", &F);
      C = (F - 32) / 1.8;
      printf("\nTemperatura em Celsius: %.2f", C);
      break;
    case 6:
      printf("\nDigite a temperatura em Fahrenheit: ");
      scanf("%f", &F);
      K = (F - 32) * (5.0 / 9) + 273.15;
      printf("\nTemperatura em Kelvin: %.2f", K);
      break;
    case 7:
      printf("Fim do programa...");
      break;
  }
}

int main() {
  system("chcp 65001 > null"); // Só para aparecer as acentuações na linha de comando

  // Exemplo de uso da função de conversão de comprimento
  double valor;
  int origem = 0, destino;

  printf("Digite o valor de comprimento: ");
  if (scanf("%lf", &valor) != 1) {
    fprintf(stderr, "Erro: Entrada inválida.\n");
    return 1;
  }

  printf("Digite a unidade de origem (0: metros, 1: centímetros, 2: milímetros): ");
  if (scanf("%d", &origem) != 1 || origem < 0 || origem > 2) {
    fprintf(stderr, "Erro: Entrada inválida.\n");
    return 1;
  }

  printf("Digite a unidade de destino (0: metros, 1: centímetros, 2: milímetros): ");
  if (scanf("%d", &destino) != 1 || destino < 0 || destino > 2) {
    fprintf(stderr, "Erro: Entrada inválida.\n");
    return 1;
  }

  double resultado_comprimento = converter_comprimento(valor, origem, destino);

  if (resultado_comprimento != -1) {
    printf("Resultado: %.2lf\n", resultado_comprimento);
  }

  // Exemplo de uso da função de conversão de temperatura
  float C = 0.0, F = 0.0, K = 0.0;
  int x = 0;

  while (1) {
    printf("\nConverter: \v1 - Celsius para Kelvin; \v2 - Celsius para Fahrenheit; \v3 - Kelvin para Celsius; \v4 - Kelvin para Fahrenheit; \v5 - Fahrenheit para Celsius; \v6 - Fahrenheit para Kelvin; \v7 - Sair.\n");
    scanf("%d", &x);

    temp(x, C, K, F);

    if (x == 7) break;
  }

  return 0;
}
