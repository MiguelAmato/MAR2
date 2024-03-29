// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
	Problema: Las vacas pensantes

	Llamada inicial: comida(0, N - 1)

	comida(i,j) = maxima comida que ha comido la vaca con los cubos i y j de los extremos disponibles
	siendo 0 <= i <= j <= N - 1. Solo puede elegir el cubo i o el cubo j para comer, el otro sera comido por 
	devoradora. La tabla se rellenará con -1 para decir los subproblemas no revisados

	i = cubo del extremo izquierdo actual
	j = cubo del extremo derecho actual

	dp[i][j] = 0 					si i > j
	dp[i][j] = max(izq, der)		si i <= j
	izq = dp[i+2][j] + cubos[i]		si cubos[i+1] > cubos[j] Si devoradora come el extremo izquierdo habiendo comido la vaca del izquierdo antes
	izq = dp[i+1][j-1] + cubos[i]	si cubos[i+1] <= cubos[j] 
	der = dp[i][j-2] + cubos[j]		si cubos[j-1] > cubos[i] Si devoradora come el extremo derecho habiendo comido la vaca del derecho antes
	der = dp[i+1][j-1] + cubos[j]	si cubos[j-1] <= cubos[i]

	Coste en tiempo: O(N * N) Siendo N el numero de cubos
	Coste en espacio: O(n^2)
*/

int comida(const vector<int> & cubos, vector<vector<int>> & dp, int i, int j) {
	int & ret = dp[i][j];
	if (ret == -1) {
		if (i > j) ret = 0;
		else {
			int izq, der;
			if (i + 1 < cubos.size() && cubos[i + 1] > cubos[j])
				izq = comida(cubos,dp,i+2,j) + cubos[i];
			else
				izq = comida(cubos,dp,i+1,j-1) + cubos[i];
			if (j - 1 >= 0 && cubos[j - 1] > cubos[i])
				der = comida(cubos,dp,i,j-2) + cubos[j];
			else
				der = comida(cubos,dp,i+1,j-1) + cubos[j];
			ret = max(izq,der);
		}
	}
	return ret;
}

bool resuelveCaso() {
    int N;
	cin >> N;
    if (N == 0)
        return false;
    vector<int> cubos(N);
	for (int & i : cubos) cin >> i;
	vector<vector<int>> dp(N, vector<int>(N, -1)); // Inicializamos a un valor no posible como -1
	cout << comida(cubos, dp, 0, N - 1) << "\n";
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
