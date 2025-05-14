#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct QA {
    std::string pregunta;
    std::string respuesta;
};

// Función para convertir texto a minúsculas
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Leer conocimiento desde archivo
std::vector<QA> cargarConocimiento(const std::string& nombreArchivo) {
    std::vector<QA> baseConocimiento;
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    while (getline(archivo, linea)) {
        size_t pos = linea.find('|');
        if (pos != std::string::npos) {
            QA entrada;
            entrada.pregunta = linea.substr(0, pos);
            entrada.respuesta = linea.substr(pos + 1);
            baseConocimiento.push_back(entrada);
        }
    }

    return baseConocimiento;
}

// Buscar respuesta a partir de pregunta
std::string buscarRespuesta(const std::string& preguntaUsuario, const std::vector<QA>& baseConocimiento) {
    std::string preguntaLower = toLower(preguntaUsuario);

    for (const auto& qa : baseConocimiento) {
        if (toLower(qa.pregunta).find(preguntaLower) != std::string::npos) {
            return qa.respuesta;
        }
    }

    return "Lo siento, no tengo una respuesta para esa pregunta.";
}

// Registrar pregunta en archivo de log
void registrarPregunta(const std::string& pregunta, const std::string& archivoLog = "log.txt") {
    std::ofstream log(archivoLog, std::ios::app);
    log << pregunta << std::endl;
}

int main() {
    std::vector<QA> conocimiento = cargarConocimiento("conocimiento.txt");
    std::string preguntaUsuario;

    std::cout << "Hola Soy GalletaBot. Preguntame algo sobre galletas.\n";

    while (true) {
        std::cout << "\nTu: ";
        getline(std::cin, preguntaUsuario);

        if (preguntaUsuario == "salir") {
            break;
        }

        registrarPregunta(preguntaUsuario);

        std::string respuesta = buscarRespuesta(preguntaUsuario, conocimiento);
        std::cout << "GalletaBot: " << respuesta << "\n";
    }

    std::cout << "¡Hasta luego!\n";
    return 0;
}
