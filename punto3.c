#include <stdio.h>


void filtro_promedio(float entrada[], float salida[], int tamano, int ventana)
{
    // Revisar parametros inválidos
    if (ventana <= 0 || tamano <= 0)
    {
        printf("Error: ventana y tamano deben ser mayores que 0.\n");
        return;
    }

    // Para cada posición i del arreglo
    for (int i = 0; i < tamano; i++)
    {
        // Índice donde empieza la ventana
        int inicio;
        // Al inicio no hay suficientes elementos a la izquierda
        if (i - ventana + 1 < 0)
            inicio = 0;
        else
            inicio = i - ventana + 1;

        // Cuántos elementos se promedian (desde inicio hasta i)
        int cantidad = i - inicio + 1;
        // Acumulador de la suma
        float suma = 0.0f;

        // Sumar todos los valores de la ventana
        for (int j = inicio; j <= i; j++)
            suma += entrada[j];

        // Promedio = suma / cantidad; se guarda en salida[i]
        salida[i] = suma / (float)cantidad;
    }
}

int main(void)
{
    // Arreglo de entrada con ruido (25.0 es el pico)
    float entrada[] = {10.2f, 10.5f, 25.0f, 10.3f, 10.1f};
    // Arreglo donde se escribe el resultado
    float salida[5];
    // Cantidad de elementos
    int tamano = 5;
    // Tamaño de la ventana del promedio
    int ventana = 3;

    // Aplicar la función para el filtro
    filtro_promedio(entrada, salida, tamano, ventana);

    // Imprimir arreglo original
    printf("Arreglo original: ");
    for (int i = 0; i < tamano; i++)
        printf("%.1f ", entrada[i]);
    printf("\n");

    // Imprimir arreglo suavizado
    printf("Arreglo suavizado: ");
    for (int i = 0; i < tamano; i++)
        printf("%.1f ", salida[i]);
    printf("\n");

    return 0;
}

