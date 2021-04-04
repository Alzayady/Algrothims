#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
const int MOD = 1e9+7;
const int N=205;
const ll INF=1e17;
vector<int>dx={1,-1,0,0};
vector<int>dy={0,0,1,-1};
int n, m;
// link  :  https://cses.fi/problemset/task/1671
vector<vector<pair<ll, ll>>>graph;
int main() {
    IO;
    cin >> n >> m;
    graph.resize(n + 2);
    for (int i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        //graph[b].push_back({a, c});
    }
    set<pair<ll, ll>> dick;
    vector<ll> ans(n + 5, INF);
    ans[1] = 0;
    dick.insert({0,1});
    for (int i = 0; i < n-1; i++) {
        pair<ll, ll> nn = *dick.begin();
        ll node = nn.second;
        dick.erase(dick.begin());
 
        for (pair<ll, ll> next : graph[node]) {
            if (next.second + ans[node] < ans[next.first]) {
                dick.erase(make_pair(ans[next.first],next.first));
                ans[next.first] = ans[node] + next.second;
                dick.insert({ans[next.first], next.first});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
