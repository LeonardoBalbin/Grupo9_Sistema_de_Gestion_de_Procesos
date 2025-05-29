//huayllaniotarolaeric
#include <iostream>
using namespace std;
int main() {
    //VAriable pa asignar;
    int opcion;
    
    do {
        cout << "\n------------- SISTEMA DE GESTION DE PROCESOS --------------------\n";
        cout << "1. Agregar proceso";
        cout << "2. Eliminar proces";
        cout << "3. Buscar proceso";
        cout << "4. Mostrar todos los procesos";
        cout << "5. Salir";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int id, prioridad, memoria;
                char nombre[//cantidad];
                
                cout << "ingrese Id del proceso: ";
                cin >> id;
                cout << "ingrese nombre del proceso: ";
                cin.ignore();
                cin.getline(nombre, 50);
                cout << "ingrese prioridad: ";
                cin >> prioridad;
                cout << "ingrese memoria requerida (MB): ";
                cin >> memoria;
                
                insertar(id, nombre, prioridad, memoria);
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese Id del proceso a eliminar: ";
                cin >> id;
                eliminar(id);
                break;
            }
            case 3: {
                int id;
                cout << "Ingrese Id del proceso a buscar: ";
                cin >> id;
                Proceso* encontrado = buscar(id);
                if(encontrado != NULL) {
                    cout << "\nProceso encontrado:\n";
                    cout << "Nombre: " << encontrado->nombre << "\n";
                    cout << "Prioridad: " << encontrado->prioridad << "\n";
                    cout << "Memoria: " << encontrado->memoria << " MB\n";
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 4:
                mostrar();
                break;
            case 5:
                cout << "Abandonando el sistema...";
                break;
            default:
                cout << "Error. Ingrese otra vez..";
        }
        
        if(opcion != 5) {
            pausa();
        }
        
    } while(opcion != 5);
    
    return 0;
}
