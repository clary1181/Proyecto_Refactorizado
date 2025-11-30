// Utilidades.h
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
#include <limits>
#include <string>

using namespace std;

inline int leerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (!cin.fail()) break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intente de nuevo.\n";
    }
    return valor;
}
inline float leerFloat(const string& mensaje) {
    float valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (!cin.fail()) break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intente de nuevo.\n";
    }
    return valor;
}
inline double leerDoble(const string& mensaje) {
    // Usaremos double en lugar de float, ya que precio se maneja como double en Producto
    double valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (!cin.fail()) break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intente de nuevo.\n";
    }
    return valor;
}

inline char leerChar(const string& mensaje) {
    char valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (!cin.fail()) break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intente de nuevo.\n";
    }
    return valor;
}


inline string leerString(const string& mensaje) {
    string valor;
    // La clave es usar std::ws (whitespace) para ignorar el newline pendiente 
    // y luego usar getline para leer toda la línea (incluyendo espacios).
    while (true) {
        cout << mensaje;
        // Se limpia el buffer de entrada para evitar saltos y se lee toda la línea
        if (std::cin.peek() == '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::getline(std::cin >> std::ws, valor);

        if (!valor.empty()) break;

        std::cout << "La entrada no puede estar vacia. Intente de nuevo.\n";
    }
    return valor;
}

#endif

