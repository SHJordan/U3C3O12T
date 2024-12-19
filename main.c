#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Enum para representar as unidades de memória
typedef enum {
  Bits,   // valor como inteiro = 0
  Bytes,  // valor como inteiro = 1
  KB,     // 2
  MB,     // 3
  GB,     // 4
  TB      // 5
} unidade_memoria;

// constanque que auxilia na representação das unidades de memória
const char* nomeUnidade[6] = {"Bit(s)", "Byte(s)", "KB", "MB", "GB", "TB"};

// Função de conversão
double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final);

int main(){
  system("chcp 65001 > null"); //Só para aparecer as acentuações na linha de comando
  double valor = 0, result = 0;
  int opcao = -1, casasDec = 3;
  unidade_memoria inUnid = Bytes, outUnid = Bytes;

  printf("Insira o valor (ex: 3.58): ");
  scanf("%lf", &valor);

  printf("\nInsira um dos números abaixo para escolher a unidade de entrada:\n");
  printf("\t[1] Bit(s)\n\t[2] Byte(s)\n\t[3] KB\n\t[4] MB\n\t[5] GB\n\t[6] TB\nEscolha: ");
  scanf("%d", &opcao);
  if(opcao > 0 && opcao < 7){
    inUnid = opcao-1;
  }

  printf("\nAgora escolha da mesma forma a unidade de saída:\n");
  printf("\t[1] Bit(s)\n\t[2] Byte(s)\n\t[3] KB\n\t[4] MB\n\t[5] GB\n\t[6] TB\nEscolha: ");
  scanf("%d", &opcao);
  if(opcao > 0 && opcao < 7){
    outUnid = opcao-1;
  }

  result = converter_memoria(valor, inUnid, outUnid);

  if(outUnid > inUnid){
    casasDec *= (outUnid-inUnid);
  }

  printf("\nresultado:\n\t%.3lf %s = %.*lf %s\n", valor, nomeUnidade[inUnid], casasDec, result, nomeUnidade[outUnid]);
}

double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final){
  int expoente = 0;
  double resultado = -1, bitCorrecao = 1;
  // tratamento de entradas inválidas
  if(valor < 0){
    fprintf(stderr, "Erro: Valores de quantidade de memória não podem ser negativo.\n");
    return -1; // Indica erro
  }

  // regulando os valores para conversão (1 byte = 8 bits)
    if(unidade_final == Bits){
      bitCorrecao *= 8;
      unidade_final = Bytes;
    }

    if(unidade_origem == Bits){
      bitCorrecao *= 0.125; // 1/8 = 0,125
      unidade_origem = Bytes;
    }

  // cálculo do expoente
    expoente = (unidade_origem-unidade_final);
  // result = valor*1000^(uf - uo)*(correção caso tenha bits no meio: multiplica ou divide por 8)
  resultado = valor*pow(1000, expoente)*bitCorrecao;

  return resultado;
  
}

// int main() {
//   system("chcp 65001 > null"); //Só para aparecer as acentuações na linha de comando
//   double valor;
//   int origem = 0, destino;

//   printf("Digite o valor de comprimento: ");
//   if (scanf("%lf", &valor) != 1) {
//     fprintf(stderr, "Erro: Entrada inválida.\n");
//     return 1;
//   }

//   printf("Digite a unidade de origem (0: metros, 1: centímetros, 2: milímetros): ");
//   if (scanf("%d", &origem) != 1 || origem < 0 || origem > 2) {
//     fprintf(stderr, "Erro: Entrada inválida.\n");
//     return 1;
//   }

//   printf("Digite a unidade de destino (0: metros, 1: centímetros, 2: milímetros): ");
//   if (scanf("%d", &destino) != 1 || destino < 0 || destino > 2) {
//     fprintf(stderr, "Erro: Entrada inválida.\n");
//     return 1;
//   }

//   double resultado = converter_comprimento(valor, origem, destino);

//   if (resultado != -1) {
//     printf("Resultado: %.2lf\n", resultado);
//   }

//   return 0;
// }
