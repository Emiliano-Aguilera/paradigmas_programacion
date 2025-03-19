#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// Prototipos de funcion
bool compareString (const char*, const char*, int);
constexpr bool compareStringConst (const char*, const char*, int);
void testCompareString(const char*, const char*);
void testCompareStringConst(const char*, const char*);

int main() {
    // Test 1: checkear 2 strings iguales que midan mas de 64 caracteres
    /* Se usa char* ya que string no se puede hacer constexpr porque esta basada en
    un vector, el cual usa memoria dinamica, lo que lo hace incompatible con ejecucion en compilacion */
    const char* string1 = "Estas strings son identicas, pero deben tener 64 caracteres como minimo";

    cout << "Resultado test 1" << endl;
    // Ejercicio 4a y 4b
    // Llama a la funcion que compara strings en ejecucion, y toma el tiempo de ejecucion
    testCompareString(string1, string1);

    // Ejercicio 4c
    // Llama a la funcion que compara strings en compilacion, y toma el tiempo de ejecucion
    testCompareStringConst(string1, string1);

    // Separador entre tests
    cout << "_______________________________" << endl;
    // Test 2
    // Compara 2 strings distintas, que solo difieren en el ultimo caracter, y miden mas de 64 caracteres de largo
    const char* string2 = "Estas strings son distintas, deberia medir mas de 64 caracteres de largo:";
    const char* string3 = "Estas strings son distintas, deberia medir mas de 64 caracteres de largo;";

    cout << "Resultado test 2" << endl;

    // Ejercicio 4a y 4b
    // Llama a la funcion que compara strings en ejecucion, y toma el tiempo de ejecucion
    testCompareString(string2, string3);

    // Ejercicio 4c
    // Llama a la funcion que compara strings en compilacion, y toma el tiempo de ejecucion(en compilacion)
    testCompareStringConst(string2, string3);

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

// Funcion recursiva que compara strings en tiempo de compilacion
constexpr bool CompareStringConst (const char* s1, const char* s2, int position) {
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

/* Funcion que ejecuta la funcion para comparar strings en runtime,
toma el tiempo de ejecucion de la misma, y lo muestra por consola. */
void testCompareString(const char* s1, const char* s2) {
    // Tomar tiempo de inicio
    auto startTime = high_resolution_clock::now();
    // Ejecutar comparacion
    bool result = compareString(s1, s2, 0);
    // Tomar tiempo de fin
    auto endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime = (endTime - startTime);
    
    cout << "Tiempo en runtime: " << elapsedTime.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << result << endl;
}

/* Funcion que ejecuta la funcion para comparar strings en compilacion,
toma el tiempo de ejecucion de la misma, y lo muestra por consola. */
void testCompareStringConst(const char* s1, const char* s2) {
    // Tomar tiempo de inicio
    auto startTime = high_resolution_clock::now();   
    // Ejecutar comparacion
    bool result = CompareStringConst(s1, s2, 0);
    // Tomar tiempo de fin
    auto endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime_c = duration_cast<nanoseconds>(endTime - startTime);
    
    cout << "Tiempo en compilacion: " << elapsedTime_c.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << result << endl;
}