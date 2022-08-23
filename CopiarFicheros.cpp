/********** Copiar el contenido de un fichero en otro ***********/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* des = NULL, * org = NULL;
    int conta = 0, car = 0;
    int check_des = 1; //control apertura correcta flujo. Inicializamos a 1 (error)
    int check_org = 1; //control apertura correcta flujo. Inicializamos a 1 (error)

    // Comprobar el número de argumentos pasados
    // en la línea de órdenes
    if (argc != 3)
    {
        printf("Sintaxis: copiar origen destino\n");
        exit(1);
    }

    //control error apertura. 0 
    check_org = fopen_s(&org, argv[1], "rb");
    check_des = fopen_s(&des, argv[2], "wb");


    // Abrir el fichero indicado por argv[1] para leer
    // y el indicado por argv[2] para escribir
    if ( check_des != 0 || check_org != 0)
    {
        printf("No se puede realizar la copia\n");
        exit(1);
    }
    else {

        // Copiar
        while (!ferror(org) && !feof(org) && !ferror(des))
        {
            car = fgetc(org);
            conta++;   // contar caracteres
            fputc(car, des);
        }

        // Verificar si la copia se hizo con éxito
        if (ferror(org) || ferror(des))
            perror("Error durante la copia");
        else
            printf("Se han copiado %d caracteres\n", conta - 1);

        fclose(org);
        fclose(des);
    }

    return 0;
}
