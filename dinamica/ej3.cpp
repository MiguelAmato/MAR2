// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
	Problema: Juego de tablero

	i: coordenada x
	j: coordenada y

	maximo(0, j) = tablero[i][j] 	
	maximo(i, j) += max(maximo(i - 1, j - 1), maximo(i - 1, j), maximo(i - 1, j + 1))

	Coste del algoritmo: N * N
*/

pair<int, int> maximo(vector<vector<int>> & tablero, const int & N) {
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= N; ++j) 
			tablero[i][j] += max(tablero[i - 1][j - 1], max(tablero[i - 1][j], tablero[i - 1][j + 1]));
	}
	int maxi = tablero[N - 1][1], pos = 1;
	for (int i = 2; i < tablero[N - 1].size(); ++i) {
		if (tablero[N - 1][i] > maxi) {
			maxi = tablero[N - 1][i];
			pos = i;
		}
	}
	return { maxi, pos };
}


bool resuelveCaso() {
    int N;
	cin >> N;
    if (!cin)
        return false;
	vector<vector<int>> tablero(N, vector<int>(N + 2, 0));
    for (int i = 0; i < N; ++i) {
		for (int j = 1; j <= N; ++j)
			cin >> tablero[i][j];
	}
	pair<int, int> ret = maximo(tablero, N);
	cout << ret.first << " " << ret.second << "\n";
    return true;
}

int main() {
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
     #endif 
    
    while (resuelveCaso());

     #ifndef DOMJUDGE 
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}