# Proyecto final
## Sistema de archivos
### Concepto y noción de archivo real y virtual
1. Definición de archivo real y archivo virtual
   1. Archivo real: Es un objeto que almacena de forma física programas, datos o cualquiero otro elemento que requiera el sistema operativo, siendo definido por el tamaño real que ocupa en el disco duro en forma de bytes.
   2. Archivo virtual: Es un archivo de uso temporal que es utilizado por los procesos del sistema mientras se están ejecutando dichos procesos.

2. Ejemplos de gestión de archivos reales y virtuales por distintos sistemas operativos
   1. Archivo real
      1. Windows: Utiliza es sistema de archivos NTFS, FAT32, exFAT, entre otros, para gestionar los dispositivos que almacenan los archivos reales.
      2. Linux: Utiliza sistemas de archivos como ext4, xfs, o btrfs para manejar archivos reales. Los archivos son tratados como flujos de bytes y se acceden mediante descriptores de archivo.
   2. Archivo virtual
      1. Windows: En Windows, los archivos virtuales son utilizados principalmente para abstracciones como los registros del sistema o los archivos de memoria mapeada.
      2. Linux: En Linux, los archivos virtuales son comunes en sistemas como /proc y /sys, que exponen información del sistema y hardware.
3. Caso práctico: Los archivos virtuales son más útiles para gestionar el consumo y uso del procesador en tiempo real, puesto que al ser una variable en constante cambio, cosa que no es posible con los archivos reales.
### Componentes de un sistema de archivos
1. Componentes clave de un sistema de archivos
   1. Estructura jerárquica de directorios: Proporciona una organización lógica para almacenar archivos.
   2. Bloques de almacenamiento: El almacenamiento físico en un dispositivo se divide en bloques de tamaño fijo.
   3. Tablas de asignación de archivos: Mapea los nombres de archivos a bloques de almacenamiento.
   4. Metadatos: Almacena información sobre los archivos, como su tamaño, fecha de creación, etc.
   5. Espacio libre: Almacena información sobre los bloques de almacenamiento disponibles.
   6. Sistema de archivos virtual: Capa de abstracción que permite al sistema operativo interactuar con diferentes tipos de sistemas de archivos de manera uniforme.
   7. Permisos y seguridad: Controla el acceso y la integridad de los archivos.
   8. Sistema de log: Registra las operaciones realizadas en el sistema de archivos.
   9. Cache: Almacena información temporalmente para acelerar las operaciones de lectura y escritura.
   10. Soporte para operaciones básicas: Implementa operaciones como crear, leer, escribir, eliminar, mover, copiar.
2. Comparación entre EXT4 y NTFS.

|Nombre|Ext4|NTFS|
|---|---|---|
|Estructura de directorios|Árbol jerárquico basado en entradas de directorio con soporte para nombres largos y enlaces simbólicos.|Árbol jerárquico con soporte para nombres largos y atributos extendidos.|
|Bloques de almacenamiento|Tamaño configurable (1 KB a 64 KB), lo que permite optimizar el uso de espacio según el tamaño del disco.|Tamaño dinámico según el tamaño del volumen, típicamente entre 4 KB y 64 KB.|
|Tabla de asignación|Utiliza i-nodos para almacenar metadatos y punteros directos e indirectos hacia bloques de datos.|Utiliza la Master File Table (MFT), donde cada archivo es representado por una entrada con metadatos y punteros.|
|Metadatos|Almacenados en i-nodos: permisos, tamaño, timestamps (creación, modificación, acceso).|Almacenados en la MFT: permisos, tamaño, timestamps y atributos extendidos.|
|Espacio libre|Administrado mediante un bitmap para rastrear bloques libres.|Utiliza un bitmap y un sistema de clústeres libres para rastrear el espacio disponible.|
|Sistema de Archivos Virtual|Soportado por el kernel de Linux a través de la capa VFS, que abstrae la interacción con ext4.|Accedido a través del subsistema de archivos de Windows, con compatibilidad integrada en el sistema operativo.|
|Permisos y seguridad|Modelo basado en usuarios y grupos de Unix, con permisos rwx para propietario, grupo y otros.|Permisos avanzados mediante ACLs (Access Control Lists) y soporte para cifrado con EFS.|
|Sistema de Logs|Journaling integrado para registrar cambios pendientes en el sistema de archivos. Soporta modos de journaling: writeback, ordered, y data journal.|Journaling completo integrado para garantizar la consistencia, almacenando cambios en un archivo de registro.|
|Cache|Caché basada en el kernel de Linux para operaciones frecuentes, mejorando el rendimiento.|Caché integrada en el subsistema de almacenamiento de Windows, utilizando la memoria RAM para acelerar el acceso.|
|Operaciones básicas|Soporte completo para crear, leer, escribir, mover y eliminar archivos. Compatible con operaciones POSIX.|Soporte completo para operaciones básicas y extendidas, como recuperación de archivos eliminados y compresión.|
3. Ventajas y desventajas de EXT4 y NTFS
   1. EXT4:
      1. Ventajas:
         1. Soporte para nombres largos y enlaces simbólicos.
         2. Buen performace con archivos grandes.
         3. Reduce la fragmentación en el disco.
         4. Permite un número ilimitado de inodos.
      2. Desventajas:
         1. No soporta el atributo de "eliminación segura".
         2. No nativa para Windows y MacOS.
         3. La función de asignación retrasada podría provocar una posible pérdida de datos.
   2. NTFS:
      1. Ventajas:
         1. Admite archivos de tamaño gigantesco.
         2. Casi no tiene límites realistas de tamaño de partición o de tamaño de archivo al cambiar el tamaño del clúster.
         3. Permite a los usuarios configurar la compresión de archivos cuando se queda sin espacio en disco.
         4. Proporciona un cifrado transparente y sólido de cualquier archivo o carpeta en un volumen NTFS.
         5. Utiliza archivos de registro e información de puntos de control para restaurar automáticamente la consistencia del sistema de archivos.
         6. Utiliza algoritmos CompactOS que comprimen toda la partición del sistema y evitan la fragmentación al escribir datos comprimidos en fragmentos asignados de forma contigua.
         7. Agrega la función de cambio de tamaño para reducir o expandir una partición.
         8. Utiliza un diario de cambios para restaurar la información cuando ocurre un corte de energía u otros problemas del sistema.
         9. Permite a los usuarios configurar cuotas de disco que limitan la cantidad de espacio que los usuarios pueden consumir.
      2.  Desventajas:
          1.  No es compatible con sistemas operativos muy antiguos.
          2.  Limitaciones en la denominación de archivos.
          3.  No admite el formateo de disquetes.
          4.  Requiere una gran cantidad de “sobrecarga de espacio” para funcionar.
### Organización lógica y física de archivos
1. Árbol jerárquico

![Árbol jerárquico](https://imgs.search.brave.com/zOmKXYh3HxKVD1nqxX4g3O8pz4laOh4VIc4n7sJhjPg/rs:fit:860:0:0:0/g:ce/aHR0cHM6Ly9pLnNz/dGF0aWMubmV0L09s/eXphYzAxLnBuZw)

2. El programa primero hace la solicitud para acceder a datos en una dirección lógica, luego se consulta la tabla de asignación correspondiente al sistema de archivos, posteriormente se hace la conversión a coordenadas físicas en el disco, se accede a esas coordenadas en el disco y se hace la transferiencia de los datos solicitados.
3. Supongamos que un archivo está dividido en bloques lógicos. Cuando se accede a un bloque:
   1. El i-nodo del archivo almacena punteros a los bloques físicos:
      * Punteros directos: Apuntan directamente a bloques en el disco.
      * Punteros indirectos: Apuntan a otros bloques que contienen más punteros.
   2. El sistema consulta el i-nodo para encontrar la dirección física del bloque lógico solicitado.
   3. El controlador accede al bloque físico correspondiente en el disco.
### Mecanismos de acceso a los archivos
1. Mecanismos de acceso:
   1. Secuencial: Es cuando un grupo de elementos es accedido en un predeterminado orden secuencial. En determinados casos es la única forma de acceder a los datos.
   2. Directo: Explotan la capacidad de los discos para acceder directamente a cualquier bloque de dirección conocida.
   3. Indexado: Método común de acceso a disco que almacena datos en forma secuencial, al tiempo que mantiene un índice de campos claves para todos los registros en el archivo para acceso directo.
2. Pseudocódigos:
   1. Acceder a un archivo de manera secuencial:
   ~~~
   INICIO

    // Declarar variables
    archivo ← abrir_archivo("nombre_del_archivo", "modo_lectura")
    SI archivo = NULL ENTONCES
        mostrar "Error: No se pudo abrir el archivo"
        TERMINAR

    // Leer el archivo secuencialmente
    MIENTRAS NO fin_de_archivo(archivo) HACER
        linea ← leer_linea(archivo)  // Leer una línea del archivo
        mostrar "Contenido:", linea  // Procesar o mostrar la línea leída
    FIN MIENTRAS

    // Cerrar el archivo
    cerrar_archivo(archivo)
    mostrar "Lectura del archivo completada"

   FIN
   ~~~
   2. Acceder a un archivo directamente mediante su posición:
   ~~~
   INICIO

    // Declarar variables
    archivo ← abrir_archivo("nombre_del_archivo", "modo_lectura")
    SI archivo = NULL ENTONCES
        mostrar "Error: No se pudo abrir el archivo"
        TERMINAR

    // Posicionar el puntero del archivo
    posicion ← ingresar_posicion()  // Solicitar la posición al usuario
    mover_puntero(archivo, posicion)  // Mover puntero a la posición especificada

    // Leer o escribir datos en la posición actual
    datos ← leer_datos(archivo, tamaño_datos)
    mostrar "Datos leídos:", datos

    // Cerrar el archivo
    cerrar_archivo(archivo)
    mostrar "Acceso directo al archivo completado"

   FIN
   ~~~
   3. Acceder a un archivo utilizando un índice:
   ~~~
   INICIO

    // Declarar variables
    archivo ← abrir_archivo("nombre_del_archivo", "modo_lectura")
    SI archivo = NULL ENTONCES
        mostrar "Error: No se pudo abrir el archivo"
        TERMINAR

    // Crear índice de registros (posición en el archivo)
    índice ← [pos1, pos2, pos3, ..., posN]  // Lista con las posiciones de los registros

    // Solicitar al usuario el número de registro
    mostrar "Ingrese el número de registro que desea acceder:"
    numero_registro ← leer_entrada()

    SI numero_registro < 1 O numero_registro > tamaño(índice) ENTONCES
        mostrar "Error: Número de registro fuera de rango"
        cerrar_archivo(archivo)
        TERMINAR

    // Mover el puntero a la posición del registro en el índice
    posicion ← índice[numero_registro - 1]
    mover_puntero(archivo, posicion)

    // Leer los datos del registro
    datos ← leer_datos(archivo, tamaño_registro)
    mostrar "Datos del registro:", datos

    // Cerrar el archivo
    cerrar_archivo(archivo)
    mostrar "Acceso al archivo utilizando índice completado"

   FIN
   ~~~   
3. Comparación entre mecanismos de acceso: 
   1. Secuencial: Simplicidad, eficiencia en lectura completa, menos movimiento
      1. Casos de uso: Logs, multimedia, cintas magnéticas
   2. Directo: Acceso rápido, ideal para consultas aleatorias
      1. Bases de datos, documentos, sistemas operativos
   3. Indexado: Eficiencia en búsquedas, escalabilidad, organización estructurada
      1. Bases de datos grandes, catálogos, sistemas de archivos
### Modelo jerárquico y mecanismos de recuperación en caso de falla *
1. *
2. *
3. *
## Protección y seguridad
### Concepto y objetivos de protección y seguridad
1. Conceptos:
   1. Protección: Es un mecanismo para controlar el acceso de los programas, de los procesos o de los usuarios a los recursos definidos por el sistema informático.
   2. Seguridad: Es el conjunto de medidas tomadas para protegerse contra robos, ataques, crímenes y espionajes o sabotajes.
2. Objetivos principales:
   1. Protección de Recursos: Evitar que procesos o usuarios no autorizados accedan, modifiquen o interfieran con los recursos del sistema.
   2. Confidencialidad: Garantizar que la información sensible sea accesible únicamente para usuarios o procesos autorizados.
   3. Integridad: Asegurar que los datos y recursos no sean modificados de forma no autorizada o accidental.
   4. Disponibilidad: Garantizar que los recursos y servicios del sistema estén accesibles para los usuarios legítimos cuando los necesiten
   5. Autenticación: Verificar la identidad de los usuarios y procesos antes de otorgarles acceso al sistema.
   6. Prevención de Errores Humanos: Minimizar el impacto de errores accidentales.
   7. Prevención de Colisiones y Conflictos: Evitar interferencias entre procesos o usuarios, garantizando que cada uno opere en su propio espacio.
   8. Protección frente a Amenazas Externas: Defender el sistema contra accesos no autorizados provenientes de redes o dispositivos externos.
3. Como ejemplo en un servidor compartido, propiedad de una empresa, al momento de alojar una base de datos con los clientes se debe dar acceso remoto a todos los empleados que lo necesiten, por lo tanto, el sistema operativo debe garantizar la seguridad de los datos sensibles y la disponibilidad del servicio.
### Clasificación aplicada a la seguridad
1. Clasificación de seguridad:
   1. Seguridad de hardware: Hace referencia a la protección de elementos físicos, incluyendo sistemas de alimentación ininterrumpida (SAI), cortafuegos o firewall de hardware, y módulos de seguridad de hardware (HSM).
   2. Seguridad de Software: Este concepto se refiere a la protección del software contra ataques de hackers. Incluye casos de desbordamientos de buffer, defectos de diseño o implementación, entre otros.
   3. Seguridad de red: Es un subtipo de ciberseguridad principalmente relacionado con la protección de datos en red (evitar que la información sea modificada o robada).
2. Papel de cada tipo de seguridad: 
   1.  La protección a nivel de hardware garantiza que los recursos físicos del sistema (CPU, memoria, dispositivos de E/S, etc.) se utilicen de manera segura y eficiente.
   2. Seguridad de software: La protección a nivel de software se encarga de gestionar el acceso a los recursos del sistema a través de mecanismos como permisos, autenticación y aislamiento.
   3. Seguridad de red: La protección a nivel de red garantiza la seguridad de los datos en tránsito y previene accesos no autorizados desde redes externas o internas.
3. Ejemplos prácticos:
   1. Seguridad de hardware: El hardware impide que un programa en modo usuario acceda directamente a los registros de la CPU o a la memoria del kernel, asegurando que los procesos no interfieran entre sí.
   2. Seguridad de software: Un sistema operativo como Windows utiliza listas de control de acceso (ACL) para definir qué usuarios o grupos pueden interactuar con un archivo específico.
   3. Seguridad de red: Un servidor web utiliza un certificado SSL para cifrar las conexiones HTTPS, garantizando que los datos sensibles no sean interceptados durante la transmisión.
### Funciones del sistema de protección:
1. Un sistema de acceso usa un control de acceso mediante autentificación y autorización para asegurarse que los usuarios que intenten acceder tengan los permisos y sean quienes dicen ser, además de confirmar su nivel de acceso por rol.
2. Funciones principales:
   1. Autenticación: Proceso de verificar la identidad de un usuario o proceso mediante credenciales.
   2. Autorización: Proceso de determinar qué acciones puede realizar un usuario o proceso autenticado sobre un recurso por medio de las listas de control de acceso.
   3. Control de acceso: Son el conjunto de reglas y mecanismos que regulan cómo los usuarios o procesos interactúan con los recursos.
   4. Auditoría: Registro y análisis de las actividades en el sistema para identificar accesos no autorizados o comportamientos sospechosos.
   5. Aislamiento: Garantiza que cada usuario o proceso opere en un espacio protegido e independiente.
   6. Cifrado: Proteger los datos para que solo usuarios autorizados puedan interpretarlos.
3. Ejemplo práctico:
   1. Autenticación: Un usuario ingresa su contraseña para iniciar sesión.
   2. Autorización: El sistema verifica si el usuario tiene permisos para abrir un archivo específico.
   3. Acceso Controlado: Si tiene permiso, el archivo se abre; si no, se genera un mensaje de error.
   4. Auditoría: Se registra el intento de acceso (autorizado o denegado) en un log.
   5. Aislamiento: El usuario no puede acceder a recursos asignados a otros usuarios o procesos.
### Implantación de matrices de acceso
1. *
2. *
3. *
### Protección basada en lenguaje
1. La especificación de protección en un lenguaje de programación permite la descripción de alto nivel de políticas para la asignación y uso de recursos.
2. Java utiliza un recolector de basura (Garbage Collector) para administrar la memoria automáticamente, evitando errores comunes como fugas de memoria o accesos a memoria inválida.
~~~ Java
public class MemorySafetyExample {
    public static void main(String[] args) {
        int[] array = new int[5];
        
        try {
            // Intento de acceder fuera del límite del arreglo
            array[10] = 42; 
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Intento de acceder a una posición fuera del límite del arreglo.");
        }
        
        // No se permite acceso a punteros directos
        // int *ptr = &array; // Esto no es válido en Java
        
        // Garbage Collector libera la memoria automáticamente
        MemorySafetyExample obj = new MemorySafetyExample();
        obj = null; // El objeto será eliminado por el Garbage Collector
    }
}
~~~
1. Comparación entre enfoques de protección:

|Aspecto|Protección en Lenguaje|Protección en Hardware|Protección en Software|
|---|---|---|---|
|Nivel de implementación|Compilador o tiempo de ejecución|Procesador y memoria (MMU)|Kernel y políticas del sistema|
|Rendimiento|Moderado (depende del lenguaje)|Alto (nativo en hardware)|Moderado (depende de la carga)|
Seguridad|Prevención de errores lógicos|Prevención de accesos no autorizados|Control granular sobre recursos|
|Flexibilidad|Limitada (abstracción de hardware)|Baja (dependiente del hardware)|Alta (políticas configurables)|
|Independencia|Independiente del sistema operativo|Depende del procesador|Depende del kernel del sistema|
|Casos de uso|Aplicaciones críticas de memoria|Aislamiento de procesos y seguridad|Permisos de usuarios y aplicaciones|
### Validación y amenazas al sistema
1. Tipos de amenazas:
   1. Malware: Son las amenazas más conocidas por el público no especializado en temas de informática. Se trata,  básicamente, de código con el que se infecta un programa ejecutable y que se propaga copiándose a sí mismo e infectando a otros programas o archivos.
   2. Ataques DDOS: Los ataques DDOS emplean muchos ordenadores para distribuir las peticiones al servidor. A menudo, esos equipos pertenecen a usuarios que no saben para qué se están utilizando sus ordenadores, que han sido añadidos a una red Zombie por los hackers infectándolos con malware.
   3. Rootkit: Es un software que permite a los ciber intrusos acceder a equipos sin ser detectados para robar información sensible. Los Rootkits permiten acceso privilegiado a un usuario (el hacker) ,que se conecta de forma remota, alterando el sistema operativo para ocultar la maniobra.
2. Mecanismos de validación:
   1.  Autenticación de usuarios: La autenticación verifica que una entidad (usuario o proceso) es quien dice ser antes de concederle acceso al sistema. Esto evita accesos no autorizados.
   2.  Control de acceso: El control de acceso determina quién puede acceder a recursos específicos del sistema operativo y qué acciones puede realizar.
   3.  Control de integridad: El control de integridad verifica que los datos y archivos del sistema no hayan sido alterados de manera no autorizada.
   4.  Validación de procesos y aplicaciones: El sistema operativo debe garantizar que solo procesos confiables se ejecuten y que no haya interferencias entre procesos.
   5.  Auditoría y monitoreo: La auditoría registra eventos del sistema (como accesos, modificaciones o intentos fallidos) para detectar comportamientos sospechosos.
3. *
### Cifrado
1. Cifrado simétrico y asimétrico
   1. Cifrado simétrico: En el cifrado simétrico, sólo hay una clave, y todas las partes implicadas utilizan la misma clave para cifrar y descifrar la información. Al utilizar una única clave, el proceso es sencillo.
   2. Cifrado asimétrico: El cifrado asimétrico, por otro lado, se creó para resolver el problema inherente al cifrado simétrico: la necesidad de compartir una única clave de cifrado alrededor que se utiliza tanto para cifrar como para descifrar datos.
2. Ejemplos:
   1. Cifrado simétrico: Cifrado de discos
   2. Cifrado asimétrico: Secure Shell (SSH)
3. Ejemplo práctico:
~~~C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para cifrar/descifrar usando XOR
void xor_encrypt_decrypt(const char *input_file, const char *output_file, const char *key) {
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        perror("Error al abrir los archivos");
        exit(1);
    }

    size_t key_length = strlen(key);
    unsigned char buffer;
    size_t i = 0;

    // Leer byte a byte el archivo y aplicar XOR con la clave
    while (fread(&buffer, sizeof(unsigned char), 1, fin)) {
        buffer ^= key[i % key_length]; // XOR con la clave (cifrado/descifrado)
        fwrite(&buffer, sizeof(unsigned char), 1, fout);
        i++;
    }

    fclose(fin);
    fclose(fout);
}

int main() {
    char input_file[256], output_file[256], key[256];

    // Solicitar nombres de archivo y clave
    printf("Ingrese el nombre del archivo de entrada: ");
    scanf("%255s", input_file);
    printf("Ingrese el nombre del archivo de salida: ");
    scanf("%255s", output_file);
    printf("Ingrese la clave para cifrar/descifrar: ");
    scanf("%255s", key);

    // Llamar a la función para cifrar/descifrar
    xor_encrypt_decrypt(input_file, output_file, key);

    printf("Proceso completado. El archivo resultante se guardó como '%s'.\n", output_file);
    return 0;
}

~~~