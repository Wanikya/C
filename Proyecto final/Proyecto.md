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