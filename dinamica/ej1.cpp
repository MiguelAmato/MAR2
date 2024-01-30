// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int subproblema1(const vector<int> &cuerdas, int rellenar, int i) {
    if (!rellenar) 
        return 1;
    else if (!i)
        return 0;
    else {
        if (rellenar - cuerdas[i - 1] >= 0)
            return subproblema1(cuerdas, rellenar - cuerdas[i - 1], i - 1)+ subproblema1(cuerdas, rellenar, i - 1);
        else
            return subproblema1(cuerdas, rellenar, i - 1);
    }
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin)
        return false;
    int L;
    cin >> L;
    vector<int> cuerdas(N);
    int aux;
    for (int &i : cuerdas) {
        cin >> i >> aux;
    }
    int mat = subproblema1(cuerdas, L, N);
    if (mat > 0) 
        cout << "SI\n" << " " << mat << "\n"; // continuará...
    else 
        cout << "NO\n";
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