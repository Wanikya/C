#include <stdio.h>
#include <stdbool.h>

#define FILAS 5
#define COLUMNAS 5

// Función para verificar si una posición está dentro de los límites de la matriz
bool estaEnLimites(int fila, int columna) {
    return (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS);
}

// Función para realizar una búsqueda en profundidad (DFS) en la matriz
void dfs(int matriz[FILAS][COLUMNAS], bool visitado[FILAS][COLUMNAS], int fila, int columna) {
    // Movimientos posibles: arriba, abajo, izquierda, derecha, y las 4 diagonales
    int movimientosFila[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int movimientosColumna[] = {0, 0, -1, 1, -1, 1, -1, 1};

    // Marca la celda como visitada
    visitado[fila][columna] = true;

    // Explora todas las celdas adyacentes
    for (int i = 0; i < 8; i++) {
        int nuevaFila = fila + movimientosFila[i];
        int nuevaColumna = columna + movimientosColumna[i];

        // Si la celda vecina es válida, no ha sido visitada, y no es 0, continúa la búsqueda
        if (estaEnLimites(nuevaFila, nuevaColumna) && !visitado[nuevaFila][nuevaColumna] && matriz[nuevaFila][nuevaColumna] != 0) {
            dfs(matriz, visitado, nuevaFila, nuevaColumna);
        }
    }
}

// Función principal para contar bloques de datos en la matriz
int contarBloques(int matriz[FILAS][COLUMNAS]) {
    bool visitado[FILAS][COLUMNAS] = {false}; // Inicializa todas las celdas como no visitadas
    int cantidadBloques = 0;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            // Si encontramos una celda con datos no visitada, es un nuevo bloque
            if (matriz[i][j] != 0 && !visitado[i][j]) {
                dfs(matriz, visitado, i, j); // Marca todo el bloque como visitado
                cantidadBloques++;
            }
        }
    }

    return cantidadBloques;
}

int main() {
    // Ejemplo de matriz
    int matriz[FILAS][COLUMNAS] = {
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0}
    };

    printf("Matriz analizada:\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    int cantidadBloques = contarBloques(matriz);
    printf("\nCantidad de bloques en la matriz: %d\n", cantidadBloques);

    return 0;
}
