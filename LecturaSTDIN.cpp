/*** Escribir datos en un fichero registro a registro ***/
/* fwrite.c
 */
#include <stdio.h>
#include <stdlib.h>
//#include <string.h> // Para strlen

typedef struct
{
    char nombre[40];
    char direccion[40];
    long telefono;
} registro;      // tipo registro


/*    This function flushes the stdio input buffer */
void flush_input(void)
{
    /* getchar returns an int */
    int ch;
    /* Read characters until there are none left */
      
    do
        ch = getchar();
    while (ch != EOF && ch != '\n');
    /* Clear EOF state */
    clearerr(stdin);
}

/*    This function flushes the stdio input buffer (peor solucion) */
void clear_stdin()
{
    char read_rem[200];
    gets_s(read_rem);
}


int main()
{
    char resp = 's';
    registro reg;      // definir un registro
 
    //lemos los datos y los imprimimos hasta salir del bucle
    do {
        
        printf("\nnombre:    ");
        fgets(reg.nombre, sizeof reg.nombre, stdin); //sizeof nos devuelve el tamaño del array
        printf("direccion: ");
        fgets(reg.direccion, sizeof reg.direccion, stdin);
        printf("telefono:  ");
        scanf_s("%ld", &reg.telefono);

        printf("\nNOMBRE: %s", reg.nombre);
        printf("\nDIRECCION: %s", reg.direccion);
        printf("\nTELEFONO: %ld", reg.telefono);

        // Remover salto de línea
       /*if ((strlen(reg.telefono) > 0) && (reg.telefono[strlen(reg.nombre) - 1] == '\n'))
        {
            reg.telefono[strlen(reg.telefono) - 1] = '\0';
        }*/ 

        printf("\n");
        printf("\nDesea salir del programa (s/n)?:");
        scanf_s(" %c", &resp, 1); // poniendo un espacio delante %c nos aseguramos la lectura correcta        

        flush_input(); // limpiamos stdin para evitar problemas en la siguiente iteracion con \n que se registra al clicar ENTER

    } while (resp == 'n'); 
    
    return 0;   
}


