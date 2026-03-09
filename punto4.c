#include <stdio.h>

#define MAX_CELDAS 16

void detectar_picos(int filas, int cols, int mapa[4][4]);

int main(void)
{
    // Armamos el mapa 4x4; el 9 en el medio es el pico
    int mapa[4][4] = {
        {1, 2, 1, 0},
        {2, 9, 2, 0},
        {1, 2, 1, 0},
        {0, 0, 0, 0}
    };

    //Llamar la funcipon
    detectar_picos(4, 4, mapa);

    return 0;
}

void detectar_picos(int filas, int cols, int mapa[4][4])
{
    // Para guardar las coordenadas de cada pico que encontremos
    int picos_i[MAX_CELDAS];
    int picos_j[MAX_CELDAS];
    int num_picos = 0;

    // Recorremos toda la matriz, celda por celda
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int es_pico = 1;  // De entrada pues se asume, y si algún vecino lo supera lo bajamos

            // arriba: solo miro si existe esa fila
            if (i - 1 >= 0 && mapa[i][j] <= mapa[i - 1][j])
                es_pico = 0;
            // abajo
            if (i + 1 < filas && mapa[i][j] <= mapa[i + 1][j])
                es_pico = 0;
            // izquierda
            if (j - 1 >= 0 && mapa[i][j] <= mapa[i][j - 1])
                es_pico = 0;
            // derecha
            if (j + 1 < cols && mapa[i][j] <= mapa[i][j + 1])
                es_pico = 0;

            // si pasó todas las pruebas, anotamos el par (i, j)
            if (es_pico)
            {
                picos_i[num_picos] = i;
                picos_j[num_picos] = j;
                num_picos++;
            }
        }
    }

    // si no encontramos nada, avisamos y seguimos
    if (num_picos == 0)
    {
        printf("No se encontraron picos.\n");
        return;
    }

    // listamos todos los picos que fuimos guardando
    for (int k = 0; k < num_picos; k++)
        printf("Pico en (%d, %d) con valor %d\n", picos_i[k], picos_j[k], mapa[picos_i[k]][picos_j[k]]);
}