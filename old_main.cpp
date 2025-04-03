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

void procesar_linea(string linea, string* tipo, string* numero, string* nombre, string* semestre){
    if (linea.find("tipo:")!= string::npos){
        if (linea.find("certamen")!= string::npos) *tipo = "certamen";
        else if (linea.find("control")!= string::npos) *tipo = "control";
        else if (linea.find("tarea")!= string::npos) *tipo = "tarea";
    }
    else if (linea.find("numero:")!= string::npos) *numero = linea.substr(linea.find(":") + 2);
    else if (linea.find("nombre:")!= string::npos) *nombre = linea.substr(linea.find(":") + 2);
    else if (linea.find("semestre_publicacion:")!= string::npos) *semestre = linea.substr(linea.find(":") + 2);
}

void mover_corrupto(string& nombre_archivo){
    // aqui si el archivo es corrupto se mueve sin cambiar el nombre
    path archivo_origen = nombre_archivo;;

    // Crear el path del archivo destino
    path archivo_destino = "Output/Archivos Corruptos/" + archivo_origen.filename().string();


    // Verificar si el archivo existe antes de moverlo
    if (exists(archivo_origen)) {
        try {
            rename(archivo_origen, archivo_destino);
            cout << "Archivo movido a: " << archivo_destino << endl;
        } catch (const filesystem_error& e) {
            cerr << "Error al mover el archivo: " << e.what() << endl;
        }
    } else {
        cerr << "El archivo no existe: " << archivo_origen << endl;
    }
}

void mover_archivo_tarea(ifstream &archivo, string destino, string nombre){
    path carpeta = destino;
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }
    
    // Obtener el path original del archivo
    path archivo_origen = archivo.tellg();
    // Crear el path del archivo destino
    path archivo_destino = carpeta / nombre;
    // Mover y renombrar el archivo
    rename(archivo_origen, archivo_destino);
    cout << "Archivo movido a: " << archivo_destino << endl;
}

void mover_archivo_certamen_control(ifstream &archivo, string destino, string numero, string tipo, string semestre){
    path carpeta = destino;
    if (!exists(carpeta)) {
        create_directory(carpeta); 
    }

    string nombre_archivo;
    if (tipo == "certamen") {
        nombre_archivo = "C" + numero + "_" + semestre;
    } else {
        n
        ombre_archivo = "Q" + numero + "_" + semestre;
    }

    // Crear el path del archivo destino
    path archivo_destino = carpeta / nombre_archivo;

    // Mover el archivo al destino con el nuevo nombre
    rename(destino, archivo_destino);
    cout << "Archivo movido a: " << archivo_destino << endl;
}

void trabajar_archivo(ifstream &archivo){
    string linea;
    string tipo;
    string numero;
    string nombre;
    string semestre;
    string carpeta_destino;
    while (getline(archivo, linea)) {
        linea.pop_back();
        procesar_linea(linea, &tipo, &numero, &nombre, &semestre);
    }

    if (tipo == "certamen" && numero != "" && semestre != ""){
        carpeta_destino = "Output/Certamenes/" + semestre;
    }
    else if (tipo == "control" && numero != "" && semestre != ""){
        carpeta_destino = "Output/Controles/" + semestre;
    }
    else if (tipo == "tarea" && nombre != "" && semestre != ""){
        carpeta_destino = "Output/Tareas/" + semestre;
    }
    else{
        carpeta_destino = "Output/Archivos Corruptos";
    }

    if (carpeta_destino == "Output/Archivos Corruptos"){
        // modificar esto para pasarle el path: tipo Pruebas/nombre_archivo
        mover_corrupto(archivo);
    }
    else if (tipo == "certamen" || tipo == "control"){
        mover_archivo_certamen_control(archivo, carpeta_destino, numero, tipo, semestre);
    }
    else {
        mover_archivo_tarea(archivo, carpeta_destino, nombre);
    }

}

int main(){
    crear_output();

    for (const auto &entrada : directory_iterator("Pruebas/General")) {
        ifstream archivo(entrada.path());
        trabajar_archivo(archivo);
        archivo.close();
    }
    return 0;
}