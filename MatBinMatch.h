//////////////////////////////////////////////////////////
//          ����ƥ���㷨��ģ�壨�ڽӾ���ʵ�֣� v1.3     //
//////////////////////////////////////////////////////////
//                                                      //
// ��һ����Ȩ����ͼ�����ƥ��                           //
// 1. init:     �����ƥ���ϵ��;                       //
// 2. insert:   ����һ���µ�ƥ���ϵ;                   //
// 3. run:      ��ȷ����С��ƥ���ϵ�����м���;         //
// 4. matchCnt: �������ƥ����;                         // 
// 5. getMatch: ����ƥ���ŵ� vector<pair>;            // 
//                                                      //
// 1.1 ������������ƥ�书��;                            //
// 1.2 �����ڽӾ���汾���߱�ɾ�߹���;                  //
// 1.3 ��������ƥ�书��;                                // 
//                                                      //
//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////

#include <vector>
#include <algorithm>
using namespace std;
 
class BinMatch {
    
    int     X,  Y,  M; 
    vector<vector<bool> >   G;
    vector<int>     back;
    vector<bool>    mark;
    
    bool find( int v ) {
        for( int w = 0; w <= Y; ++w ) {
            if( G[v][w] && !mark[w] ) {
                mark[w] = true;
                if( back[w] == -1 || find( back[w] ) ) {
                    back[w] = v;
                    return  true;
                }
            }
        } 
        return  false;
    }
    
public:
    
    void init( int x, int y ) {
        X = x;  Y = y; 
        G.assign( X + 1, vector<bool>( Y + 1, false ) );
    } 
    
    void insert( int v, int w ) { G[v][w] = true; }
    
    void erase( int v, int w ) { G[v][w] = false; }
    
    void run() {
        back.assign( Y + 1, -1 );
        for( int v = M = 0; v <= X; ++v ) {
            mark.assign( Y + 1, false ); 
            M += find( v );
        }
    } 
    
    int matchCnt() const { return M; }
    
    void runPerfect() {
        run();
        vector<int> old_match = back; 
        int         old_matchs = M; 
        vector<int> exclude;
        for( int i = 0; i <= Y; ++i ) {
            if( old_match[i] != -1 ) {
                G[old_match[i]][i] = false;
                run();
                G[old_match[i]][i] = true;
                if( M == old_matchs )
                    exclude.push_back( i ); 
            } 
        } 
        for( int i = 0; i < exclude.size(); ++i )
            old_match[exclude[i]] = -1;
        back = old_match;
    } 
    
    vector<pair<int, int> > getMatch() const {
        vector<pair<int, int> > ans;
        for( int i = 0; i < Y; ++i )
            if( back[i] != -1 )
                 ans.push_back( make_pair( back[i], i ) );
        sort( ans.begin(), ans.end() );
        return  ans;
    }
    
    
}; 

//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////
