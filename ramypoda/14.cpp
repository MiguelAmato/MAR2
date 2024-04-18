// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

/*
	Problema: Los funcionarios del Ministerio

	1: Representacion de la solucion
	Un vector de tamaño N que representa a los N trabajadores, en cada posicion se le asignara una un tiempo de tarea de tal
	forma que la suma total de tiempo sea minimo.

	2: Tamaño de la solucion
	Tamaño del vector sol: N

	3: Valores que puede tomar la solucion
	Cada celda puede tomar el tiempo de las N tareas que hay

	4: Describir el arbol de solucion
	El arbol de solución se conformará de N etapas las cuales será el trabajador al que hay que asignarle una tarea
	y los hijos serán las tareas disponibles a asignar.

	5: Ramificacion y profundidad
	La Ramificación de tamaño N ya que el maximo de ramas son todas las tareas y profundidad N ya que son los trabajadores
	a asignarle una tarea.

	6: Tamaño 
	R^P.

	7: Test de factibilidad:
	Que ninguno de los N trabajadores coincida con otro en una de las N tareas.

	8: La información del nodo (struct Nodo):
*/
struct Nodo {
	vector<int> sol;
	int k; // etapa
	int suma; // Acumulado real
	int estimado; // Acumulado optimista (prioridad)
	vector<bool> marcas;
	bool operator<(const Nodo &n2) const {
		return estimado < n2.estimado;
	}
};

struct tInfo {
	const vector<vector<int>>& trabajos; 
	const vector<int> & minimos; 
	const vector<int> & maximos;
};

int tiempos(const tInfo & info) {
	int N = info.trabajos.size();
	Nodo Y;
	Y.sol = vector<int>(N);
	Y.k = -1;
	Y.suma = 0;
	Y.marcas = vector<bool>(N, false);
	Y.estimado = info.minimos[0]; // Calculo voraz
	priority_queue<Nodo> pq;
	pq.push(Y);
	int sol_mejor = INT_MAX;
	while (!pq.empty() && pq.top().estimado <= sol_mejor) {
		Y = pq.top(); pq.pop();
		Nodo X(Y);
		++X.k;
		for (int i = 0; i < N; ++i) {
			if (!Y.marcas[i]) {
				X.marcas[i] = true;
				X.sol[X.k] = i; 
				X.suma = Y.suma + info.trabajos[X.k][i];
				X.estimado = X.suma + info.minimos[X.k + 1]; // Calculo voraz
				if (X.estimado <= sol_mejor) {
					if (X.k == N - 1)
						sol_mejor = X.suma;
					else {
						pq.push(X);
						sol_mejor = min(sol_mejor, X.suma + info.maximos[X.k + 1]);
					}
				}
				X.marcas[i] = false;
			}
		}
	}
	return sol_mejor;
}

bool resuelveCaso() {
	int N;
    cin >> N;
    if (N == 0)
        return false;
	vector<vector<int>> trabajos(N, vector<int>(N));
	vector<int> minimos(N, INT_MAX), v_min(N,0), v_max(N,0);
	vector<int> maximos(N, -1);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> trabajos[i][j];
			minimos[i] = min(trabajos[i][j], minimos[i]);
			maximos[i] = max(trabajos[i][j], maximos[i]);
		}
	}
	// Pre-calculo de las estimaciones
	v_min[N - 1] = minimos[N - 1];
	v_max[N - 1] = maximos[N - 1];
	for (int i = N - 2; i >= 0; --i) {
		v_min[i] = v_min[i + 1] + minimos[i];
		v_max[i] = v_max[i + 1] + maximos[i];
	}
	cout << tiempos({trabajos, v_min, v_max}) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
