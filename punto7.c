#include <stdio.h>

// Estructura para una medición (igual que punto 5)
typedef struct {
    char id[32];
    float temperatura;
    int humedad;
} Medicion;

int cargar_datos(char nombre_archivo[], Medicion datos[], int max_datos);
void exportar_corregido(char nom_arch[], Medicion datos[], int cant, float offset);

int main(void)
{
    Medicion datos[64];
    int max_datos = 64;
    int n;

    n = cargar_datos("sensores.txt", datos, max_datos);
    if (n < 0)
        return 1;

    // Corregir temperaturas con offset y guardar en archivo
    exportar_corregido("sensores_calibrados.txt", datos, n, -1.5f);

    return 0;
}

void exportar_corregido(char nom_arch[], Medicion datos[], int cant, float offset)
{
    FILE *f;

    f = fopen(nom_arch, "w");
    if (f == NULL)
    {
        printf("Error: no se pudo crear el archivo '%s'.\n", nom_arch);
        return;
    }

    // Recorrer el arreglo y escribir cada línea con la temperatura corregida
    for (int i = 0; i < cant; i++)
    {
        float nueva_temp = datos[i].temperatura + offset;
        fprintf(f, "%s,%.1f,%d\n", datos[i].id, nueva_temp, datos[i].humedad);
    }

    fclose(f);
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