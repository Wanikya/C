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
2. Comparación entre EXT4 y NTFS.*

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
         1. 