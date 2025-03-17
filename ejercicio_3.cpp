#include <iostream>
#include <memory>

using namespace std;

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

shared_ptr<Node> create_node(int value) {
    auto nodo = make_shared<Node>();
    nodo->value = value;
    nodo->next = nullptr;
    return nodo;
}

void push_front(int value) {
    shared_ptr<Node> nodo = create_node(value);
    nodo->next = primero;
    primero = nodo;
}

void push_back(int value) {
    shared_ptr<Node> nodo = create_node(value);
    shared_ptr<Node> actual = primero;

    while (actual->next != nullptr) {
        actual = actual->next;
    }

    actual->next = nodo;
}

void insert(int value, int position) {
    int nodeCount = countNodes();

    if (nodeCount <= position) {
        cerr << "Posicion invalida, insertando nodo al final." << endl;
        push_back(value);
    } else {
        shared_ptr<Node> nodo = create_node(value);
        shared_ptr<Node> actual = primero;

        for (int i = 0; i < position - 1; i++) {
            actual = actual->next;
        }
        nodo->next = actual->next;
        actual->next = nodo;
    }
}

void erase(int position) {
    int nodeCount = countNodes();
    shared_ptr<Node> actual = primero;

    if (position >= nodeCount) {
        cerr << "Posicion invalida, borrando ultimo nodo" << endl;
        position = nodeCount - 1;
    }
    
    for (int i = 0; i < position - 1; i++) {
        actual = actual->next;
    }

    actual->next = actual->next->next;
}   
 
void print_list() {
    shared_ptr<Node> actual = primero;

    while (actual != nullptr) {
        cout << actual->value << " -> ";
        actual = actual->next;
    }
    cout << "null" << endl;
}

int countNodes() {
    shared_ptr<Node> actual = primero;
    int nodeCount {};

    while (actual != nullptr) {
        actual = actual->next;
        nodeCount++;
    }

    return nodeCount;
}