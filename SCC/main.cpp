#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N=4*1e5+2;
const int MOD=1000000007;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
vector<vector<int >> vec;
vector<vector<int >> vec_rev;
vector<int>visited;
stack<int>stk;
vector<vector<int>>SCC;
void dfs1(int node ){
    if(visited[node])return;
    visited[node]=true;
    for(int next : vec[node]){
        dfs1(next);
    }
    stk.push(node);
}
void dfs2(int node){
    if(visited[node])return;
    visited[node]=true;
    SCC.back().push_back(node);
    for(int next : vec_rev[node]){
        dfs2(next);
    }
}
int main(){
    IO;
    int n ,m;
    cin>>n >>m;
    vec.resize(n+2);
    vec_rev.resize(n+2);
    int a , b ;
    for(int i =0;i<m ;i++){
        cin>>a>>b;
        vec[a].push_back(b);
        vec_rev[b].push_back(a);
    }
    visited.resize(n+5,false);
    for(int i = 1 ;i<=n ; i++){
        dfs1(i);
    }
    visited.clear();
    visited.resize(n+5,false);
    while (stk.size()){
        int node =stk.top();
        stk.pop();
        if(!visited[node]){
            SCC.emplace_back();
            dfs2(node);
        }
    }
    for(auto it : SCC){
        cout<<"========"<<endl;
        for(int num : it){
           cout<<num<<endl;
        }
    }
}
