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

	Coste del algoritmo: M*P*C siendo M el numero de monedas y P el precio a pagar y C la cantidad de monedas que hay 
	Coste en espacio: O(n^2)
*/

int monedas(const vector<int> & valor, vector<int> & cant, const int & N, const int & P) {
	vector<vector<int>> dp(N + 1, vector<int>(P + 1, INF));
	dp[0][0] = 0;
	for (int i = 1 ; i <= valor.size(); ++i) {
		dp[i][0] = 0;
		for (int j = 1; j <= P; ++j) {
			int aux = INF;
			for (int k = 0; k <= cant[i-1] && valor[i-1] * k <= j; ++k) {
				if (dp[i-1][j-(valor[i-1]*k)] != INF)
					aux = min(aux, dp[i-1][j-(valor[i-1]*k)] + k);
			}
			dp[i][j] = aux;
		}
	}
	return dp[N][P];
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
	int sol = monedas(valor, cant, N, P);
	if (sol != INF)
		cout << "SI " << sol;
	else
		cout << "NO";
	cout << "\n"; 
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