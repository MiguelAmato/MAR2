// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define MIN -1000000000

/*
	Problema: El cazatesoros

	cazatesoros(i,j) = funcion que permite maximizar la cantidad de oro recogida con T de oxigeno, 
	la matriz dinamica será representada con i columnas que representan cuantos tesoros se han recogido
	y la j los segundos que se necesitan para conseguirlos. La matriz queda como: La maxima cantidad
	de oro que se puede conseguir con i tesoros disonibles con una cantidad j de segundos de aire.

	i: Tesoros disponibles
	j: Segundos de la botella

	cazatesoros(0,j) = 0
	cazatesoros(i,0) = 0
	cazatesoros(i,j) = max(cazatersoros(i-1, j - datos[i-1].first) + datos[i-1].second, cazatersoros(i-1, j))
	cazatesoros(i,j) = cazatersoros(i-1, j)

	Coste del algoritmo: T * N siendo N el numero de tesoros y T el tiempo de la bomba de aire 
*/

pair<int, vector<int>> cazatesoros(const vector<pair<int, int>> & datos, const int T) {
	vector<vector<int>> dp(datos.size() + 1, vector<int>(T + 1, 0));
	for (int i = 1; i <= datos.size(); ++i) {
		for (int j = 1; j <= T; ++j) {
			if ((3*datos[i-1].first) <= j)
				dp[i][j] = max(dp[i-1][j - (3*datos[i-1].first)] + datos[i-1].second, dp[i-1][j]);
			else
				dp[i][j] = dp[i-1][j];	
		}
	}
	vector<int> ret;
	int j = T;
	int i = datos.size();
	while (j > 0 && i > 0) {
		if ((3 * datos[i-1].first) <= j && dp[i - 1][j] != dp[i][j])  {
			ret.push_back(i - 1);
			j -= (3 * datos[i-1].first);
		}
		--i;
	}

	return { dp[datos.size()][T], ret };
}

bool resuelveCaso() {
    int T;
	cin >> T;
    if (!cin)
        return false;
    int N;
	cin >> N;
	vector<pair<int, int>> datos(N);
	for (auto & i : datos) cin >> i.first >> i.second;
	auto[maximo,ret] = cazatesoros(datos, T);
	sort(ret.begin(), ret.end());
	cout << maximo << "\n" << ret.size() << "\n";
	for (int i = 0; i < ret.size(); ++i) {
		cout << datos[ret[i]].first << " " << datos[ret[i]].second << "\n";
	}
	cout << "---\n";
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