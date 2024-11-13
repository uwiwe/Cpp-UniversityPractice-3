#include <iostream>
#include <vector>

using namespace std;

struct Coordenadas {
    int x;
    int y;
};

// Calcular la pendiente con la formula y2-y1/x2-x1 (m)
float calcularPendiente(const Coordenadas& p1, const Coordenadas& p2) {
    if (p1.x == p2.x) { // por la formula, si x2 = x1 significa que el denominador de la division para calcular la pendiente da 0 y es indefinida
        return 1e9; // valor grande para representar pendiente indefinida
    }
    return static_cast<float>(p2.y - p1.y) / (p2.x - p1.x);
}

// Calcular corte en y (b)
float calcularInterseccion(const Coordenadas& punto, float pendiente) {
    return punto.y - pendiente * punto.x;
}

int main() {
    int puntos;
    cout << "Ingrese la cantidad de puntos que desea conocer su cuadrante: " << endl;
    cin >> puntos;

    vector<Coordenadas> coordenadas(puntos); // Para organizar las coordenadas de cada punto de forma accesible
    for (int i = 0; i < puntos; ++i) {
        cout << "Ingrese la coordenada x del punto " << i + 1 << ": ";
        cin >> coordenadas[i].x;
        cout << "Ingrese la coordenada y del punto " << i + 1 << ": ";
        cin >> coordenadas[i].y;
    }

    for (int i = 0; i < puntos; ++i) {
        int cuadrante;
        if (coordenadas[i].x == 0 && coordenadas[i].y == 0) {
            cout << "Punto " << coordenadas[i].x << ", " << coordenadas[i].y << " no se encuentra en ningun cuadrante" << endl;
        } 
        else {
            if (coordenadas[i].x >= 0 && coordenadas[i].y >= 0) {
                cuadrante = 1;
            } else if (coordenadas[i].x <= 0 && coordenadas[i].y >= 0) {
                cuadrante = 2;
            } else if (coordenadas[i].x <= 0 && coordenadas[i].y <= 0) {
                cuadrante = 3;
            } else {
                cuadrante = 4;
            }
            cout << "Punto " << coordenadas[i].x << ", " << coordenadas[i].y << " se encuentra en el cuadrante: " << cuadrante << endl;
        }
    }

    if (puntos > 1) {
        float pendienteInicial = calcularPendiente(coordenadas[0], coordenadas[1]); // Pendiente de la linea recta que une los primeros dos puntos
        
        bool mismaLinea = true;

        for (int i = 1; i < puntos - 1 && mismaLinea; ++i) { // Si mismaLinea = false no se ejecuta el loop
            float pendienteActual = calcularPendiente(coordenadas[i], coordenadas[i + 1]);
            if (pendienteActual != pendienteInicial) {
                mismaLinea = false;
            } else {
                cout << "Las coordenadas x,y: " << coordenadas[i + 1].x << ", " << coordenadas[i + 1].y << " si pertenecen a la misma linea iniciada en x,y: " << coordenadas[0].x << ", " << coordenadas[0].y << " con x,y: " << coordenadas[1].x << ", " << coordenadas[1].y << endl;
            }
        }

        if (pendienteInicial == 1e9) {
            cout << "La ecuacion dada forma una linea vertical, siendo esta x = " << coordenadas[0].x << endl;
        } else {
            float interseccion = calcularInterseccion(coordenadas[0], pendienteInicial);
            cout << "La ecuacion dada es la siguiente (desde los primeros dos puntos, por lo que para aquellos puntos que no esten en la misma linea, no aplica):" << "y = " << pendienteInicial << "x + " << interseccion << endl;
        }

        if (mismaLinea) {
            cout << "Todos los puntos estan en la misma linea, por lo que la ecuacion si aplica para todos los puntos." << endl;
        } else {
            cout << "Todos los puntos no estan en la misma linea, por lo que la ecuacion no aplica para todos los puntos." << endl;
        }
    } else {
        cout << "Se necesita al menos dos puntos para verificar la linea." << endl;
    }

    return 0;
}
