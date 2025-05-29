#include <iostream>
using namespace std;

int longitudCadena(const char* cadena) {
    int longitud = 0;
    while(cadena[longitud] != '\0') {
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

    GestorProcesos() { primero = NULL; }
    

    void insertar(int id, const char* nombre, int prioridad, int memoria) {
        Proceso* nuevo = new Proceso();
        nuevo->id = id;

        int i = 0;
        while(nombre[i] != '\0' && i < 49) {
            nuevo->nombre[i] = nombre[i];
            i++;
        }
        nuevo->nombre[i] = '\0';
        
        nuevo->prioridad = prioridad;
        nuevo->memoria = memoria;
        nuevo->siguiente = NULL;
        
        if(primero == NULL) {
            primero = nuevo;
        } else {
            // Recorrer la lista hasta el final para insertar el nuevo proceso
            Proceso* actual = primero;
            while(actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        cout << "Proceso registrado correctamente.\n";
    }
    
    void mostrar() {
        cout << "\n------ LISTA DE PROCESOS ------\n";
        cout << "ID\tNombre\t\tPrioridad\tMemoria\n";
        cout << "----------------------------------------\n";
        Proceso* actual = primero;
        if (actual == NULL) {
            cout << "No hay procesos registrados.\n";
        }
        while(actual != NULL) {
            cout << actual->id << "\t";
            cout << actual->nombre;
            int espacios = 16 - longitudCadena(actual->nombre);
            for(int i = 0; i < espacios; i++) cout << " ";
            cout << "\t" << actual->prioridad;
            cout << "\t\t" << actual->memoria << " MB\n";
            actual = actual->siguiente;
        }
    }
    

};
int main() {
    GestorProcesos gp;
    int opcion;
    
    do {
        cout << "\n------- SISTEMA DE GESTION DE PROCESOS ------\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso \n";
        cout << "3. Buscar proceso \n";
        cout << "4. Mostrar procesos\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int id, prioridad, memoria;
                char nombre[50];
                
                cout << "Ingrese ID del proceso: ";
                cin >> id;
                cout << "Ingrese nombre del proceso: ";
                cin.ignore();
                cin.getline(nombre, 50);
                cout << "Ingrese prioridad: ";
                cin >> prioridad;
                cout << "Ingrese memoria requerida (MB): ";
                cin >> memoria;
                
                gp.insertar(id, nombre, prioridad, memoria);
                break;
            }
            case 2:
                cout << "Funcionalidad de eliminar.\n";
                break;
            case 3:
                cout << "Funcionalidad de buscar.\n";
                break;
            case 4:
                gp.mostrar();
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Error. Intente nuevamente.\n";
        }
        
    } while(opcion != 5);
    
    return 0;
}
