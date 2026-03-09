#include <stdio.h>

// Estructura para guardar una medición (id, temperatura, humedad)
typedef struct {
    // ID del sensor, ej. SENS_01
    char id[32];
    // Temperatura en grados
    float temperatura;
    // Humedad en porcentaje
    int humedad;
} Medicion;

// Carga las mediciones desde el archivo y devuelve cuántas se leyeron
int cargar_datos(char nombre_archivo[], Medicion datos[], int max_datos);

int main(void)
{
    // Arreglo donde se guardan las mediciones leídas
    Medicion datos[64];
    // Tamaño máximo del arreglo para no pasarse
    int max_datos = 64;
    // Cantidad de registros que devolvió cargar_datos
    int n;

    n = cargar_datos("sensores.txt", datos, max_datos);

    // Si retornó -1, hubo error al abrir el archivo
    if (n < 0)
        return 1;

    // Mostrar cuántas se cargaron y listar cada una
    printf("Se cargaron %d mediciones:\n", n);
    for (int i = 0; i < n; i++)
        printf("  %s - Temperatura: %.1f, Humedad: %d\n", datos[i].id, datos[i].temperatura, datos[i].humedad);

    return 0;
}

int cargar_datos(char nombre_archivo[], Medicion datos[], int max_datos)
{
    FILE *f;
    // Buffer para leer cada línea del archivo
    char linea[128];
    // Contador de mediciones guardadas
    int num = 0;

    f = fopen(nombre_archivo, "r");
    if (f == NULL)
    {
        printf("Error: no se pudo abrir el archivo '%s'.\n", nombre_archivo);
        return -1;
    }

    // Leer línea a línea hasta que no haya más
    while (fgets(linea, sizeof(linea), f) != NULL)
    {
        // No guardar más de max_datos
        if (num >= max_datos)
            break;

        // Extraer id,temp,hum con sscanf; formato: ID,float,int
        // Si sscanf lee los 3 campos retorna 3 y guardamos en datos[num]
        if (sscanf(linea, "%[^,],%f,%d", datos[num].id, &datos[num].temperatura, &datos[num].humedad) == 3)
            num++;
    }

    fclose(f);
    return num;
}