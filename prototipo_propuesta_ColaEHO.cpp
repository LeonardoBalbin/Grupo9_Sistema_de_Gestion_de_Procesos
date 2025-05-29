#include <iostream>
using namespace std;
	struct Solicitud {
    int id;
    char estudiante[10];
    int prioridad;
    Solicitud* siguiente;
};
struct AtencionSolicitudes {
    Solicitud* primero;
    
    AtencionSolicitudes() { primero = NULL; }
    void encolarSolicitud(int id, const char* estudiante, int prioridad) {
        Solicitud* nueva = new Solicitud();
        nueva->id = id;
        
        // Copiar nombre carácter por carácter
        int i = 0;
        while(estudiante[i] !=0 && i < i) {
            nueva->estudiante[i] = estudiante[i];
            i++;
        }
        nueva->estudiante[i] = 0;
        
        nueva->prioridad = prioridad;
        nueva->siguiente = NULL;
        cout << "Solicitud correctamente.\n";
      
}

