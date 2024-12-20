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

// constante que auxilia na representação das unidades de memória
const char nomeUnidade[6][8] = {"Bit(s)", "Byte(s)", "KB", "MB", "GB", "TB"};

// Função de conversão
double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final);

int main(){
  system("chcp 65001 > null"); //Só para aparecer as acentuações na linha de comando

  double valor = -1, result = 0;
  int opcao = -1, casasDec = 3;
  unidade_memoria inUnid = Bytes, outUnid = Bytes;

  printf("Insira o valor (ex: 3.58): ");
  scanf("%lf", &valor);
  while(getchar() != '\n' || valor < 0){
    printf("\tEntrada inválida! Somente números reais positivos! Ex.: 4.1\n\tNova tentativa: ");
    fflush(stdin);
    
    scanf("%lf", &valor);
  }

  printf("\nInsira um dos números abaixo para escolher a unidade de entrada:\n");
  printf("\t[1] Bit(s)\n\t[2] Byte(s)\n\t[3] KB\n\t[4] MB\n\t[5] GB\n\t[6] TB\nEscolha: ");
  scanf("%d", &opcao);
  while(getchar() != '\n' || opcao < 1 || opcao > 6){
    printf("\tEntrada inválida! Ex. de entrada correta '1'\n\tNova tentativa: ");
    fflush(stdin);

    scanf("%d", &opcao);
  }
  inUnid = opcao-1;

  printf("\nAgora escolha da mesma forma a unidade de saída:\n");
  printf("\t[1] Bit(s)\n\t[2] Byte(s)\n\t[3] KB\n\t[4] MB\n\t[5] GB\n\t[6] TB\nEscolha: ");
  scanf("%d", &opcao);
  while(getchar() != '\n' || opcao < 1 && opcao > 6){
    printf("\tEntrada inválida! Ex. de entrada correta '2'\n\tNova tentativa: ");
    fflush(stdin);

    scanf("%d", &opcao);
  }
  outUnid = opcao-1;

  result = converter_memoria(valor, inUnid, outUnid);

  printf("\nresultado:\n\t%g %s = %g %s\n", valor, nomeUnidade[inUnid], result, nomeUnidade[outUnid]);
}

double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final){
  int expoente = 0;
  double resultado = -1, bitCorrecao = 1;
  // tratamento de entradas inválidas
  if(valor < 0){
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