#include <iostream>
#include <cstdlib>  // Para system("pause")
using namespace std;

// Estructura para representar un proceso
struct Proceso {
    int id;
    string nombre;
    int prioridad;
};

// Estructura de nodo para la lista enlazada
struct Nodo {
    Proceso proceso;
    Nodo* siguiente;
};

class GestorProcesos {
private:
    Nodo* cabeza;  // Puntero al primer nodo

public:
    // Constructor
    GestorProcesos()
    
    // Destructor para liberar memoria
    ~GestorProcesos() {
        while (cabeza != nullptr) {
            eliminarProceso(cabeza->proceso.id);
        }
    }

    // 1. Insertar un nuevo proceso (al final de la lista)
    void insertarProceso(int id, string nombre, int prioridad) {
        Nodo* nuevoNodo = new Nodo();
        nuevoNodo->proceso = {id, nombre, prioridad};
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
        cout << "Proceso '" << nombre << "' insertado correctamente.\n";
    }

    // 2. Eliminar proceso por ID
    void eliminarProceso(int id) {
        if (cabeza == nullptr) {
            cout << "Error: La lista de procesos está vacía\n";
            return;
        }

        // Caso especial: eliminar el primer nodo
        if (cabeza->proceso.id == id) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cout << "Proceso ID " << id << " eliminado correctamente.\n";
            return;
        }

        // Buscar el proceso en el resto de la lista
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            if (actual->siguiente->proceso.id == id) {
                Nodo* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                delete temp;
                cout << "Proceso ID " << id << " eliminado correctamente.\n";
                return;
            }
            actual = actual->siguiente;
        }

        cout << "Error: Proceso con ID " << id << " no encontrado\n";
    }

    // 3. Buscar proceso por ID
    Proceso* buscarProceso(int id) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->proceso.id == id) {
                return &(actual->proceso);
            }
            actual = actual->siguiente;
        }
        return nullptr;  // No encontrado
    }

    // 4. Modificar prioridad de un proceso
    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* proceso = buscarProceso(id);
        if (proceso != nullptr) {
            proceso->prioridad = nuevaPrioridad;
            cout << "Prioridad del proceso ID " << id << " actualizada a " << nuevaPrioridad << ".\n";
        } else {
            cout << "Error: Proceso con ID " << id << " no encontrado\n";
        }
    }

    // 5. Mostrar todos los procesos
    void mostrarProcesos() {
        if (cabeza == nullptr) {
            cout << "No hay procesos en el sistema\n";
            return;
        }

        cout << "\n=== Lista de Procesos ===\n";
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cout << "ID: " << actual->proceso.id 
                 << " | Nombre: " << actual->proceso.nombre 
                 << " | Prioridad: " << actual->proceso.prioridad << endl;
            actual = actual->siguiente;
        }
        cout << "=========================\n";
    }
};

// Menú interactivo para probar la lista enlazada
void menuGestorProcesos() {
    GestorProcesos gestor;
    int opcion, id, prioridad;
    string nombre;

    do {
        cout << "\n=== MENU GESTOR DE PROCESOS ===\n";
        cout << "1. Agregar nuevo proceso\n";
        cout << "2. Eliminar proceso por ID\n";
        cout << "3. Buscar proceso por ID\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Mostrar todos los procesos\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese ID del proceso: ";
                cin >> id;
                cout << "Ingrese nombre del proceso: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese prioridad: ";
                cin >> prioridad;
                gestor.insertarProceso(id, nombre, prioridad);
                break;

            case 2:
                cout << "Ingrese ID del proceso a eliminar: ";
                cin >> id;
                gestor.eliminarProceso(id);
                break;

            case 3:
                cout << "Ingrese ID del proceso a buscar: ";
                cin >> id;
                {
                    Proceso* p = gestor.buscarProceso(id);
                    if (p != nullptr) {
                        cout << "Proceso encontrado: " << p->nombre 
                             << " (Prioridad: " << p->prioridad << ")\n";
                    } else {
                        cout << "Proceso no encontrado\n";
                    }
                }
                break;

            case 4:
                cout << "Ingrese ID del proceso: ";
                cin >> id;
                cout << "Ingrese nueva prioridad: ";
                cin >> prioridad;
                gestor.modificarPrioridad(id, prioridad);
                break;

            case 5:
                gestor.mostrarProcesos();
                break;

            case 6:
                cout << "Saliendo del gestor de procesos...\n";
                break;

            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }
        system("pause");  // Pausa para ver resultados
        system("cls");    // Limpiar pantalla (Windows)
    } while (opcion != 6);
}

int main() {
    menuGestorProcesos();
    return 0;
}
