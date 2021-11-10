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
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
    int n ,k;
    cin>>n >>k;
    ll arr[n+2];
    ll dp[n+2];
    for(int i =0 ;i < n ; i++){
        cin>>arr[i];
        dp[i]=INT_MAX;
    }
    dp[0]=0;
    for(int i = 1;i < n ; i++)
    {
        ll ans=INT_MAX;
        for(int j = 1 ; j<=k&&i-j>=0 ; j++){
            ans=min(ans,dp[(i-j)]+abs(arr[i]-arr[i-j]));
        }
        dp[i]=ans;
    }
    cout<<dp[n-1]<<endl;

    return 0;
}
