#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
// #define int long long

typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;

mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
const int N = 1e5+100;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

int n;
vector<vector<int>> g;
vector<int> vec;
vector<ll> ans;
vector<int> s;

int dfs1(int node, int p) {
    int res = 0;
    for (int next: g[node]) {
        if (next == p)continue;
        res += dfs1(next, node);
    }
    s[node] = res + 1;
    return res + 1;
}

unordered_map<int, int> shit[N];
pair<int, ll> shitAns[N]; // dominate color and ans

void dfs(int node, int p) {
    int big = -1;
    for (int nx: g[node]) {
        if (p == nx)continue;
        if (big == -1 or s[nx] > s[big]) {
            big = nx;
        }
        dfs(nx, node);
    }
    if (big == -1) big = node;
    swap(shit[big], shit[node]);
    swap(shitAns[big], shitAns[node]);
    if (shit[node][vec[node]] + 1 > shit[node][shitAns[node].first]) {
        shitAns[node].first = vec[node];
        shitAns[node].second = vec[node];
    }else if(shit[node][vec[node]] + 1 == shit[node][shitAns[node].first]){
        shitAns[node].second += vec[node];
    }
    shit[node][vec[node]]++;
    for (int nx: g[node]) {
        if (nx == p)continue;
        if (nx == big) continue;
        for (auto it: shit[nx]) {
            int c = it.first;
            int rep = it.second;
            if (rep + shit[node][c] > shit[node][shitAns[node].first]) {
                shitAns[node].first = c;
                shitAns[node].second = c;
            } else if (rep + shit[node][c] == shit[node][shitAns[node].first]) {
                shitAns[node].second += c;
            }
            shit[node][c] += rep;
        }
    }
    ans[node] = shitAns[node].second;
}

int32_t main() {
    IO;
    cin >> n;
    ans.resize(n + 1);
    g.resize(n + 1);
    vec.resize(n + 1);
    s.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> vec[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs1(1, -1);
    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    cout << endl;
    return 0;
}

