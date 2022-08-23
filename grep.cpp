// grep.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/********** Search char string on file/s **********/
/* command line options: string to look file1 file2 filen
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
            printf("%s[%d]: %s\n", nombrefich, nrolinea, linea);
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



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
