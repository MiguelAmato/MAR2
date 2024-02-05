// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
	Problema : Aibofobia

	aiobofobia(i,j) = 0													Si i > j
	aiobofobia(i,j) = 1													Si i == j
	aiobofobia(i,j) = min(aiobofobia(i,j-1), aiobofobia(i+1,j)) + 1		Si palabra[i] != palabra[j]
	aiobofobia(i,j) = aiobofobia(i+1,j-1)								Si palabra[i] == palabra[j]

	Coste del algoritmo : N * N Siendo N el numero de letras que tiene la palabra
*/

int aiobofobia(const string & palabra, vector<vector<int>> & dp, int i, int j) {
	int & ret = dp[i][j];
	if (ret == -1) {
		if (i >= j) ret = 0;
		else if (palabra[i] != palabra[j])
			ret = min(aiobofobia(palabra,dp,i,j-1), aiobofobia(palabra,dp,i+1,j)) + 1;
		else
			ret = aiobofobia(palabra,dp,i+1,j-1);
	}
	return ret;
}

/*
	Reconstruccion: Si i == j significa que la palabra que hay que construir es un caracter, asi que se añade ese 
	caracter, si palabra[i] == palabra[j] significa que no hay que añadir ninguna letra extra, por lo que se añaden
	las que ya estaban en la palabra y se avanza con la recursion, si dp[i][j] == dp[i][j-1] + 1 significa que
	se ha añadido una letra por la izquierda, lo que se hace es que el primer push_back es la ultima letra mirada
	de palabra, lo mismo en caso contrario para dp[i][j] == dp[i + 1][j] + 1
*/

void construir(string & palabra, const vector<vector<int>> & dp, int i, int j, string & sol) {
	if (i > j) return;
	else if (i == j) sol.push_back(palabra[i]);
	else {
		if (palabra[i] == palabra[j]) {
			sol.push_back(palabra[i]);
			construir(palabra, dp, i + 1, j - 1, sol);
			sol.push_back(palabra[j]);
		}
		else if (dp[i][j] == dp[i][j-1] + 1) {
			sol.push_back(palabra[j]);
			construir(palabra, dp, i, j - 1, sol);
			sol.push_back(palabra[j]);
		}
		else if (dp[i][j] == dp[i + 1][j] + 1) {
			sol.push_back(palabra[i]);
			construir(palabra, dp, i + 1, j, sol);
			sol.push_back(palabra[i]);
		}
	}
}

bool resuelveCaso() {
    string palabra;
	cin >> palabra;
    if (!cin)
        return false;
    vector<vector<int>> dp(palabra.size(), vector<int>(palabra.size(), -1));
	int sol = aiobofobia(palabra, dp, 0, palabra.size() - 1);
	string palindromo = "";
	construir(palabra, dp, 0, palabra.size() - 1, palindromo);
	cout << sol << " " << palindromo << "\n";
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