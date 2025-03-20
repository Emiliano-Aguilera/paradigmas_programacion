#include <iostream>
#include <format>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;
using VectorInt =  vector<vector<int>>;

// prototipos de funcion
VectorInt createMatrix(int size);
void printMatrix(VectorInt matrix);

int main() {
    int n;

    cout << "Ingrese n: ";
    cin >> n;

    // Check de que el usuario esta ingresando un n valido
    while (n <= 1) {
        cout << "n debe ser mayor a 1." << '\n';
        cout << "Ingrese n: ";
        cin >> n;
    }
    
    // Crear la matriz
    VectorInt matrix = createMatrix(n);

    // Imprimir matriz
    printMatrix(matrix);
    
    return 0;
}

// Declaracion de funciones

// Funcion que devuelve una matriz en base a un tamaño
VectorInt createMatrix(int size) {
    // Primero crea un vector de longitud size
    VectorInt matrix (size);

    // Luego rellena el vector con vectores de longitud size
    for (int i = 0; i < size; i++){
        matrix[i] = vector<int> (size); 
    }
    
    // Rellena la matriz con numeros desde i a n^2
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Parentesis redundantes, mejoran legibilidad
            int value = (i * size) + (j+1);
            matrix[i][j] = value;
        }
    }

    return matrix;
}

// Imprime una matriz sin usar condicionales con un solo for 
void printMatrix(VectorInt matrix) {
    // Calcular el tamaño de la matriz
    int size = matrix.size();

    // Itera con valores que van de 0 a n^2
    for (int k = 0; k < size*size; k++) {
        // Define i y j en base a el valor que esta dentro de la matriz, de forma que itere de mayor a menor
        int i = size - (k / size) - 1;
        int j = size - (k % size) - 1;
        // Imprime el valor usando format para que sea mas legible el codigo.
        cout << format("M[{}][{}] = {}\n", i, j, matrix[i][j]);
    }
}