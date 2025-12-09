## **¿Por qué hemos elegido este problema?** **¿Qué técnica hemos utilizado?**
Hemos elegido este problema porque desde que leimos de lo que constaba, vimos que seria bastante facil de utilizar dyv como manera de encontrar el valor mas alto en cada uno de los vectores conteniendo las baterias para encontrar facilmente los joltages.

## **Descripción de la resolución problema**
Lo primero que hacemos luego de definir el archivo .txt de entrada es ir, en un bucle, convirtiendo cada linea leida en un vector conteniendo cada caracter en un vector para poder analizar mediante la siguiente funcion:
```
vector<int> bankToVec(string bank){
    vector<int> temp;
    for(int i=0; i<int(bank.size()); i++){
        temp.push_back(int(bank.at(i)-48));
    }
    return temp;
}
```
### Parte1  
La parte 1 pide que en cada banco se enciendan exactamente 2 baterias.
Nuestra idea original y la que implementamos en la parte 1 fue la de primero analizar el vector salvo el ultimo caracter para encontrar (mediante dyv) el de valor mas alto y definir ese como la posicion de los dieces, y luego repetir el proceso empezando desde la siguiente posicion donde se encontro el numero mas alto e incluyendo el valor final para encontrar el 2do valor mas alto para sumarle al anterior.
```
vector<int> joltageDec(vector<int> bank, int str, int end, vector<int> buffer){
    int mid = (str + end)/2, pos;
    vector<int> outID={0,0};
    if((end-str)==0){
        outID[0]=bank.at(str);
        outID[1]=str;
        return outID;
    }else{
        int bot=joltageDec(bank, str, mid, buffer).at(0), top=joltageDec(bank, mid+1, end, buffer).at(0);
        if(bot>=top){
            pos=getPos(buffer,bot,0, int(buffer.size()));
            outID[0]=bot;
            outID[1]=pos;
            return outID;
        }else{
            pos=getPos(buffer,top,0,int(buffer.size()));
            outID[0]=top;
            outID[1]=pos;
            return outID;
        }
    }
}
```
La funcion joltageDec devuelve un vector de ints porque mediante este metodo, es posible devolver tanto el numero que queremos como la posicion en la que se encontraba para darle como parametro a la otra funcion:
```
int joltageUni(vector<int> bank, int str, int end){
    int mid = (str+end)/2;
    if((end-str)==0){
        return bank.at(str);
    }else{
        int bot =joltageUni(bank, str, mid), top =joltageUni(bank, mid+1, end);
        if(bot>=top){
            return bot;
        }else{
            return top;
        }
    }
}
```
Luego, se suma 10 veces joltageDec con joltageUni y luego con todas sus iteraciones pasadas y se pasa por pantalla hasta acabar el proceso. 

### Parte 2
La parte 2, a diferencia de la parte 1, pide 12 baterias encendidas en lugar de 2, asi que tuvimos que cambiar nuestro metodo de obtencion. En lugar de utilizar una funcion separada para cada digito, hemos eliminado la funcion joltageUni y hemos cambiado la funcion joltageDec a joltage para que funcione iterativamente, dependiendo en su lugar de la cantidad de baterias que pidan, no especificamente ningun numero en particular. 
```
vector<int> joltage(vector<int> bank, int str, int end, vector<int> buffer, int getmin){
    int mid = (str + end)/2, pos;
    vector<int> outID={0,0};
    if((end-str)==0){
        outID[0]=bank.at(str);
        outID[1]=str;
        return outID;
    }else{
        int bot=joltage(bank, str, mid, buffer, getmin).at(0), top=joltage(bank, mid+1, end, buffer, getmin).at(0);
        if(bot>=top){
            pos=getPos(buffer,bot,getmin, int(buffer.size()));
            outID[0]=bot;
            outID[1]=pos;
            return outID;
        }else{
            pos=getPos(buffer,top,getmin,int(buffer.size()));
            outID[0]=top;
            outID[1]=pos;
            return outID;
        }
    }
}
```
Adicionalmente, el main tambien ha sido alterado para poder acomodar estos cambios al proceso. 
```
int main(){
    string file = "input.txt", bank;
    ifstream inputFile(file);
    vector<int> v;
    int min=0, max, batteries= 12;
    long long joltTotal=0, toSum;

    while(getline(inputFile, bank)){
        min=0;
        v = bankToVec(bank);
        max=int(v.size()-1);
        for(int i=batteries-1; i>=0; i--){
            toSum=(joltage(v,min,max-i,v,min).at(0));
            min=joltage(v,min,max-i,v,min).at(1);
            min++;
            joltTotal+=toSum*pow(10,i);
        }
        cout << "-> " << joltTotal << " " << endl;
    }
}
```

## **Otras alternativas**  
La alternativa utilizada para la parte 2 tambien es una funcional para la parte 1 y fue lo que utilizamos primero para probar que el nuevo sistema. Respecto a otras tecnicas que podriamos haber utilizado para resolver este dia, a lo mejor podria ser posible resolverse mediante arboles. 

## **Valoración personal sobre lo aprendido**
Este dia fue bastante divertido de resolver, puesto a que el cambio de la parte 1 a la parte 2 presento un cambio de perspectiva interesante y un nuevo desafio para adaptar. Una habilidad relevante que aprendimos mediante la resolucion del problema fue el uso de funciones vectoriales para poder devolver una mayor cantidad de parametros. 
