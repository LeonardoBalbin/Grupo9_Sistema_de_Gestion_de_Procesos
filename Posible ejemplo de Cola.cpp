#include <iostream>
using namespace std;

class ColaPrioridad {
private:
    struct NodoCola {
        Proceso dato;
        NodoCola* siguiente;
    };
    NodoCola* frente;
    NodoCola* fin;
    
public:
    ColaPrioridad() : frente(nullptr), fin(nullptr) {}
    
    void encolar(Proceso p) {
        NodoCola* nuevoNodo = new NodoCola{p, nullptr};
        if (!frente || p.prioridad > frente->dato.prioridad) {
            nuevoNodo->siguiente = frente;
            frente = nuevoNodo;
        } else {
            NodoCola* actual = frente;
            while (actual->siguiente && actual->siguiente->dato.prioridad >= p.prioridad) {
                actual = actual->siguiente;
            }
            nuevoNodo->siguiente = actual->siguiente;
            actual->siguiente = nuevoNodo;
        }
    }
};
