#include <iostream>
#include <memory>

using namespace std;

// Struct de nodo, contiene un valor y un puntero al siguiente nodo
struct Node {
    int value {};
    shared_ptr<Node> next;
};

// Variable que apunta al primer elemento de la lista
shared_ptr<Node> first;

// Prototipos de funcion
shared_ptr<Node> create_node(int);

void push_front(int);
void push_back(int);
void insert(int, int);
void erase(int);
void print_list();

int count_nodes();

int main() {
    // inicializa el primer nodo
    first = create_node(0);

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
    auto node = make_shared<Node>();
    // Inicializa el valor del nodo
    node->value = value;
    // Inicializa el puntero al siguiente nodo como nullptr
    node->next = nullptr;
    return node;
}

// Inserta un nodo al principio de la lista
void push_front(int value) {
    // Crea el nodo a insertar
    shared_ptr<Node> node = create_node(value);
    // Hace que el nodo creado apunte al primer nodo de la lista(que pasa a ser el segundo)
    node->next = first;
    // El puntero "primero" pasa a apuntar al nuevo nodo, haciendolo el primero de la lista
    first = node;
}

// Inserta un nodo al final de la lista
void push_back(int value) {
    // Crea el nodo a insertar
    shared_ptr<Node> node = create_node(value);
    // Puntero que apunta al nodo actual durante la iteracion, iniciando en el primer nodo
    shared_ptr<Node> iterator = first;

    // Itera sobre los nodos hasta llegar al ultimo, el cual tiene next = nullptr
    while (iterator->next != nullptr) {
        iterator = iterator->next;
    }

    // Hace que el ultimo nodo apunte al nuevo nodo a insertar, haciendolo el ultimo nodo.
    iterator->next = node;
}

/* Inserta un nodo en una posicion dada, si la posicion es mayor a la longitud de la lista,
 lo inserta al final de la misma */
void insert(int value, int position) {
    // Cuenta cuantos nodos hay para poder verificar que la posicion es valida.
    int nodeCount = count_nodes();

    // En caso de no serlo, muestra una advertencia y lo inserta al final
    if (nodeCount <= position) {
        cerr << "Posicion invalida, insertando nodo al final." << endl;
        push_back(value);
    } else {
        // Crea el nodo a insertar
        shared_ptr<Node> node = create_node(value);
        // Puntero al nodo actual para iterar, comienza en el primer nodo
        shared_ptr<Node> iterator = first;

        // Itera hasta llegar a la posicion deseada
        for (int i = 0; i < position - 1; i++) {
            iterator = iterator->next;
        }
        // El nodo a insertar pasa a apuntar al siguiente nodo de su posicion
        node->next = iterator->next;
        // El nodo actual(el anterior a la posicion a insertar) pasa a apuntar al nodo a insertar
        iterator->next = node;
    }
}

// Borra un nodo segun su posicion, si la posicion es invalida, borra el ultimo nodo
void erase(int position) {
    // Cuenta cuantos nodos hay para poder verificar la posicion
    int nodeCount = count_nodes();

    // Si la posicion es mayor a la cantidad de nodos, borra el ultimo
    if (position >= nodeCount) {
        cerr << "Posicion invalida, borrando ultimo nodo" << endl;
        position = nodeCount - 1;
        erase(position);
    }

    // Puntero al nodo actual para iterar, comienza por el primer nodo
    shared_ptr<Node> iterator = first;
    // Recorre la lista hasta llegar a la posicion deseada
    for (int i = 0; i < position - 1; i++) {
        iterator = iterator->next;
    }

    /* Hace que el nodo actual(el anterior a la posicion a borrar) apunte 2 nodos hacia adelante,
     borrando el que le sigue(el que esta en la posicion a borrar) */
    iterator->next = iterator->next->next;
}   

// Imprime la lista enlazada
void print_list() {
    // Puntero a nodo que se usa para iterar, inicia en el primer nodo
    shared_ptr<Node> iterator = first;

    /* Mientras no me encuentre en nullptr(final de la lista) voy imprimiendo el valor actual 
    y recorriendo la lista */
    while (iterator != nullptr) {
        cout << iterator->value << " -> ";
        iterator = iterator->next;
    }
    // Imprime null para simbolizar el final de la lista
    cout << "null" << endl;
}

// Cuenta los nodos, es una funcion auxiliar
int count_nodes() {
    // Puntero al primer nodo, se usa para iterar
    shared_ptr<Node> iterator = first;
    // Variable que lleva al cantidad de nodos
    int nodeCount {};

    // Mientras no este en nullptr(el final de la lista) recorro los nodos y sumo 1 al contador
    while (iterator != nullptr) {
        iterator = iterator->next;
        nodeCount++;
    }

    return nodeCount;
}