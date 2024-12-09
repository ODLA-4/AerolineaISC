#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAXASIENTOS 14
#define PRECIO1 2000
#define PRECIO2 2500
#define PRECIO3 3000

//Prototipos de funciones
void InicioAsientos(bool asientos[], char nombres[][20]);
int contarAsientosDisponibles(bool asientos[], int inicio, int fin);
void mostrarAsientosDisponibles(bool asientos[], int inicio, int fin);
int seleccionarAsiento(bool asientos[], int inicio, int fin);
void imprimirReporte(bool asientos[], char nombre[][20], int ingresos1, int ingresos2, int ingresos3);

int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int seccion, asientosdispototal, disponibles_primera, disponibles_segunda, disponibles_fumadores;
    int asientoselec=0, asientosnofumadores, asientosfumadores, opc;
    int ingresos1=0, ingresos2=0, ingresos3=0, costo;
    bool asientos[MAXASIENTOS];
    char nombre[20];
    char nombres[MAXASIENTOS][20];
    InicioAsientos(asientos, nombres); //Se inicializan los asientos y nombres
    printf("Bienvenido a aerolinea - AEROISC");
    while(1){ //El programa corre hasta que sea interrumpido
        printf("\nDesea comprar un boleto? Si(1) / No(2): ");
        scanf("%d", &opc);
        if (opc != 1){ //Numero diferente a 1 va a terminar el programa. Si se escribe letra el programa sigue
            break;
        }
        asientosnofumadores = contarAsientosDisponibles(asientos,0,11);
        if(asientosnofumadores==0){
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("Lugares	de la seccion de No fumadores agotados\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        asientosfumadores = contarAsientosDisponibles(asientos,12,13);
        if(asientosfumadores==0){
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("Lugares	de la seccion de fumadores agotados\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        asientosdispototal = contarAsientosDisponibles(asientos,0,13);
        if(asientosdispototal==0){
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("El avion esta lleno. El proximo vuelo sale mañana\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        }
        printf("Cual es su nombre?: ");
        scanf("%s", nombre); //Solo toma un nombre, si se ponen mas de uno, solo detecta el primero
        printf("En que seccion desea estar? Seccion 1, Seccion 2, o Fumadores (3): ");
        scanf("%d", &seccion);
        switch (seccion){
            case 1:
                disponibles_primera = contarAsientosDisponibles(asientos,0,5);
                if (disponibles_primera>0){
                    mostrarAsientosDisponibles(asientos, 0, 5);
                    asientoselec = seleccionarAsiento(asientos,0,5);
                    costo = PRECIO1;
                    ingresos1 += costo;
                    printf("Reservacion exitosa\nPase de abordaje:\n");
                    printf("Nombre: %s\nSeccion: %d\nAsiento: %d\nCosto: $%d\n", nombre, seccion, asientoselec, costo);
                    strcpy(nombres[asientoselec - 1], nombre); //Copia el nombre en la matriz de nombres
                }else{
                    printf("Lugares agotados, desea comprar en la seccion 2 o 3? Si(1) / No(2): ");
                    scanf("%d",&opc);
                    if(opc==1){
                        continue;//Esto manda al menu y ya ahi pones si quieres otro boleto o no
                    }
                }
                break;
            case 2:
                disponibles_segunda = contarAsientosDisponibles(asientos,6,11);
                if(disponibles_segunda>0){
                    mostrarAsientosDisponibles(asientos, 6, 11);
                    asientoselec = seleccionarAsiento(asientos,6,11);
                    costo = PRECIO2;
                    ingresos2 += costo; //Suma los ingresos
                    printf("Reservacion exitosa\nPase de abordaje:\n");
                    printf("Nombre: %s\nSeccion: %d\nAsiento: %d\nCosto: $%d\n", nombre, seccion, asientoselec, costo);
                    strcpy(nombres[asientoselec - 1], nombre);
                }else{
                    printf("Lugares agotados, desea comprar en la seccion 1 o 3? Si(1) / No(2): ");
                    scanf("%d",&opc);
                    if(opc==1){
                        continue;//Esto manda al menu y ya ahi pones si quieres otro boleto o no
                    }
                }
                break;
            case 3:
                disponibles_fumadores = contarAsientosDisponibles(asientos,12,13);
                if(disponibles_fumadores>0){
                    mostrarAsientosDisponibles(asientos, 12, 13);
                    asientoselec = seleccionarAsiento(asientos,12,13);
                    costo = PRECIO3;
                    ingresos3 += costo;
                    printf("Reservacion exitosa\nPase de abordaje:\n");
                    printf("Nombre: %s\nSeccion: %d\nAsiento: %d\nCosto: $%d\n", nombre, seccion, asientoselec, costo);
                    strcpy(nombres[asientoselec - 1], nombre);
                }else{
                    printf("Lugares agotados, desea comprar en la seccion 1 o 2? Si(1) / No(2): ");
                    scanf("%d",&opc);
                    if(opc==1){
                        continue;//Esto manda al menu y ya ahi pones si quieres otro boleto o no
                    }
                }
                break;
            default:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("Seccion no valida");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
        }
    }
    imprimirReporte(asientos, nombres, ingresos1, ingresos2, ingresos3);
    return 0;
}

//Inicializa los asientos para que no tengan basura y funcione correctamente el programa
void InicioAsientos(bool asientos[], char nombres[][20]){
    for (int i=0; i<MAXASIENTOS; i++){
        asientos[i] = false;
        strcpy (nombres[i], "");
    }
}

//Cuenta los asientos disponibles
int contarAsientosDisponibles(bool asientos[], int inicio, int fin){
    int disponibles = 0;
    for (int i=inicio; i<=fin; i++){
        if(!asientos[i]) disponibles++;
    }
    return disponibles;
}

// Muestra los asientos disponibles en un rango específico
void mostrarAsientosDisponibles(bool asientos[], int inicio, int fin){
    for (int i=inicio; i <= fin; i++) {
        if (!asientos[i]) printf("%d ", i + 1);
    }
    printf("\n");
}

//Permite seleccionar el asiento deseado
int seleccionarAsiento(bool asientos[], int inicio, int fin){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int asiento;
    while(1){
        printf("Seleccione el asiento: ");
        scanf("%d", &asiento);
        if(asiento>=inicio+1 && asiento<=fin+1 && !asientos[asiento-1]){ //Se le resta 1 porque la metriz empieza en 0
            asientos[asiento - 1] = true; //Ocupa el asiento
            return asiento;//Retorna el asiento ocupado
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("Asiento ocupado o no valido\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    }
}

//Imprime el reporte final
void imprimirReporte(bool asientos[], char nombres[][20], int ingresos1, int ingresos2, int ingresos3){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);//Cambia el color del texto del reporte
    printf("\nAereolinea ISC");
    printf("\nAguascalientes-Mexico\n");
    printf("\nPrimera seccion\n");
    for(int i=0; i<6; i++){
        if(asientos[i]){
        printf("%s - Asiento %d\n", nombres[i], i+1);
        }
    }
    printf("Total ingresos Primera Seccion: $%d\n", ingresos1);
    printf("\nSegunda seccion\n");
    for(int i=6; i<12; i++){
        if(asientos[i]){
        printf("%s - Asiento %d\n", nombres[i], i+1);
        }
    }
    printf("Total ingresos segunda Seccion: $%d\n", ingresos2);
    printf("\nSeccion fumadores\n");
    for(int i=12; i<14; i++){
        if(asientos[i]){
        printf("%s - Asiento %d\n", nombres[i], i+1);
        }
    }
    printf("Total ingresos Seccion fumadores: $%d\n", ingresos3);
    //Regresa el color al original luego de dar el reporte
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
}