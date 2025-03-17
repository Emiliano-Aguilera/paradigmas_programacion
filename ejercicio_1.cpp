#include <iostream>
#include <format>
#include <vector>

using namespace std;

using vector_int =  vector<vector<int>>;

// prototipos de funcion
vector_int createMatrix(int size);
void printMatrix(vector_int matrix, int size);
void printMatrix_b(vector_int matrix, int size);

int main() {
    int n = 0;

    cout << "Ingrese n: ";
    cin >> n;

    while (n <= 1) {
        cout << "n debe ser mayor a 1." << '\n';
        cout << "Ingrese n: ";
        cin >> n;
    }
    
    vector_int matrix = createMatrix(n);

    printMatrix(matrix, n);
    //print_matrix_b(matrix, n);

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

void printMatrix(vector_int matrix, int size) {
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

void printMatrix_b(vector_int matrix, int size) {
    // Intento de iterar inversamente la matriz sin usar condicionales
    for (int k = 0; k < size*size; k++) {
        int i = size - (k / size) - 1;
        int j = size - (k % size) - 1;
        cout << format("M[{}][{}] = {}\n", i, j, matrix[i][j]);
    }
}