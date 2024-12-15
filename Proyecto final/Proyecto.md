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
### Organización lógica y física 
1. *
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
2. 