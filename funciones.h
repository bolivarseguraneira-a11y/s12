#ifndef FUNCIONES_H
#define FUNCIONES_H

typedef struct {
    int id;
    char marca[30];
    char modelo[30];
    char tipo[30]; 
    char estado[20]; 
    float precio;
    int disponible; 
} Vehiculo;

void mostrarInventario();
void buscarVehiculo();
void registrarVenta();

//validación
int validarCadena(char *cadena, int maxLen);
int validarNumeroPositivo(int num);
float validarNumeroPositivoFloat(float num);

#endif
