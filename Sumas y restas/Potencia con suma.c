#include <stdio.h>

// Función para multiplicar dos números usando sumas recursivas
int multiplicar(int a, int b) {
    if (b == 0) return 0;
    return a + multiplicar(a, b - 1);
}

// Función para calcular a^b usando la función de multiplicación recursiva
int potencia(int a, int b) {
    if (b == 0) return 1;
    return multiplicar(a, potencia(a, b - 1));
}

// Función para dividir `a` entre `b` usando restas recursivas
int dividir(int a, int b) {
    if (b == 0) {
        printf("Error: División por cero no permitida.\n");
        return -1; // Retorna -1 para indicar error en división por cero
    }
    if (a < b) return 0; // Si `a` es menor que `b`, el cociente es 0
    return 1 + dividir(a - b, b); // Cuenta una "unidad" en el cociente y resta `b` de `a`
}

int main() {
    int opcion, a, b;

    printf("Seleccione la operacion a realizar:\n");
    printf("1. Multiplicacion\n");
    printf("2. Potencia\n");
    printf("3. Division\n");
    printf("Ingrese la opcion (1-3): ");
    scanf("%d", &opcion);

    printf("Ingrese el primer número: ");
    scanf("%d", &a);
    printf("Ingrese el segundo número: ");
    scanf("%d", &b);

    int resultado;
    switch(opcion) {
        case 1:
            resultado = multiplicar(a, b);
            printf("Resultado de %d * %d = %d\n", a, b, resultado);
            break;
        case 2:
            resultado = potencia(a, b);
            printf("Resultado de %d^%d = %d\n", a, b, resultado);
            break;
        case 3:
            resultado = dividir(a, b);
            if (resultado != -1) {
                printf("Resultado de %d / %d = %d\n", a, b, resultado);
            }
            break;
        default:
            printf("Opción no válida.\n");
    }

    return 0;
}
