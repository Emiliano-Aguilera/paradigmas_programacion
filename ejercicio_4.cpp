#include <iostream>
#include <chrono>

bool compareString (const char*, const char*, int);
constexpr bool compareString_const (const char*, const char*, int);



int main() {
    const char* string_1 = "abababababab";
    const char* string_2 = "abababababab";

    // Ejercicio 4a y 4b
    auto startTime = std::chrono::high_resolution_clock::now();
    std::cout << "Resultado: ";
    std::cout << std::boolalpha <<  compareString(string_1, string_2, 0);
    std::cout << std::endl;
    auto endTime = std::chrono::high_resolution_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "Tiempo en runtime: ";
    std::cout << elapsedTime.count() << "[ns]";
    std::cout << std::endl;

    // Ejercicio 4c
    startTime = std::chrono::high_resolution_clock::now();    
    std::cout << "Resultado: ";
    std::cout << std::boolalpha << compareString_const(string_1, string_2, 0);
    std::cout << std::endl;
    endTime = std::chrono::high_resolution_clock::now();

    elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "Tiempo en compilacion: ";
    std::cout << elapsedTime.count() << "[ns]";
    std::cout << std::endl;

    return 0;
}

bool compareString (const char* s1, const char* s2, int position) {
    int length = sizeof(s1) / sizeof(char);
    int length_1 = sizeof(s1) / sizeof(char);

    if (length != length_1) {
        return false;
    }
    if (s1[position] == s2[position] && position < length){
        return compareString(s1, s2, position + 1);
    } 
    else if (s1[position] == s2[position] && position == length) {
        return true;
    }
    else {
        return false;
    }
}

constexpr bool compareString_const (const char* s1, const char* s2, int position) {
    int length = sizeof(s1) / sizeof(char);
    int length_1 = sizeof(s1) / sizeof(char);

    if (length != length_1) {
        return false;
    }
    if (s1[position] == s2[position] && position < length){
        return compareString(s1, s2, position + 1);
    } 
    else if (s1[position] == s2[position] && position == length) {
        return true;
    }
    else {
        return false;
    }
}