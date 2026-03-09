#include <stdio.h>

void cifrar_cadena(char texto[], int desplazamiento){

    int i = 0;

    // Mientras sigan habiendo caracteres en la cadena de texto...
    while(texto[i] != '\0'){
        // Revisa que este en el rango de las mayúsculas de la A a la Z
        if(texto[i] >= 'A' && texto[i] <= 'Z')
        {
            // Encontrar la posición con respecto a la A (como pivote)
            int pos = texto[i] - 'A';
            // Toma la letra y le suma el desplazamiento
            pos = (pos + desplazamiento) % 26; // El %26 es para que siempre quede la posición entre 0 y 25
            if(pos<0){
                pos = pos + 26;
            }
            texto[i] = 'A' + pos;
        }else if(texto[i] >= 'a' && texto[i] <= 'z'){
            // Lo mismo pero con las minúsculas
            int pos = texto[i] - 'a';
            pos = (pos + desplazamiento) % 26;
            if (pos < 0)
                pos = pos + 26;
            texto[i] = 'a' + pos;

        }
        // Siguiente letra
        i++;

    }


};

int main(void)
{
    // Almacenar la frase
    char texto[256];

    // Cantidad de desplazamientos
    int desplazamiento;

    // Pedirle al usuario la frase
    printf("Ingrese la frase: ");
    fgets(texto, 256, stdin);

    // Quitarle el '\n' al fgets */
    int j = 0;
    while (texto[j] != '\0')
    {
        if (texto[j] == '\n')
        {
            texto[j] = '\0';
            break;
        }
        j++;
    }

    // Pedirle el desplazamiento
    printf("Ingrese el desplazamiento: ");
    scanf("%d", &desplazamiento);

    // Llamar la función e imprimir el texto
    cifrar_cadena(texto, desplazamiento);
    printf("Texto cifrado: %s\n", texto);

    return 0;
}

