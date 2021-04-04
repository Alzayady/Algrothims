#include <bits/stdc++.h>
using namespace std;
#define  IO   ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
typedef long long ll ;
typedef unsigned long long ull;
const ll INF = 1e17;
vector<vector<int>>nex ;
// link  : https://cses.fi/problemset/task/1673
int main() {
    IO;
    int n, m;
    cin >> n >> m;
    vector<pair<ll, pair<ll, ll >>> edges;
    nex.resize(n + 2);
    ll a, b, c;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        edges.push_back({c, {a, b}});
        nex[a].push_back(b);
    }
    vector<ll> dis(n + 2, -1 * INF);
    dis[1] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            a = edges[j].second.first;
            b = edges[j].second.second;
            c = edges[j].first;
            if (dis[a] != -1 * INF)dis[b] = max(dis[b], dis[a] + c);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            a = edges[j].second.first;
            b = edges[j].second.second;
            c = edges[j].first;
            if (dis[a] != -1 * INF) {
                if (dis[a] + c > dis[b]) {
                    dis[b] = INF;
                    dis[a]=INF;
                }
            }
        }
    }
    cout << (abs(dis[n]) >= INF ? -1 : dis[n]) << endl;
    return 0;
}
