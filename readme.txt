Integrantes:
Sergio Rojas 202273619-4 P.200
Martín Ferrera 202273552-k P.200

Usamos la libreria filesystem para crear las carpetas y mover los archivos.

Se probó en Arch Linux y Ubuntu WSL2; con g++ 11.4.0 y Make 4.3
Para ejecutar el programa, se debe compilar desde el directorio del proyecto de la siguiente manera:
Make
./main

Supuestos:
Los archivos makefile, main.cpp y Pruebas estan en el mismo directorio.
Además dentro de la carpeta Pruebas se encuentra la carpeta General con los archivos a trabajar.
