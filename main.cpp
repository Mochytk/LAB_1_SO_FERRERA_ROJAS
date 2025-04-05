#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

void crear_output() {
    create_directories("Output/Certamenes");
    create_directories("Output/Controles");
    create_directories("Output/Tareas");
    create_directories("Output/Archivos Corruptos");
}

void procesar_linea(string linea, string* tipo, string* numero, string* nombre, string* semestre) {
    if (linea.find("tipo:") != string::npos) {
        if (linea.find("certamen") != string::npos) *tipo = "certamen";
        else if (linea.find("control") != string::npos) *tipo = "control";
        else if (linea.find("tarea") != string::npos) *tipo = "tarea";
    }
    else if (linea.find("numero:") != string::npos) *numero = linea.substr(linea.find(":") + 2);
    else if (linea.find("nombre:") != string::npos) *nombre = linea.substr(linea.find(":") + 2);
    else if (linea.find("semestre_publicacion:") != string::npos) *semestre = linea.substr(linea.find(":") + 2);
}

void mover_corrupto(const path& archivo_origen) {
    path destino_dir = "Output/Archivos Corruptos";
    create_directories(destino_dir);

    path archivo_destino = destino_dir / archivo_origen.filename();

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

void mover_archivo_tarea(const path& archivo_origen, const string& destino, const string& nombre) {
    path carpeta_destino = destino;
    create_directories(carpeta_destino);

    path archivo_destino = carpeta_destino / nombre;

    try {
        rename(archivo_origen, archivo_destino);
        cout << "Archivo movido a: " << archivo_destino << endl;
    } catch (const filesystem_error& e) {
        cerr << "Error al mover la tarea: " << e.what() << endl;
    }
}

void mover_archivo_certamen_control(const path& archivo_origen, const string& destino, const string& numero, const string& tipo, const string& semestre) {
    path carpeta_destino = destino;
    create_directories(carpeta_destino);

    string nombre_archivo;
    if (tipo == "certamen") {
        nombre_archivo = string("C") + numero + "_" + semestre;
    } else {
        nombre_archivo = string("Q") + numero + "_" + semestre;
    }

    path archivo_destino = carpeta_destino / nombre_archivo;

    try {
        rename(archivo_origen, archivo_destino);
        cout << "Archivo movido a: " << archivo_destino << endl;
    } catch (const filesystem_error& e) {
        cerr << "Error al mover el archivo: " << e.what() << endl;
    }
}

void trabajar_archivo(const path& file_path) {
    ifstream archivo(file_path);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << file_path << endl;
        return;
    }

    string linea;
    string tipo, numero, nombre, semestre;
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        procesar_linea(linea, &tipo, &numero, &nombre, &semestre);
    }
    archivo.close();

    string carpeta_destino;
    if (tipo == "certamen" && !numero.empty() && !semestre.empty()) {
        carpeta_destino = "Output/Certamenes/" + semestre;
    } else if (tipo == "control" && !numero.empty() && !semestre.empty()) {
        carpeta_destino = "Output/Controles/" + semestre;
    } else if (tipo == "tarea" && !nombre.empty() && !semestre.empty()) {
        carpeta_destino = "Output/Tareas/" + semestre;
    } else {
        carpeta_destino = "Output/Archivos Corruptos";
    }

    if (carpeta_destino == "Output/Archivos Corruptos" || semestre > "2025-1") {
        mover_corrupto(file_path);
    } 
    else if (tipo == "certamen" || tipo == "control") {
        mover_archivo_certamen_control(file_path, carpeta_destino, numero, tipo, semestre);
    }
    else {
        mover_archivo_tarea(file_path, carpeta_destino, nombre);
    }
}

int main() {
    crear_output();

    for (const auto& entrada : directory_iterator("Pruebas/General")) {
        if (is_regular_file(entrada.path())) {
            trabajar_archivo(entrada.path());
        }
    }

    return 0;
}