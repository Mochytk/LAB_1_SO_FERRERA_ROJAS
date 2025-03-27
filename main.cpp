#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
<<<<<<< Updated upstream
using namespace std::filesystem;
=======
namespace fs = std::filesystem;
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
    // Mostrar contenidos carpeta
    for (const auto &entrada : directory_iterator("General")) {
        ifstream archivo(entrada.path());  // Abrir el archivo
        trabajar_archivo(archivo);
    }
=======
    /*
    Vamos de a poco:
        - Primero leer la carpeta Pruebas/General
        - Empezar a leer archivo a archivo
        - Si encontramos las condiciones de Certamen, Control o Tarea
          la movemos
        - Si no, a la carpeta corruptos
        - y ya.
    */

    // Ruta de carpeta
    fs::path carpeta = "Pruebas";

    // Si no existe, crear la carpeta
    if (!fs::exists(carpeta)) {
        fs::create_directory(carpeta); 
        cout << "Carpeta creada: " << carpeta << "\n"; 
    }

    // Nombre del archivo dentro de la carpeta
    fs::path ruta_archivo = carpeta / "archivo.txt"; 

    // Crear el archivo

    ofstream archivo(ruta_archivo);

    // Si el archivo se abrió
    if (archivo.is_open()) {
        archivo << "probando\n";
        archivo.close();
        cout << "Archivo creado!" << endl;

    }
    
    // Si no
    else {
        cout << "Error al abrir el archivo!" << endl;
    }

>>>>>>> Stashed changes
    return 0;
}