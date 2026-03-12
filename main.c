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
void analizar_temperaturas(Medicion datos[], int cantidad);
void exportar_corregido(char nom_arch[], Medicion datos[], int cant, float offset);

int main(void) {
    Medicion datos[64];
    int max_datos = 64;
    int n = 0;

    int opcion;
    float offset;

    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Cargar Archivo\n");
        printf("2. Mostrar Analisis\n");
        printf("3. Exportar Datos Calibrados\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:

                n = cargar_datos("sensores.txt", datos, max_datos);

                if (n < 0)
                {
                    printf("Error al leer el archivo.\n");
                    n = 0;
                }
                else
                {
                    printf("Se cargaron %d mediciones.\n", n);
                }

                break;

            case 2:

                if (n <= 0)
                {
                    printf("Primero debe cargar el archivo.\n");
                }
                else
                {
                    analizar_temperaturas(datos, n);
                }

                break;

            case 3:

                if (n <= 0)
                {
                    printf("Primero debe cargar el archivo.\n");
                }
                else
                {
                    printf("Ingrese el offset de calibracion: ");
                    scanf("%f", &offset);

                    exportar_corregido("sensores_calibrados.txt", datos, n, offset);

                    printf("Archivo sensores_calibrados.txt generado.\n");
                }

                break;

            case 4:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 4);

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
