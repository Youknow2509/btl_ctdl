#include <bits/stdc++.h>

using namespace std;

struct Tree{
    pair<string, string> data;
    Tree *nodeLeft, *nodeRight;
};

Tree *newNode(pair<string, string> p){
    Tree *t  = new Tree();
    t->data = p;
    t->nodeLeft = t->nodeRight = NULL;
    return t;
}

Tree *insert_node(Tree *t, pair<string, string> p){
    if (!t){
        return newNode(p);
    }
    if (p.first < t->data.first)
        t->nodeLeft = insert_node(t->nodeLeft, p);
    else
        t->nodeRight = insert_node(t->nodeRight, p);
    return t;
}   

void show_tree(Tree *t){
    
}

int main(){

    #ifndef ONLINE_JUDGE
    freopen("file/inp.txt", "r", stdin);
    freopen("file/out.txt", "w", stdout);
    #endif

    return 0;
}