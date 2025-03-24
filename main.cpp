

#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std::filesystem;

int main(){

    // Ruta de carpeta
    path carpeta = "PROBANDO";

    // Si no existe, crear la carpeta
    if (!std::filesystem::exists(carpeta)) {
        std::filesystem::create_directory(carpeta); 
        std::cout << "Carpeta creada: " << carpeta 
             << std::endl; 
    }

    // Nombre del archivo dentro de la carpeta
    std::filesystem::path ruta_archivo = carpeta / "archivo.txt"; 

    // Crear el archivo

    std::ofstream archivo(ruta_archivo);

    // Si el archivo se abrió
    if (archivo.is_open()) {
        archivo << "probando\n";
        archivo.close();
        std::cout << "Archivo creado!" << std::endl;

    }
    
    // Si no
    else {
        std::cout << "Error al abrir el archivo!" << std::endl;
    }

    return 0;
}