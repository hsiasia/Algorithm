#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;
int minf=INT_MAX;
bool bfs(vector<vector<int> >rGraph, int s, int t, int parent[],int V);
int fordFulkerson(vector<vector<int> > graph, int s, int t, int V,int min_degree,int minf);

int main() {
    int v,e;
    cin>>v>>e;
    vector<vector<int> > rount(v+1, vector<int>(v+1,0));

    int x,y;    //存輸入
    for(int num=1; num<=e; num++){
        cin>>x>>y;
        rount[x][y]=1;
        rount[y][x]=1;
    }

    int minD=INT_MAX;   //減少計算次數 先得到擁有最小degree的點
    int minV;
    for(int i=1;i<=v;i++){
        int Dcount=0;
        for(int j=1;j<=v;j++){
            if(rount[i][j]>0)
                Dcount++;
        }
        if(minD>Dcount){
            minD=Dcount;
            minV=i;
        }
    }

    int ans;
    for(int des=1; des<=v; des++){ //進行fordFulkerson檢查minV對其他點的minflow
        if(des == minV){
            continue;
        }
        ans = fordFulkerson(rount, minV, des, v, minD, minf);
    }

    cout<<ans;
    return 0;
}

bool bfs(vector<vector<int> >rGraph, int s, int t, int parent[],int V)
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    int u;
    while (!q.empty()){
        u = q.front();
        q.pop();
        for (int v = 1; v <= V; v++){
            if (!visited[v] && rGraph[u][v] > 0)  {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if(v==t){
                    return true;
                }
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int> > graph, int s, int t, int V, int mind, int minf) {

    int u, v;
    vector<vector<int> > rGraph = {};
    rGraph.assign(graph.begin(), graph.end());

    int parent[V+1];
    memset(parent, 0, sizeof(parent));
    int max_flow = 0;

    while(bfs(rGraph, s, t, parent, V)){

        int path_flow = 1;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    if(max_flow < minf){
        minf = max_flow;
    }

    return minf;
}
