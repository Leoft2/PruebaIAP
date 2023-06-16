#include <stdio.h>

// Definir constantes
#define COSTO_HORA 50
#define RECARGO_FINDE 0.3
#define DESCUENTO_MANANA 0.1
#define DESCUENTO_NOCHE 0.15

// Declarar funciones
void Carga(int *modalidad, int *hora_inicio, int *hora_fin);
float Calculo(int modalidad, int hora_inicio, int hora_fin);

// Función principal
int main()
{
    // Declarar variables
    int modalidad, hora_inicio, hora_fin;
    int total_clientes = 0;
    int total_horas = 0;
    int clientes_manana = 0;
    int clientes_tarde = 0;
    int clientes_noche = 0;
    int horas_manana = 0;
    int horas_tarde = 0;
    int horas_noche = 0;
    float total_facturado = 0;
    float total_bonificado = 0;
    float ganancia = 0;

    // Iniciar bucle de carga de datos
    do
    {
        // Llamar a la función Carga
        Carga(&modalidad, &hora_inicio, &hora_fin);

        // Verificar si la carga finalizó
        if (hora_inicio == 24)
        {
            break;
        }

        // Incrementar el contador de clientes
        total_clientes++;

        // Calcular las horas conectadas
        int horas_conectadas = hora_fin - hora_inicio;

        // Incrementar el contador de horas totales
        total_horas += horas_conectadas;

        // Determinar la franja horaria del cliente
        if (hora_inicio >= 8 && hora_inicio < 13)
        {
            // Franja de la mañana
            clientes_manana++;
            horas_manana += horas_conectadas;
        }
        else if (hora_inicio >= 13 && hora_inicio < 21)
        {
            // Franja de la tarde
            clientes_tarde++;
            horas_tarde += horas_conectadas;
        }
        else
        {
            // Franja de la noche
            clientes_noche++;
            horas_noche += horas_conectadas;
        }

        // Llamar a la función Calculo y obtener el monto a pagar
        float monto = Calculo(modalidad, hora_inicio, hora_fin);

        // Incrementar el total facturado
        total_facturado += monto;

        // Calcular el importe bonificado según la franja horaria
        float bonificacion = 0;
        if (hora_inicio >= 8 && hora_inicio < 13)
        {
            // Franja de la mañana: descuento del 10%
            bonificacion = monto * DESCUENTO_MANANA;
        }
        else if (hora_inicio >= 21 || hora_inicio < 8)
        {
            // Franja de la noche: descuento del 15%
            bonificacion = monto * DESCUENTO_NOCHE;
        }

        // Incrementar el total bonificado
        total_bonificado += bonificacion;

    } while (1); // Fin del bucle

    // Calcular la ganancia como la diferencia entre el total facturado y el total bonificado
    ganancia = total_facturado - total_bonificado;

    // Mostrar los resultados por pantalla

    printf("Cantidad total de clientes: %d\n", total_clientes);
    printf("Cantidad de horas conectados: %d\n", total_horas);

    // Comparar las franjas horarias para determinar cuál tuvo más clientes conectados
    if (clientes_manana > clientes_tarde && clientes_manana > clientes_noche)
    {
        printf("La franja horaria que tuvo más clientes conectados fue la mañana.\n");
    }
    else if (clientes_tarde > clientes_manana && clientes_tarde > clientes_noche)
    {
        printf("La franja horaria que tuvo más clientes conectados fue la tarde.\n");
    }
    else if (clientes_noche > clientes_manana && clientes_noche > clientes_tarde)
    {
        printf("La franja horaria que tuvo más clientes conectados fue la noche.\n");
    }
    else
    {
        printf("Hubo un empate entre las franjas horarias con más clientes conectados.\n");
    }

    // Comparar las franjas horarias para determinar cuál tuvo menos horas conectados
    if (horas_manana < horas_tarde && horas_manana < horas_noche)
    {
        printf("La franja horaria que tuvo menos horas conectados fue la mañana.\n");
    }
    else if (horas_tarde < horas_manana && horas_tarde < horas_noche)
    {
        printf("La franja horaria que tuvo menos horas conectados fue la tarde.\n");
    }
    else if (horas_noche < horas_manana && horas_noche < horas_tarde)
    {
        printf("La franja horaria que tuvo menos horas conectados fue la noche.\n");
    }
    else
    {
        printf("Hubo un empate entre las franjas horarias con menos horas conectados.\n");
    }

    // Calcular el porcentaje que representa la cantidad de clientes de cada franja horaria
    float porcentaje_manana = (float)clientes_manana / total_clientes * 100;
    float porcentaje_tarde = (float)clientes_tarde / total_clientes * 100;
    float porcentaje_noche = (float)clientes_noche / total_clientes * 100;

    printf("El porcentaje que representa la cantidad de clientes de la mañana es: %.2f%%\n", porcentaje_manana);
    printf("El porcentaje que representa la cantidad de clientes de la tarde es: %.2f%%\n", porcentaje_tarde);
    printf("El porcentaje que representa la cantidad de clientes de la noche es: %.2f%%\n", porcentaje_noche);

    printf("Total facturado: $%.2f\n", total_facturado);
    printf("Suma de importes bonificados: $%.2f\n", total_bonificado);
    printf("Ganancia: $%.2f\n", ganancia);

    return 0;
}

// Función para cargar los datos del cliente
void Carga(int *modalidad, int *hora_inicio, int *hora_fin)
{
    // Pedir al usuario que ingrese la modalidad
    printf("Ingrese la modalidad: 1 para semanal, 2 para fines de semana.\n");
    scanf("%d", modalidad);

    // Validar que la modalidad sea correcta
    while (*modalidad != 1 && *modalidad != 2)
    {
        printf("Modalidad inválida. Ingrese 1 o 2.\n");
        scanf("%d", modalidad);
    }

    // Pedir al usuario que ingrese la hora de inicio
    printf("Ingrese la hora de inicio (0 a 23). Ingrese 24 para finalizar.\n");
    scanf("%d", hora_inicio);

    // Validar que la hora de inicio sea correcta
    while (*hora_inicio < 0 || *hora_inicio > 24)
    {
        printf("Hora de inicio inválida. Ingrese un número entre 0 y 24.\n");
        scanf("%d", hora_inicio);
    }

    // Verificar si se ingresó 24 para finalizar
    if (*hora_inicio == 24)
    {
        return;
    }

    // Pedir al usuario que ingrese la hora de fin
    printf("Ingrese la hora de fin (0 a 23).\n");
    scanf("%d", hora_fin);

    // Validar que la hora de fin sea correcta y mayor que la hora de inicio
    while (*hora_fin < 0 || *hora_fin > 23 || *hora_fin <= *hora_inicio)
    {
        printf("Hora de fin inválida. Ingrese un número entre 0 y 23 mayor que la hora de inicio.\n");
        scanf("%d", hora_fin);
    }
}

// Función para calcular el monto a pagar según la modalidad y las horas
float Calculo(int modalidad, int hora_inicio, int hora_fin) {
	
}


    

