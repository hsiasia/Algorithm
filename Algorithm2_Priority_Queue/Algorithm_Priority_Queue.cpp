#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef struct CombinNode
{
    int freq=0;
    char key;
    CombinNode *left=nullptr;
    CombinNode *right=nullptr;
}CombinNode,*CombinNodept;

struct cmp
{
    bool operator() (CombinNode *x, CombinNode *y)
    {
        return x->freq > y->freq;  // �ɧǱƦC
    }
};

priority_queue<CombinNodept,vector<CombinNodept>,cmp> pq;

void printNode(CombinNode *pt, string output)
{
    if(pt == nullptr){
        return;
    }

    if(pt->left != nullptr){
        output += "0";
        printNode(pt->left,output);
    }

    if(!pt->left && !pt->right){
        printf("%c ",pt->key);
        for(int i=0;i<output.size();i++){
            cout<<output[i];
        }
        printf("\n");
    }
    output.pop_back();

    if(pt->right != nullptr){
        output += "1";
        printNode(pt->right,output);
    }
}

int main()
{
    int Q;
    int num;
    char word;

    cin>>Q;

    for(int i=0;i<Q;i++){
        cin>>word>>num;
        CombinNode *pt = new CombinNode;
        pt->key = word;
        pt->freq = num;
        pq.push(pt);
    }

    for(int i=1;i<Q;i++){
        CombinNode *pt2 = new CombinNode;
        CombinNode *pleft = new CombinNode;
        CombinNode *pright = new CombinNode;

        pleft = pq.top();
        pq.pop();
        pright = pq.top();
        pq.pop();

        pt2->freq = pleft->freq+pright->freq;
        pt2->left = pleft;
        pt2->right = pright;

        pq.push(pt2);
    }

    string output = " ";
    printNode(pq.top(),output);
}
