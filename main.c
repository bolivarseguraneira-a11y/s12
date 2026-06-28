#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main() {
    int opcion;
    do {
        printf("\n=== CONCESIONARIA ===\n");
        printf("1. Ver inventario completo\n");
        printf("2. Buscar vehiculo por preferencias\n");
        printf("3. Registrar venta\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Error: Ingrese un numero valido.\n");
            while (getchar() != '\n');
            opcion = 0;
            continue;
        }
        
        if (opcion < 1 || opcion > 4) {
            printf("Opcion no valida. Ingrese un numero entre 1 y 4.\n");
            continue;
        }

        switch(opcion) {
            case 1: mostrarInventario(); break;
            case 2: buscarVehiculo(); break;
            case 3: registrarVenta(); break;
            case 4: printf("Saliendo del sistema...\n"); break;
        }
    } while(opcion != 4);

    return 0;
}