/ grep.cpp : This file contains the 'main' function. Program execution begins and ends there.
// grep.exe string to look file1 file2 ....
// ........................................


/********** Search char string on file/s **********/
/* grep.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BuscarCadena(char* cadena1, char* cadena2)
{
    // ¿cadena2 está contenida en cadena1?
    if (strstr(cadena1, cadena2))
        return 1; // se encontró
    else
        return 0; // no se encontró
}

void BuscarEnFich(char* nombrefich, char* cadena)
{
    FILE* pf;
    char linea[256];
    int nrolinea = 0;
    int control = 1; //asumimos error en la apertura

    // Abrir el fichero nombrefich

    control = fopen_s(&pf, nombrefich, "r"); // si ok control = 0


    if ( control != 0)
    {
        perror(nombrefich);
        printf("error");
        return;
    }

    // Buscar cadena en el fichero asociado con pf
    while (fgets(linea, sizeof(linea), pf) != NULL)
    {
        nrolinea++;
        if (BuscarCadena(linea, cadena))
            printf("\n%s[%d]: %s\n", nombrefich, nrolinea, linea);
    }
    fclose(pf);
}

int main(int argc, char* argv[])
{
    int i;

    // Verificar el número de argumentos
    if (argc < 3)
    {
        printf("Sintaxis: %s palabra f1 f2 ... fn\n", argv[0]);
        exit(-1);
    }

    // Llamar a la función BuscarEnFich por cada fichero
    for (i = 2; i < argc; i++)
        BuscarEnFich(argv[i], argv[1]);
}
