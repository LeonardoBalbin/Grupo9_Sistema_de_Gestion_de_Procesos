#include <iostream>
using namespace std;


int longitudCadena(const char* cadena) {
    int longitud = 0;
    while (cadena[longitud] != '\0') {
        longitud++;
    }
    return longitud;
}

struct Proceso {
    int id;
    char nombre[50];
    int prioridad;
    int memoria;
    Proceso* siguiente;
};

struct GestorProcesos {
    Proceso* primero;
    
    GestorProcesos() : primero(nullptr) {}
    
    ~GestorProcesos() { 
        Proceso* actual = primero;
        while (actual != nullptr) {
            Proceso* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
    
    void insertar(int id, const char* nombre, int prioridad, int memoria) {
        Proceso* nuevo = new Proceso();
        nuevo->id = id;
        
        
        int i = 0;
        while (nombre[i] != '\0' && i < 49) {
            nuevo->nombre[i] = nombre[i];
            i++;
        }
        nuevo->nombre[i] = '\0'; // 
        
        nuevo->prioridad = prioridad;
        nuevo->memoria = memoria;
        nuevo->siguiente = nullptr;
        
        if (primero == nullptr) {
            primero = nuevo;
        } else {
            Proceso* actual = primero;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        cout << "Proceso agregado correctamente.\n";
    }
    
    
    
    void mostrar() {
        Proceso* actual = primero;
        cout << "\n=== LISTA DE PROCESOS ===\n";
        cout << "ID\tNombre\t\tPrioridad\tMemoria\n";
        cout << "----------------------------------------\n";
        
        while (actual != nullptr) {
            cout << actual->id << "\t";
            
          
            cout << actual->nombre;
            int espacios = 16 - longitudCadena(actual->nombre);
            for (int i = 0; i < espacios; i++) cout << " ";
            
            cout << "\t" << actual->prioridad;
            cout << "\t\t" << actual->memoria << " MB\n";
            
            actual = actual->siguiente;
        }
        
        if (primero == nullptr) {
            cout << "No hay procesos registrados.\n";
        }
        cout << "========================================\n";
    }
};


