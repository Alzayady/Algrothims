#include <bits/stdc++.h>
#define endll "\n";
using namespace std;
bool bfs(vector<vector<int>> c,int s,int t,vector<int> &vis,vector<int> &par){
     queue<int> q;
     q.push(s);
     vis[s]=1;
     while(!q.empty()){
         int u=q.front();
         q.pop();
         for(int i=0;i<c.size();i++){
             if(vis[i]==0&&c[u][i]>0){
                 par[i]=u;vis[i]=1;q.push(i);
                 if(i==t){
                     return true;
                 }
             }
         }
     }
     return false;
}
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        int e;cin>>e;
        vector<vector<int>> c(n,vector<int> (n,0));
        int u,v,w;
        for(int i=0;i<e;i++){
           cin>>u>>v>>w;
           c[u-1][v-1]+=w;
           c[v-1][u-1]+=w;
        }
        int max_flow=0;
        while(true){
            vector<int> vis(n,0),par(n,-1);
            if(bfs(c,0,n-1,vis,par)==false){
                break;
            }
            int max1=INT_MAX;
            int v=n-1;
            while(par[v]!=-1){
                max1=min(c[par[v]][v],max1);
                v=par[v];
            }
            v=n-1;
            while(par[v]!=-1){
                c[par[v]][v]-=max1;
                c[v][par[v]]+=max1;
                v=par[v];
            }
            max_flow+=max1;
        }
        cout<<max_flow<<endll;
    }
    return 0;
}

/*

*/
