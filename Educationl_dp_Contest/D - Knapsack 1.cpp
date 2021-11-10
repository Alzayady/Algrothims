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
const int INF=1e9+5;
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
    int n ,w;
    cin>>n>>w ;
    vector<ll>temp_row(w+2);
    vector<vector<ll>>dp(n+1,temp_row);
    int weight , value;
    for(int i = 0 ;i < n ; i ++){
        cin>>weight>>value;
        for(int j =w-weight ; j >=0; j --){
            dp[i+1][j+weight]=max(dp[i+1][j+weight],dp[i][j]+value);
        }
        for(int j = 0 ;j<=w;j++)  dp[i+1][j]=max(dp[i+1][j],dp[i][j]);

    }
    ll ans= 0;
    for(int i =0 ; i <=w; i++)ans=max(ans,dp[n][i]);
    cout<<ans<<endl;

    return 0;
}
