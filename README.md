# Neutrones-en-CAB
Archivos necesarios para el procesamiento de imágenes adquiridas con un Skipper-CCD producido por Microchip para la colaboración DAMIC.

## Compresión de las imágenes con extensión .bz2
bzip2 -d imagen_comprimida.fits.bz2

bzip2 es un programa de compresión de datos que comprime de a un archivo (usa el algoritmo Burrow-Wheeler).

## Conversión imágenes crudas del CMOS a .fits
Se usa el código raw2fits.py

### Modo de uso 
$ python3 raw2fits.py /ruta_completa_conteniendo_los_archivos_a_procesar/*.*

### En PC @hipercandombe

activar el entorno py3v1 donde está instalada la librería necesaria rawpy.

eliana@hipercandombe:~$ source py3v1/bin/activate

~/Soft/CMOS/raw2fits.py

## Uso skipper2root.exe
Usage:
  /home/eliana/Soft/skipper2root/skipper2root.exe <input file> -o <output filename> 


Options:
  -s for saving the individual values of all the samples.
  -i for saving a fits image file with the averaged pixels. It will be named "proc_<input filename>.fits".
  -S for saving a fits image file with all the samples (-i must be used). It will be named "smpl_<input filename>.fits".
  -n for NOT creating an output ROOT file. User must select '-i' or '-S' option.
  -w for ignoring the OS position and using the whole image as effective OS. ONLY works if image is mostly empty.
  -r raw mode. Raw image pixel values, no subtraction of the OS mean.
  -d for overwriting the output file if it exist.

  -z <zero threshold cut in ADC> for using pixels with skPix vale smaller than zeroCut in the OS mean.
  -a <auto zero threshold cut in OS SIGMAs> for using pixels with skPix vale smaller than OS_SD*zeroCut in the OS mean.
  -b for computing a running baseline using the empty pixels. This option mus be used together with '-z' or '-a' option. 
  -R <window radius> sets the radius of the running baseline window. Only meaningful when used with the -b option. 

  -B for computing a row-by-row baseline by fitting the 0-electron peak (new method). This option overrides most of the other options. 
  -c for also fitting the column-by-column shifts when using the -B option. Ignored if there aren't enough rows for this to be useful. 
  -g <gain> sets the gain assumed (ADU/e-/ssamp, default 1.0) when fitting the 0-electron peak when using the -B option.
  -Q <quantile> sets the fraction of pixels discarded when fitting the 0-electron peak when using the -B option. Use a large value if many pixels have crosstalk. 

  -H if the first sample of a high-charge pixel is much bigger than the rest, use the first sample. 
  -f ignore the first sample. 
  -N ignore rows with a large number of noisy pixels (too many pixels in the tails of the 0e Gaussian). 
  -p don't check the pixel counts (normally we error out if NPIX != NSAMP*NCOL*NROW). 

  -q quiet
  -v verbose
  -h this help message



