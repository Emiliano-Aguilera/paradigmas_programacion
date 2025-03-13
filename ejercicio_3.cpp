#include <iostream>
#include <memory>

struct Node {
    int value {};
    std::shared_ptr<Node> next;
};

std::shared_ptr<Node> primero;

std::shared_ptr<Node> create_node(int value);
void push_front(int value);
void push_back(int value);
void insert(int value, int position);
void erase(int position);
void print_list();

int countNodes();

int main() {
    primero = create_node(0);

    push_front(1);
    print_list();

    push_back(4);
    print_list();

    insert(9, 2);
    print_list();

    insert(100, 7);
    print_list();

    std::cout << "Borrando" << std::endl;
    erase(2);
    print_list();

    erase(99);
    print_list();



    return 0;
}

std::shared_ptr<Node> create_node(int value) {
    auto nodo = std::make_shared<Node>();
    nodo->value = value;
    nodo->next = nullptr;
    return nodo;
}

void push_front(int value) {
    std::shared_ptr<Node> nodo = create_node(value);
    nodo->next = primero;
    primero = nodo;
}

void push_back(int value) {
    std::shared_ptr<Node> nodo = create_node(value);
    std::shared_ptr<Node> actual = primero;

    while (actual->next != nullptr) {
        actual = actual->next;
    }

    actual->next = nodo;
}

void insert(int value, int position) {
    int nodeCount = countNodes();

    if (nodeCount <= position) {
        std::cerr << "Posicion invalida, insertando nodo al final." << std::endl;
        push_back(value);
    } else {
        std::shared_ptr<Node> nodo = create_node(value);
        std::shared_ptr<Node> actual = primero;

        for (int i = 0; i < position - 1; i++) {
            actual = actual->next;
        }
        nodo->next = actual->next;
        actual->next = nodo;
    }
}

void erase(int position) {
    int nodeCount = countNodes();
    std::shared_ptr<Node> actual = primero;

    if (position >= nodeCount) {
        std::cerr << "Posicion invalida, borrando ultimo nodo" << std::endl;\
        position = nodeCount - 1;
    }
    
    for (int i = 0; i < position - 1; i++) {
        actual = actual->next;
    }

    actual->next = actual->next->next;
}   
 
void print_list() {
    std::shared_ptr<Node> actual = primero;

    while (actual != nullptr) {
        std::cout << actual->value << " -> ";
        actual = actual->next;
    }
    std::cout << "null" << std::endl;
}

int countNodes() {
    std::shared_ptr<Node> actual = primero;
    int nodeCount {};

    while (actual != nullptr) {
        actual = actual->next;
        nodeCount++;
    }

    return nodeCount;
}