

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
    carpeta = "Output/Certamenes";
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }

    //crear carpeta controles
    carpeta = "Output/Controles";
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }

    //crear carpeta tareas
    carpeta = "Output/Tareas";
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }

    //crear carpeta archivos corruptos
    carpeta = "Output/Archivos Corruptos";
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }
}

void procesar_linea(string linea, string* tipo, string* numero, string* semestre){
    if (linea.find("tipo:")){
        //if (linea.find("certamen")) tipo -> "certamen";
        //else if (linea.find("control")) tipo -> "control";
        //else if (linea.find("tarea")) tipo -> "tarea";
    }
    else if (linea.find("numero:")){

    }
    else if (linea.find("semestre_publicacion:")){

    }
}

void trabajar_archivo(ifstream &archivo){
    string linea;
    string* tipo;
    string* numero;
    string* semestre;
    while (getline(archivo, linea)) {  // Leer todas las líneas
        procesar_linea(linea, tipo, numero, semestre);
    }
    if (*tipo == "" || *numero == "" || *semestre == ""){

    }
}

int main(){
    crear_output();

    // Mostrar contenidos carpeta
    for (const auto &entrada : directory_iterator("General")) {
        ifstream archivo(entrada.path());  // Abrir el archivo
        trabajar_archivo(archivo);
    }
    return 0;
}