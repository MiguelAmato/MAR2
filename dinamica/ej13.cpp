// Nombre del alumno Miguel Antonio Amato Hermo
// Usuario del Juez MAR203


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
	Problema: Parentesis

	a(i,j): 

	b(i,j):

	c(i,j):

*/


bool resuelveCaso() {
    string cadena;
	cin >> cadena;
    if (!cin)
        return false;
    
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