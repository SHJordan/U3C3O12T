#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Enum para representar as unidades de comprimento
typedef enum {
  Bits,
  Bytes,
  KB,
  MB,
  GB,
  TB
} unidade_memoria;


// Função de conversão
double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final);

void main(){
  double result = converter_memoria(1, Bytes, KB);

  printf("resultado: %lf\n", result);
}

double converter_memoria(double valor, unidade_memoria unidade_origem, unidade_memoria unidade_final){
  int expoente = 0, addExp = 0;
  double resultado = -1;
  // tratamento de entradas inválidas
  if(valor < 0){
    fprintf(stderr, "Erro: Valores de quantidade de memória não podem ser negativo.\n");
    return -1; // Indica erro
  }

  if(unidade_final == Bits){
    addExp += 3;
    unidade_final = Bytes;
  }

  if(unidade_origem == Bits){
    addExp -= 3;
    unidade_origem = Bytes;
  }

  expoente = (unidade_final-unidade_origem)*10 + addExp;

  resultado = valor*pow(2, expoente);

  return resultado;
  
}
// double converter_comprimento(double valor, unidade_comprimento unidade_origem, unidade_comprimento unidade_destino) {
//   //Tratamento de entradas inválidas
//   if (valor < 0) {
//     
//   }

//   switch (unidade_origem) {
//     case METROS:
//       switch (unidade_destino) {
//         case METROS: return valor;
//         case CENTIMETROS: return valor * 100;
//         case MILIMETROS: return valor * 1000;
//       }
//       break;
//     case CENTIMETROS:
//       switch (unidade_destino) {
//         case METROS: return valor / 100;
//         case CENTIMETROS: return valor;
//         case MILIMETROS: return valor * 10;
//       }
//       break;
//     case MILIMETROS:
//       switch (unidade_destino) {
//         case METROS: return valor / 1000;
//         case CENTIMETROS: return valor / 10;
//         case MILIMETROS: return valor;
//       }
//       break;
//   }

//   fprintf(stderr, "Erro: Combinação de unidades inválida.\n");
//   return -1; // Indica erro
// }


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
