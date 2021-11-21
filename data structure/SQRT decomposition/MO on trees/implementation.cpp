#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long

typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;

mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
const int N = 405;
const int BLOCK = 200;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

int n;
vector<int> vec;
vector<vector<int>> g;
vector<int> tin, tout;
vector<int> flatten;
vector<int> node_id, id_node;
int cur_id = 0;
vector<vector<int>> table;

void dfs(int node, int p) {
    node_id[node] = cur_id++;
    id_node[node_id[node]] = node;
    tin[node] = (int) flatten.size();
    table[node][0] = p;
    flatten.push_back(node_id[node]);
    for (int nx: g[node]) {
        if (nx == p)continue;
        dfs(nx, node);
        flatten.push_back(node_id[node]);
        flatten.push_back(node_id[node]);
    }
    tout[node] = (int) flatten.size();
    flatten.push_back(node_id[node]);
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = 19; i >= 0; --i) {
        if (!is_ancestor(table[u][i], v))
            u = table[u][i];
    }
    return table[u][0];
}


struct query {
    int l, r, id, lc, bl, a, b;

    bool operator<(const query &bb) const {
        if (bl != bb.bl) {
            return bl < bb.bl;
        }
        return r < bb.r;
    }
};

int32_t main() {
    int t;
    scanf("%d%d", &n, &t);
    table.resize(n, vector<int>(21, 0));
    vec.resize(n);
    g.resize(n);
    tin.resize(n);
    tout.resize(n);
    node_id.resize(1e6);
    id_node.resize(1e6);
    for (int i = 0; i < n; i++) {
        scanf("%d", &vec[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0);
    vector<query> q(t);
    for (int i = 1; i <= 20; i++) {
        for (int j = 0; j < n; j++) {
            if (table[j][i - 1] == -1)continue;
            table[j][i] = table[table[j][i - 1]][i - 1];
        }
    }
    for (int i = 0; i < t; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        b--;
        if (id_node[a] > id_node[b])swap(a, b);
        q[i] = query();
        q[i].lc = lca(a, b);
        if (q[i].lc == a or q[i].lc == b) {
            q[i].l = tin[a];
            q[i].r = tin[b];
        } else {
            q[i].l = tout[a];
            q[i].r = tin[b];
        }
        q[i].id = i;
        q[i].bl = i / BLOCK;
        q[i].a = a;
        q[i].b = b;
    }
    sort(q.begin(), q.end());
    int l = 0;
    int r = -1;
    int ans = 0;
    vector<int> temp = vec;
    if (temp.size())
        sort(temp.begin(), temp.end());
    vector<int> un;
    for (int i = 0; i < temp.size(); i++) {
        if (i == 0 or i != un.back()) {
            un.push_back(temp[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        vec[i] = lower_bound(un.begin(), un.end(), vec[i]) - un.begin();
    }
    vector<int> m(un.back() + 10);
    vector<int> res(t);

    vector<int> repNode(cur_id + 10);
    auto setAns = [&](int v) {
        if (m[v] == 1) {
            ans++;
        } else if (m[v] == 0) {
            ans--;
        }
    };
    for (int i = 0; i < t; i++) {

        while (l > q[i].l) { // add
            l--;
            int v = vec[id_node[flatten[l]]];
            repNode[flatten[l]]++;
            if (repNode[flatten[l]] % 2 == 0) {
                // was taken before
                m[v]--;
                setAns(v);
            } else {
                // take node
                m[v]++;
                setAns(v);
            }
        }
        while (r < q[i].r) { // add
            r++;
            int v = vec[id_node[flatten[r]]];
            repNode[flatten[r]]++;
            if (repNode[flatten[r]] % 2 == 0) {
                // was taken before
                m[v]--;
                setAns(v);
            } else {
                // take node
                m[v]++;
                setAns(v);
            }
        }
        while (l < q[i].l) { // remove
            int v = vec[id_node[flatten[l]]];
            repNode[flatten[l]]--;
            if (repNode[flatten[l]] % 2 == 1) {
                m[v]++;
                setAns(v);
            } else {
                m[v]--;
                setAns(v);
            }
            l++;
        }
        while (r > q[i].r) { // reomove
            int v = vec[id_node[flatten[r]]];
            repNode[flatten[r]]--;
            if (repNode[flatten[r]] % 2 == 1) {
                m[v]++;
                setAns(v);
            } else {
                m[v]--;
                setAns(v);
            }
            r--;
        }
        res[q[i].id] = ans;
        if (q[i].lc != q[i].a and q[i].lc != q[i].b) {
            int v = vec[q[i].lc];
            if (m[v] % 2 == 0) {
                res[q[i].id]++;
            }
        }
    }
    for (auto it: res) {
        printf("%d\n", it);
    }
    return 0;
}
