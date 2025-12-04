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

int rotateDial(string line){
    char aux = line.at(0);
    int dir;
    if(aux == 'R'){
        dir=1;
    }else if(aux == 'L'){
        dir=-1;
    }
    int magnitude = stoi(line.substr(1));
    int sumtodial = (dir*(magnitude));
    return sumtodial;
}

int main(){
    string file = "inputdia1.txt";
    int dial=50, passnum=0, sumtodial;
    float passes;
    ifstream passkey(file);

    if(passkey.is_open()){
        string line;
        while(getline(passkey, line)){
            sumtodial = rotateDial(line);
            if( ((sumtodial+dial>100)||(sumtodial+dial<0)) && !((dial==0)&&((sumtodial+dial>(-100))&&(sumtodial+dial<100))) ){
                passes =(abs(sumtodial)/100);
                if((dial!=0)&&((sumtodial%100+dial>100) | (sumtodial%100+dial<0))){
                    passes++;
                }
                passnum+=passes;
            }
            cout << dial << " "; 
            dial = dial+sumtodial%100;
            if((dial>=100) | (dial <0)){
                dial=abs(abs(dial)-100);
            }
            if(dial==0){
                passnum++;
            }
            cout << sumtodial << " -> " << dial << " " << passnum << endl;
        }
        cout << "\n" << passnum << endl;
    }
    return -1;
    // cout <<  getTotLines("input.txt") << endl;
}