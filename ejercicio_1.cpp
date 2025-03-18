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

// Declaracion de funciones

// Funcion que devuelve una matriz en base a un tamaño
vector_int createMatrix(int size) {
    // Primero crea un vector de longitud size
    vector_int matrix (size);

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
void printMatrix(vector_int matrix) {
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

// Imprime una matriz usando condicionales y un solo for
void printMatrix_b(vector_int matrix) {
    // Calcula el tamaño de la matriz
    int size = matrix.size();

    // Se definen i y j de esta forma para iterar de mayor a menor
    int i = size-1;
    int j = size-1;
    
    // k va de 0 a n^2
    for (int k = 0; k < size*size; k++) {
        cout << format("M[{}][{}] = {}\n", i, j, matrix[i][j]);

        // Si j es 0, significa que llegue al final de la fila, por lo tanto debo cambiar i y reiniciar j
        if (j == 0) {
            i--;
            j = size-1;
        }
        // Si j no es 0, entonces debo seguir iterando sobre la fila, disminuyendo j
        else {
            j--;
        }
    }
}

/*
Compara ambos metodos de iteracion usando chrono para medir el tiempo y usando matrices cada vez mas grandes,
yendo desde tamaño 3 hasta precision, entendiendo que mientras mas iteraciones, mas precisa sera la medida del tiempo
ya que se calcula el promedio de todos los tiempos.
*/
void compareSolutions() {
    // Primero se hace un tiempo fuera del for ya se debe definir el tipo de dato de sumT_1 y sumT_2. 

    // Crea un matriz de tamaño 2x2
    vector_int matrix = createMatrix(2);
    // Tomar el tiempo que toma imprimir con el metodo sin condicionales
    auto startTime = high_resolution_clock::now();
    printMatrix(matrix);
    auto endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime_1 = (endTime - startTime);
    
    // Tomar el tiempo que toma imprimir con el metodo que usa condicionales
    startTime = high_resolution_clock::now();
    printMatrix_b(matrix);
    endTime = high_resolution_clock::now();
    // Calcular diferencia entre los tiempos
    auto elapsedTime_2 = (endTime - startTime);

    // Asigna ambos tiempos a las variables que van a contener la suma de tiempos de todas las iteraciones
    auto sumT_1 = elapsedTime_1;
    auto sumT_2 = elapsedTime_2;

    // Define la cantidad de veces que se va a ejecutar la medicion y el tamaño maximo de matrix que se va a medir
    int precision = 100;

    for (int i = 3; i <= precision; i++) {
        vector_int matrix = createMatrix(i);
        // Tomar el tiempo que toma imprimir con el metodo de condicionales
        startTime = high_resolution_clock::now();
        printMatrix(matrix);
        endTime = high_resolution_clock::now();

        // Calcular diferencia entre los tiempos
        elapsedTime_1 = (endTime - startTime);

        sumT_1 += elapsedTime_1;

        startTime = high_resolution_clock::now();
        printMatrix_b(matrix);
        endTime = high_resolution_clock::now();

        // Calcular diferencia entre los tiempos
        elapsedTime_2 = (endTime - startTime);      
        sumT_2 += elapsedTime_2;
    }

    /* 
    Se divide la suma de tiempos entre la precision - 1 para obtener el promedio, se resta 2 ya que es el tamaño minimo de matriz
     por lo que no se ejecutan 100 mediciones, sino 100 - 1, o sea 99
    */
    auto tiempo_promedio_1 = sumT_1 / (precision - 1);
    auto tiempo_promedio_2 = sumT_2 / (precision - 1);

    cout << "Tiempo promedio de " << precision << " printeos sin condicionales: " << tiempo_promedio_1 << "[ns]" << endl;
    cout << "Tiempo promedio de " << precision << " printeos con condicionales: " << tiempo_promedio_2 << "[ns]" << endl;
}