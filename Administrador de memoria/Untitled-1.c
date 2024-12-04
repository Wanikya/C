#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar una partición de memoria
typedef struct {
    int id;            // Identificador de la partición
    int size;          // Tamaño de la partición
    int is_free;       // Indicador de si está libre (1) o ocupada (0)
    int process_id;    // ID del proceso asignado (-1 si está libre)
} Partition;

#define MAX_PARTICIONES 100  // Número máximo permitido de particiones

void mostrarMemoria(Partition *particiones, int num_particiones) {
    printf("\nEstado de la memoria:\n");
    printf("=======================================\n");
    for (int i = 0; i < num_particiones; i++) {
        printf("Partición %d: Tamaño %d - %s (Proceso %d)\n",
               particiones[i].id,
               particiones[i].size,
               particiones[i].is_free ? "Libre" : "Ocupada",
               particiones[i].process_id);
    }
    printf("=======================================\n\n");
}

void asignarProceso(Partition *particiones, int num_particiones, int process_id, int process_size) {
    for (int i = 0; i < num_particiones; i++) {
        if (particiones[i].is_free && particiones[i].size >= process_size) {
            particiones[i].is_free = 0;
            particiones[i].process_id = process_id;
            printf("Proceso %d asignado a la partición %d.\n", process_id, particiones[i].id);
            return;
        }
    }
    printf("No se pudo asignar el proceso %d. No hay suficiente espacio disponible.\n", process_id);
}

void liberarProceso(Partition *particiones, int num_particiones, int process_id) {
    for (int i = 0; i < num_particiones; i++) {
        if (!particiones[i].is_free && particiones[i].process_id == process_id) {
            particiones[i].is_free = 1;
            particiones[i].process_id = -1;
            printf("Proceso %d liberado de la partición %d.\n", process_id, particiones[i].id);
            return;
        }
    }
    printf("No se encontró el proceso %d en la memoria.\n", process_id);
}

int main() {
    int total_memoria, num_particiones;

    // Solicitar tamaño total de memoria y número de particiones
    printf("Ingrese el tamaño total de la memoria: ");
    scanf("%d", &total_memoria);
    printf("Ingrese el número de particiones (máximo %d): ", MAX_PARTICIONES);
    scanf("%d", &num_particiones);
    
    // Validar el número de particiones
    if (num_particiones > MAX_PARTICIONES) {
        printf("El número de particiones no puede exceder %d.\n", MAX_PARTICIONES);
        return 1;
    }

    // Calcular tamaño de cada partición y configurar particiones
    Partition particiones[MAX_PARTICIONES];
    int partition_size = total_memoria / num_particiones;
    for (int i = 0; i < num_particiones; i++) {
        particiones[i].id = i + 1;
        particiones[i].size = partition_size;
        particiones[i].is_free = 1;
        particiones[i].process_id = -1;
    }

    int opcion;
    do {
        printf("\nSeleccione una opción:\n");
        printf("1. Mostrar estado de la memoria\n");
        printf("2. Asignar proceso a una partición\n");
        printf("3. Liberar proceso de una partición\n");
        printf("4. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarMemoria(particiones, num_particiones);
                break;
            case 2: {
                int process_id, process_size;
                printf("Ingrese el ID del proceso: ");
                scanf("%d", &process_id);
                printf("Ingrese el tamaño del proceso: ");
                scanf("%d", &process_size);
                asignarProceso(particiones, num_particiones, process_id, process_size);
                break;
            }
            case 3: {
                int process_id;
                printf("Ingrese el ID del proceso a liberar: ");
                scanf("%d", &process_id);
                liberarProceso(particiones, num_particiones, process_id);
                break;
            }
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } while (opcion != 4);

    return 0;
}
