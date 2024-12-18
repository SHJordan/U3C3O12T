#include <stdio.h>

void temp(int a, float C, float K, float F);

int main(void){

    float C=0.0, F=0.0, K=0.0;
    int x=0;

    while(1){
        printf("\nConverter: \v1 - Celsius para Kelvin; \v2 - Celsius para Fahrenheit; \v3 - Kelvin para Celsius; \v4 - Kelvin para Fahrenheit; \v5 - Fahrenheit para Celsius; \v6 - Fahrenheit para Kelvin; \v7 - Sair.\n");
        scanf("%d", &x);

        temp(x, C, K, F);

        if(x==7) break;
    }

    return 0;
}

void temp(int a, float C, float K, float F){
    
     switch (a){

            case 1:
            printf("\nDigite a temperatura em Celsius: ");
            scanf("%f", &C);
            K = C + 273.15;
            printf("\nTemperatura em Kelvin: %.2f", K);
            break;

            case 2:
            printf("\nDigite a temperatura em Celsius: ");
            scanf("%f", &C);
            F = C*1.8 + 32;
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
            F = (K-273.15)*1.8 + 32;
            printf("\nTemperatura em Fahrenheit: %.2f", F);
            break;

            case 5:
            printf("\nDigite a temperatura em Fahrenheit: ");
            scanf("%f", &F);
            C = (F-32)/1.8;
            printf("\nTemperatura em Celsius: %.2f", C);
            break;

            case 6:
            printf("\nDigite a temperatura em Fahrenheit: ");
            scanf("%f", &F);
            K = (F-32) * (5/9) + 273.15;
            printf("\nTemperatura em Kelvin: %.2f", K);
            break;

            case 7:
            printf("Fim do programa...");
            break;
        }
}
