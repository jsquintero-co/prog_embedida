#include <stdio.h>

// Estructura para una medición (igual que punto 5)
typedef struct {
    char id[32];
    float temperatura;
    int humedad;
} Medicion;

// Firmes con la patria jajaja (firma de las funciones)
int cargar_datos(char nombre_archivo[], Medicion datos[], int max_datos);
void analizar_temperaturas(Medicion datos[], int cantidad);

int main(void)
{
    Medicion datos[64];
    int max_datos = 64;
    int n;

    n = cargar_datos("sensores.txt", datos, max_datos);
    if (n < 0)
        return 1;

    // Analizar el arreglo llenado y mostrar máx, mín y promedio
    analizar_temperaturas(datos, n);

    return 0;
}

void analizar_temperaturas(Medicion datos[], int cantidad)
{
    // Evitar división por cero y arreglo vacío
    if (cantidad <= 0)
    {
        printf("No hay datos para analizar.\n");
        return;
    }

    // Inicializar con el primer elemento
    float temp_max = datos[0].temperatura;
    float temp_min = datos[0].temperatura;
    float suma = 0.0f;
    int indice_max = 0;
    int indice_min = 0;

    // Recorrer el arreglo para obtener máx, mín y suma
    for (int i = 0; i < cantidad; i++)
    {
        suma += datos[i].temperatura;
        if (datos[i].temperatura > temp_max)
        {
            temp_max = datos[i].temperatura;
            indice_max = i;
        }
        if (datos[i].temperatura < temp_min)
        {
            temp_min = datos[i].temperatura;
            indice_min = i;
        }
    }

    // Promedio = suma / cantidad
    float promedio = suma / (float)cantidad;

    // Imprimir resultados con el ID del sensor para máx y mín
    printf("Temperatura maxima: %.1f (sensor %s)\n", temp_max, datos[indice_max].id);
    printf("Temperatura minima: %.1f (sensor %s)\n", temp_min, datos[indice_min].id);
    printf("Promedio general: %.1f\n", promedio);
}

int cargar_datos(char nombre_archivo[], Medicion datos[], int max_datos)
{
    FILE *f;
    char linea[128];
    int num = 0;

    f = fopen(nombre_archivo, "r");
    if (f == NULL)
    {
        printf("Error: no se pudo abrir el archivo '%s'.\n", nombre_archivo);
        return -1;
    }

    while (fgets(linea, sizeof(linea), f) != NULL)
    {
        if (num >= max_datos)
            break;
        if (sscanf(linea, "%[^,],%f,%d", datos[num].id, &datos[num].temperatura, &datos[num].humedad) == 3)
            num++;
    }

    fclose(f);
    return num;
}