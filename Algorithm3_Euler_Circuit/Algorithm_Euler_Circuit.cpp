#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include <stack>
#include <vector>

using namespace std;

stack<int> visit;
stack<int> outputans;
int rount[10001][10001]={0};
vector<vector<int> > listarray(10001);
int V,E;

void Visit(int start);

int main()
{

    cin>>V>>E;

    int i,j;
    for(int num=1;num<=E;num++){
        cin>>i>>j;
        listarray[i].push_back(j);
        rount[i][j]=1;
        listarray[j].push_back(i);
        rount[j][i]=1;
    }

    int check=0;
    for(int x=1;x<=V;x++){
        if(listarray[x].size()%2==1){
            check=1;
        }

        sort(listarray[x].begin(),listarray[x].end());

    }

    visit.push(1);
    Visit(1);

    if(check==0&&outputans.size()==E+1){
        while(outputans.size()>0){
            cout<<outputans.top()<<" ";
            outputans.pop();
        }
    }
    else
        cout<<"not exist";
}

void Visit(int start){
    for(int y=0;y<listarray[start].size();y++){
        if(rount[start][listarray[start][y]] == 1){
            rount[start][listarray[start][y]]=0;
            rount[listarray[start][y]][start]=0;

            visit.push(listarray[start][y]);
            Visit(listarray[start][y]);
        }
    }

    if(outputans.size()!=E+1){
        int ans = visit.top();
        visit.pop();
        outputans.push(ans);
    }
}

