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
      1. Ventajas:
         1. Es posible comenzar a ejecutar un programa, cargando solo una parte del mismo en memoria, y el resto se cargará bajo la solicitud.
         2. No es necesario que las páginas estén contiguas en memoria.
         3. Fácil control de todas las páginas, ya que tienen el mismo tamaño.
         4. Se elimina el problema de fragmentación externa.
         5. Se obtiene una alta velocidad de acceso a memoria gracias a la TDP.
      2. Desvantajas:
         1. Problema importante "Superfluity".
         2. El costo del Hardware y el Software se incrementa.
         3. Consumen más recursos de memoria.
         4. Aparece el problema de Fragmentación Interna.
   2. Segmentación: La segmentación de memoria es un esquema de manejo de memoria mediante el cual la estructura del programa refleja su división lógica, llevándose a cabo una agrupación lógica de la información en bloques de tamaño variable denominados segmentos, es decir que los segmentos pueden ser de distintos tamaños, incluso de forma dinámica.
      1. Ventajas:
         1. El programador conoce las unidades lógicas de su programa.
         2. Es posible compilar módulos separados como segmentos.
         3. Facilidad de modificación de los módulos.
         4. El cambio dentro de un módulo no afecta al resto de los módulos.
      2. Desventajas:
         1. Se complica el manejo de memoria virtual.
         2. El costo del Hardware y el Software se incrementa.
         3. Mayor consumo de recursos: memoria, tiempo de CPU, etc.
         4. Aparece el problema de Fragmentación Externa.
2. Código:
~~~C
#include <stdio.h>
#include <stdlib.h>

#define NUM_PAGINAS 8      // Número total de páginas lógicas
#define TAM_PAGINA 1024    // Tamaño de cada página en bytes
#define NUM_MARCOS 8       // Número total de marcos físicos

// Función para inicializar la tabla de páginas con asignaciones aleatorias
void inicializar_tabla_paginas(int tabla_paginas[], int num_paginas, int num_marcos) {
    for (int i = 0; i < num_paginas; i++) {
        tabla_paginas[i] = rand() % num_marcos;  // Asignar cada página a un marco físico aleatorio
    }
}

// Función para traducir una dirección lógica a física
int traducir_direccion(int direccion_logica, int tabla_paginas[], int tam_pagina) {
    int numero_pagina = direccion_logica / tam_pagina;       // Calcular número de página
    int desplazamiento = direccion_logica % tam_pagina;      // Calcular desplazamiento dentro de la página

    if (numero_pagina >= NUM_PAGINAS) {
        printf("Error: Número de página fuera de rango.\n");
        return -1;
    }

    int marco_fisico = tabla_paginas[numero_pagina];         // Obtener marco físico de la tabla de páginas
    int direccion_fisica = (marco_fisico * tam_pagina) + desplazamiento; // Calcular dirección física

    printf("Dirección lógica: %d --> Página: %d, Marco: %d, Desplazamiento: %d --> Dirección física: %d\n",
           direccion_logica, numero_pagina, marco_fisico, desplazamiento, direccion_fisica);

    return direccion_fisica;
}

int main() {
    int tabla_paginas[NUM_PAGINAS];  // Tabla de páginas
    int direccion_logica;            // Dirección lógica ingresada por el usuario

    // Inicializar la tabla de páginas con asignaciones aleatorias
    inicializar_tabla_paginas(tabla_paginas, NUM_PAGINAS, NUM_MARCOS);

    printf("Tabla de páginas inicializada:\n");
    for (int i = 0; i < NUM_PAGINAS; i++) {
        printf("Página %d --> Marco %d\n", i, tabla_paginas[i]);
    }

    printf("\nIngrese direcciones lógicas aleatorias (ingrese -1 para salir):\n");

    while (1) {
        printf("Dirección lógica: ");
        scanf("%d", &direccion_logica);

        if (direccion_logica == -1) {
            break;  // Salir del programa
        }

        if (direccion_logica < 0) {
            printf("Error: La dirección lógica no puede ser negativa.\n");
            continue;
        }

        // Traducir la dirección lógica a física
        traducir_direccion(direccion_logica, tabla_paginas, TAM_PAGINA);
    }

    printf("Saliendo del programa...\n");
    return 0;
}
~~~
### Administración de memoria virtual
1. Código:
~~~C
#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGINAS 100

// Función para verificar si una página ya está en los marcos
int buscar_pagina(int marcos[], int num_marcos, int pagina) {
    for (int i = 0; i < num_marcos; i++) {
        if (marcos[i] == pagina) {
            return i;  // Retorna la posición si la página está presente
        }
    }
    return -1;  // Retorna -1 si la página no está en los marcos
}

// Función para imprimir el estado actual de los marcos de memoria
void imprimir_marcos(int marcos[], int num_marcos) {
    printf("Marcos: ");
    for (int i = 0; i < num_marcos; i++) {
        if (marcos[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", marcos[i]);
        }
    }
    printf("\n");
}

int main() {
    int num_marcos, num_referencias;
    int referencias[MAX_PAGINAS];
    int marcos[MAX_PAGINAS];  // Simula los marcos de memoria
    int contador_usos[MAX_PAGINAS];  // Guarda el orden de uso de cada página
    int fallos_pagina = 0;

    // Inicializar marcos y contadores
    for (int i = 0; i < MAX_PAGINAS; i++) {
        marcos[i] = -1;  // Inicialmente los marcos están vacíos
        contador_usos[i] = 0;
    }

    // Entrada: número de marcos y referencias
    printf("Ingrese el número de marcos de página: ");
    scanf("%d", &num_marcos);

    printf("Ingrese el número de referencias a páginas: ");
    scanf("%d", &num_referencias);

    printf("Ingrese la secuencia de referencias a páginas:\n");
    for (int i = 0; i < num_referencias; i++) {
        scanf("%d", &referencias[i]);
    }

    // Simulación del algoritmo LRU
    for (int i = 0; i < num_referencias; i++) {
        int pagina_actual = referencias[i];
        int posicion = buscar_pagina(marcos, num_marcos, pagina_actual);

        // Si la página no está en memoria, ocurre un fallo de página
        if (posicion == -1) {
            int indice_reemplazo = -1;

            // Buscar un marco vacío o la página menos recientemente usada
            if (i < num_marcos) {
                // Si hay marcos vacíos, usa el primero disponible
                indice_reemplazo = i;
            } else {
                // Encuentra la página menos recientemente usada
                int min_uso = i;
                for (int j = 0; j < num_marcos; j++) {
                    if (contador_usos[marcos[j]] < min_uso) {
                        min_uso = contador_usos[marcos[j]];
                        indice_reemplazo = j;
                    }
                }
            }

            // Reemplaza la página
            marcos[indice_reemplazo] = pagina_actual;
            contador_usos[pagina_actual] = i;  // Actualiza el uso de la página
            fallos_pagina++;
        } else {
            // Si la página ya está en memoria, actualiza su uso
            contador_usos[pagina_actual] = i;
        }

        // Imprimir el estado actual de los marcos
        printf("Referencia: %d --> ", pagina_actual);
        imprimir_marcos(marcos, num_marcos);
    }

    // Resultado final
    printf("\nNúmero total de fallos de página: %d\n", fallos_pagina);

    return 0;
}
~~~
2. *
### Integración
1. Windows administra la memoria virtual mediante una combinación de RAM (memoria física) y un archivo de paginación (o pagefile) ubicado en el disco duro o SSD. La memoria virtual permite que el sistema maneje más datos de los que caben en la memoria física, proporcionando un espacio de respaldo en el almacenamiento secundario.
2. Código:
~~~Python
import time
import random
from collections import deque

# Simulación de memoria virtual
class VirtualMemory:
    def __init__(self, memory_size, swap_size):
        self.memory_size = memory_size  # Tamaño de la memoria física (RAM)
        self.swap_size = swap_size      # Tamaño del archivo de paginación (Swap)
        self.memory = deque()           # Memoria RAM como una cola (FIFO para simulación LRU)
        self.swap = []                  # Simulación del archivo de paginación
        self.page_counter = 0           # Contador de páginas cargadas

    def load_process(self, process):
        if len(self.memory) < self.memory_size:
            # Hay espacio en memoria RAM
            self.memory.appendleft((process, time.time()))  # Tiempo usado para simular LRU
            print(f"Proceso {process} cargado en RAM.")
        else:
            # No hay espacio, se realiza SWAPPING
            self.swap_out()
            self.memory.appendleft((process, time.time()))
            print(f"Proceso {process} cargado en RAM tras SWAP.")
        self.page_counter += 1

    def swap_out(self):
        # Encuentra la página menos recientemente usada (LRU)
        process_to_swap = self.memory.pop()
        self.swap.append(process_to_swap)
        print(f"Proceso {process_to_swap[0]} SWAP OUT (movido al archivo de paginación).")
        if len(self.swap) > self.swap_size:
            removed = self.swap.pop(0)
            print(f"Proceso {removed[0]} eliminado del SWAP (swap lleno).")

    def access_process(self, process):
        # Simula el acceso a un proceso
        for i, (proc, _) in enumerate(self.memory):
            if proc == process:
                # Actualiza el tiempo de acceso
                self.memory[i] = (proc, time.time())
                print(f"Proceso {process} accedido en RAM.")
                return
        # Si no está en RAM, buscar en SWAP
        for i, (proc, _) in enumerate(self.swap):
            if proc == process:
                print(f"Proceso {process} encontrado en SWAP. SWAP IN realizado.")
                self.swap.pop(i)
                self.load_process(process)
                return
        print(f"Proceso {process} no encontrado en memoria ni en SWAP.")

    def show_status(self):
        print("\n=== Estado de la Memoria ===")
        print("RAM:")
        for proc, _ in self.memory:
            print(f"  Proceso {proc}")
        print("SWAP:")
        for proc, _ in self.swap:
            print(f"  Proceso {proc}")
        print("===========================\n")

# Simulación
if __name__ == "__main__":
    memory_size = 3  # Tamaño de la memoria RAM (número de procesos que puede contener)
    swap_size = 5    # Tamaño del archivo de paginación (swap)
    vm = VirtualMemory(memory_size, swap_size)

    # Lista de procesos simulados
    processes = ["A", "B", "C", "D", "E", "F", "G"]

    # Cargar procesos en memoria
    for process in processes:
        vm.load_process(process)
        vm.show_status()
        time.sleep(1)

    # Acceder procesos aleatoriamente
    print("\n--- Acceso aleatorio a procesos ---")
    for _ in range(5):
        process = random.choice(processes)
        vm.access_process(process)
        vm.show_status()
        time.sleep(1)
~~~
Resultado:
~~~
Proceso A cargado en RAM.

=== Estado de la Memoria ===
RAM:
  Proceso A
SWAP:
===========================

Proceso B cargado en RAM.

=== Estado de la Memoria ===
RAM:
  Proceso B
  Proceso A
SWAP:
===========================

Proceso C cargado en RAM.

=== Estado de la Memoria ===
RAM:
  Proceso C
  Proceso B
  Proceso A
SWAP:
===========================

Proceso D SWAP OUT (movido al archivo de paginación).
Proceso D cargado en RAM tras SWAP.

=== Estado de la Memoria ===
RAM:
  Proceso D
  Proceso C
  Proceso B
SWAP:
  Proceso A
===========================
~~~
## Administración de Entrada/Salida
### Dispositivos y manejadores de dispositivos
1. Dispositivos de bloque y dispositivos de carácter:
   1. Dispositivos de bloque: Son dispositivos que manejan datos en bloques de tamaño fijo (normalmente 512 bytes o más). Estos dispositivos permiten acceso aleatorio a los bloques, lo que significa que se puede leer o escribir en cualquier bloque en cualquier momento
      * Ejemplo: Disco duro (HDD).
   2. Dispositivos de carácter: Son dispositivos que manejan datos como una secuencia de bytes o caracteres, sin importar el tamaño. Estos dispositivos no permiten acceso aleatorio; solo permiten leer o escribir de manera secuencial.
      * Ejemplo: Teclado.
2. Código:
~~~Python
import time
import random

# Simulación de un dispositivo virtual de entrada
class VirtualInputDevice:
    def __init__(self, name="VirtualInput"):  # Constructor del dispositivo
        self.name = name
        self.buffer = []  # Buffer de entrada para almacenar datos
        self.is_open = False  # Estado del dispositivo

    def open_device(self):
        if not self.is_open:
            self.is_open = True
            print(f"[INFO] Dispositivo '{self.name}' abierto correctamente.")
        else:
            print(f"[WARNING] Dispositivo '{self.name}' ya está abierto.")

    def close_device(self):
        if self.is_open:
            self.is_open = False
            print(f"[INFO] Dispositivo '{self.name}' cerrado correctamente.")
        else:
            print(f"[WARNING] Dispositivo '{self.name}' ya está cerrado.")

    def read_data(self):
        if not self.is_open:
            print(f"[ERROR] No se puede leer. El dispositivo '{self.name}' está cerrado.")
            return None

        if not self.buffer:
            # Simulamos la llegada de nuevos datos
            simulated_data = self.generate_input_data()
            self.buffer.append(simulated_data)
            print(f"[INFO] Nuevos datos recibidos: {simulated_data}")

        # Leer el primer elemento del buffer
        data = self.buffer.pop(0)
        print(f"[READ] Datos leídos desde el dispositivo: {data}")
        return data

    def generate_input_data(self):
        # Simula datos generados aleatoriamente (como un teclado virtual)
        data = random.choice(["Hello", "World", "Data", "Input", "Device", "Test"])
        return data

# Controlador del dispositivo virtual
class DeviceDriver:
    def __init__(self):
        self.device = VirtualInputDevice()

    def handle_request(self):
        print("\n=== Simulación del manejador de dispositivos ===")
        self.device.open_device()

        for _ in range(5):  # Simula 5 lecturas de datos
            time.sleep(1)  # Simula tiempo de espera
            data = self.device.read_data()
            if data is None:
                break

        self.device.close_device()
        print("[INFO] Manejador de dispositivo finalizado.")

if __name__ == "__main__":
    driver = DeviceDriver()
    driver.handle_request()
~~~
### Mecanismos y funciones de los manejadores de dispositivos
1. Una interrupción por E/S es un mecanismo que permite a los dispositivos periféricos comunicarse con el procesador principal de una computadora, solicitar atención y realizar operaciones de entrada o salida sin necesidad de que el procesador esté ejecutando un programa específico, cuando un dispositivo periférico (como un teclado, un mouse o un disco duro) necesita atención del procesador, activa una línea de interrupción (IRQ) específica.
~~~
INICIO

PROCESO principal:
    Mientras (True):
        Ejecutar instrucción del proceso actual
        Si (se genera interrupción):
            Llamar a manejador_interrupcion()

FUNCIÓN manejador_interrupcion():
    Guardar el estado del proceso actual (registros, contador de programa, etc.)
    Identificar la fuente de la interrupción
    Si (interrupción es por E/S):
        Llamar a rutina_E/S()
    Restaurar el estado del proceso actual
    Reanudar la ejecución del proceso original

FUNCIÓN rutina_E/S():
    Mostrar "Interrupción de E/S recibida"
    Leer datos del dispositivo de E/S (simulado)
    Actualizar estado del sistema o proceso que espera la E/S
    Mostrar "E/S completada"

FIN
~~~
2. Código:
~~~C
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // Para sleep()

// Variables globales
bool interrupcion_e_s = false;  // Bandera para simular una interrupción

// Función que simula el manejador de interrupciones
void manejador_interrupcion() {
    printf("\n[INTERRUPCIÓN] Se ha detectado una interrupción de E/S.\n");
    
    // Guardar el estado del proceso actual
    printf("[INFO] Guardando el estado del proceso actual...\n");
    
    // Llamar a la rutina de E/S
    rutina_e_s();

    // Restaurar el estado del proceso actual
    printf("[INFO] Restaurando el estado del proceso actual...\n");
    printf("[INFO] Reanudando la ejecución del proceso principal...\n\n");
}

// Función que simula la rutina de E/S
void rutina_e_s() {
    printf("[E/S] Manejo de la operación de E/S...\n");
    sleep(1); // Simula tiempo de procesamiento
    printf("[E/S] Operación de E/S completada.\n");
}

// Función principal que simula un proceso en ejecución
void proceso_principal() {
    int contador = 0;
    
    while (contador < 10) {
        printf("Proceso principal ejecutándose... (Iteración %d)\n", contador + 1);
        sleep(1); // Simula el tiempo de ejecución del proceso
        
        // Simula la generación de una interrupción en la iteración 5
        if (contador == 4) {
            interrupcion_e_s = true;
        }

        // Verificar si se generó una interrupción
        if (interrupcion_e_s) {
            manejador_interrupcion(); // Llamar al manejador de interrupciones
            interrupcion_e_s = false; // Restablecer la bandera
        }
        
        contador++;
    }
    
    printf("\n[INFO] Proceso principal completado.\n");
}

int main() {
    printf("=== Simulación de manejo de interrupciones por E/S ===\n\n");
    proceso_principal(); // Ejecuta el proceso principal
    printf("\n=== Fin de la simulación ===\n");
    return 0;
}
~~~
### Estructuras de datos para manejo de dispositivos
1. Una cola de entrada/salida (cola de E/S) es una estructura de datos utilizada en sistemas operativos para gestionar las solicitudes de entrada/salida de los dispositivos periféricos, como discos, teclados, impresoras, etc.
~~~C
#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // Tamaño máximo de la cola

// Estructura para un elemento en la cola con prioridad
typedef struct {
    int dato;       // Información del elemento
    int prioridad;  // Prioridad del elemento (menor número = mayor prioridad)
} Elemento;

// Estructura para la cola con prioridad
typedef struct {
    Elemento elementos[MAX];  // Arreglo de elementos
    int tamano;               // Número actual de elementos en la cola
} ColaPrioridad;

// Función para inicializar la cola
void inicializarCola(ColaPrioridad *cola) {
    cola->tamano = 0;
}

// Función para verificar si la cola está vacía
int esVacia(ColaPrioridad *cola) {
    return cola->tamano == 0;
}

// Función para verificar si la cola está llena
int esLlena(ColaPrioridad *cola) {
    return cola->tamano == MAX;
}

// Función para insertar un elemento en la cola según su prioridad
void insertar(ColaPrioridad *cola, int dato, int prioridad) {
    if (esLlena(cola)) {
        printf("[ERROR] La cola está llena. No se puede insertar más elementos.\n");
        return;
    }

    int i = cola->tamano - 1;

    // Desplazar elementos para mantener el orden de prioridad
    while (i >= 0 && cola->elementos[i].prioridad > prioridad) {
        cola->elementos[i + 1] = cola->elementos[i];
        i--;
    }

    // Insertar el nuevo elemento en la posición correcta
    cola->elementos[i + 1].dato = dato;
    cola->elementos[i + 1].prioridad = prioridad;
    cola->tamano++;

    printf("[INFO] Elemento %d con prioridad %d insertado correctamente.\n", dato, prioridad);
}

// Función para eliminar el elemento con mayor prioridad
void eliminar(ColaPrioridad *cola) {
    if (esVacia(cola)) {
        printf("[ERROR] La cola está vacía. No se puede eliminar ningún elemento.\n");
        return;
    }

    // El elemento con mayor prioridad está en la primera posición
    printf("[INFO] Elemento %d con prioridad %d eliminado.\n", 
            cola->elementos[0].dato, cola->elementos[0].prioridad);

    // Desplazar elementos hacia adelante
    for (int i = 1; i < cola->tamano; i++) {
        cola->elementos[i - 1] = cola->elementos[i];
    }

    cola->tamano--;
}

// Función para mostrar los elementos de la cola
void mostrarCola(ColaPrioridad *cola) {
    if (esVacia(cola)) {
        printf("[INFO] La cola está vacía.\n");
        return;
    }

    printf("Elementos en la cola con prioridad:\n");
    for (int i = 0; i < cola->tamano; i++) {
        printf("Dato: %d | Prioridad: %d\n", cola->elementos[i].dato, cola->elementos[i].prioridad);
    }
}

int main() {
    ColaPrioridad cola;
    inicializarCola(&cola);

    printf("=== Simulación de una Cola con Prioridad ===\n");

    // Insertar elementos en la cola
    insertar(&cola, 10, 2);
    insertar(&cola, 20, 1);
    insertar(&cola, 30, 3);
    insertar(&cola, 40, 0);  // Prioridad más alta

    // Mostrar el estado actual de la cola
    mostrarCola(&cola);

    // Eliminar elementos de la cola
    eliminar(&cola);
    mostrarCola(&cola);

    eliminar(&cola);
    mostrarCola(&cola);

    return 0;
}
~~~
Salida:
~~~
=== Simulación de una Cola con Prioridad ===
[INFO] Elemento 10 con prioridad 2 insertado correctamente.
[INFO] Elemento 20 con prioridad 1 insertado correctamente.
[INFO] Elemento 30 con prioridad 3 insertado correctamente.
[INFO] Elemento 40 con prioridad 0 insertado correctamente.
Elementos en la cola con prioridad:
Dato: 40 | Prioridad: 0
Dato: 20 | Prioridad: 1
Dato: 10 | Prioridad: 2
Dato: 30 | Prioridad: 3
[INFO] Elemento 40 con prioridad 0 eliminado.
Elementos en la cola con prioridad:
Dato: 20 | Prioridad: 1
Dato: 10 | Prioridad: 2
Dato: 30 | Prioridad: 3
[INFO] Elemento 20 con prioridad 1 eliminado.
Elementos en la cola con prioridad:
Dato: 10 | Prioridad: 2
Dato: 30 | Prioridad: 3
~~~
2. Código:
~~~C
#include <stdio.h>
#include <string.h>

// Definición de constantes
#define MAX_DISPOSITIVOS 5
#define ACTIVO 1
#define INACTIVO 0

// Estructura que representa un dispositivo
typedef struct {
    int id;                    // Identificador del dispositivo
    char nombre[20];           // Nombre del dispositivo
    int estado;                // Estado del dispositivo (ACTIVO/INACTIVO)
    void (*inicializar)();     // Función para inicializar el dispositivo
    void (*leer)();            // Función para leer del dispositivo
    void (*escribir)();        // Función para escribir en el dispositivo
} Dispositivo;

// Funciones de operaciones para dispositivos
void inicializarDispositivo() {
    printf("-> Dispositivo inicializado correctamente.\n");
}

void leerDispositivo() {
    printf("-> Leyendo datos del dispositivo...\n");
}

void escribirDispositivo() {
    printf("-> Escribiendo datos en el dispositivo...\n");
}

// Función para mostrar la tabla de dispositivos
void listarDispositivos(Dispositivo dispositivos[], int n) {
    printf("\n=== Tabla de Dispositivos ===\n");
    printf("ID\tNombre\t\tEstado\n");
    printf("-------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%s\n", dispositivos[i].id, dispositivos[i].nombre,
               dispositivos[i].estado == ACTIVO ? "Activo" : "Inactivo");
    }
    printf("\n");
}

// Función para cambiar el estado de un dispositivo
void cambiarEstado(Dispositivo dispositivos[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (dispositivos[i].id == id) {
            dispositivos[i].estado = (dispositivos[i].estado == ACTIVO) ? INACTIVO : ACTIVO;
            printf("[INFO] El dispositivo '%s' ahora está %s.\n", dispositivos[i].nombre,
                   dispositivos[i].estado == ACTIVO ? "Activo" : "Inactivo");
            return;
        }
    }
    printf("[ERROR] No se encontró un dispositivo con ID %d.\n", id);
}

// Función para ejecutar operaciones en un dispositivo
void ejecutarOperacion(Dispositivo dispositivos[], int n, int id, char operacion) {
    for (int i = 0; i < n; i++) {
        if (dispositivos[i].id == id) {
            if (dispositivos[i].estado == INACTIVO) {
                printf("[ERROR] El dispositivo '%s' está inactivo.\n", dispositivos[i].nombre);
                return;
            }
            switch (operacion) {
                case 'i': dispositivos[i].inicializar(); break;
                case 'r': dispositivos[i].leer(); break;
                case 'w': dispositivos[i].escribir(); break;
                default: printf("[ERROR] Operación inválida.\n"); break;
            }
            return;
        }
    }
    printf("[ERROR] No se encontró un dispositivo con ID %d.\n", id);
}

int main() {
    // Crear una tabla de dispositivos
    Dispositivo dispositivos[MAX_DISPOSITIVOS] = {
        {1, "Teclado", ACTIVO, inicializarDispositivo, leerDispositivo, escribirDispositivo},
        {2, "Mouse", INACTIVO, inicializarDispositivo, leerDispositivo, escribirDispositivo},
        {3, "Impresora", ACTIVO, inicializarDispositivo, leerDispositivo, escribirDispositivo},
        {4, "Escáner", INACTIVO, inicializarDispositivo, leerDispositivo, escribirDispositivo},
        {5, "Disco Duro", ACTIVO, inicializarDispositivo, leerDispositivo, escribirDispositivo},
    };

    int opcion, id;
    char operacion;

    do {
        printf("=== Manejador de Dispositivos ===\n");
        printf("1. Listar dispositivos\n");
        printf("2. Activar/Desactivar un dispositivo\n");
        printf("3. Ejecutar operación en un dispositivo\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                listarDispositivos(dispositivos, MAX_DISPOSITIVOS);
                break;
            case 2:
                printf("Ingrese el ID del dispositivo a cambiar estado: ");
                scanf("%d", &id);
                cambiarEstado(dispositivos, MAX_DISPOSITIVOS, id);
                break;
            case 3:
                printf("Ingrese el ID del dispositivo: ");
                scanf("%d", &id);
                printf("Seleccione operación (i = inicializar, r = leer, w = escribir): ");
                scanf(" %c", &operacion);
                ejecutarOperacion(dispositivos, MAX_DISPOSITIVOS, id, operacion);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("[ERROR] Opción inválida. Inténtelo de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}
~~~
### Operaciones de Entrada/Salida
1. Descripción general: Un disco magnético utiliza un sistema mecánico (cabezal de lectura/escritura) para acceder a la información almacenada en su superficie.
   1. Pasos:
      1. Solicitud del archivo: El sistema operativo o un programa realiza una solicitud de lectura de un archivo específico.
      2. Búsqueda del archivo: El sistema operativo consulta la tabla de archivos (como la FAT o MFT) para localizar las pistas, sectores y cilindros donde está almacenado el archivo.
      3. Movimiento del cabezal: El brazo mecánico mueve el cabezal de lectura al cilindro correspondiente. Este movimiento se llama "seek".
      4. Rotación del disco: El disco magnético gira para alinear el sector deseado bajo el cabezal. Este tiempo se llama "latencia rotacional".
      5. Lectura de los datos: El cabezal lee los datos magnéticos del sector correspondiente y los convierte en datos digitales. La información se almacena en el buffer del controlador de disco.
      6. Transferencia de datos: Los datos leídos se transfieren al sistema operativo a través de un canal de E/S.
      7. Entrega al programa: Finalmente, los datos se entregan al programa que solicitó la lectura.
~~~C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Para la función sleep (simulación de tiempo)

// Definición de constantes
#define NUM_SECTORES 10  // Número de sectores en el disco simulado
#define TIEMPO_BUSQUEDA 2  // Tiempo de búsqueda en segundos
#define TIEMPO_ROTACION 1  // Tiempo de latencia rotacional en segundos

// Estructura para simular un archivo
typedef struct {
    char nombre[20];  // Nombre del archivo
    int sector;       // Sector donde está almacenado el archivo
} Archivo;

// Simulación de disco
Archivo disco[NUM_SECTORES];

// Función para inicializar el disco con archivos simulados
void inicializarDisco() {
    for (int i = 0; i < NUM_SECTORES; i++) {
        sprintf(disco[i].nombre, "archivo_%d.txt", i);  // Nombres de archivo
        disco[i].sector = i;  // Cada archivo en un sector único
    }
}

// Función para mostrar el contenido del disco
void mostrarDisco() {
    printf("=== Contenido del Disco Simulado ===\n");
    printf("Sector\tNombre del Archivo\n");
    printf("-------------------------------\n");
    for (int i = 0; i < NUM_SECTORES; i++) {
        printf("%d\t%s\n", disco[i].sector, disco[i].nombre);
    }
    printf("\n");
}

// Función para buscar un archivo en el disco
int buscarArchivo(char *nombreArchivo) {
    printf("[INFO] Buscando archivo '%s'...\n", nombreArchivo);
    sleep(TIEMPO_BUSQUEDA);  // Simula el tiempo de búsqueda
    for (int i = 0; i < NUM_SECTORES; i++) {
        if (strcmp(disco[i].nombre, nombreArchivo) == 0) {
            printf("[INFO] Archivo encontrado en el sector %d.\n", disco[i].sector);
            return disco[i].sector;
        }
    }
    printf("[ERROR] Archivo '%s' no encontrado.\n", nombreArchivo);
    return -1;
}

// Función para leer datos del sector
void leerSector(int sector) {
    printf("[INFO] Moviendo cabezal al sector %d...\n", sector);
    sleep(TIEMPO_ROTACION);  // Simula la latencia rotacional
    printf("[INFO] Leyendo datos del sector %d...\n", sector);
    printf("-> Contenido del archivo: 'Datos simulados del %s'\n", disco[sector].nombre);
}

// Función principal
int main() {
    char nombreArchivo[20];
    int sector;

    printf("=== Simulación de Lectura de Archivo en Disco Magnético ===\n\n");

    // Inicializar disco simulado
    inicializarDisco();

    // Mostrar contenido del disco
    mostrarDisco();

    // Solicitar al usuario el nombre del archivo
    printf("Ingrese el nombre del archivo a leer: ");
    scanf("%s", nombreArchivo);

    // Buscar archivo
    sector = buscarArchivo(nombreArchivo);

    // Leer archivo si se encontró
    if (sector != -1) {
        leerSector(sector);
    }

    printf("\n[INFO] Lectura completada. Finalizando programa...\n");

    return 0;
}
~~~
2. Código:
~~~ C
#include <stdio.h>
#include <stdlib.h>
#include <libaio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    io_context_t ctx;
    struct iocb cb;
    struct iocb *cbs[1];
    char buffer[BUFFER_SIZE];
    int fd;

    // Inicializar el contexto de E/S asíncrona
    io_setup(128, &ctx);

    // Abrir el archivo
    fd = open("ejemplo.txt", O_RDONLY);
    if (fd == -1) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Configurar la operación de lectura asíncrona
    io_prep_pread(&cb, fd, buffer, BUFFER_SIZE, 0);
    cbs[0] = &cb;

    // Ejecutar la operación de lectura asíncrona
    if (io_submit(ctx, 1, cbs) != 1) {
        perror("Error al enviar la solicitud de E/S");
        close(fd);
        return 1;
    }

    // Esperar la finalización de la operación
    struct io_event event;
    int ret = io_getevents(ctx, 1, 1, &event, NULL);
    if (ret == 1) {
        printf("Leído: %s\n", buffer);
    }

    // Cerrar el archivo
    close(fd);
    io_destroy(ctx);
    return 0;
}
~~~
### Integración
1. Código:
~~~C
#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    // Ordenar las solicitudes de los cilindros en orden ascendente
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void scan(int arr[], int n, int head, int direction) {
    // Ordenar las solicitudes
    sort(arr, n);
    
    // Variable para almacenar la distancia total recorrida
    int total_distance = 0;
    int current_position = head;
    
    // Se mueve en la dirección especificada
    printf("Cabeza del disco se mueve desde %d hacia %s:\n", head, (direction == 1) ? "derecha" : "izquierda");
    
    // Primero atender las solicitudes en la dirección de movimiento
    if (direction == 1) {
        // Atender solicitudes en la dirección derecha
        for (int i = 0; i < n; i++) {
            if (arr[i] > current_position) {
                total_distance += abs(arr[i] - current_position);
                current_position = arr[i];
                printf("Se atiende solicitud en el cilindro %d\n", arr[i]);
            }
        }

        // Luego, se invierte la dirección y se atienden las solicitudes restantes
        total_distance += abs(current_position - arr[n - 1]); // Moverse hasta el final
        current_position = arr[n - 1];

        for (int i = n - 1; i >= 0; i--) {
            if (arr[i] < current_position) {
                total_distance += abs(arr[i] - current_position);
                current_position = arr[i];
                printf("Se atiende solicitud en el cilindro %d\n", arr[i]);
            }
        }
    } else {
        // Atender solicitudes en la dirección izquierda
        for (int i = n - 1; i >= 0; i--) {
            if (arr[i] < current_position) {
                total_distance += abs(arr[i] - current_position);
                current_position = arr[i];
                printf("Se atiende solicitud en el cilindro %d\n", arr[i]);
            }
        }

        // Luego, se invierte la dirección y se atienden las solicitudes restantes
        total_distance += abs(current_position - arr[0]); // Moverse hasta el final
        current_position = arr[0];

        for (int i = 0; i < n; i++) {
            if (arr[i] > current_position) {
                total_distance += abs(arr[i] - current_position);
                current_position = arr[i];
                printf("Se atiende solicitud en el cilindro %d\n", arr[i]);
            }
        }
    }

    // Imprimir la distancia total recorrida
    printf("\nDistancia total recorrida: %d\n", total_distance);
}

int main() {
    int n, head, direction;

    // Solicitar al usuario las entradas
    printf("Ingrese el número de solicitudes: ");
    scanf("%d", &n);

    int arr[n];

    printf("Ingrese las solicitudes de los cilindros: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Ingrese la posición inicial de la cabeza del disco: ");
    scanf("%d", &head);

    printf("Ingrese la dirección de movimiento (1 para derecha, 0 para izquierda): ");
    scanf("%d", &direction);

    // Llamar a la función de SCAN
    scan(arr, n, head, direction);

    return 0;
}
~~~
2. Código:
~~~C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos un tamaño máximo para los dispositivos
#define MAX_BUFFER 256

// Estructura para el dispositivo "Disco Duro"
typedef struct {
    char data[MAX_BUFFER]; // Simula el almacenamiento de datos
} HardDrive;

void hardDrive_write(HardDrive *hd, const char *data) {
    strncpy(hd->data, data, MAX_BUFFER - 1); // Escribe en el disco
    printf("Disco duro: Datos escritos en el disco.\n");
}

void hardDrive_read(HardDrive *hd) {
    printf("Disco duro: Leyendo del disco: %s\n", hd->data);
}

// Estructura para el dispositivo "Impresora"
typedef struct {
    char data[MAX_BUFFER]; // Datos a imprimir
} Printer;

void printer_print(Printer *printer) {
    printf("Impresora: Imprimiendo: %s\n", printer->data);
}

// Estructura para el dispositivo "Teclado"
typedef struct {
    char input[MAX_BUFFER]; // Entrada del teclado
} Keyboard;

void keyboard_input(Keyboard *keyboard) {
    printf("Teclado: Introduzca texto para almacenar (máximo 255 caracteres): ");
    fgets(keyboard->input, MAX_BUFFER, stdin); // Simula la entrada de texto
    keyboard->input[strcspn(keyboard->input, "\n")] = 0; // Elimina el salto de línea
}

// Estructura para el controlador de dispositivos
typedef struct {
    HardDrive hd;
    Printer printer;
    Keyboard keyboard;
} DeviceController;

// Función para simular la comunicación entre dispositivos
void simulate_communication(DeviceController *controller) {
    // Paso 1: El teclado recibe entrada
    keyboard_input(&controller->keyboard);
    
    // Paso 2: El controlador escribe la entrada del teclado en el disco duro
    hardDrive_write(&controller->hd, controller->keyboard.input);
    
    // Paso 3: El disco duro lee y pasa los datos a la impresora
    hardDrive_read(&controller->hd);
    strcpy(controller->printer.data, controller->hd.data);
    
    // Paso 4: La impresora imprime los datos
    printer_print(&controller->printer);
}

int main() {
    DeviceController controller;
    
    // Inicializar los dispositivos (en este caso, simplemente inicializamos sus datos)
    memset(&controller, 0, sizeof(DeviceController));
    
    // Simular la comunicación entre dispositivos
    simulate_communication(&controller);
    
    return 0;
}
~~~
Entrada:
~~~
Teclado: Introduzca texto para almacenar (máximo 255 caracteres): Hola, este es un ejemplo de comunicación entre dispositivos.
~~~
Salida:
~~~
Disco duro: Datos escritos en el disco.
Disco duro: Leyendo del disco: Hola, este es un ejemplo de comunicación entre dispositivos.
Impresora: Imprimiendo: Hola, este es un ejemplo de comunicación entre dispositivos.
~~~
### Avanzado
1. Los sistemas operativos modernos optimizan las operaciones de entrada/salida (E/S) mediante el uso de memoria caché, una técnica fundamental que mejora significativamente el rendimiento al reducir la latencia y la sobrecarga asociada con las operaciones de E/S. La memoria caché es una forma de almacenamiento temporal que almacena datos de acceso frecuente o recientemente utilizados, de modo que, cuando un proceso o dispositivo necesita esos datos nuevamente, pueden ser recuperados más rápidamente.
## Dispositivos de entrada y salida en Linux