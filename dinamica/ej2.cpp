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
	Problema: Construyendo Dianas

	i: Sectores usados
	j: Puntuación

	dianas[i][0] = 0
	dianas[0][j] = INF
	dianas[i][j] = min(dianas[i - 1][j - puntos[i - 1]] + 1, diana[i - 1][j]) 	Si j - puntos[i - 1] >= 0 
	dianas[i][j] = diana[i - 1][j]												Si j - puntos[i - 1] < 0

	Coste del algoritmo: N * C
*/

int dianas(const vector<int> & puntos, vector<int> & dp, const int &N) {
	dp[0] = 0;
	for (int i = 1; i <= puntos.size(); ++i) {
		for (int j = puntos[i - 1]; j <= N; ++j)
			dp[j] = min(dp[j - puntos[i - 1]] + 1, dp[j]);
	}
	return dp[N];
}

vector<int> reconstruir(const vector<int> & dp, const vector<int> & puntos, const int &N) {
	vector<int> ret;
	int i = puntos.size(), j = N;
	while (j > 0) {
		if (puntos[i - 1] <= j && dp[j] == dp[j - puntos[i - 1]] + 1) {
			ret.push_back(puntos[i - 1]);
			j -= puntos[i - 1];
		}
		else
			--i;
	}
	return ret;
}


bool resuelveCaso() {
    int N;
	cin >> N;
    if (!cin)
        return false;
    int C;
	cin >> C;
	vector<int> puntos(C);
	for(int & i : puntos) cin >> i; 
	vector<int> dp(N + 1, INF);
	int sol = dianas(puntos, dp, N);
	if (sol != INF && sol != 0) {
		cout << sol << ":";
		vector<int> reco = reconstruir(dp, puntos, N);
		for (int & i : reco)
			cout << " " << i;
	}
	else 
		cout << "Imposible";
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