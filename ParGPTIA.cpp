#include <stdio.h>

// Función para cargar los datos del cliente
void carga(int* modalidad, int* horaInicio, int* horaFin) {
    printf("Ingrese la modalidad (1: semanal, 2: fines de semana): ");
    scanf("%d", modalidad);
    
    if (*modalidad == 1 || *modalidad == 2) {
        printf("Ingrese la hora de inicio (0-23): ");
        scanf("%d", horaInicio);
        
        if (*horaInicio >= 0 && *horaInicio <= 23) {
            printf("Ingrese la hora de fin (0-23): ");
            scanf("%d", horaFin);
        }
    }
}

// Función para realizar el cálculo
void calculo(int modalidad, int horaInicio, int horaFin, int* clientes, int* horas, int* franjaClientes, int* franjaHoras, float* totalFacturado, float* importesBonificados, float* ganancia) {
    float costoPorHora = 50.0;
    float bonificacionMenos10 = 0.1;
    float bonificacionMenos15 = 0.15;
    float bonificacionFinSemana = 0.3;
    float importeBonificado = 0.0;
    
    while (horaInicio != 24) {
        int horasCliente = horaFin - horaInicio;
        float importeCliente = costoPorHora * horasCliente;
        
        *clientes += 1;
        *horas += horasCliente;
        *totalFacturado += importeCliente;
        
        if (modalidad == 2) {
            importeBonificado += importeCliente * bonificacionFinSemana;
        } else {
            if (horaInicio >= 8 && horaFin <= 12) {
                importeBonificado += importeCliente * bonificacionMenos10;
                *franjaClientes += 1;
            } else if (horaInicio >= 13 && horaFin <= 20) {
                *franjaClientes += 1;
            } else if (horaInicio >= 21 || horaFin <= 7) {
                importeBonificado += importeCliente * bonificacionMenos15;
                *franjaClientes += 1;
            }
        }
        
        carga(&modalidad, &horaInicio, &horaFin);
    }
    
    *importesBonificados = importeBonificado;
    *franjaHoras = *clientes - *franjaClientes;
    *ganancia = *totalFacturado - *importesBonificados;
}

int main() {
    int modalidad, horaInicio, horaFin;
    int clientes = 0;
    int horas = 0;
    int franjaClientes = 0;
    int franjaHoras = 0;
    float totalFacturado = 0.0;
    float importesBonificados = 0.0;
    float ganancia = 0.0;
    
    carga(&modalidad, &horaInicio, &horaFin);
    calculo(modalidad, horaInicio, horaFin, &clientes, &horas, &franjaClientes, &franjaHoras, &totalFacturado, &importesBonificados, &ganancia);
    
    printf("Cantidad total de Clientes: %d\n", clientes);
    printf("Cantidad de Horas conectados: %d\n", horas);
    printf("Franja horaria con más clientes conectados: %d\n", franjaClientes);
    printf("Franja horaria con menos horas conectadas: %d\n", franjaHoras);
    printf("Porcentaje de clientes en cada franja horaria: %.2f%%\n", (float)franjaClientes / clientes * 100.0);
    printf("Total facturado: %.2f\n", totalFacturado);
    printf("Suma de importes bonificados: %.2f\n", importesBonificados);
    printf("Ganancia: %.2f\n", ganancia);
    
    return 0;
}

