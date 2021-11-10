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
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
    int n ,w;
    cin>>n>>w ;
    pair<ll , ll > arr[n+1];
    ll all=0;
    for (int i = 0; i<n; ++i) {
        cin>>arr[i].first>>arr[i].second;
        all+=arr[i].second;
    }
    vector<ll> values (all+2,INF);
    values[0]=0;
    for(int i =0 ;i < n ; i++){
        vector<ll> temp_values=values;

        for(int j = 0 ; j+arr[i].second<=all; j++){
           temp_values[j+arr[i].second]=min(values[j+arr[i].second],values[j]+arr[i].first);
        }
        values=temp_values;
    }
    ll ans=0;
    for(int i =all ;i>=0 ;i--){
        if(values[i]<=w){
            ans=i;
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}
