#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <stdexcept>

using namespace std;

// Prototipos de funcion
void logMessage(string, int tag); // logMessage normal
void logMessage(string message, string archivo, int linea); // logMessage error en linea de archivo
void logMessage(string message, string username); // logMessage seguridad de usuario

int test_logMessage();

// LAST no es valido, se usa para poder añadir nuevas tags sin necesidad de modificar el check
enum TAGS {DEBUG, INFO, WARNING, ERROR, CRITICAL, SECURITY, LAST};
const string tagStrings[] = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL", "SECURITY"};

int main() {
    return test_logMessage();
}

// Ejercicio a
void logMessage(string message, int tag) {
    // Abre el archivo en modo append
    ofstream outFile("log.txt", ios::app);
    string tag_string;

    /* Checkea que el tag usado sea correcto, de lo contrario inserta un tag de error con el 
        mensaje de error*/
    if (tag >= DEBUG && tag < LAST) {
        tag_string = tagStrings[tag];

        if (outFile.is_open()) {
            outFile << format("[{}] <{}>\n", tag_string, message);
        } else {
            throw runtime_error("Error abriendo archivo");
        }
    } else {
        string runtimeMessage = format(
            "Tag invalido: {}, Mensaje: \"{}\"", tag, message);
        throw runtime_error(runtimeMessage);
    }
}

// Ejercicio b
// Ejercicio II
void logMessage(string message, string archivo, int linea) {
    string errorMessage = format(
        "{} en la linea {} del archivo {}", message, linea, archivo);
    logMessage(errorMessage, ERROR);
}

// Ejercicio III
void logMessage(string message, string username){
    string accessMessage = format("{} to {}", message, username);
    logMessage(accessMessage, SECURITY);
}

// Ejercicio IV
int test_logMessage() {
    try {
        // Una entrada de cada tipo para logMessage (ejercicio a)
        for (int i = DEBUG; i <= CRITICAL; i++) {
            logMessage(format("{} test message.", tagStrings[i]), i);
        }
        // Una entrada de tipo ERROR que especifica la linea y el archivo (ejercicio b II)
        logMessage("Syntax Error", "ejercicio_1.cpp", 25);

        // Una entrada de tipo Security que loggea el acceso de un usuario (ejercicio b III)
        logMessage("Access Granted", "emiag");

        // Una entrada con un tipo invalido, genera un log tipo ERROR
        logMessage("Mensaje con error", 666);

        // Mensaje de log valido que nunca se va a ejecutar
        logMessage("Mensaje valido", WARNING);
        
        return 0;
    } 
    catch (runtime_error& e) {
        logMessage(e.what(), ERROR);
        return 1;
    } 
    catch (...) {
        logMessage("Algo salio mal, error desconocido", ERROR);
        return 1;
    }
}