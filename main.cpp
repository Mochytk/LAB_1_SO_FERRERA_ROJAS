

#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

void crear_output(){
    //crear carpeta output
    path carpeta = "Output";
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }

    //crear carpeta certamenes
    path carpeta = "Output/Certamenes";
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }

    //crear carpeta controles
    //crear carpeta tareas
    //crear carpeta archivos corruptos
}


//void dividir_archivo(filesystem archivo){
//    ifstream archivo(archivo.path());  // Abrir el archivo directamente
//    string linea;
//    string tipo;
//    string numero;
//    string semestre;
//    while (getline(archivo, linea)) {  // Leer todas las líneas
//        procesar_linea(linea);
//    }
//    if (tipo == NULL || numero == NULL || semestre == NULL){
//
//    }
//}

//void procesar_linea(string linea){
//    if (linea.find("tipo:")){
//
//    }
//    else if (linea.find("numero:")){
//
//    }
//    else if (linea.find("semestre_publicacion:")){
//
//    }
//}


int main(){
    crear_output();

    // Mostrar contenidos carpeta
    for (const auto &archivo : directory_iterator("General")) {
        //dividir_archivo(archivo);
    }
    return 0;
}