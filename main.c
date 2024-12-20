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
const char nomeUnidade[6][8] = {"Bit(s)", "Byte(s)", "KB", "MB", "GB", "TB"};

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

// Função de conversão de memória
double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final) {
  int expoente = 0;
  double resultado = -1, bitCorrecao = 1;

  if (valor < 0) {
    return -1; // Indica erro
  }

  // regulando os valores para conversão (1 byte = 8 bits)
  if (unidade_final == Bits) {
    bitCorrecao *= 8;
    unidade_final = Bytes;
  }

  if (unidade_origem == Bits) {
    bitCorrecao *= 0.125; // 1/8 = 0,125
    unidade_origem = Bytes;
  }

  // cálculo do expoente
  expoente = (unidade_origem - unidade_final);
  // result = valor*1000^(uf - uo)*(correção caso tenha bits no meio: multiplica ou divide por 8)
  resultado = valor * pow(1000, expoente) * bitCorrecao;

  return resultado;
}

int main() {
  system("chcp 65001 > null"); // Só para aparecer as acentuações na linha de comando

  // Exemplo de uso da função de conversão de comprimento
  double valor_comprimento;
  int origem = 0, destino;

  printf("Digite o valor de comprimento: ");
  if (scanf("%lf", &valor_comprimento) != 1) {
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

  double resultado_comprimento = converter_comprimento(valor_comprimento, origem, destino);

  if (resultado_comprimento != -1) {
    printf("Resultado: %.2lf\n", resultado_comprimento);
  }

  // Exemplo de uso da função de conversão de memória
  double valor_memoria = -1, result_memoria = 0;
  int opcao = -1;
  unidade_memoria inUnid = Bytes, outUnid = Bytes;

  printf("Insira o valor de memória (ex: 3.58): ");
  scanf("%lf", &valor_memoria);
  while (getchar() != '\n' || valor_memoria < 0) {
    printf("\tEntrada inválida! Somente números reais positivos! Ex.: 4.1\n\tNova tentativa: ");
    fflush(stdin);
    scanf("%lf", &valor_memoria);
  }

  printf("\nInsira um dos números abaixo para escolher a unidade de entrada:\n");
  printf("\t[1] Bit(s)\n\t[2] Byte(s)\n\t[3] KB\n\t[4] MB\n\t[5] GB\n\t[6] TB\nEscolha: ");
  scanf("%d", &opcao);
  while (getchar() != '\n' || opcao < 1 || opcao > 6) {
    printf("\tEntrada inválida! Ex. de entrada correta '1'\n\tNova tentativa: ");
    fflush(stdin);
    scanf("%d", &opcao);
  }
  inUnid = opcao - 1;

  printf("\nAgora escolha da mesma forma a unidade de saída:\n");
  printf("\t[1] Bit(s)\n\t[2] Byte(s)\n\t[3] KB\n\t[4] MB\n\t[5] GB\n\t[6] TB\nEscolha: ");
  scanf("%d", &opcao);
  while (getchar() != '\n' || opcao < 1 || opcao > 6) {
    printf("\tEntrada inválida! Ex. de entrada correta '2'\n\tNova tentativa: ");
    fflush(stdin);
    scanf("%d", &opcao);
  }
  outUnid = opcao - 1;

  result_memoria = converter_memoria(valor_memoria, inUnid, outUnid);

  printf("\nresultado:\n\t%g %s = %g %s\n", valor_memoria, nomeUnidade[inUnid], result_memoria, nomeUnidade[outUnid]);

  return 0;
}
