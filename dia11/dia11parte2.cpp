#include <iostream>
#include <string>
#include <unordered_map>
#include "ListLinked.h"
#include "HashTable.h"
#include "TableEntry.h"

using namespace std;

// Clave para memoización: nodo + estado de dac y fft
struct State {
    string node;
    bool hasDac;
    bool hasFft;

    bool operator==(const State &other) const {
        return node == other.node && hasDac == other.hasDac && hasFft == other.hasFft;
    }
};

// Hash para usar State en unordered_map
struct StateHash {
    size_t operator()(const State& s) const {
        return hash<string>()(s.node) ^ hash<int>()(s.hasDac) ^ (hash<int>()(s.hasFft) << 1);
    }
};

// DFS con memoización usando long long
long long dfs(HashTable<ListLinked<string>*> &graph, const string &node, bool hasDac, bool hasFft,
              unordered_map<State,long long,StateHash> &memo) {

    if (node == "out") {
        return (hasDac && hasFft) ? 1LL : 0LL;
    }

    State st{node, hasDac, hasFft};
    if (memo.count(st)) return memo[st];

    bool newHasDac = hasDac || node == "dac";
    bool newHasFft = hasFft || node == "fft";

    long long count = 0;
    ListLinked<string>* outs;
    try {
        outs = graph.search(node);
    } catch(...) {
        return 0; // nodo sin salidas
    }

    for(int i=0;i<outs->size();i++){
        string next = outs->get(i);
        count += dfs(graph, next, newHasDac, newHasFft, memo);
    }

    memo[st] = count;
    return count;
}

int main() {
    HashTable<ListLinked<string>*> graph(1000, 1000);

    string line;
    while(getline(cin, line)){
        if(line.empty()) continue;
        size_t pos = line.find(":");
        string node = line.substr(0,pos);
        ListLinked<string>* outs = new ListLinked<string>();
        string rest = line.substr(pos+1);
        size_t start = 0, end;
        while((end=rest.find(" ",start))!=string::npos){
            string out = rest.substr(start,end-start);
            if(!out.empty()) outs->append(out);
            start = end+1;
        }
        string last = rest.substr(start);
        if(!last.empty()) outs->append(last);
        graph.insert(node, outs);
    }

    unordered_map<State,long long,StateHash> memo;
    long long totalPaths = dfs(graph, "svr", false, false, memo);
    cout << totalPaths << endl;

    return 0;
}
