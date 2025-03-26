

#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

int main(){
    // crear carpeta base
    path carpeta = "Output";
    // Si no existe, crear la carpeta
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }

    // Mostrar contenidos carpeta
    for (const auto &i : directory_iterator("General")) {
        ifstream archivo(i.path());  // Abrir el archivo directamente

        string linea;
        while (getline(archivo, linea)) {  // Leer todas las líneas
            if (linea.find("tipo:")){

            }
            else if (linea.find("numero:")){

            }
            else if (linea.find("semestre_publicacion:")){

            }
        }
    }


    return 0;
}