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
	Luego subo toda, la funcion y los costes, la tengo en el portatil
*/

pair<int, int> bombilla(const vector<int> & costes, const vector<int> & potencias, const int pMin, const int pMax) {
	vector<int> dp(pMax + 1, INF);
	dp[0] = 0;
	for (int i = 1; i <= costes.size(); ++i) {
		for (int j = potencias[i - 1]; j <= pMax; ++j)
			dp[j] = min(dp[j - potencias[i - 1]] + costes[i - 1], dp[j]);
	}
	int mini = INF, pos;
	for (int i = pMin; i <= pMax; ++i) {
		if (dp[i] < mini) {
			mini = dp[i];
			pos = i;
		}
	}
	pair<int, int> ret;
	ret.first = mini;
	ret.second = pos;
	return ret;
}

bool resuelveCaso() {
	int N;
    cin >> N;
    if (!cin)
        return false;
    int pMax, pMin;
	cin >> pMax >> pMin;
	vector<int> potencias(N);
	for (int & i : potencias) cin >> i;
	vector<int> costes(N);
	for (int & i : costes) cin >> i;
	pair<int, int> ret = bombilla(costes, potencias, pMin, pMax);
	if (ret.first != INF)
		cout << ret.first << " " << ret.second << "\n";
	else
		cout << "IMPOSIBLE\n";
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