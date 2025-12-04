#include<bits/stdc++.h>

#define R 1
#define L -1

using namespace std;

int getTotLines(string file){
    ifstream inputFile(file);
    if (inputFile.is_open()){
        string temp;
        int count=0;
        while(getline(inputFile, temp)){
            count++;
        }
        inputFile.close();
        return count;
    }
        cout << "error abriendo fichero" << endl;
        return -1;
}

int rotateDial(string line, int dial){
    char aux = line.at(0);
    int dir;
    if(aux == 'R'){
        dir=1;
    }else if(aux == 'L'){
        dir=-1;
    }
    int magnitude = stoi(line.substr(1));
    dial = dial+(dir*(magnitude%100));
    while((dial>=100) | (dial <0)){
        dial=abs(abs(dial)-100);
    }
    cout << dial << endl;
    return dial;
}

int main(){
    string file = "inputdia1.txt";
    int dial=50, passnum=0;
    ifstream passkey(file);

    if(passkey.is_open()){
        string line;
        while(getline(passkey, line)){
            dial = rotateDial(line, dial);
            if(dial==0){
                passnum++;
            }
        }
        cout << "\n" << passnum << endl;
    }
    return -1;
    // cout <<  getTotLines("input.txt") << endl;
}