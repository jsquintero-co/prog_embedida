#include <stdio.h>

double calcular_pi(int N){
    // Definir el acumulador
    double acumulador = 0.0;

    // Definir el número de iteraciones
    int k;

    // Para cada valor de K desde 0 hasta N
    for(k=0; k<= N; k++){
        // Denominador de la serie de Leibniz
        double termino = 1.0 / (2 * k + 1);

        // Revisar si es par para sumar
        if(k%2 == 0){
            acumulador = acumulador + termino;
        }else // Si es impar se resta
        acumulador = acumulador - termino;

    }
    // Se múltiplica por 4 porque es lo que está antes de la sumatoria
    return 4.0 * acumulador;
};

int main(void){

    int N;

    double resultado;

    // Solicitar entrada al usario
    printf("Ingrese el número de términos N: ");
    scanf("%d", &N);

    // Validar la entrada del usuario
    if(N < 0){
        printf("\nERROR: N debe ser mayor o igual a 0");
        return 0;
    }

    // Llamar la función
    resultado = calcular_pi(N);

    // Imprimir resultado con los 8 decimales
    printf("Aproximación de π: %.8f\n", resultado);

    return 0;
}