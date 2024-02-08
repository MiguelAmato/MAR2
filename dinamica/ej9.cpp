// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1000000000

/*
	Problema: El carpintero Ebanisto

	cortes(i,j) = Mínimo acumulado de esfuerzo de cortes entre el comienzo de la tabla i al final de la tabla j

	cortes(i,i) =  0					
	cortes(i,j) = min i <= k <= j-1 { cortes(i,k) + cortes(k+1,j) + ((marcas[j] - marcas[i-1]) * 2) }

	Coste del Algoritmo: O(n^3)
	Coste en espacio: O(n^2)
*/

int cortes(const vector<int> & marcas, int i, int j) {
	int n = marcas.size();
	vector<vector<int>> dp(n, vector<int>(n, 0));
	for (int i = n - 2; i >= 0; --i) {
		for (int j = i + 1; j < n; ++j) {
			dp[i][j] = INF;
			for (int k = i; k <= j-1; ++k) {
				int aux = dp[i][k] + dp[k+1][j] + ((marcas[j] - marcas[i-1]) * 2);
				if (aux < dp[i][j])
					dp[i][j] = aux; 
			}
		}
	}
	return dp[0][n - 1];
}

bool resuelveCaso() {
    int L, N;
	cin >> L >> N;
    if (L == 0 && N == 0)
        return false;
    vector<int> marcas(N + 1); // Marcas donde hay que cortar
	for (int i = 0; i < N ; ++i)
		cin >> marcas[i];
	marcas[N] = L;
	cout << cortes(marcas, 0, N) << "\n";
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
