[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/9qQbKJI7)
# Frecuencia de palabras
El programa *wordfreq* imprime las 20 palabras más frecuentes en un archivo de texto. Basado en el código en: [wordfreq.txt](http://hpca23.cse.tamu.edu/taco/utsa-www/cs2073-2.old/c/wordfreq.txt).

## Uso del programa
El programa lee texto desde STDIN y produce una lista de las 20 palabras más frecuentes. Por ejemplo:
```
$ cat sample.txt | ./wordfreq 
me	5
con	4
jueves	4
los	4
un	3
hoy	3
la	3
y	3
morire	2
en	2
paris	2
el	2
como	2
que	2
humeros	2
he	2
a	2
le	2
duro	2
aguacero	1
```
## Compilación
Para compilar el programa:
```
$ make
```
Para compilar facilitando la depuración con gdb:
```
$ make debug
```
Para compilar habilitando la herramienta *AddressSanitizer*, facilita la depuración en tiempo de ejecución.
```
$ make sanitize
```
