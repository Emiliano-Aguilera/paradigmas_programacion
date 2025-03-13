#include <iostream>
#include <format>
#include <vector>

// prototipos de funcion
std::vector<std::vector<int>> createMatrix(int size);
void printMatrix(std::vector<std::vector<int>> matrix, int size);
void printMatrix_b(std::vector<std::vector<int>> matrix, int size);


int main() {
    int n = 0;

    std::cout << "Ingrese n: ";
    std::cin >> n;

    while (n <= 1) {
        std::cout << "n debe ser mayor a 1." << '\n';
        std::cout << "Ingrese n: ";
        std::cin >> n;
    }
    
    std::vector<std::vector<int>> matrix = createMatrix(n);

    printMatrix(matrix, n);
    //print_matrix_b(matrix, n);

    return 0;
}

// declaracion de funciones
std::vector<std::vector<int>> createMatrix(int size) {
    std::vector<std::vector<int>> matrix (size);

    for (int i = 0; i < size; i++){
        matrix[i] = std::vector<int> (size); 
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

void printMatrix(std::vector<std::vector<int>> matrix, int size) {
    int i = size-1;
    int j = size-1;
    
    for (int k = 0; k < size*size; k++) {
        std::cout << std::format("M[{}][{}] = {}\n", i, j, matrix[i][j]);
        if (j == 0) {
            i--;
            j = size-1;
        }
        else {
            j--;
        }
    }
}

void printMatrix_b(std::vector<std::vector<int>> matrix, int size) {
    // Intento de iterar inversamente la matriz sin usar condicionales
    for (int k = 0; k < size*size; k++) {
        int i = size - (k / size) - 1;
        int j = size - (k % size) - 1;
        std::cout << std::format("M[{}][{}] = {}\n", i, j, matrix[i][j]);
    }
}