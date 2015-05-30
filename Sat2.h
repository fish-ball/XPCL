#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Sat2 {
    
    // colors of a node.
    enum{GRAY = 0, WHITE = 1, BLACK = 2};
    
    int V, scnt, cnt;
    vector<vector<int> > G, R;
    vector<set<int> > CG, CR;
    vector<int> postI, postR, id;
    
    static int opp(int v) {return v&1 ? v-1 : v+1;}
    
    void dfsR(const vector<vector<int> >& GP, int w) {
        id[w] = scnt;
        for(int i = 0, t; i < GP[w].size(); ++i) {
            t = GP[w][i];
            if(id[t] == -1) dfsR(GP, t);
        }
        postI[cnt++] = w;
    }
    
    void SC() {
        postI.resize(V);
        postR.resize(V);
        scnt = cnt = 0;
        id.assign(V, -1);
        for(int v = 0; v < V; ++v) {
            if(id[v] == -1) {
                dfsR(R, v);
            }
        }
        postR = postI;
        scnt = cnt = 0;
        id.assign(V, -1);
        for(int v = V - 1; v >= 0; --v) {
            if(id[postR[v]] == -1) {
                dfsR(G, postR[v]);
                ++scnt;
            }
        }
        CG.assign(scnt, set<int>());
        CR.assign(scnt, set<int>());
        for(int i = 0; i < V; ++i) {
            for(int j = 0; j < G[i].size(); ++j) {
                if(id[i] == id[G[i][j]]) continue;
                CG[id[i]].insert(id[G[i][j]]);
                CR[id[G[i][j]]].insert(id[i]);
            }
        }
    }
    
    void tSort(int w) {
        postR[w] = 1;
        for(set<int>::iterator it = CG[w].begin(); it != CG[w].end(); ++it)
            if(!postR[*it])
                tSort(*it);
        postI.push_back(w);
    }
    
    void shield(int w) {
        postR[w] = BLACK;
        for(set<int>::iterator it = CR[w].begin(); it != CR[w].end(); ++it)
            if(postR[*it] == GRAY)
                shield(*it);
    }
    
    void color() {
        postI.clear();
        postR.assign(scnt, 0);
        for(int i = 0; i < scnt; ++i)
            if(!postR[i])
                tSort(i);
        postR.assign(scnt, GRAY);
        vector<int> oppo(scnt);
        for(int i = 0; i < V; ++i)
            oppo[id[i]] = id[opp(i)];
        for(int i = 0; i < scnt; ++i) {
            int v = postI[i];
            if(postR[v] == GRAY) {
                postR[v] = WHITE;
                shield(oppo[v]);
            }
        }
    }
    
public:
    
    void init(int v) {
        V = v;
        G.assign(V, vector<int>(0));
        R.assign(V, vector<int>(0));
    }
    
    void insert(int v, int w) {
        G[v].push_back(w);
        R[w].push_back(v);
        G[opp(w)].push_back(opp(v));
        R[opp(v)].push_back(opp(w));
    }
    
    bool run() {
        SC();
        for(int i = 0; i < V; i += 2)
            if(id[i] == id[opp(i)])
                return false;
        color();
        postI.clear();
        for(int i = 0; i < V; ++i)
            if(postR[id[i]] == WHITE)
                postI.push_back(i);
        return true;
    }
    
    const vector<int>& getSets() const {return postI;}

};
