// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
	Problema: Subsecuencia común más larga

	subsecuencia(i,j) = en la tabla simboliza a la subsecuencia común más grande que se puede hacer desde la 
	pos i de la primera palabra con la pos j de la segunda palabra.

	i: Posición a revisar de la primera cadena.
	j: Posición a revisar de la segunda cadena.

	subsecuencia(i,j) = 0 												Si i >= N1 && j >= N2, Siendo N1 y N2 el tamaño de las dos palabras.
	subsecuencia(i,j) = subsecuencia(i+1,j+1) + 1 						Si p1[i] == p2[j] 
	subsecuencia(i,j) = max(subsecuencia(i+1,j), subsecuencia(i,j+1))	Si p1[i] != p2[j]
*/

int subsecuencia(const string & p1, const string & p2, vector<vector<int>> & dp, int i, int j) {
	if (i >= p1.size() || j >= p2.size()) return 0;
	int & ret = dp[i][j];
	if (ret == -1) {
		if (p1[i] == p2[j])
			ret = subsecuencia(p1,p2,dp,i+1,j+1) + 1;
		else if (p1[i] != p2[j])
			ret = max(subsecuencia(p1,p2,dp,i+1,j), subsecuencia(p1,p2,dp,i,j+1));
	}
	return ret;
}

void construir(const string & p1, const string & p2, vector<vector<int>> & dp, int i, int j, string & sol) {
	if (i >= p1.size() || j >= p2.size()) return;
	if (p1[i] == p2[j]) {
		sol.push_back(p1[i]);
		construir(p1, p2, dp, i+1, j+1, sol);
	}
	else if (dp[i][j+1] < dp[i+1][j])
		construir(p1, p2, dp, i+1, j, sol);
	else
		construir(p1, p2, dp, i, j+1, sol);
}

bool resuelveCaso() {
    string p1;
	cin >> p1;
    if (!cin)
        return false;
	string p2;
    cin >> p2;
	vector<vector<int>> dp(p1.size() + 1, vector<int>(p2.size() + 1, -1));
	int sol = subsecuencia(p1, p2, dp, 0, 0);
	string subsecuencia = "";
	construir(p1,p2,dp,0,0,subsecuencia);
	cout << subsecuencia << "\n";
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