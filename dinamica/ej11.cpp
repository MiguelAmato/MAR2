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
	Problema: Mejor no llevar muchas monedas

	i : Monedas de valor usadas
	j : Precio a pagar

	monedas(i,j) : el minimo numero de monedas que se puede pagar usando i monedas de valor para pagar un precio j

	monedas(0,j) :  INF
	monedas(i,0) : 	0
	monedas(i,j) : 	min(monedas(i-1,j-valor[i-1]) + 1, monedas(i-1,j));		Si cant[i-1] > 0 && j-valor[i-1] >= 0
	monedas(i,j) : 	monedas(i-1,j);

	Coste del algoritmo: M*P siendo M el numero de monedas y P el precio a pagar 
	Coste en espacio: O(n^2)
*/

int monedas(const vector<int> & valor, vector<int> & cant, int & P) {
	vector<int> dp(P + 1, INF);
	dp[0] = 0;
	for (int i = 1; i <= valor.size(); ++i) {
		for (int j = 1; j <= P && cant[i-1] > 0; ++j) {
			if (j - valor[i-1] >= 0) {
				dp[j] = min(dp[j - valor[i-1]] + 1, dp[j]);
				if (dp[j] == dp[j - valor[i-1]] + 1)
					--cant[i-1];
			}
		}
	}
	return dp[P];
}

bool resuelveCaso() {
    int N;
	cin >> N;
    if (!cin)
        return false;
    vector<int> valor(N);
	for (int & i : valor) cin >> i;
	vector<int> cant(N);
	for (int & i : cant) cin >> i;
	int P;
	cin >> P;
	cout << monedas(valor, cant, P) << "\n";
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