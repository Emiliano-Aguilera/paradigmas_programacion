#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <stdexcept>

using namespace std;

// Prototipos de funcion
// logMessage normal
void logMessage(string, int); 
// logMessage error en linea de archivo
void logMessage(string, string, int); 
// logMessage seguridad de usuario
void logMessage(string, string); 

// Funcion que ejecuta los tests
int testLogMessage();

// LAST no es valido, se usa para poder añadir nuevas tags sin necesidad de modificar el check
enum TAGS {DEBUG, INFO, WARNING, ERROR, CRITICAL, SECURITY, LAST};
const string tagStrings[] = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL", "SECURITY"};

int main() {
    return testLogMessage();
}

// Ejercicio a
void logMessage(string message, int tag) {
    // Abre el archivo en modo append
    ofstream outFile("log.txt", ios::app);
    string tagString;

    /* Checkea que el tag usado sea correcto, de lo contrario inserta un tag de error con el 
    mensaje de error */
    if (tag >= DEBUG && tag < LAST) {
        // Accede a la string correspondiente al tag
        tagString = tagStrings[tag];

        // Check de que el archivo se abrio correctamente
        if (outFile.is_open()) {
            // Escribir en el archivo el mensaje con su tag correspondiente
            outFile << format("[{}] <{}>\n", tagString, message);
        } else {
            // Si hay un error, lanza un runtime error, que es manejado por test_LogMessage
            throw runtime_error("Error abriendo archivo");
        }
    } else {
        /* En el caso de que el tag ingresado sea invalido, va a lanzar un runtime error,
        el error va a contener el tag invalido y el mensaje que se intento loggear */ 
        string runtimeMessage = format(
            "Tag invalido: {}, Mensaje: \"{}\"", tag, message);
        throw runtime_error(runtimeMessage);
    }
}

// Ejercicio b
// Ejercicio II
// Sobrecarga de logMessage que permite loggear un error en la linea de un archivo
void logMessage(string message, string file, int line) {
    // Se crea una string que contiene el mensaje, la linea y el archivo
    string errorMessage = format(
        "{} en la linea {} del archivo {}", message, line, file);
    /* Una vez creada la string que contiene el mensaje correspondiente, se usa la 
    funcion original para loggear el error */
    logMessage(errorMessage, ERROR);
}

// Ejercicio III
// Sobrecarga de logMessage que loggea el acceso o no de un usuario
void logMessage(string message, string username) {
    // Crea la string con el mensaje y el usuario
    string accessMessage = format("{} to {}", message, username);
     // Usa la funcion original para loggear el mensaje con el tag SECURITY
    logMessage(accessMessage, SECURITY);
}

// Ejercicio IV
/* Funcion que ejecuta logMessage con distintas entradas, maneja los posibles runtime errors 
y detiene la ejecucion, retornando 1 y haciendo que main retorne 1. */
int testLogMessage() {
    // Intenta ejecutar el codigo, y maneja los errores
    try {
        // Una entrada de cada tipo para logMessage (ejercicio a)
        for (int i = DEBUG; i < LAST; i++) {
            logMessage(format("{} test message.", tagStrings[i]), i);
        }

        // Una entrada de tipo ERROR que especifica la linea y el archivo (ejercicio b II)
        logMessage("Syntax Error", "ejercicio_1.cpp", 25);

        // Una entrada de tipo Security que loggea el acceso de un usuario (ejercicio b III)
        logMessage("Access Granted", "emiag");

        // Una entrada con un tipo invalido, genera un log tipo ERROR
        logMessage("Mensaje con error", 666);

        // Mensaje de log valido que nunca se va a ejecutar debido al error de arriba
        logMessage("Mensaje valido", WARNING);
        
        return 0;
    }
    catch (runtime_error& e) {
        /* En caso de runtime error, e.what() devuelve el mensaje/traceback, lo que sera el 
        mensaje del log de tipo ERROR que se crea */
        logMessage(e.what(), ERROR);
        // Devuelve 1 como especifica la consiga, para que main temine con error
        return 1;
    } 
    catch (...) {
        // Cualquier otro error, se va a generar una entrada de log 
        logMessage("Algo salio mal, error desconocido", ERROR);
        // Devuelve 1 como especifica la consiga, para que main temine con error
        return 1;
    }
}