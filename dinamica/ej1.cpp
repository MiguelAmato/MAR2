// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

#define INF 1000000000000000000

/*
    Subproblema 1: Calcular las posibles combinaciones de cuerdas que se pueden usar para formar una de longitud j

    i: Numero de cuerdas usadas
    j: Cuanto me falta de longitud para llegar a L

    Función recursiva (i, j):
    s1(i, 0) = 1;
    s1(0, j) = 0;
    s1(i, j) = s1(i - 1, j - cuerdas[i - 1]) + s1(i - 1, j);        Si j - cuerdas[i - 1] >= 0
    s1(i, j) = s1(i - 1, j);                                        Si j - cuerdas[i - 1] < 0

    El coste del algoritmo es: N * L
*/

long long int s1(const vector<int> &cuerdas, const int &L) {
    vector<long long int> dp(L + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= cuerdas.size(); ++i) {
        for (int j = L; j - cuerdas[i - 1] >= 0; --j) 
            dp[j] = dp[j - cuerdas[i - 1]] + dp[j];
    }
    return dp[L];
}

/*
    Subproblema 2: Calcular el mínimo de cuerdas que se pueden usar para llegar a una longitud j

    i: Numero de cuerdas usadas
    j: Cuanto me falta de longitud para llegar a L

    Función recursiva (i, j):
    s2(i, 0) = 0;
    s2(0, j) = INF;
    s2(i, j) = min(s2(i - 1, j - cuerdas[i - 1]) + 1, s2(i - 1, j));        Si j - cuerdas[i - 1] >= 0
    s2(i, j) = s1(i - 1, j);                                                Si j - cuerdas[i - 1] < 0

    El coste del algoritmo es: N * L
*/

long long int s2(const vector<int> &cuerdas, const int &L) {
    vector<long long int> dp(L + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= cuerdas.size(); ++i) {
        for (int j = L; j - cuerdas[i - 1] >= 0; --j) 
            dp[j] = min(dp[j - cuerdas[i - 1]] + 1, dp[j]);
    }
    return dp[L];
}

/*
    Subproblema 3: Minimo coste necesario para conseguir una cuerda de longitud j

    i: Numero de cuerdas usadas
    j: Cuanto me falta de longitud para llegar a L

    Función recursiva (i, j):
    s3(i, 0) = 0
    s3(0, j) = INF
    s3(i, j) = min(s3(i - 1, j - cuerdas[i - 1]) + precio[i - 1], s3(i - 1, j));        Si j - cuerdas[i - 1] >= 0
    s3(i, j) = s1(i - 1, j);                                                            Si j - cuerdas[i - 1] < 0

    El coste del algoritmo es: N * L
*/

long long int s3(const vector<int> &cuerdas, const vector<int> &precio, const int &L) {
    vector<long long int> dp(L + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= cuerdas.size(); ++i) {
        for (int j = L; j - cuerdas[i - 1] >= 0; --j) 
            dp[j] = min(dp[j - cuerdas[i - 1]] + precio[i - 1], dp[j]);
    }
    return dp[L];
}


bool resuelveCaso() {
    int N;
    std::cin >> N;
    if (!std::cin)
        return false;
    int L;
    std::cin >> L;
    std::vector<int> cuerdas(N);
    std::vector<int> precios(N);
    for (int i = 0; i < N; ++i) std::cin >> cuerdas[i] >> precios[i];
    long long int mat = s1(cuerdas, L);
    if (mat > 0)
        std::cout << "SI" << " " << mat << " " << s2(cuerdas, L) << " " << s3(cuerdas, precios, L) << "\n";
    else  
        std::cout << "NO\n";
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