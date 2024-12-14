# Actividades
## Administración de memoria
### Política y filosofía
1. La fragmentación externa es el conjunto de memoria no usada en forma de huecos entre procesos y que a su ves no son capaz de soportar otro proceso, solo puede ser recuperada con la desfragmentación o compactación de la memoria.
   
    La fragmentación interna es la memoria no usada generada por una reserva de memoria mayor a la que requiere y la única forma de recuperarla es esperar a que el proceso acabe.
2. Políticas de reemplazo de páginas en sistemas operativos:
   * Óptimo: Es un algoritmo teórico que retira la página que no será referenciada en la mayor cantidad de tiempo en el futuro.
   * Primero en entrar, primero en salir (FIFO): Es un algoritmo que guarda en una cola el orden de cargado de las páginas que el sistema operativo genera, para así en cuanto se requiera liberar espacio para nuevas páginas, eliminar aquella que sea la más antigua, aunque sea la más usada.
   * Segunda oportunidad (reloj): Es una modificación del algoritmo FIFO, en donde al momento de ser necesario sacar una página, se lee el valor de referencia de la página, si es "1" se cambia a "0" y se lleva al final de la cola, si es "0" se eliminar, este valor está dado por la unidad de gestión de memoria (MMU) al acceder a una página.
   * De páginas de reloj (CLOCK) (Reloj Mejorado): Es una mejora al algoritmo de reloj al tener una cola circular y al solo modificar el valor de referencia en caso de ser necesario, ahorrando memoria y evitando el cambio de puntero en cada de requerir espacio.
   * Más usada frecuentemente (MFU): Remplaza las páginas que hayan sido referenciadas de manera frecuente, bajo la suposición de que al ser usadas mucho recientemente serán menos necesarias en un futuro.
   * Menos usada frecuentemente (LFU): Reemplaza la página que ha sido referenciada menos veces, asumiendo que las páginas menos usadas en el pasado serán menos necesarias en el futuro.
   * No usada recientemente (NRU): Es un algoritmo que lee las páginas, sus valores de referencia y su tiempo de modificación y los agrupa en 4 categorias:
      * Categoría 0: No referenciada, No modificada
      * Categoría 1: No referenciada, modificada
      * Categoría 2: referenciada, No modificada
      * Categoría 3: referenciada, modificada
    
        Y posteriormente eliminar de manera aleatoria las páginas de menoe categoría.
    * Menos usada recientemente (LRU): Este algoritmo, a diferencia del NRU, genera una lista donde ordena a la página más usada en primer puesto y a la menos usada en último, eliminando está última como priorodad. Para mantener esto actualiza la lista conforme se haga referencia a cada página.
    * Envejecimiento (Aging):  Similar a LRU, pero utiliza contadores para aproximar el tiempo de uso reciente de cada página. Los contadores se actualizan periódicamente para reflejar la antigüedad relativa de las páginas.
    * Aleatorio (Random): Elije una página aleatoria para reemplazar.

    El método más eficiente es el óptimo, puesto que al poder analizar el tiempo de uso de cada página puede permitir el mantener una lista actualizada con las páginas que serán usadas de manera más reciente.

### Memoria real
1. 
~~~ C
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tamano;           // Tamaño de la partición
    int id_de_proceso;    // ID del proceso asignado (-1 si está libre)
} Particion;

// Función para imprimir el estado de la memoria
void imprime_memoria(Particion *particiones, int num_particiones) {
    printf("\nEstado de la memoria:\n");
    for (int i = 0; i < num_particiones; i++) {
        if (particiones[i].id_de_proceso == -1) {
            printf("Partición %d: %d KB (Libre)\n", i + 1, particiones[i].tamano);
        } else {
            printf("Partición %d: %d KB (Proceso %d)\n", i + 1, particiones[i].tamano, particiones[i].id_de_proceso);
        }
    }
    printf("\n");
}

int main() {
    int memoria_total, num_particiones;
    printf("Ingrese el tamaño total de la memoria (KB): ");
    scanf("%d", &memoria_total);

    printf("Ingrese el número de particiones: ");
    scanf("%d", &num_particiones);

    if (num_particiones <= 0) {
        printf("El número de particiones debe ser mayor a 0.\n");
        return 1;
    }

    // Crear dinámicamente el arreglo de particiones
    Particion *particiones = (Particion *)malloc(num_particiones * sizeof(Particion));
    if (particiones == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Inicializar particiones
    int tamano_total_particion = 0;
    for (int i = 0; i < num_particiones; i++) {
        printf("Ingrese el tamaño de la partición %d (KB): ", i + 1);
        scanf("%d", &particiones[i].tamano);
        particiones[i].id_de_proceso = -1; // Todas las particiones están libres al inicio
        tamano_total_particion += particiones[i].tamano;
    }

    if (tamano_total_particion > memoria_total) {
        printf("Error: El tamaño total de las particiones excede el tamaño de la memoria.\n");
        free(particiones);
        return 1;
    }

    int opcion;
    do {
        printf("\n--- Menú ---\n");
        printf("1. Asignar proceso\n");
        printf("2. Liberar proceso\n");
        printf("3. Mostrar estado de la memoria\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                int id_proceso, tamano_proceso;
                printf("Ingrese el ID del proceso: ");
                scanf("%d", &id_proceso);
                printf("Ingrese el tamaño del proceso (KB): ");
                scanf("%d", &tamano_proceso);

                int asignado = 0;
                for (int i = 0; i < num_particiones; i++) {
                    if (particiones[i].id_de_proceso == -1 && particiones[i].tamano >= tamano_proceso) {
                        particiones[i].id_de_proceso = id_proceso;
                        asignado = 1;
                        printf("Proceso %d asignado a la partición %d.\n", id_proceso, i + 1);
                        break;
                    }
                }
                if (!asignado) {
                    printf("No se encontró una partición disponible para el proceso %d.\n", id_proceso);
                }
                break;
            }
            case 2: {
                int id_proceso;
                printf("Ingrese el ID del proceso a liberar: ");
                scanf("%d", &id_proceso);

                int liberado = 0;
                for (int i = 0; i < num_particiones; i++) {
                    if (particiones[i].id_de_proceso == id_proceso) {
                        particiones[i].id_de_proceso = -1;
                        liberado = 1;
                        printf("Proceso %d liberado de la partición %d.\n", id_proceso, i + 1);
                        break;
                    }
                }
                if (!liberado) {
                    printf("No se encontró el proceso %d en ninguna partición.\n", id_proceso);
                }
                break;
            }
            case 3:
                imprime_memoria(particiones, num_particiones);
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 4);

    // Liberar la memoria dinámica
    free(particiones);
    return 0;
}

~~~
2. 
~~~C
#include <stdio.h>

#define MAX_BLOQUES 100
#define MAX_PROCESOS 100

void primera_cabida(int bloques[], int num_bloques, int procesos[], int num_procesos) {
    int asignaciones[MAX_PROCESOS]; // Almacena el índice del bloque asignado a cada proceso (-1 si no se asignó)

    // Inicializar asignaciones a -1 (no asignado)
    for (int i = 0; i < num_procesos; i++) {
        asignaciones[i] = -1;
    }

    // Algoritmo de Primera Cabida
    for (int p = 0; p < num_procesos; p++) { // Iterar sobre cada proceso
        for (int b = 0; b < num_bloques; b++) { // Buscar un bloque disponible
            if (bloques[b] >= procesos[p]) { // Si el bloque tiene espacio suficiente
                asignaciones[p] = b;         // Asignar este bloque al proceso
                bloques[b] -= procesos[p];   // Reducir espacio disponible en el bloque
                break;                       // Salir del bucle para el siguiente proceso
            }
        }
    }

    // Mostrar resultados
    printf("\nResultados de la asignación:\n");
    for (int i = 0; i < num_procesos; i++) {
        if (asignaciones[i] != -1) {
            printf("Proceso %d (%d KB) -> Bloque %d\n", i + 1, procesos[i], asignaciones[i] + 1);
        } else {
            printf("Proceso %d (%d KB) -> No asignado\n", i + 1, procesos[i]);
        }
    }
}

int main() {
    int num_bloques, num_procesos;
    int bloques[MAX_BLOQUES], procesos[MAX_PROCESOS];

    // Leer información de los bloques de memoria
    printf("Ingrese el número de bloques de memoria: ");
    scanf("%d", &num_bloques);
    printf("Ingrese los tamaños de los bloques (KB):\n");
    for (int i = 0; i < num_bloques; i++) {
        printf("Bloque %d: ", i + 1);
        scanf("%d", &bloques[i]);
    }

    // Leer información de los procesos
    printf("\nIngrese el número de procesos: ");
    scanf("%d", &num_procesos);
    printf("Ingrese los tamaños de los procesos (KB):\n");
    for (int i = 0; i < num_procesos; i++) {
        printf("Proceso %d: ", i + 1);
        scanf("%d", &procesos[i]);
    }

    // Ejecutar el algoritmo de Primera Cabida
    primera_cabida(bloques, num_bloques, procesos, num_procesos);

    return 0;
}
~~~
### Organización de memoria virtual
1. Paginación y Segmentación:
   
   1. Paginación: Es un mecanismo que implementa la memoria virtual mediante la administración de la transferencia de páginas entre la memoria física y el disco. La paginación implica dos componentes: una tabla de páginas y un controlador de errores de página. 