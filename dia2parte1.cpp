#include <bits/stdc++.h>
using namespace std;

bool NumeroInvalido(long long n){ 
    string s = to_string(n);
     if (s.size() % 2 != 0){ 
        return false; }
      
     int half = s.size() / 2; 
      
      return s.substr(0, half) == s.substr(half, half); 
    }

    long long procesarRango(long long L, long long R) {
    
    if (R - L <= 1) {
        long long suma = 0;
        for (long long i = L; i <= R; i++) {
            if (NumeroInvalido(i)){
                suma += i; //si es invalido se suma
            } 
        }
        return suma;
    }

    
    long long medio = (L + R) / 2;
    long long parteizquierda = procesarRango(L, medio);
    long long partederecha = procesarRango(medio + 1, R);

    return parteizquierda + partederecha;
}

vector<pair<long long, long long>> leerInput(const string& ruta) { //funcion que mira el contenido del txt
    ifstream file(ruta);
    vector<pair<long long, long long>> rangos;

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << ruta << endl;
        return rangos;
    }

    string linea;
    getline(file, linea);

    stringstream ss(linea);
    string token;

    while (getline(ss, token, ',')) {
        if (token.empty()) continue;

        size_t guion = token.find('-');
        if (guion != string::npos) {
            long long inicio = stoll(token.substr(0, guion));
            long long fin = stoll(token.substr(guion + 1));
            rangos.emplace_back(inicio, fin);
        }
    }

    return rangos;
}

int main() {
    string ruta = "input-dia2.txt";
    vector<pair<long long, long long>> rangos = leerInput(ruta);


    long long total = 0;

    for (pair<long long, long long>& r : rangos) {
        total += procesarRango(r.first, r.second); //r es como la i en un for simple, va recorriendo las parejas del vector
    } //el for para al llegar al final del contenido

    cout << "Suma total de IDs invalidos = " << total << endl;

    return 0;
}