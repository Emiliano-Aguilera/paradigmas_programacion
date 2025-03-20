#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// Prototipos de funcion
bool compareString (const char*, const char*, int);

// Funcion recursiva que compara strings en tiempo de compilacion, no se puede declarar como prototipo.
consteval bool compareStringConst (const char* s1, const char* s2, int position) {
    /* 
    Si ambos caracteres son iguales, y el caracter siguiente no es el final de string,
    entonces entra en recursividad, esto va a suceder hasta que se llegue al final de
    la string, o hasta que haya 2 caracteres distintos(s1[position] != s2[position]).
    */
    if (s1[position] == s2[position] && s1[position + 1] != '\0'){
        return compareStringConst(s1, s2, position + 1);
    }
    else if (s1[position] == s2[position] && s1[position + 1] == '\0') {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    // Test 1: checkear 2 strings iguales que midan mas de 64 caracteres

    constexpr const char* string1 = "Estas strings son identicas, pero deben tener 64 caracteres como minimo";

    cout << "Resultado test 1" << endl;

    // Tomar el tiempo que le toma comparar 2 strings iguales en runtime
    // Tiempo de inicio
    auto startTime = high_resolution_clock::now();

    // Ejecutar comparacion
    bool result1 = compareString(string1, string1, 0);

    // Tomar tiempo de fin
    auto endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime = (endTime - startTime);
    
    cout << "Tiempo en runtime: " << elapsedTime.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << result1 << endl;


    // Comparacion en compilacion
    startTime = high_resolution_clock::now();   
    const bool result2 = compareStringConst(string1, string1, 0);
    endTime = high_resolution_clock::now();

    elapsedTime = duration_cast<nanoseconds>(endTime - startTime);
    
    cout << "Tiempo en compilacion: " << elapsedTime.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << result2 << endl;


    // Separador entre tests
    cout << "_______________________________" << endl;


    // Test 2
    // Compara 2 strings distintas, que solo difieren en el ultimo caracter, y miden mas de 64 caracteres de largo

    constexpr const char* string2 = "Estas strings son distintas, deberia medir mas de 64 caracteres de largo:";
    constexpr const char* string3 = "Estas strings son distintas, deberia medir mas de 64 caracteres de largo;";

    cout << "Resultado test 2" << endl;

    // Comparacion en runtime
    startTime = high_resolution_clock::now();
    bool result3 = compareString(string2, string3, 0);
    endTime = high_resolution_clock::now();
    elapsedTime = (endTime - startTime);
    
    cout << "Tiempo en runtime: " << elapsedTime.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << result3 << endl;

    // Comparacion en compilacion
    startTime = high_resolution_clock::now();   
    const bool result4 = compareStringConst(string2, string3, 0);
    endTime = high_resolution_clock::now();
    
    elapsedTime = duration_cast<nanoseconds>(endTime - startTime);
    
    cout << "Tiempo en compilacion: " << elapsedTime.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << result4 << endl;

    return 0;
}

// Funcion recursiva que compara strings en runtime
bool compareString (const char* s1, const char* s2, int position) {
    /* 
    Si ambos caracteres son iguales, y el caracter siguiente no es el final de string,
    entonces entra en recursividad, esto va a suceder hasta que se llegue al final de
    la string, o hasta que haya 2 caracteres distintos(s1[position] != s2[position]).
    */
    if (s1[position] == s2[position] && s1[position + 1] != '\0'){
        return compareString(s1, s2, position + 1);
    }
    else if (s1[position] == s2[position] && s1[position + 1] == '\0') {
        return true;
    }
    else {
        return false;
    }
}