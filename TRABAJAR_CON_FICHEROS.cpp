// TRABAJAR_CON_FICHEROS.cpp 
//

#include <stdio.h>
#include <string.h> //necesario para strlen

int main()
{
    // flujo (Esta estructura define un buffer y los miembros necesarios para movernos por el mismo)
    FILE* pf; 
    FILE* pf1;
    FILE* pf2;
    FILE* pf3;

    // nombre ficheros
    const char* fictexto = "mifichero-t.txt";
    const char* ficbinario = "mifichero-b.bin";
    const char* ficbinario2 = "mifichero-b2.bin";
    const char* ficbinario3 = "mifichero-b3.bin";

    // Abrir el fichero
    //fopen_s( &pf, "mifichero-t.txt", "wt"); // w: write, t: fichero de texto
    fopen_s(&pf, fictexto, "wt"); // w: write, t: fichero de texto

    // Escribir en el fichero
    // Esta función se utiliza igual que printf, pero tiene un parámetro más,
    // el primero, que se corresponde con el flujo que define el fichero en el que se quiere escribir
    fprintf(pf, "¡Hola mundo!\n"); //
    fprintf(pf, "%d * %d = %d\n", 9, 256, 9 * 256);

    // Control errores
    if (ferror(pf)) {
        printf("Error al escribir en el fichero %s\n", fictexto);
        clearerr(pf);
    }
    else {
        printf("Escritura correcta en el fichero %s\n", fictexto);
    }

    // Cerrar el fichero
    fclose(pf);



    // Abrir el fichero
     fopen_s(&pf1, ficbinario, "wb"); // w: write, b: fichero binario

    // Escribir en el fichero
    // Esta función se utiliza igual que printf, pero tiene un parámetro más,
    // el primero, que se corresponde con el flujo que define el fichero en el que se quiere escribir
    fprintf(pf1, "¡Hola mundo!\n"); //
    fprintf(pf1, "%d * %d = %d\n", 9, 256, 9 * 256);

    // Control errores
    if (ferror(pf)) {
        printf("Error al escribir en el fichero %s\n", ficbinario);
        clearerr(pf);
    }
    else {
        printf("Escritura correcta en el fichero %s\n", ficbinario);
    }

    // Cerrar el fichero
    fclose(pf1);



    int n = 0;
    const char* s = "¡Hola mundo!\n";
  
    fopen_s(&pf2, ficbinario2, "wb"); // w: write, b: fichero binario

    // Escribir en el fichero
    fwrite(s, strlen(s), 1, pf);
    n = 9; fwrite(&n, sizeof(int), 1, pf2);
    n = 256; fwrite(&n, sizeof(int), 1, pf2);
    n = 17432583; fwrite(&n, sizeof(int), 1, pf2);

    // Control errores
    if (ferror(pf)) {
        printf("Error al escribir en el fichero %s\n", ficbinario2);
        clearerr(pf);
    }
    else {
        printf("Escritura correcta en el fichero %s\n", ficbinario2);
    }
   
    // Cerrar el fichero
    fclose(pf2);

    

    // Control errores usando perror
    if (fopen_s(&pf3, ficbinario3, "r") != 0) {
        perror("\nError al abrir el fichero");
        perror(ficbinario3);
        return 3;
    }
    else {
        printf("Lectura correcta del fichero %s\n", ficbinario3);
        fclose(pf3);

    }
 
   return 0;  
}
