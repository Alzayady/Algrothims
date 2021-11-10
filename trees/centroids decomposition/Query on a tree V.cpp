#include <bits/stdc++.h>

#include <utility>

#define N 100009

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

vector<vector<int>> g;
int n;

struct centroid_decomposition {
    vector<int> size;
    vector<int> par;

    centroid_decomposition(int n) {
        size.resize(n);
        par.resize(n, -2);
        decompose(0, -1);
    }

    int get_size(int node, int p = -1) {
        size[node] = 1;
        for (int next : g[node]) {
            if (next == p)continue;
            if (par[next] != -2)continue;
            size[node] += get_size(next, node);
        }
        return size[node];
    }

    int get_centroid(int node, int p, int sz) {
        for (int next : g[node]) {
            if (par[next] != -2)continue;
            if (p == next)continue;
            if (2 * size[next] > sz) {
                return get_centroid(next, node, sz);
            }
        }
        return node;
    }

    void decompose(int node, int p) {
        get_size(node, p);
        int centroid = get_centroid(node, p, size[node]);
        par[centroid] = p;
        for (int nei : g[centroid])
            if (par[nei] == -2)
                decompose(nei, centroid);
    }


};


struct lca {

    vector<int> in;
    vector<int> out;
    vector<vector<int>> table;
    int cur = 0;

    lca() {
        in.resize(N);
        out.resize(N);
        table.resize(N, vector<int>(20, 0));
        build(0);
        build_table();
    }

    void build(int node, int p = 0) {
        in[node] = cur++;
        table[node][0] = p;
        for (int next : g[node]) {
            if (next == p)continue;

            build(next, node);
        }
        out[node] = cur++;
    }

    void build_table() {
        for (int i = 1; i < 20; i++) {
            for (int j = 0; j < n; j++) {
                table[j][i] = table[table[j][i - 1]][i - 1];
            }
        }
    }

    bool is_ancestor(int u, int v) {
        if (u == -1 or v == -1)return false;
        return in[u] <= in[v] and out[u] >= out[v];
    }

    int query(int u, int v) {
        if (is_ancestor(u, v))return u;
        if (is_ancestor(v, u))return v;
        for (int i = 20; i >= 0; i--) {
            if (!is_ancestor(table[v][i], u)) {
                v = table[v][i];
            }
        }
        return table[v][0];
    }

};

vector<int> par;
set<vector<int>> children[N];
lca *lca_original;
vector<int> depth_original;

void get_depth(int node, int cur, int p = -1) {
    depth_original[node] = cur;
    for (int next : g[node]) {
        if (next == p)continue;
        get_depth(next, cur + 1, node);
    }
}

int get_distance_original(int u, int v) {
    if (u == -1 or v == -1)return INT_MAX;
    int l = lca_original->query(u, v);
    return abs(depth_original[u] - depth_original[l]) + abs(depth_original[v] - depth_original[l]);
}

int get_distance_centroids(int u, int v) {
    if (u == -1 or v == -1)return INT_MAX;
    return get_distance_original(u, v);
}

int get_least(int node) {
    if (children[node].empty())return -1;
    return (*children[node].begin())[1];
}

int solve(int node) {
    int ans = get_distance_centroids(node, get_least(node));
    int cur = par[node];
    while (cur != -1) {
        ans = min(ans, get_distance_centroids(node, get_least(cur)));
        cur = par[cur];
    }
    if (ans == INT_MAX)return -1;
    return ans;
}

void make_white(int node) {
    children[node].insert({0, node});
    int cur = par[node];
    while (cur != -1) {
        int new_len = get_distance_centroids(cur, node);
        children[cur].insert({new_len, node});
        cur = par[cur];
    }
}


void make_black(int node) {
    children[node].erase({0, node});
    int cur = par[node];
    while (cur != -1) {
        int dist = get_distance_centroids(cur, node);
        children[cur].erase({dist, node});
        cur = par[cur];
    }
}

int main() {
//    IO;
    scanf("%d", &n);
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int t;
    scanf("%d", &t);
    centroid_decomposition *centroidDecomposition = new centroid_decomposition(n);
    par = centroidDecomposition->par;
    lca_original = new lca();
    depth_original.resize(n);
    get_depth(0, 0, 0);
    vector<bool> white(N, 0);
    while (t--) {
        int ty;
        int node;
        scanf("%d%d", &ty, &node);
        node--;
        if (ty == 0) {
            if (!white[node]) {
                make_white(node);
                white[node] = 1;
            } else {
                make_black(node);
                white[node] = 0;
            }
        } else {
            printf("%d\n", solve(node));
        }
    }
}
