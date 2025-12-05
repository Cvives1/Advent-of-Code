#include<bits/stdc++.h>
using namespace std;

vector<int> bankToVec(string bank){
    vector<int> temp;
    for(int i=0; i<int(bank.size()); i++){
        temp.push_back(int(bank.at(i)-48));
    }
    return temp;
}

int getPos(vector<int> v, int get, int str, int end){
    for(int i=str; i<end;i++){
        if(v.at(i)==get){
            return i;
        }
    }
    return -1;
}

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


int main(){
    string file = "input.txt", bank;
    ifstream inputFile(file);
    vector<int> v;
    int min=0, max, dec, pos, uni, joltTotal=0;

    while(getline(inputFile, bank)){
        v = bankToVec(bank);
        max=int(v.size()-1);
        dec = joltageDec(v, min, max-1, v).at(0);
        pos = joltageDec(v, min, max-1, v).at(1);
        uni = joltageUni(v, pos+1, max); 

        cout << joltTotal;
        joltTotal+= 10*dec+uni;
        cout << " + " << 10*dec+uni << " = " << joltTotal << endl;
    }

    //cout << dec << " at pos " << pos << endl;


}
