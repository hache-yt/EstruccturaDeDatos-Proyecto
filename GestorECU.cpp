#include <iostream> // Librería para entrada y salida estándar (cin, cout)
#include <cmath>    // Librería para funciones matemáticas como sqrt() y pow()
#include <string>   // Librería para usar el tipo string
#include <fstream>  // Abri archivo
using namespace std; // Para no escribir std:: cada vez que usamos cin, cout o string

// ESTRUCTURA 1: LISTA ENLAZADA - GESTOR DE ECUACIONES
struct NodoEcuacion { // Nodo de la lista para cada ecuación
    int id;            // Identificador único de la ecuación
    string expresion;  // La ecuación en formato de texto
    string complejidad;// Nivel de complejidad ("Alta" o "Baja")
    NodoEcuacion* sig; // Apuntador al siguiente nodo
};
class ListaEcuaciones { // Clase para manejar la lista de ecuaciones
private:
    NodoEcuacion* inicio; // Apunta al primer nodo de la lista
public:
    ListaEcuaciones() : inicio(NULL) {} // Constructor: inicializa lista vacía
    void insertarEcuacion(int id, string expresion, string complejidad) { // Agrega un nodo
        NodoEcuacion* nueva = new NodoEcuacion{id, expresion, complejidad, NULL}; // Crea nodo
        if (inicio == NULL) { // Si la lista está vacía
            inicio = nueva;   // El nodo nuevo es el primero
        } else {
            NodoEcuacion* actual = inicio; // Comenzar desde el inicio
            while (actual->sig != NULL)   // Recorrer hasta el último nodo
                actual = actual->sig;
            actual->sig = nueva;          // Enlazar el nuevo nodo al final
        }
        cout << "? Ecuacion agregada: " << expresion << " (" << complejidad << ")\n"; // Mensaje
    }
    NodoEcuacion* buscarEcuacion(int id) { // Buscar un nodo por ID
        NodoEcuacion* actual = inicio;      // Empezar desde el inicio
        while (actual != NULL) {            // Recorrer toda la lista
            if (actual->id == id)          // Si el ID coincide
                return actual;             // Devuelve el nodo
            actual = actual->sig;          // Avanzar al siguiente nodo
        }
        return NULL; // No encontrado
    }
    void mostrarEcuaciones() {             // Mostrar todas las ecuaciones
        NodoEcuacion* actual = inicio;     // Comenzar desde el inicio
        cout << "\n?? Ecuaciones registradas:\n"; // Encabezado
        while (actual != NULL) {           // Recorrer la lista
            cout << "ID: " << actual->id << " | " << actual->expresion 
                 << " | Complejidad: " << actual->complejidad << endl; // Mostrar datos
            actual = actual->sig;          // Avanzar al siguiente nodo
        }
    }
    void guardarArchivo() {                // Guardar ecuaciones en archivo
        ofstream archivo("ecuaciones.txt"); // Abrir archivo
        NodoEcuacion* actual = inicio;     // Comenzar desde el inicio
        while (actual != NULL) {           // Recorrer lista
            archivo << actual->id << "," << actual->expresion << "," << actual->complejidad << endl; // Guardar
            actual = actual->sig;          // Avanzar al siguiente nodo
        }
        archivo.close();                   // Cerrar archivo
        cout << "?? Ecuaciones guardadas correctamente.\n"; // Mensaje
    }
};
// ESTRUCTURA 2: COLA DE PRIORIDAD - PLANIFICADOR
struct NodoCola {          // Nodo para la cola de prioridad
    NodoEcuacion ecuacion; // La ecuación que se encola
    NodoCola* sig;         // Apuntador al siguiente nodo en la cola
};
class ColaPrioridad {       // Clase para manejar la cola
private:
    NodoCola* frente;      // Apunta al primer nodo (de mayor prioridad)
public:
    ColaPrioridad() : frente(NULL) {} // Constructor: cola vacía
    void encolar(NodoEcuacion eq) { // Agregar nodo a la cola según prioridad
        NodoCola* nuevo = new NodoCola{eq, NULL}; // Crear nodo nuevo
        if (frente == NULL || eq.complejidad == "Alta") { // Si cola vacía o prioridad alta
            nuevo->sig = frente; // Nuevo apunta al frente actual
            frente = nuevo;      // Nuevo pasa a ser el frente
        } else {
            NodoCola* actual = frente; // Recorrer la cola
            while (actual->sig != NULL && actual->sig->ecuacion.complejidad != "Baja")
                actual = actual->sig;  // Avanzar hasta encontrar baja prioridad
            nuevo->sig = actual->sig;  // Enlazar nuevo nodo
            actual->sig = nuevo;       // Insertar en la posición correcta
        }
        cout << "?? Encolada ecuacion: " << eq.expresion << endl; // Mensaje
    }
    NodoEcuacion desencolar() { // Sacar nodo del frente
        if (frente == NULL) {   // Si la cola está vacía
            cout << "??  No hay ecuaciones en cola.\n";
            return NodoEcuacion{-1, "", "", NULL}; // Retorna nodo vacío
        }
        NodoCola* temp = frente;    // Guardar nodo del frente
        frente = frente->sig;        // Mover frente al siguiente
        NodoEcuacion eq = temp->ecuacion; // Guardar ecuación
        delete temp;                // Liberar memoria del nodo
        return eq;                  // Devolver ecuación
    }
    bool estaVacia() {           // Verificar si la cola está vacía
        return frente == NULL;
    }
    void mostrarCola() {         // Mostrar todas las ecuaciones en la cola
        NodoCola* actual = frente; // Comenzar desde el frente
        cout << "\n?? Cola de prioridad:\n"; // Encabezado
        while (actual != NULL) {   // Recorrer toda la cola
            cout << actual->ecuacion.expresion << " (" << actual->ecuacion.complejidad << ")\n"; // Mostrar
            actual = actual->sig;  // Avanzar al siguiente nodo
        }
    }
};
// ESTRUCTURA 3: PILA - GESTOR DE MEMORIA TEMPORAL
struct NodoPila {       // Nodo de la pila
    string variable;     // Variable temporal o datos usados en la ecuación
    NodoPila* sig;       // Apuntador al siguiente nodo de la pila
};
class PilaMemoria {      // Clase para manejar la pila de memoria
private:
    NodoPila* tope;      // Apunta al nodo superior de la pila
public:
    PilaMemoria() : tope(NULL) {} // Constructor: pila vacía
    void push(string variable) { // Agregar nodo al tope
        NodoPila* nuevo = new NodoPila{variable, tope}; // Crear nodo apuntando al tope actual
        tope = nuevo;         // Nuevo nodo pasa a ser el tope
        cout << "?? Memoria asignada: " << variable << endl; // Mensaje
    }
    void pop() {              // Quitar nodo del tope
        if (tope != NULL) {   // Verificar si hay nodos
            cout << "?? Liberando memoria: " << tope->variable << endl; // Mensaje
            NodoPila* temp = tope; // Guardar nodo
            tope = tope->sig;      // Mover tope al siguiente nodo
            delete temp;           // Liberar memoria
        }
    }
    void mostrarPila() {       // Mostrar todas las variables en memoria
        NodoPila* actual = tope; // Comenzar desde el tope
        cout << "\n?? Variables en memoria:\n"; // Encabezado
        while (actual != NULL) { // Recorrer pila
            cout << actual->variable << endl; // Mostrar variable
            actual = actual->sig;            // Avanzar al siguiente
        }
    }
};
// FUNCIÓN PRINCIPAL: SIMULADOR DEL SISTEMA
void resolverEcuacion(NodoEcuacion eq, PilaMemoria& pila) { // Resolver ecuación y usar memoria temporal
    cout << "\n?? Resolviendo: " << eq.expresion << endl; // Mensaje
    pila.push("Datos temporales de " + eq.expresion); // Asignar memoria temporal
    if (eq.complejidad == "Alta") { // Ecuaciones cuadráticas
        double a, b, c;              // Variables para coeficientes
        cout << "Ingrese coeficientes a, b, c: ";
        cin >> a >> b >> c;           // Leer coeficientes
        double D = pow(b, 2) - 4 * a * c; // Calcular discriminante
        if (D >= 0) {                 // Si hay raíces reales
            double x1 = (-b + sqrt(D)) / (2 * a); // Primera raíz
            double x2 = (-b - sqrt(D)) / (2 * a); // Segunda raíz
            cout << "Raices reales: x1 = " << x1 << ", x2 = " << x2 << endl; // Mostrar
        } else {
            cout << "No existen soluciones reales.\n"; // Mensaje
        }
    } else { // Ecuaciones lineales
        double a, b;                  // Variables para coeficientes
        cout << "Ingrese coeficientes a y b: ";
        cin >> a >> b;                // Leer coeficientes
        cout << "Solucion: x = " << -b / a << endl; // Calcular y mostrar
    }
    pila.pop();                        // Liberar memoria temporal
    cout << "? Ecuacion resuelta.\n"; // Mensaje de finalización
}
// PROGRAMA PRINCIPAL
int main() {
    ListaEcuaciones lista; // Crear lista de ecuaciones
    ColaPrioridad cola;    // Crear cola de prioridad
    PilaMemoria pila;      // Crear pila de memoria temporal

    int opcion, id = 1;    // Variables para menú e ID
    string expresion, complejidad; // Variables para ingresar ecuación

    do { // Menú principal
        cout << "\n===== SISTEMA DE GESTION DE PROCESOS MATEMATICOS =====\n";
        cout << "1. Registrar ecuacion\n2. Mostrar ecuaciones\n3. Encolar ecuacion\n";
        cout << "4. Mostrar cola\n5. Resolver ecuacion\n6. Guardar ecuaciones\n0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion; // Leer opción del usuario

        switch (opcion) {
        case 1: // Registrar ecuación
            cout << "Ingrese la ecuacion: ";
            cin.ignore();       // Limpiar buffer
            getline(cin, expresion); // Leer toda la línea
            cout << "Complejidad (Alta/Baja): ";
            cin >> complejidad; // Leer complejidad
            lista.insertarEcuacion(id, expresion, complejidad); // Insertar en lista
            id++;              // Incrementar ID
            break;
        case 2: // Mostrar ecuaciones
            lista.mostrarEcuaciones();
            break;
        case 3: { // Encolar ecuación
            int idBuscar;
            cout << "Ingrese el ID de la ecuacion a encolar: ";
            cin >> idBuscar; // Leer ID
            NodoEcuacion* eq = lista.buscarEcuacion(idBuscar); // Buscar ecuación
            if (eq != NULL) cola.encolar(*eq); // Encolar si existe
            else cout << "? Ecuacion no encontrada.\n"; // Si no existe
            break;
        }
        case 4: // Mostrar cola
            cola.mostrarCola();
            break;
        case 5: // Resolver ecuación del frente de la cola
            if (!cola.estaVacia()) {
                NodoEcuacion eq = cola.desencolar(); // Sacar ecuación de la cola
                resolverEcuacion(eq, pila);           // Resolver usando memoria temporal
            } else {
                cout << "??  No hay ecuaciones pendientes.\n"; // Cola vacía
            }
            break;
        case 6: // Guardar ecuaciones en archivo
            lista.guardarArchivo();
            break;
        case 0: // Salir
            cout << "\n?? Fin de la simulacion.\n";
            break;
        default: // Opción inválida
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0); // Repetir mientras no sea salir

    return 0; // Fin del programa
}

