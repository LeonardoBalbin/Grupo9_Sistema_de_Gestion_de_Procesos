#include <iostream>
#include <cstring>
using namespace std;

// ---------------- FUNCIONES AUXILIARES ----------------
int leerEnteroSeguro(const char* mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Intente nuevamente.\n";
        } else {
            cin.ignore(1000, '\n');
            return valor;
        }
    }
}

// ---------------- ESTRUCTURAS ----------------
struct Proceso {
    int id;
    char nombre[50];
    int prioridad;
    int memoria;
    Proceso* siguiente;
};

struct NodoCola {
    Proceso* proceso;
    NodoCola* siguiente;
};

struct NodoPila {
    int memoria;
    NodoPila* siguiente;
};

// ---------------- GESTOR DE PROCESOS ----------------
struct GestorProcesos {
    Proceso* primero;

    GestorProcesos() { primero = NULL; }

    void insertar(Proceso* nuevo) {
        nuevo->siguiente = NULL;
        if (!primero) primero = nuevo;
        else {
            Proceso* actual = primero;
            while (actual->siguiente) actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    Proceso* buscarPorID(int id) {
        Proceso* actual = primero;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    void eliminar(int id) {
        Proceso* actual = primero;
        Proceso* anterior = NULL;
        while (actual) {
            if (actual->id == id) {
                if (anterior) anterior->siguiente = actual->siguiente;
                else primero = actual->siguiente;
                delete actual;
                cout << "Proceso eliminado.\n";
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        cout << "Proceso no encontrado.\n";
    }

    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* p = buscarPorID(id);
        if (p) {
            p->prioridad = nuevaPrioridad;
            cout << "Prioridad actualizada.\n";
        } else cout << "Proceso no encontrado.\n";
    }

    void mostrar() {
        Proceso* actual = primero;
        cout << "\nID\tNombre\tPrioridad\tMemoria\n";
        while (actual) {
            cout << actual->id << "\t" << actual->nombre << "\t" << actual->prioridad << "\t\t" << actual->memoria << " MB\n";
            actual = actual->siguiente;
        }
    }
};

// ---------------- COLA DE PRIORIDAD ----------------
struct ColaPrioridad {
    NodoCola* frente;

    ColaPrioridad() { frente = NULL; }

    void encolar(Proceso* p) {
        NodoCola* nuevo = new NodoCola{p, NULL};
        if (!frente || p->prioridad > frente->proceso->prioridad) {
            nuevo->siguiente = frente;
            frente = nuevo;
        } else {
            NodoCola* actual = frente;
            while (actual->siguiente && p->prioridad <= actual->siguiente->proceso->prioridad) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    void ejecutar() {
        if (!frente) {
            cout << "No hay procesos en la cola.\n";
            return;
        }
        NodoCola* temp = frente;
        frente = frente->siguiente;
        cout << "Ejecutando proceso ID: " << temp->proceso->id << endl;
        delete temp;
    }

    void mostrar() {
        NodoCola* actual = frente;
        cout << "\n--- Cola de Prioridad ---\n";
        while (actual) {
            cout << "ID: " << actual->proceso->id << " | Prioridad: " << actual->proceso->prioridad << endl;
            actual = actual->siguiente;
        }
    }
};

// ---------------- PILA DE MEMORIA ----------------
struct PilaMemoria {
    NodoPila* cima;

    PilaMemoria() { cima = NULL; }

    void asignar(int memoria) {
        NodoPila* nuevo = new NodoPila{memoria, cima};
        cima = nuevo;
        cout << "Memoria asignada: " << memoria << " MB\n";
    }

    void liberar() {
        if (!cima) {
            cout << "No hay memoria para liberar.\n";
            return;
        }
        NodoPila* temp = cima;
        cima = cima->siguiente;
        cout << "Memoria liberada: " << temp->memoria << " MB\n";
        delete temp;
    }

    void mostrar() {
        NodoPila* actual = cima;
        cout << "\n--- Estado de la Memoria ---\n";
        while (actual) {
            cout << actual->memoria << " MB\n";
            actual = actual->siguiente;
        }
    }
};

// ---------------- PROGRAMA PRINCIPAL ----------------
int main() {
    GestorProcesos gp;
    ColaPrioridad cola;
    PilaMemoria pila;

    int opcion;
    do {
        cout << "\n--- SISTEMA DE GESTION DE PROCESOS ---\n";
        cout << "1. Agregar proceso\n2. Eliminar proceso\n3. Buscar proceso\n4. Modificar prioridad\n5. Mostrar procesos\n";
        cout << "6. Encolar proceso\n7. Ejecutar proceso\n8. Mostrar cola\n";
        cout << "9. Asignar memoria\n10. Liberar memoria\n11. Mostrar memoria\n12. Salir\n";
        opcion = leerEnteroSeguro("Seleccione una opcion: ");

        switch(opcion) {
            case 1: {
                Proceso* nuevo = new Proceso();
                nuevo->id = leerEnteroSeguro("ID: ");
                cout << "Nombre: ";
                cin.getline(nuevo->nombre, 50);
                nuevo->prioridad = leerEnteroSeguro("Prioridad: ");
                nuevo->memoria = leerEnteroSeguro("Memoria (MB): ");
                gp.insertar(nuevo);
                break;
            }
            case 2: {
                int id = leerEnteroSeguro("ID a eliminar: ");
                gp.eliminar(id);
                break;
            }
            case 3: {
                int id = leerEnteroSeguro("ID a buscar: ");
                Proceso* p = gp.buscarPorID(id);
                if (p) cout << "Encontrado: " << p->nombre << ", prioridad: " << p->prioridad << endl;
                else cout << "No encontrado.\n";
                break;
            }
            case 4: {
                int id = leerEnteroSeguro("ID: ");
                int nueva = leerEnteroSeguro("Nueva prioridad: ");
                gp.modificarPrioridad(id, nueva);
                break;
            }
            case 5:
                gp.mostrar();
                break;
            case 6: {
                int id = leerEnteroSeguro("ID del proceso a encolar: ");
                Proceso* p = gp.buscarPorID(id);
                if (p) cola.encolar(p);
                else cout << "Proceso no encontrado.\n";
                break;
            }
            case 7:
                cola.ejecutar();
                break;
            case 8:
                cola.mostrar();
                break;
            case 9: {
                int m = leerEnteroSeguro("MB a asignar: ");
                pila.asignar(m);
                break;
            }
            case 10:
                pila.liberar();
                break;
            case 11:
                pila.mostrar();
                break;
            case 12:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 12);

    return 0;
}

