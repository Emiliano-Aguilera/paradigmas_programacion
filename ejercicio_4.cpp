#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

// Prototipo de funcion
bool compareString (const char*, const char*, int);
constexpr bool compareString_const (const char*, const char*, int);
void testCompareString(const char*, const char*);
void testCompareString_const(const char*, const char*);

int main() {
    // Test 1
    const char* string_1 = "Estas strings son identicas, pero deben tener 64 caracteres como minimo";
    const char* string_2 = "Estas strings son identicas, pero deben tener 64 caracteres como minimo";

    cout << "Resultado test 1" << endl;
    // Ejercicio 4a y 4b
    testCompareString(string_1, string_2);
    // Ejercicio 4c
    testCompareString_const(string_1, string_2);

    cout << "_______________________________" << endl;
    // Test 2
    const char* string_3 = "Estas strings son distintas, deberia medir mas de 64 caracteres de largo:";
    const char* string_4 = "Estas strings son distintas, deberia medir mas de 64 caracteres de largo;";

    cout << "Resultado test 2" << endl;
    // Ejercicio 4a y 4b
    testCompareString(string_3, string_4);
    // Ejercicio 4c
    testCompareString_const(string_3, string_4);

    return 0;
}

bool compareString (const char* s1, const char* s2, int position) {
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

constexpr bool compareString_const (const char* s1, const char* s2, int position) {
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

void testCompareString(const char* s1, const char* s2) {
    // Tomar tiempo de inicio
    auto startTime = high_resolution_clock::now();
    // Ejecutar comparacion
    bool resultado = compareString(s1, s2, 0);
    // Tomar tiempo de fin
    auto endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime = (endTime - startTime);
    
    cout << "Tiempo en runtime: " << elapsedTime.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << resultado << endl;
}

void testCompareString_const(const char* s1, const char* s2) {
    // Tomar tiempo de inicio
    auto startTime_c = high_resolution_clock::now();   
    // Ejecutar comparacion
    bool resultado_c = compareString_const(s1, s2, 0);
    // Tomar tiempo de fin
    auto endTime_c = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime_c = duration_cast<nanoseconds>(endTime_c - startTime_c);
    
    cout << "Tiempo en compilacion: " << elapsedTime_c.count() << "[ns]" << endl;
    cout << "Resultado: " << boolalpha << resultado_c << endl;
}