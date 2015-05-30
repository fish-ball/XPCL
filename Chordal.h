//////////////////////////////////////////////////////////
//                     弦图判定 v1.0                    //
//////////////////////////////////////////////////////////
//                                                      //
// 1. init:     清空图;                                 //
// 2. insert:   插入一个新的边;                         //
// 3. chordal:  判别该图是否弦图;                       // 
//                                                      //
//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<int SZ>
class Graph {

    int V,  E;
    vector<int> G[SZ];
    vector<pair<int, int> > P;

    bool X[SZ][SZ];

    int ord[SZ], cdn[SZ], seq[SZ];
    
public:
    
    void init(int N) {
        V = N;
        for( int i = 0; i < V; ++i )
            G[i].clear();
        memset(X, 0, sizeof(X));
    }
    
    void insert(int v, int w) {
        G[v].push_back(w);
        G[w].push_back(v);
        X[v][w] = X[w][v] = true;
    }
    
    bool chordal() {
        memset(ord, -1, sizeof(ord));
        memset(cdn, 0, sizeof(cdn));
        for(int rem = 0; rem < V; ++rem) {
            int mx = -1, pos;
            for(int i = 0; i < V; ++i)
                if(ord[i] == -1 && cdn[i] > mx)
                    mx = cdn[pos = i];
            ord[pos] = rem;
            seq[rem] = pos;
            for(int i = 0; i < G[pos].size(); ++i)
                ++cdn[G[pos][i]];
        }
        P.clear();
        for(int i = 1; i < V; ++i) {
            int v = seq[i], u, w, p = -1;
            vector<int> temp(0);
            for(int j = 0; j < G[v].size(); ++j) {
                u = G[v][j];
                if(ord[u] < i) {
                    temp.push_back(u);
                    if(ord[u] > p)
                        p = ord[w = u];
                }
            }
            for(int k = 0; k < temp.size(); ++k)
                if(temp[k] != w)
                    P.push_back(make_pair(temp[k], w));
        }
        for(int i = 0; i < P.size(); ++i)
            if(!X[P[i].first][P[i].second])
                return  false;
        return  true;
    }
    
};

//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////
