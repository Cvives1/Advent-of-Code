#include <bits/stdc++.h>
using namespace std;

bool NumeroInvalido(long long n) {
    string s = to_string(n);
    int tamaño = s.size();

    
    for (int l = 1; l <= tamaño / 2; l++) {
        
        string patron = s.substr(0, l); //pilla un posible patron 
        string repetido = "";
        int veces = tamaño / l;

        for (int i = 0; i < veces; i++)
            repetido += patron; //coloca el posible patron en repetido

        if (repetido == s)
            return true;  //si ese patron coincide devuelve true
    }

    return false;
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
    string ruta = "input-dia2";
    vector<pair<long long, long long>> rangos = leerInput(ruta);


    long long total = 0;

    for (pair<long long, long long>& r : rangos) {
        total += procesarRango(r.first, r.second); //r es como la i en un for simple, va recorriendo las parejas del vector
    } //el for para al llegar al final del contenido

    cout << "Suma total de IDs invalidos = " << total << endl;

    return 0;
}
