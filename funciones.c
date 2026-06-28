#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

void mostrarInventario() {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo de inventario.\n");
        return;
    }

    Vehiculo v;
    printf("\n--- INVENTARIO   ---\n");
    printf("ID\tMarca\t\tModelo\t\tTipo\t\tEstado\tPrecio\t\tDisponible\n");
    
    while (fscanf(archivo, "%d %s %s %s %s %f %d", &v.id, v.marca, v.modelo, v.tipo, v.estado, &v.precio, &v.disponible) == 7) {
        printf("%d\t%s\t\t%s\t\t%s\t\t%s\t%.2f\t%s\n", 
               v.id, v.marca, v.modelo, v.tipo, v.estado, v.precio, v.disponible ? "Si" : "No");
    }
    fclose(archivo);
}

void buscarVehiculo() {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el inventario.\n");
        return;
    }

    char tipoBuscado[30], marcaBuscada[30], estadoBuscado[20];
    float presupuesto;

    printf("\n--- BUSQUEDA DE VEHICULOS ---\n");
    
    do {
        printf("Ingrese Tipo (ej. Camioneta): ");
        if (scanf("%29s", tipoBuscado) != 1 || !validarCadena(tipoBuscado, 30)) {
            printf("Error: Tipo invalido. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
 
    do {
        printf("Ingrese Marca (ej. Chevrolet): ");
        if (scanf("%29s", marcaBuscada) != 1 || !validarCadena(marcaBuscada, 30)) {
            printf("Error: Marca invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    

    do {
        printf("Ingrese Estado (Nuevo/Usado): ");
        if (scanf("%19s", estadoBuscado) != 1 || !validarCadena(estadoBuscado, 20)) {
            printf("Error: Estado invalido. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
   
    do {
        printf("Ingrese Presupuesto Maximo: $");
        if (scanf("%f", &presupuesto) != 1 || !validarNumeroPositivoFloat(presupuesto)) {
            printf("Error: Presupuesto debe ser un numero positivo. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    Vehiculo v;
    int encontrados = 0;
    
    printf("\nResultados encontrados:\n");
    while (fscanf(archivo, "%d %s %s %s %s %f %d", &v.id, v.marca, v.modelo, v.tipo, v.estado, &v.precio, &v.disponible) == 7) {
        if (v.disponible == 1 && 
            strcasecmp(v.tipo, tipoBuscado) == 0 && 
            strcasecmp(v.marca, marcaBuscada) == 0 && 
            strcasecmp(v.estado, estadoBuscado) == 0 && 
            v.precio <= presupuesto) {
            
            printf("ID: %d | %s %s | Precio: $%.2f\n", v.id, v.marca, v.modelo, v.precio);
            encontrados++;
        }
    }
    
    if(encontrados == 0) {
        printf("No se encontraron vehiculos con esas caracteristicas.\n");
    }
    fclose(archivo);
}

void registrarVenta() {
    int idVehiculoBuscado;
    char nombreCliente[50];
    
    printf("\n--- REGISTRAR VENTA ---\n");
    
   
    do {
        printf("Nombre del cliente: ");
        if (scanf("%49s", nombreCliente) != 1 || !validarCadena(nombreCliente, 50)) {
            printf("Error: Nombre invalido. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
   
    do {
        printf("ID del vehiculo a comprar: ");
        if (scanf("%d", &idVehiculoBuscado) != 1 || !validarNumeroPositivo(idVehiculoBuscado)) {
            printf("Error: ID debe ser un numero positivo. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    FILE *archivoIn = fopen("inventario.txt", "r");
    FILE *archivoTemp = fopen("temp.txt", "w");
    FILE *archivoVentas = fopen("ventas.txt", "a");

    if (archivoIn == NULL || archivoTemp == NULL || archivoVentas == NULL) {
        printf("Error al manejar los archivos.\n");
        return;
    }

    Vehiculo v;
    int vehiculoEncontrado = 0;

    while (fscanf(archivoIn, "%d %s %s %s %s %f %d", &v.id, v.marca, v.modelo, v.tipo, v.estado, &v.precio, &v.disponible) == 7) {
        if (v.id == idVehiculoBuscado && v.disponible == 1) {
            v.disponible = 0; 
            vehiculoEncontrado = 1;
            fprintf(archivoVentas, "Cliente: %s | ID_Vehiculo: %d | Marca: %s | Modelo: %s | Precio: %.2f\n", 
                    nombreCliente, v.id, v.marca, v.modelo, v.precio);
            printf("\n¡Venta registrada con exito para %s!\n", nombreCliente);
        }
        fprintf(archivoTemp, "%d %s %s %s %s %.2f %d\n", v.id, v.marca, v.modelo, v.tipo, v.estado, v.precio, v.disponible);
    }

    if (!vehiculoEncontrado) {
        printf("Vehiculo no encontrado o ya vendido.\n");
    }

    fclose(archivoIn);
    fclose(archivoTemp);
    fclose(archivoVentas);

    remove("inventario.txt");
    rename("temp.txt", "inventario.txt");
}

int validarCadena(char *cadena, int maxLen) {
    if (cadena == NULL || strlen(cadena) == 0 || strlen(cadena) >= maxLen) {
        return 0;
    }
    return 1;
}

int validarNumeroPositivo(int num) {
    return num > 0;
}

float validarNumeroPositivoFloat(float num) {
    return num > 0;
}
