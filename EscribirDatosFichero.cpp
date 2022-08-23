/********************************************************************
* NOMBRE: #Jose Javier#
* PRIMER APELLIDO: #Culebras#
* SEGUNDO APELLIDO: #Perez#
* DNI: #02641584#
* EMAIL: #culex.jj@gmail.com#
*
* Programa: lectura y/o escritura de archivos
* Descripcion: Se solicita el tipo de operacion
* la lectura solo es posible en formato binario.
* la escritura puede ser en formato binario o csv
* los datos se obtienen por la entrada estandar 
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strlen - strcat


/** declaracion estructura tipo registro **/

typedef struct
{
    char nombre[40];
    char direccion[40];
    char telefono[11];
} registro;      

/** declaracion de funciones **/

void flush_input(void); // limpiar buffer stdin
int existe(char* nombreFichero); // verificar si el nombre de fichero existe
void crearFichero(char* nombreFichero); // crear un fichero nuevo
void mostrarFichero(char* nombreFichero); // leer datos del fichero


/*===================================================================
  Programa principal
  =================================================================*/

int main()
{
/** declaracion de variables **/
    char resp = 's'; // respuesta
    registro reg; // registro
    char nombreFichero[30]; // nombre del fichero


    printf("\nSeleccionar operacion:");
    printf("\n1. Escritura");
    printf("\n2. Lectura (solo archivos binarios)");
    printf("\n");

    resp = getchar();
    flush_input(); // limpiamos stdin para evitar problemas en la siguiente iteracion con \n que se registra al clicar ENTER 

    if (resp == '1') {

        /** solicitar nombre del fichero y comprobar si existe **/

        printf("Nombre del fichero: ");
        gets_s(nombreFichero);

        if (existe(nombreFichero) != 0) // 0 = existe
        {
            crearFichero(nombreFichero); // si  no existe se crea el fichero
        }
        else {
            printf("\nEl fichero existe, desea sobrescribirlo? (s/n) ");
            resp = getchar();
            flush_input(); // limpiamos stdin para evitar problemas en la siguiente iteracion con \n que se registra al clicar ENTER 

            if (resp == 's')
            {
                crearFichero(nombreFichero);
            }
            else {
                printf("\nFin de programa");
                return 0;
            }
        }
    }
    else {

        printf("Nombre del fichero: ");
        gets_s(nombreFichero);

        if (existe(nombreFichero) == 0) // 0 = existe
        {
            mostrarFichero(nombreFichero); // se muestra el fichero
        }
        else {
            printf("\nEl fichero existe");
            printf("\nFin de programa");
            system("pause");
            return 0;
        }

    }

    return 0;
}


/** definicion de funciones **/

void flush_input(void) // limpiar buffer stdin
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


int existe(char* nombreFichero) // verificar si el nombre de fichero existe
{
    FILE* pf = NULL; // buffer
    int exis = 1; // control apertura correcta flujo. Inicializamos a 1 (no existe)

    exis = fopen_s(&pf, nombreFichero, "r"); // Verificar si el fichero existe 0 = no existe

    if (exis == 0)
    {
        exis = 0; // existe
        fclose(pf);
    }

    return exis;
}



void crearFichero(char* nombreFichero) // crear un fichero nuevo
{
    FILE* pf = NULL; // buffer
    registro reg; // registro
    char linea[110] = { '\0' }; // inicializamos  vector 
    char resp;
    int check = 1; // control apertura correcta flujo. Inicializamos a 1 (error)


    printf("\nSeleccionar formato escritura");
    printf("\n1. archivo binario");
    printf("\n2. archivo csv");
    printf("\n");

    resp = getchar();
    flush_input(); // limpiamos stdin para evitar problemas en la siguiente iteracion con \n que se registra al clicar ENTER 

    switch (resp) {
        /*-- archivo binario --*/
    case '1':
        check = fopen_s(&pf, nombreFichero, "w+");  // control error apertura. check = 0 no error

        if (check != 0)
        {
            printf("El fichero no puede abrirse.");
            exit(1);
        }

        /* Leer datos de la entrada estándar y escribirlos en el fichero */

        do
        {
            printf("\nnombre:    "); 
            gets_s(reg.nombre);
            printf("direccion: ");
            gets_s(reg.direccion);
            printf("telefono:  ");
            gets_s(reg.telefono);

            /* Almacenar un registro en el fichero */
            fwrite(&reg, sizeof(reg), 1, pf);
            if (ferror(pf))
            {
                perror("Error durante la escritura");
                exit(2);
            }

            printf("\n");
            printf("desea escribir otro registro? (s/n) ");
            scanf_s(" %c", &resp, 1); // poniendo un espacio delante %c nos aseguramos la lectura correcta        

            flush_input(); // limpiamos stdin para evitar problemas en la siguiente iteracion con \n que se registra al clicar ENTER

        } while (resp == 's');
        break;
        /*-- archivo csv --*/
    case '2':
        check = fopen_s(&pf, nombreFichero, "w+");  // control error apertura. check = 0 no error

        if (check != 0)
        {
            printf("El fichero no puede abrirse.");
            exit(1);
        }

        /* Leer datos de la entrada estándar y escribirlos en el fichero */

        do
        {

            printf("\nnombre:    ");
            fgets(reg.nombre, sizeof reg.nombre, stdin); // sizeof nos devuelve el tamaño del array
            printf("direccion: ");
            fgets(reg.direccion, sizeof reg.direccion, stdin);
            printf("telefono:  ");
            fgets(reg.telefono, sizeof reg.telefono, stdin);

            // fprintf no se puede usar para este ejemplo por los saltos de linea \n de cada lectura
            // fprintf(pf,"%s , %s , %s", reg.nombre, reg.direccion, reg.telefono);
            //jose javier
            //    , calle mayor 1
            //    , 888999888
              
            /* Almacenar un registro en el fichero */

            strcat_s(linea, 110, reg.nombre); // origen + destino = nueva linea. 110 es el tamaño de la cadena
            linea[strcspn(linea, "\n")] = 0;
            strcat_s(linea, 110, ";");
            strcat_s(linea, 110, reg.direccion);
            linea[strcspn(linea, "\n")] = 0;
            strcat_s(linea, 110, ";");
            strcat_s(linea, 110, reg.telefono);

            fputs(linea, pf); //escribimos la cadena formateada en el fichero

           

            if (ferror(pf))
            {
                perror("Error durante la escritura");
                exit(2);
            }

            linea[0] = '\0'; // vaciamos el array de la cadena para dejarlo preparado para la siguiente iteracion

            printf("\n");
            printf("desea escribir otro registro? (s/n) ");
            scanf_s(" %c", &resp, 1); // poniendo un espacio delante %c nos aseguramos la lectura correcta        

            flush_input(); // limpiamos stdin para evitar problemas en la siguiente iteracion con \n que se registra al clicar ENTER

        } while (resp == 's');
        break;

    default:
        printf("\nOpcion no valida");
     }

    system("pause");
}


void mostrarFichero(char* nombreFichero)
{
    FILE* pfe = NULL; // identificador del fichero de entrada
    FILE* pfs = NULL; // identificador del dispositivo de salida
    registro reg;     // registro
    char resp = 0;
    int check = 1; // control apertura correcta flujo. Inicializamos a 1 (error)
    int contador = 0;

    // Abrir el fichero nombreFichero para leer "r"
    check = fopen_s(&pfe, nombreFichero, "rb");

    if (check != 0)
    {
        printf("El fichero no puede abrirse.");
        exit(1);
    }

    // Leer datos del fichero y mostrarlos en la salida estándar,
    // o bien por la impresora.
    /*printf("\ndesea escribir los datos por la impresora? (s/n) ");
    resp = getchar();
    flush_input(); // limpiamos stdin para evitar problemas en la siguiente iteracion con \n que se registra al clicar ENTER
    if (resp == 's')
    {
        fopen_s(&pfs, "lpt1", "w");
        if ((pfs = fopen("lpt1", "w")) == NULL)
        {
            printf("La impresora no está disponible");
            pfs = stdout; // asumimos la pantalla
        }
    }*/
        
    pfs = stdout; // pantalla

    fread(&reg, sizeof(reg), 1, pfe);
    
    while (!ferror(pfe) && !feof(pfe))
    {
        contador++;
        system("cls"); // limpiar la pantalla
        printf("\nregistro numero: %d\n", contador);
        fprintf(pfs, "Nombre:    %s\n", reg.nombre);
        fprintf(pfs, "Direccion: %s\n", reg.direccion);
        fprintf(pfs, "Telefono:  %s\n\n", reg.telefono);

        // Hacer una pausa (sólo cuando los datos se muestran
        // por pantalla)
        if (pfs == stdout)
        {
            printf("\nPulse <Entrar> para continuar ");
            getchar(); fflush(stdin);
        }

        // Leer el siguiente registro del fichero
        fread(&reg, sizeof(reg), 1, pfe);

        if (ferror(pfe))
            perror("Error durante la lectura");
    }

    /*if (pfs != stdout)
        fprintf(pfs, "\f"); // avanzar una página en la impresora
    */

    fclose(pfe);
    //fclose(pfs);

    return;
}
