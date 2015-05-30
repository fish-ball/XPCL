#include <vector>
using namespace std;

template<int SZ>
class Graph {
    int V,  E;
    vector<int> G[SZ];
public:
    void clear(int N = SZ) { for(int i=0; i<N; ++i) G[i].clear(); }
    void init(int N) { clear(V = N); }
    insert(int v, int w) { G[v].push_back(w); }
    bool isChordal() const;
};

int n, m, mk[100], deg[100], PEO[100], 

bool Graph::isChordal() const {
    
}
