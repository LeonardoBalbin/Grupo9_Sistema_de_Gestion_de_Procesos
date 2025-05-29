#include <iostream>
#include <string>

struct Proceso {
    int id;
    std::string nombre;
    int prioridad;
};


struct Nodo {
    Proceso dato;
    Nodo* siguiente;
};


struct ListaEnlazada {
    Nodo* cabeza;
    
    
    ListaEnlazada() {
        cabeza = nullptr;
    }
    
    
    void insertarProceso(Proceso p);
    bool eliminarPorID(int id);
    void mostrarProcesos();
};


void ListaEnlazada::insertarProceso(Proceso p) {
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->dato = p;
    nuevoNodo->siguiente = nullptr;
    
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

bool ListaEnlazada::eliminarPorID(int id) {
    if (cabeza == nullptr) return false;
    
    if (cabeza->dato.id == id) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return true;
    }
    
    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->dato.id != id) {
        actual = actual->siguiente;
    }
    
    if (actual->siguiente == nullptr) return false;
    
    Nodo* temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    delete temp;
    return true;
}

void ListaEnlazada::mostrarProcesos() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "ID: " << actual->dato.id 
                  << ", Nombre: " << actual->dato.nombre 
                  << ", Prioridad: " << actual->dato.prioridad << std::endl;
        actual = actual->siguiente;
    }
}


