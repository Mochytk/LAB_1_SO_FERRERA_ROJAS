#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

void crear_output() {
    /*
        
        Parametros:
        No tiene
        
        ******************************
        
        Retorno:
        No tiene

        ******************************

        Qué hace?
        Crea las carpetas de las distintas categorias en un carpeta común llamada Output

    */
    create_directories("Output/Certamenes");
    create_directories("Output/Controles");
    create_directories("Output/Tareas");
    create_directories("Output/Archivos Corruptos");
}

void procesar_linea(string linea, string* tipo, string* numero, string* nombre, string* semestre) {    
    /*
        
        Parametros:
        
        - string linea: Cadena de texto con la información a procesar.
        - string* tipo: Puntero para almacenar el tipo de evaluación (certamen/control/tarea).
        - string* numero: Puntero para almacenar el número del certamen/control en caso de ser de ese tipo.
        - string* nombre: Puntero para almacenar el nombre de la tarea en caso de ser de ese tipo.
        - string* semestre: Puntero para almacenar el semestre de publicación.
        
        ******************************
        
        Retorno:
        
        - void: La función no retorna valores, sólo modifica los parámetros por referencia.

        ******************************

        Qué hace?
        
        Procesa una línea de texto para extraer información específica:
        1. Detecta si la línea contiene "tipo:" y clasifica en certamen/control/tarea
        2. Si encuentra "numero:", "nombre:" o "semestre_publicacion:", extrae el valor
           después de los dos puntos y el espacio hasta el final de la linea
        3. Almacena los resultados en las variables apuntadas por los punteros
    
    */
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
    /*
        
        Parametros:
        - const path& archivo_origen: Ruta del archivo corrupto a mover
        
        ******************************
        
        Retorno:
        No tiene, solo mueve el archivo sin modificar el nombre

        ******************************

        Qué hace?
        1. Crea la carpeta "Archivos Corruptos" en caso de que no exista
        2. Crea la ruta destino del archivo corrupto, conservando el nombre como exige el formato del Lab
        3. Busca el archivo que hay que mover, si este existe, lo mueve con rename a la carpeta corruptos, 
        si no, da un mensaje de error

    */
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
    /*
        
        Parametros:
        - const path& archivo_origen: Ruta del archivo original que se moverá.  
        - const string& destino: Ruta de la carpeta destino donde se almacenará el archivo.  
        - const string& nombre: Nuevo nombre que tendrá el archivo en el destino, el de la tarea, como exige el formato.  
        
        ******************************
        
        Retorno:
        No tiene, solo mueve el archivo modificando el nombre según el fórmato

        ******************************

        Qué hace?
        1. Crea la carpeta destino (incluyendo subdirectorios) si no existe.  
        2. Construye la ruta completa destino combinando el directorio y el nuevo nombre.  
        3. Intenta mover/renombrar el archivo usando rename():  
           - Si tiene éxito, muestra confirmación con la ruta destino  
           - Si falla, captura filesystem_error y muestra el error  

    */
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
    /*  
        
        Parametros:  
        
        - const path& archivo_origen: Ruta del archivo original a mover (tipo filesystem::path).  
        - const string& destino: Directorio destino donde se colocará el archivo.  
        - const string& numero: Número identificador del certamen/control.  
        - const string& tipo: Tipo de evaluación ("certamen" o "control").  
        - const string& semestre: Semestre asociado al archivo (formato texto).  
        
        ******************************  
        
        Retorno:  
        
        No tiene, solo mueve el archivo modificando el nombre según el fórmato
        
        ******************************  
        
        Qué hace?  
        
        1. Crea la carpeta destino (con todos los subdirectorios necesarios).  
        2. Genera el nombre del archivo según el tipo:  
           - Certamen: Prefijo "C" + número + "_" + semestre (Ej: C3_2024-1)  
           - Control: Prefijo "Q" + número + "_" + semestre (Ej: Q2_2023-2)  
        3. Construye la ruta completa destino combinando directorio y nombre generado.  
        4. Intenta mover/renombrar el archivo:  
           - Muestra confirmación con ruta final si éxito  
           - Captura errores de filesystem y muestra detalles  
    
    */  
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
    /*  
        
        Parametros:  
        
        - const path& file_path: Ruta del archivo a procesar.  
        
        ******************************  
        
        Retorno:  
        
        - void: No retorna valores. Coordina el procesamiento y movimiento de archivos.  
        
        ******************************  
        
        Qué hace?  
        
        1. Abre el archivo y valida su apertura (muestra error si falla).  
        2. Lee línea por línea el contenido:  
           - Elimina saltos de linea (\n) si existen
           - Usa procesar_linea() para extraer información del archivo (tipo, número, nombre, semestre)  
        3. Determina la carpeta destino según:  
           - Certamen: Output/Certamenes/[semestre] (requiere número y semestre válidos)
           - Control: Output/Controles/[semestre] (requiere número y semestre válidos)
           - Tarea: Output/Tareas/[semestre] (requiere nombre y semestre válidos)
           - Archivo corrupto: Output/Archivos Corruptos (si falta información o semestre > 2025-2) (En el foro dijeron que las tareas de este año para atrás eran válidas)  
        4. Ejecuta el movimiento según tipo:  
           - Archivos corruptos: usa mover_corrupto()  
           - Certamenes/Controles: usa mover_archivo_certamen_control()  
           - Tareas: usa mover_archivo_tarea()  

    */  
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

    if (carpeta_destino == "Output/Archivos Corruptos" || semestre > "2025-2") {
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