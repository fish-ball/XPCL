/////////////////////////////////////////////////
//              ��ƫ��ģ�� v1.0                //
/////////////////////////////////////////////////
//                                             //
//               Documentation                 //
//                                             //
// ## ��ģ����ά��һ����ƫ��ʵ�ֵĿɺϲ���;    //
//                                             //
// * ģ��ԭ��: LTree<class T, class Op>;       //
// 1) T, ��Ԫ�ص�����;                         //
// 2) Op, �����ȵıȽ�׼�򣬶�Ԫ��������;      //
//      Ĭ��Ϊ less<T>                         //
//                                             //
// * ֧�ֲ���:                                 //
// 1) LTree()������һ������ƫ��-��;            //
// 2) LTree( T Elem )������һ�����ڵ��;       //
// 3) LT.size()�����ض�Ԫ�ظ���;               //
// 4) LT.empty()���п�;                        // 
// 5) LT.top()�����ضѶ���Ԫ��;     O(1)       //
// 6) LT.pop()�������Ѷ�Ԫ��;       O(logn)    // 
// 7) LT.insert(Elem)��������Ԫ��;  O(logn)    //
// 8) merge(LT1, LT2)���ϲ�������;  O(logn)    //
// 9) LT.clear()����յ�ǰ��;       O(n)       //
//                                             //
// * ��ע:                                     //
// 1) ���жԺϲ�ʱ���������������� LT1��LT2,   //
//    �ϲ�������浽 LT1��LT2 ���ÿ�;          // 
//                                             // 
/////////////////////////////////////////////////
//          2008 CopyRight(c) by elf           //
/////////////////////////////////////////////////

#include <functional>
#include <algorithm>
using namespace std;

/////////////// Inside Node Struct //////////////
//          ��ƫ�������ڲ�ʵ��               // 
/////////////////////////////////////////////////
template<class T, class Op = less<T> >
struct Node {
    T   key;
    int dist;
    Node<T, Op>*   L;
    Node<T, Op>*   R;
    // Constructor
    Node() : L( NULL ), R( NULL ) {}
    Node( T k, int d = 0 ) :
        key( k ), dist( d ),
        L( NULL ), R( NULL ) {}
};

template<class T, class Op>
void merge( Node<T, Op>* &A, Node<T, Op>* &B ) {
    
    if( A == NULL ) { swap( A, B ); return; }
    if( B == NULL ) return;
    
    if( Op()( B -> key, A -> key ) )
        swap( A, B );
    merge( A -> R, B );
    
    if( A -> L == NULL ||
        A -> R != NULL &&
        A -> R -> dist >
        A -> L -> dist ) {
        swap( A -> R, A -> L );
    }
    
    if( A -> R == NULL )    A -> dist = 0;
    else   A -> dist = A -> R -> dist + 1;
    
    B = NULL;
    
}

template<class T, class Op>
void destroy( Node<T, Op>* &tree ) {
    if( tree -> L ) destroy( tree -> L );
    if( tree -> R ) destroy( tree -> R );
    delete  tree;
    tree = NULL;
}



////////// Complete Class Declarations //////////
//                ��ƫ��ģ����                 // 
/////////////////////////////////////////////////

// Predeclaration For Friend
template<class T, class Op>
class LTree;

template<class T, class Op>
void merge( LTree<T, Op>&, LTree<T, Op>& );

// Class Declarations 
template<class T, class Op = less<T> >
class LTree {
    
    Node<T, Op>*   root;
    size_t  SZ;

public:
    
    T top() const { return root -> key; }
    bool empty() const { return root == NULL; }
    size_t size() const { return SZ; }
    friend void merge<>( LTree<T, Op>&, LTree<T, Op>& );
    void pop();
    void insert( T val );
    
    LTree() : root( NULL ), SZ( 0 ) {}
    LTree( const T& elem ) : SZ( 1 )
        { root = new Node<T, Op>( elem ); }
    void clear() { if( root ) destroy( root ); SZ = 0; }
    ~LTree() { if( root ) destroy( root ); }
    
};



//////// Complete Class Implemtentation /////////
//              ��ƫ��ģ����ʵ��               // 
/////////////////////////////////////////////////

// �ϲ����� 
template<class T, class Op>
void merge( LTree<T, Op>& A, LTree<T, Op>& B ) {
    merge( A.root, B.root );
    A.SZ += B.SZ;
    B.SZ = 0;
}

// ����ڵ���� 
template<class T, class Op>
void LTree<T, Op>::insert( T val ) {
    Node<T, Op>* newTree = new Node<T, Op>( val );
    merge( root, newTree );
    ++SZ;
}

// ɾ�������ڵ���� 
template<class T, class Op>
void LTree<T, Op>::pop() {
    merge( root -> L, root -> R );
    Node<T, Op>* newRoot = root -> L;
    delete  root;
    root = newRoot;
    --SZ;
}


/////////////////////////////////////////////////
//        Copyright(c) 2008 by elf, zzu        // 
/////////////////////////////////////////////////
