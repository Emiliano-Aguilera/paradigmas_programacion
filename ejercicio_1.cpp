#include <iostream>
#include <format>
#include <vector>
#include <chrono>

/*
Resolucion del ejercicio 1 del Homework 1
Se debe crear una matriz cuadrada de tamaño n y rellenarla con valores desde n hasta n^2
Luego se debe crear una funcion que imprima la matriz usando un solo loop.
    Para este inciso, se me ocurrieron dos formas distintas de llegar a una solucion,
    la primera usa condicionales y la segunda una relacion entre el indice y la posicion en la matriz.
    Deje ambas soluciones porque luego de testear el tiempo que toman noto que es muy similar. 
*/

using namespace std;
using namespace chrono;
using vector_int =  vector<vector<int>>;

// prototipos de funcion
vector_int createMatrix(int size);
void printMatrix(vector_int matrix);
void printMatrix_b(vector_int matrix);
void compareSolutions();

int main() {
    int n = 0;

    cout << "Ingrese n: ";
    cin >> n;

    // check de que el usuario esta ingresando un tamaño valido
    while (n <= 1) {
        cout << "n debe ser mayor a 1." << '\n';
        cout << "Ingrese n: ";
        cin >> n;
    }
    
    vector_int matrix = createMatrix(n);

    // Imprimir matriz
    printMatrix(matrix);
    //printMatrix_b(matrix, n);

    
    // compara ambos metodos de printeo usando 2 <= n <= 100
    auto startTime = high_resolution_clock::now();
    // Ejecutar comparacion
    compareSolutions();
    // Tomar tiempo de fin
    auto endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime = (endTime - startTime);

    cout << "Tiempo total: " << elapsedTime << endl;
    

    return 0;
}

// declaracion de funciones
vector_int createMatrix(int size) {
    vector_int matrix (size);

    for (int i = 0; i < size; i++){
        matrix[i] = vector<int> (size); 
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // parentesis redundantes, mejoran legibilidad
            int value = (i * size) + (j+1);
            matrix[i][j] = value;
        }
    }

    return matrix;
}

void printMatrix(vector_int matrix) {
    int size = matrix.size();
    // Intento de iterar inversamente la matriz sin usar condicionales
    for (int k = 0; k < size*size; k++) {
        int i = size - (k / size) - 1;
        int j = size - (k % size) - 1;
        cout << format("M[{}][{}] = {}\n", i, j, matrix[i][j]);
    }
}

void printMatrix_b(vector_int matrix) {
    int size = matrix.size();

    int i = size-1;
    int j = size-1;
    
    for (int k = 0; k < size*size; k++) {
        cout << format("M[{}][{}] = {}\n", i, j, matrix[i][j]);
        if (j == 0) {
            i--;
            j = size-1;
        }
        else {
            j--;
        }
    }
}

void compareSolutions() {
    vector_int matrix = createMatrix(2);
    // Tomar el tiempo que toma imprimir con el metodo de condicionales
    auto startTime = high_resolution_clock::now();
    // Ejecutar comparacion
    printMatrix(matrix);
    // Tomar tiempo de fin
    auto endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime_1 = (endTime - startTime);
    
    startTime = high_resolution_clock::now();
    // Ejecutar comparacion
    printMatrix_b(matrix);
    // Tomar tiempo de fin
    endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime_2 = (endTime - startTime);

    auto t_1 = elapsedTime_1;
    auto t_2 = elapsedTime_2;

    int precision = 100;

    for (int i = 3; i < precision; i++) {
        vector_int matrix = createMatrix(i);
        // Tomar el tiempo que toma imprimir con el metodo de condicionales
        startTime = high_resolution_clock::now();
        printMatrix(matrix);
        endTime = high_resolution_clock::now();

        // Calcular diferencia entre los tiempos
        elapsedTime_1 = (endTime - startTime);
        t_1 += elapsedTime_1;


        startTime = high_resolution_clock::now();
        printMatrix_b(matrix);
        endTime = high_resolution_clock::now();

        // Calcular diferencia entre los tiempos
        elapsedTime_2 = (endTime - startTime);      
        t_2 += elapsedTime_2;
    }

    auto tiempo_promedio_1 = t_1 / precision;
    auto tiempo_promedio_2 = t_2 / precision;

    cout << "Tiempo promedio de " << precision << " printeos sin condicionales: " << tiempo_promedio_1 << "[ns]" << endl;
    cout << "Tiempo promedio de " << precision << " printeos con condicionales: " << tiempo_promedio_2 << "[ns]" << endl;
}