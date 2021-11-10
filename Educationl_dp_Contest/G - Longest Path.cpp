#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <time.h>
#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long int ll;
const ll INF=1e18+5;
int dp[100005];
vector<vector<int>>graph;
int longest(int node){
    if(dp[node]!=-1)return dp[node];
    int ans=0;
    for(int n : graph[node]){
        ans=max(ans,longest(n));
    }
    return dp[node]=ans+1;
}
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
     int n , m ;
     cin>>n>>m;
     graph.resize(n+2);
     int a ,b;
     memset(dp,-1, sizeof(dp));
     for(int i = 0 ; i< m ; i++){
         cin>>a>>b;
         graph[a].push_back(b);
     }
     int ans=0;
     for(int i =1 ;i <= n ; i++){
         ans=max(ans,longest(i));
     }
     cout<<ans-1<<endl;
}
