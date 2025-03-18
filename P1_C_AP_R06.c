#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// Mostar menu y elegir la opcion.
int mostrarMenu()
{
    int opc;
    printf("1. Mostrar lista de choferes ordenada por Apellido y Nombre\n");
    printf("2. Mostrar lista de choferes ordenada por cantidad de kilometros conducidos en la semana\n");
    printf("3. Mostrar lista de choferes con su salario semanal\n");
    printf("4. Buscar por Chofer\n");
    printf("5. Mostrar lista de choferes con promedio de kilometros conducidos en la semana\n");
    printf("6. Mostrar estadistica de choferes\n");
    printf("7. Salir\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opc);
    return opc;
}
// Esperar una tecla. (Para visualizar el resultado)
void esperarUnaTecla()
{
    printf("Ingrese una TECLA para continuar.");
    while (getchar() != '\n')
        ;
    getchar();
}
// Función para convertir una cadena a minúsculas
void toLowerCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Para mostrar que debe ingresar en una iteracion.
void tiposDeDatos(char datos[8][50])
{
    strcpy(datos[0], "CUIL");
    strcpy(datos[1], "Apellido");
    strcpy(datos[2], "Nombre");
    strcpy(datos[3], "km conducidos dia Lunes");
    strcpy(datos[4], "km conducidos dia Martes");
    strcpy(datos[5], "km conducidos dia Miercoles");
    strcpy(datos[6], "km conducidos dia Jueves");
    strcpy(datos[7], "km conducidos dia Viernes");
}
// Ingreso de cantidad de camioneros
int cantidadCamioneros()
{
    int n;
    do
    {
        printf("Ingrese la cantidad total de camioneros: ");
        scanf("%d", &n);
        if (n < 1)
        {
            printf("Ingrese un numero positivo.");
            sleep(1);
        }
    } while (n < 1);
    return n;
}
// Validar CUIL
void validarCuil(char dato[20])
{
    int error[3];
    char infoError[3][100];
    strcpy(infoError[0], "Sus primeros dos numeros no son validos");
    strcpy(infoError[1], "El tamano debe ser de entre 10 y 11 numeros.(incluyendolos)");
    strcpy(infoError[2], "No debe tener puntos, comas o guiones.");
    char subCadena[20];
    int tamano, contador, bandera;
    char validarPrimeraParte[6][3] = {"20", "23", "24", "25", "26", "27"};
    error[0] = error[1] = error[2] = 0;
    do
    {
        if (error[0] == 1 || error[1] == 1 || error[2] == 1)
        {
            printf("Ingrese nuevamente el CUIL: ");
            scanf("%s", dato);
        }
        tamano = strlen(dato);
        strncpy(subCadena, dato, 2);
        subCadena[2] = '\0';
        error[0] = error[1] = error[2] = 0;
        bandera = 0;
        contador = 0;
        do
        {
            if (strcmp(subCadena, validarPrimeraParte[contador]) == 0)
            {
                bandera = 1;
            }
            contador++;
        } while (bandera == 0 && contador < 6);
        if (bandera == 0)
        {
            error[0] = 1;
        }
        if (tamano < 10 || tamano > 11)
        {
            error[1] = 1;
        }
        char subCadenaParaComparar;
        for (int i = 0; i < tamano; i++)
        {
            if (dato[i] == '.' || dato[i] == ',' || dato[i] == '-')
            {
                error[2] = 1;
            }
        }
        if (error[0] == 1)
        {
            printf("%s\n", infoError[0]);
        }
        if (error[1] == 1)
        {
            printf("%s\n", infoError[1]);
        }
        if (error[2] == 1)
        {
            printf("%s\n", infoError[2]);
        }
        if (error[0] == 1 || error[1] == 1 || error[2] == 1)
        {
            sleep(2);
        }
    } while (error[0] == 1 || error[1] == 1 || error[2] == 1);
}
// Ingreso de camioneros
void ingresarCamioneros(int n, char arr[n][8][50])
{
    char datos[8][50];
    char dato[20];
    tiposDeDatos(datos);
    for (int i = 0; i < n; i++)
    {
        system("cls");
        printf("Camionero %d.\n", i + 1);
        for (int e = 0; e < 8; e++)
        {
            printf("Ingrese %s del camionero: ", datos[e]);
            scanf("%s", dato);
            toLowerCase(dato);
            if (e == 0)
            {
                validarCuil(dato);
            }
            if (e >= 3)
            {
                while (atoi(dato) > 1000)
                {
                    printf("La capacidad maxima diaria es de 1000km.");
                    printf("Ingrese %s del camionero: ", datos[e]);
                    scanf("%s", dato);
                }
            }
            strcpy(arr[i][e], dato);
        }
    }
}
// Ordenar por KM
void ordenarPorKM(int n, char arr[n][8][50])
{
    int acumulador = 0, dato;
    char nombreApellido[50];
    char newArr[n][2][50];
    for (int i = 0; i < n; i++)
    {
        strcpy(newArr[i][0], arr[i][2]);
        strcat(newArr[i][0], " ");
        strcat(newArr[i][0], arr[i][1]);
        acumulador = 0;
        for (int e = 3; e < 8; e++)
        {
            dato = atoi(arr[i][e]);
            acumulador = acumulador + dato;
        }
        sprintf(newArr[i][1], "%d", acumulador);
    }
    char auxKm[20];
    char auxNombre[20];
    int lugar;
    for (int i = 0; i < n; i++)
    {
        lugar = i;
        for (int e = i + 1; e < n; e++)
        {
            if (atoi(newArr[lugar][1]) > atoi(newArr[e][1]))
            {
                lugar = e;
            }
        }
        if (lugar != i)
        {
            // Ordenamos en base a los KM recorridos
            strcpy(auxKm, newArr[i][1]);
            strcpy(newArr[i][1], newArr[lugar][1]);
            strcpy(newArr[lugar][1], auxKm);
            // Modificamos los nombres y apellidos
            strcpy(auxNombre, newArr[i][0]);
            strcpy(newArr[i][0], newArr[lugar][0]);
            strcpy(newArr[lugar][0], auxNombre);
        }
    }
    system("cls");
    printf("-------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("Nombre y apellido: %s.\n", newArr[i][0]);
        printf("Km recorridos en la semana: %s.\n", newArr[i][1]);
        printf("-------------------------------------\n");
    }
}
// Buscar por chofer
void buscarPorChofer(int n, char arr[n][8][50])
{
    char cuil[30];
    int bandera = 0, contador = 0;
    int posicion;
    system("cls");
    printf("Ingrese CUIL a buscar: ");
    scanf("%s", cuil);
    validarCuil(cuil);
    do
    {
        if (strcmp(cuil, arr[contador][0]) == 0)
        {
            bandera = 1;
            posicion = contador;
        }
        contador++;
    } while (bandera != 1 && contador < n);
    system("cls");
    if (bandera == 1)
    {
        char datos[8][50];
        int acumulador = 0;
        tiposDeDatos(datos);
        for (int i = 0; i < 8; i++)
        {
            printf("%s : %s.\n", datos[i], arr[posicion][i]);
            if (i >= 3)
            {
                acumulador = acumulador + atoi(arr[posicion][i]);
            }
        }
        printf("Total de Km recorridos: %d.\n", acumulador);
    }
    else
    {
        printf("No existe chofer con ese CUIL.\n");
    }
}

// ----------------------------------------------------- Alvaro

// el usuario elegio la opcion 1 del MENU
void MuestraListaApellidoNombre(int n, char arr[n][8][50])
{
    char arrCarApellido[n][2][50]; // nuevo array para reordenarlo y no tocar el original
                                   // char resultado1[1][50];
    // char resultado2[1][50];
    char aux[50];
    int posMenor;
    char nombreApellido[50];

    for (int i = 0; i < n; i++)
    {
        strcpy(nombreApellido, arr[i][1]);
        strcat(nombreApellido, " ");
        strcat(nombreApellido, arr[i][2]);
        strcpy(arrCarApellido[i][0], arr[i][0]);      // Cuil
        strcpy(arrCarApellido[i][1], nombreApellido); // Apellid                                           
    }

    // Rutina de ordenamiento por pivoteo
    for (int i = 0; i < n - 1; i++)
    {
        posMenor = i;

        for (int j = i + 1; j < n; j++)
        {

            if (strcmp(arrCarApellido[posMenor][1], arrCarApellido[j][1]) > 0)

            {
                posMenor = j;
            }
        }

        for (int k = 0; k < 2; k++)
        {
            strcpy(aux, arrCarApellido[i][k]);
            strcpy(arrCarApellido[i][k], arrCarApellido[posMenor][k]);
            strcpy(arrCarApellido[posMenor][k], aux);
        }
    }

    // Una vez ordenado el array nuevo, se muestra por pantalla
    printf("*************************************\n");
    printf("  CUIL   -  Apellido   -   Nombre    \n");
    for (int i = 0; i < n; i++)
    {
        printf("%s ---- %s\n", arrCarApellido[i][0], arrCarApellido[i][1]);
    }
}

void MostrarListaSalarios(int n, char arr[n][8][50])
{
    int precioKm, kmSemanales, importeSemanal, importeTotal, KmTotales;
    int a = 0;
    printf("Ingrese el precio/Km\n");
    scanf("%d", &precioKm);
    printf("Apellido -- Nombre --  Total Km/semana --  Salario Semanal \n");
    for (int i = 0; i < n; i++)
    {
        kmSemanales = 0;
        for (int j = 3; j < 8; j++)
        {
            kmSemanales = kmSemanales + atoi(arr[i][j]);
        }
        KmTotales = KmTotales + kmSemanales;

        printf("%s  --  %s  --  %d  --  %d\n", arr[i][1], arr[i][2], kmSemanales, kmSemanales * precioKm);

        a = a + kmSemanales * precioKm;
    }

    printf("El importe total es %d\n", a);
}

// ----------------------------------------------------- Andres
void listaprom(int n, char arr[n][8][50]){
    int i, j, l;
    float promedio, acum;
    char prom[n][4][50];
    for(i=0;i<n;i++){
        acum=0;
        strcpy(prom[i][0], arr[i][0]);
        strcpy(prom[i][1], arr[i][1]);
        strcpy(prom[i][2], arr[i][2]);
        for(j=3;j<8;j++){
            acum=acum+atoi(arr[i][j]);
        }
        promedio=acum/5;
        snprintf(prom[i][3], sizeof(prom[i][3]), "%.2f", promedio);
    }
    printf("------------------------------------------------\n");
    printf("CUIL    -    APELLIDO Y NOMBRE    -     PROMEDIO\n");
    for(l=0;l<n;l++){
        printf("%s   -   %s %s   -    %s\n",prom[l][0], prom[l][1], prom[l][2], prom[l][3]);
    }
}

void compramax(int n, char arr[n][8][50]){
    int i, j, k, max;
    float acum;
    float acumulador[n];
    max=0;
    for(i=0;i<n;i++){
        acum=0;
        for(j=3;j<8;j++){
            acum=acum+atoi(arr[i][j]);
        }
        acumulador[i]=acum;
    }
    for(k=1;k<n;k++){
        if(acumulador[max]<acumulador[k]){
            max=k;
        }
    }
    printf("el chofer que recorrio mas Km es: %s %s y recorrio %.2f km\n", arr[max][2], arr[max][1], acumulador[max]);
}

void compramin(int n, char arr[n][8][50]){
    int i, j, k, min;
    float acum;
    float acumulador[n];
    min=0;
    for(i=0;i<n;i++){
        acum=0;
        for(j=3;j<8;j++){
            acum=acum+atoi(arr[i][j]);
        }
        acumulador[i]=acum;
    }
    for(k=1;k<n;k++){
        if(acumulador[min]>acumulador[k]){
            min=k;
        }
    }
    printf("el chofer que recorrio menos Km es: %s %s y recorrio %.2f km\n", arr[min][2], arr[min][1], acumulador[min]);
}

void compararprommax(int n, char arr[n][8][50]){
    int i, j, l, max;
    float promedio, acum;
    char prom[n][4][50];
    for(i=0;i<n;i++){
        acum=0;
        strcpy(prom[i][0], arr[i][0]);
        strcpy(prom[i][1], arr[i][1]);
        strcpy(prom[i][2], arr[i][2]);
        for(j=3;j<8;j++){
            acum=acum+atoi(arr[i][j]);
        }
        promedio=acum/5;
        snprintf(prom[i][3], sizeof(prom[i][3]), "%.2f", promedio);
    }
    max=0;
    for(l=1;l<n;l++){
        if(atoi(prom[max][3])<atoi(prom[l][3])){
            max=l;
        }
    }
    printf("el chofer de mayor promedio es: %s %s y el promedio es %s km\n", arr[max][2], arr[max][1], prom[max][3]);
}


void compararprommin(int n, char arr[n][8][50]){
    int i, j, l, min;
    float promedio, acum;
    char prom[n][4][50];
    for(i=0;i<n;i++){
        acum=0;
        prom[i][0][50]=arr[i][0][50];
        prom[i][1][50]=arr[i][1][50];
        prom[i][2][50]=arr[i][2][50];
        for(j=3;j<8;j++){
            acum=acum+atoi(arr[i][j]);
        }
        promedio=acum/5;
        snprintf(prom[i][3], sizeof(prom[i][3]), "%.2f", promedio);
    }
    min=0;
    for(l=1;l<n;l++){
        if(atoi(prom[min][3])>atoi(prom[l][3])){
            min=l;
        }
    }
    printf("el chofer de menor promedio es: %s %s y el promedio es %s km\n", arr[min][2], arr[min][1], prom[min][3]);
}


void promkmtotal(int n, char arr[n][8][50]){
    int i, j;
    float acum, promediofinal;
    acum=0;
    for(i=0;i<n;i++){
        for(j=3;j<8;j++){
        acum=acum+atoi(arr[i][j]);
        }
    }
    promediofinal=acum/n;
    printf("el promedio de todos los kilometros realizados por chofer es: %.2f Km\n", promediofinal);
}


int main()
{
    int opc, n;
    n = cantidadCamioneros();
    char arr[n][8][50];
    ingresarCamioneros(n, arr);
    do
    {
        system("cls");
        opc = mostrarMenu();
        switch (opc)
        {
        case 1:
            MuestraListaApellidoNombre(n, arr);
            esperarUnaTecla();
            break;
        case 2:
            ordenarPorKM(n, arr);
            esperarUnaTecla();
            break;
        case 3:
            MostrarListaSalarios(n, arr);
            esperarUnaTecla();
            break;
        case 4:
            buscarPorChofer(n, arr);
            esperarUnaTecla();
            break;
        case 5:
            listaprom(n, arr);
            esperarUnaTecla();
            break;
        case 6:
            compramax(n, arr);
            compramin(n, arr);
            compararprommax(n, arr);
            compararprommin(n, arr);
            promkmtotal(n, arr);
            esperarUnaTecla();
            break;
        case 7:
            printf("Saliendo...");
            break;
        default:
            printf("Ingrese una opcion valida.");
            sleep(1);
            break;
        }
    } while (opc != 7);
}