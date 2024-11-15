#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Coordenada {
    int x;
    int y;
};

// funcion para calcular distancia entre dos puntos
double calcularDistancia(const Coordenada& p1, const Coordenada& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// funcion para verificar si un punto se encuentra dentro de los limites de un cuadrante
bool estaEnCuadrante(const Coordenada& punto, int xMin, int xMax, int yMin, int yMax) {
    return (punto.x >= xMin && punto.x <= xMax && punto.y >= yMin && punto.y <= yMax);
}

int main() {
    int xMin, xMax, yMin, yMax;
    int numPuntos;

    cout << "Ingrese los limites del cuadrante:" << endl;
    cout << "xMin: "; cin >> xMin;
    cout << "xMax: "; cin >> xMax;
    cout << "yMin: "; cin >> yMin;
    cout << "yMax: "; cin >> yMax;

    cout << "Ingrese la cantidad de puntos: ";
    cin >> numPuntos;

    vector<Coordenada> puntos(numPuntos);

    for (int i = 0; i < numPuntos; ++i) {
        cout << "Ingrese la coordenada x del punto " << i + 1 << ": ";
        cin >> puntos[i].x;
        cout << "Ingrese la coordenada y del punto " << i + 1 << ": ";
        cin >> puntos[i].y;
    }

    // Verificar cuales puntos estan dentro del cuadrante, para guardarlos en "punto"
    vector<Coordenada> puntosEnCuadrante; // inicializar vector con elementos de tipo Coordenada
    for (int i = 0; i < puntos.size(); ++i) {
        Coordenada punto = puntos[i];
        if (estaEnCuadrante(punto, xMin, xMax, yMin, yMax)) {
            puntosEnCuadrante.push_back(punto);
        }
    }
    cout << "Cantidad de puntos dentro del cuadrante: " << puntosEnCuadrante.size() << endl;

    // Calcular la distancia maxima entre puntos dentro del cuadrante
    double distanciaMaxima = 0;
    Coordenada punto1, punto2;
    for (int i = 0; i < puntosEnCuadrante.size(); ++i) {
        for (int j = i + 1; j < puntosEnCuadrante.size(); ++j) {
            double distancia = calcularDistancia(puntosEnCuadrante[i], puntosEnCuadrante[j]);
            if (distancia > distanciaMaxima) {
                distanciaMaxima = distancia;
                punto1 = puntosEnCuadrante[i];
                punto2 = puntosEnCuadrante[j];
            }
        }
    }

    if (distanciaMaxima > 0) {
        cout << "La distancia maxima entre dos puntos dentro del cuadrante es: " << distanciaMaxima << endl;
        cout << "Los puntos con la distancia maxima son: (" << punto1.x << ", " << punto1.y << ") y ("<< punto2.x << ", " << punto2.y << ")" << endl;
    } else {
        cout << "No hay puntos o solo un punto dentro del cuadrante especificado." << endl;
    }

    if (puntosEnCuadrante.empty()) {
        cout << "No hay puntos dentro del cuadrante especificado." << endl;
        return 0;
    }

    int indiceReferencia;
    cout << "Ingrese el indice del punto de referencia (0 a " << puntosEnCuadrante.size() - 1 << ") para conocer las distancias de este punto hacia los demas puntos que se encuentren dentro del cuadrante, tenga en cuenta que este indice esta compuesto por puntos que se encuentran dentro del cuadrante: ";
    cin >> indiceReferencia;

    if (indiceReferencia < 0 || indiceReferencia >= puntosEnCuadrante.size()) {
        cout << "Indice fuera de rango." << endl;
        return 0;
    }

    Coordenada puntoReferencia = puntosEnCuadrante[indiceReferencia];
    cout << "Distancias desde el punto (" << puntoReferencia.x << ", " << puntoReferencia.y << "):" << endl;

    for (int i = 0; i < puntosEnCuadrante.size(); ++i) {
        if (!(puntosEnCuadrante[i].x == puntoReferencia.x && puntosEnCuadrante[i].y == puntoReferencia.y)) {
            double distancia = calcularDistancia(puntoReferencia, puntosEnCuadrante[i]);
            cout << "Distancia a (" << puntosEnCuadrante[i].x << ", " << puntosEnCuadrante[i].y << "): " << distancia << endl;
        }
    }

    return 0;
}