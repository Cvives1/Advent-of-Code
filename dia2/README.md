## **¿Por qué hemos elegido este problema?** **¿Qué técnica hemos utilizado?**
Hemos elegido este problema porque desde el principio vimos que se podía aplicar de forma clara la técnica de divide y vencerás. Debido a que nos daban rangos numéricos amplios y con esta técnica se puede optimizar el problema.

## **Descripción de la resolución problema**
Para comenzar, hemos utilizado una función para leer el input y que nos devolviese un vector de parejas long long.
### dia2parte1.cpp | dia2parte2.cpp
```vector<pair<long long, long long>> leerInput(const string& ruta){}```

    
Después he creado una función de tipo bool, que comprueba si un numero sigue un patrón (diferente en cada parte).  
### Parte1  
En la parte 1, pide que **el patrón sea que las dos mitades del número sean iguales**, entonces se convierte el número en un string y si el tamaño de ese string no es par no puede seguir este patrón. Tras esto, se hace la mitad del tamaño del string, y por último se comparan las dos mitades para que devuelva true si es igual y false si es diferente.
```
bool NumeroInvalido(long long n){ 
    string s = to_string(n);
     if (s.size() % 2 != 0){ 
        return false; }
      
     int half = s.size() / 2; 
      
      return s.substr(0, half) == s.substr(half, half); 
    }
```  
### Parte 2
En la parte 2, pide que **cumpla cualquier tipo de patrón**, por ejemplo 121212 (se repite el número 3 veces), entonces se hace lo mismo de convertir el número en string, y se crea una variable tipo string llamada **patron** donde se van a poner los posibles patrones y otra llamada **repetido** que es donde se van a poner repetidas veces los patrones obtenidos, para compararlo con el string original.
```
bool NumeroInvalido(long long n) {
    string s = to_string(n);
    int tamaño = s.size();

    
    for (int l = 1; l <= tamaño / 2; l++) {
        
        string patron = s.substr(0, l); //pilla un posible patron 
        string repetido = "";
        int veces = tamaño / l;

        for (int i = 0; i < veces; i++){
            repetido += patron; //coloca el posible patron en repetido

        } 
        if (repetido == s){
            return true; //si ese patron coincide devuelve true
    
        }
    }

    return false;
}
```
Por último, he creado la función procesarRango que devuelve la suma de los número invalidos dentro de un rango. **En esta función es donde se utiliza la técnica de divide y venerás**.  
Esta función divide el rango en 2 mitades continuamente hasta llegar al caso base (que solo haya 1 unidad de diferencia entre la parte izquierda y la derecha).
```
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
```

## **Otras alternativas**  
No he probado otra alternativa debido a que hemos visto de primeras el divide y vencerás, pero por ejemplo hemos descartado **grafos** de manera inmediata debido a que no aporta nada útil.  

## **Valoración personal sobre lo aprendido**
Haciendo este código hemos aprendido nuevas clases de variables como **long long** (que nos permite trabajar con números más grandes) o **pair**(para manejar datos de manera más ordenada), y la manera de utilizar el **for** para recorrer un vector.
``` 
for (pair<long long, long long>& r : rangos){}
```
