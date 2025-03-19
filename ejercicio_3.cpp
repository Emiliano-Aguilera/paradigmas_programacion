#include <iostream>
#include <memory>

using namespace std;

// Struct de nodo, contiene un valor y un puntero al siguiente nodo
struct Node {
    int value {};
    shared_ptr<Node> next;
};

// Variable que apunta al primer elemento de la lista
shared_ptr<Node> primero;

// Prototipos de funcion
shared_ptr<Node> create_node(int value);

void push_front(int value);
void push_back(int value);
void insert(int value, int position);
void erase(int position);
void print_list();

int countNodes();

int main() {
    // inicializa el primer nodo
    primero = create_node(0);

    // prueba push front
    push_front(1);
    print_list();

    // prueba push back
    push_back(4);
    print_list();

    // prueba insert valido
    insert(9, 2);
    print_list();

    // prueba insert invalido
    insert(100, 7);
    print_list();

    // prueba erase valido
    erase(2);
    print_list();

    // prueba erase invalido
    erase(99);
    print_list();

    return 0;
}

// Crea un nodo
shared_ptr<Node> create_node(int value) {
    // Crea un shared pointer a un nodo
    auto nodo = make_shared<Node>();
    // Inicializa el valor del nodo
    nodo->value = value;
    // Inicializa el puntero al siguiente nodo como nullptr
    nodo->next = nullptr;
    return nodo;
}

// Inserta un nodo al principio de la lista
void push_front(int value) {
    // Crea el nodo a insertar
    shared_ptr<Node> nodo = create_node(value);
    // Hace que el nodo creado apunte al primer nodo de la lista(que pasa a ser el segundo)
    nodo->next = primero;
    // El puntero "primero" pasa a apuntar al nuevo nodo, haciendolo el primero de la lista
    primero = nodo;
}

// Inserta un nodo al final de la lista
void push_back(int value) {
    // Crea el nodo a insertar
    shared_ptr<Node> nodo = create_node(value);
    // Puntero que apunta al nodo actual durante la iteracion, iniciando en el primer nodo
    shared_ptr<Node> actual = primero;

    // Itera sobre los nodos hasta llegar al ultimo, el cual tiene next = nullptr
    while (actual->next != nullptr) {
        actual = actual->next;
    }

    // Hace que el ultimo nodo apunte al nuevo nodo a insertar, haciendolo el ultimo nodo.
    actual->next = nodo;
}

/* Inserta un nodo en una posicion dada, si la posicion es mayor a la longitud de la lista,
 lo inserta al final de la misma */
void insert(int value, int position) {
    // Cuenta cuantos nodos hay para poder verificar que la posicion es valida.
    int nodeCount = countNodes();

    // En caso de no serlo, muestra una advertencia y lo inserta al final
    if (nodeCount <= position) {
        cerr << "Posicion invalida, insertando nodo al final." << endl;
        push_back(value);
    } else {
        // Crea el nodo a insertar
        shared_ptr<Node> nodo = create_node(value);
        // Puntero al nodo actual para iterar, comienza en el primer nodo
        shared_ptr<Node> actual = primero;

        // Itera hasta llegar a la posicion deseada
        for (int i = 0; i < position - 1; i++) {
            actual = actual->next;
        }
        // El nodo a insertar pasa a apuntar al siguiente nodo de su posicion
        nodo->next = actual->next;
        // El nodo actual(el anterior a la posicion a insertar) pasa a apuntar al nodo a insertar
        actual->next = nodo;
    }
}

// Borra un nodo segun su posicion, si la posicion es invalida, borra el ultimo nodo
void erase(int position) {
    // Cuenta cuantos nodos hay para poder verificar la posicion
    int nodeCount = countNodes();
    // Puntero al nodo actual para iterar, comienza por el primer nodo
    shared_ptr<Node> actual = primero;

    // Si la posicion es mayor a la cantidad de nodos, borra el ultimo
    if (position >= nodeCount) {
        cerr << "Posicion invalida, borrando ultimo nodo" << endl;
        position = nodeCount - 1;
        erase(position);
    }
    
    // Recorre la lista hasta llegar a la posicion deseada
    for (int i = 0; i < position - 1; i++) {
        actual = actual->next;
    }

    /* Hace que el nodo actual(el anterior a la posicion a borrar) apunte 2 nodos hacia adelante,
     borrando el que le sigue(el que esta en la posicion a borrar) */
    actual->next = actual->next->next;
}   

// Imprime la lista enlazada
void print_list() {
    // Puntero a nodo que se usa para iterar, inicia en el primer nodo
    shared_ptr<Node> actual = primero;

    /* Mientras no me encuentre en nullptr(final de la lista) voy imprimiendo el valor actual 
    y recorriendo la lista */
    while (actual != nullptr) {
        cout << actual->value << " -> ";
        actual = actual->next;
    }
    // Imprime null para simbolizar el final de la lista
    cout << "null" << endl;
}

// Cuenta los nodos, es una funcion auxiliar
int countNodes() {
    // Puntero al primer nodo, se usa para iterar
    shared_ptr<Node> actual = primero;
    // Variable que lleva al cantidad de nodos
    int nodeCount {};

    // Mientras no este en nullptr(el final de la lista) recorro los nodos y sumo 1 al contador
    while (actual != nullptr) {
        actual = actual->next;
        nodeCount++;
    }

    return nodeCount;
}