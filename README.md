# Neutrones-en-CAB
Archivos necesarios para el procesamiento de imágenes adquiridas con un Skipper-CCD producido por Microchip para la colaboración DAMIC.

## Compresión de las imágenes con extensión .bz2
bzip2 -d imagen_comprimida.fits.bz2

bzip2 es un programa de compresión de datos que comprime de a un archivo (usa el algoritmo Burrow-Wheeler).

## Conversión imágenes crudas del CMOS a .fits
Se usa el código raw2fits.py
$Modo de uso$ 
$ python3 raw2fits.py /ruta_completa_conteniendo_los_archivos_a_procesar/*.*

En PC @hipercandombe activar el entorno py3v1 donde está instalada la librería necesaria rawpy.
eliana@hipercandombe:~$ source py3v1/bin/activate

