#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1e9 + 7;
const float EBS = 1e-9;
const int INF = 1e8;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

template<typename T, typename U>
pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first + r.first, l.second + r.second};
}

template<typename T, typename U>
pair<T, U> operator-(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first - r.first, l.second - r.second};
}

const static int N = 1e5 + 10;
int n;
vector<vector<int>> g;
ll ans = 0;
int value[N];
int s[N];
bool dead[N];

int get_size(int node, int p) {
    s[node] = 1;
    for (int next : g[node]) {
        if (p == next)continue;
        if (dead[next])continue;
        s[node] += get_size(next, node);

    }
    return s[node];
}

int get_centroids(int node, int p, int sz) {
    for (int next :  g[node]) {
        if (p == next)continue;
        if (dead[next])continue;
        if (s[next] * 2 > sz) {
            return get_centroids(next, node, sz);

        }
    }
    return node;
}


void append(vector<int> &v, int num) {
    for (int i = 0; i < 20; i++) {
        if (num & (1 << i)) {
            v[i]++;
        }
    }
}

int get_all_path(int node, int p, int v, vector<int> &vec) {
    if (dead[node])return 0;
    int si = 1;
    append(vec, v ^ value[node]);
    for (int next : g[node]) {
        if (next == p)continue;
        si += get_all_path(next, node, v ^ value[node], vec);
    }
    return si;
}

void solve(int node) {
    int pre = 0;
    vector<int> last(20, 0);
    for (int next : g[node]) {
        if (dead[next])continue;
        vector<int> v(20, 0);
        int c_p = get_all_path(next, node, 0, v);
        for (int i = 0; i < 20; i++) {
            int k = (1 << i);
            if (value[node] & k) {
                ans += 1ll * k * (pre - last[i]) * (c_p - v[i]);
                ans += 1ll * k * (last[i]) * v[i];
                ans += 1ll * (c_p - v[i]) * k;
            } else {
                ans += 1ll * k * last[i] * (c_p - v[i]);
                ans += 1ll * k * (pre - last[i]) * v[i];
                ans += 1ll * (v[i]) * k;
            }
            last[i] += v[i];
        }
        pre += c_p;
    }
}

void decompose(int node, int p) {
    get_size(node, p);
    int center = get_centroids(node, p, s[node]);
    dead[center] = 1;
    solve(center);
    for (int next : g[center]) {
        if (next == p)continue;
        if (dead[next])continue;
        decompose(next, center);

    }
}

int main() {
    IO;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> value[i];
        dead[i] = 0;
        ans += value[i];
    }
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    decompose(0, -1);
    cout << ans << endl;
    return 0;
}
