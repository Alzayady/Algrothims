#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 301;
const int N = 40 + 2;
const int MOD = 1e9 + 7;
vector<vector<pair<int, int>>> vec;
int n;

vector<int> euler;
vector<int> first_appear;
vector<int> height;
vector<vector<int>> parent;
vector<vector<int>> dis;

void dfs(int node, int par, int h) {
    first_appear[node] = euler.size();
    height[node] = h;
    euler.push_back(node);
    for (auto next : vec[node]) {
        if (next.first == par)continue;
        parent[0][next.first] = node;
        dis[0][next.first] = next.second;
        dfs(next.first, node, h + 1);
        euler.push_back(node);
    }
}

struct sparse_table_lca {
    vector<vector<int>> vec_here;
    int s;

    sparse_table_lca() {
        s = euler.size();
        vec_here.resize(20, vector<int>(s + 1));
        for (int i = 0; i < s; i++) {
            vec_here[0][i] = euler[i];
        }
        for (int i = 1; i < 20; i++) {
            for (int j = 0; j + (1 << i) <= s; j++) {
                int a = height[vec_here[i - 1][j]];
                int b = height[vec_here[i - 1][j + (1 << (i - 1))]];
                if (a < b) {
                    vec_here[i][j] = vec_here[i - 1][j];
                } else {
                    vec_here[i][j] = vec_here[i - 1][j + (1 << (i - 1))];
                }
            }
        }

    }

    int query(int l, int r) {
        l = first_appear[l];
        r = first_appear[r];
        if (r < l) {
            swap(l, r);
        }
        int ss = log2(r - l + 1);
        int a = vec_here[ss][l];
        int b = vec_here[ss][r - (1 << ss) + 1];
        if (height[a] < height[b]) {
            return a;
        } else {
            return b;
        }
    }
};

struct sparse_table {

    sparse_table() {
        parent.resize(20, vector<int>(n + 1));
        build();
    }

    void build() {
        for (int i = 1; i < 20; i++) {
            for (int j = 0; j < n; j++) {
                if (parent[i - 1][j] != -1) {
                    parent[i][j] = parent[i - 1][parent[i - 1][j]];
                    dis[i][j] = dis[i - 1][j] + dis[i - 1][parent[i - 1][j]];
                }
            }
        }
    }

    int get_sum(int node, int h) {
        if (h == 0) {
            return 0;
        }
        int ans = 0;
        for (int i = 0; i < 20; i++) {
            if ((h & (1 << i))) {
                ans = dis[i][node] + get_sum(parent[i][node], h - (1 << i));
                break;
            }

        }
        return ans;
    }
};

int main() {
    IO;
    cin >> n;
    vec.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        vec[a].push_back({b, c});
        vec[b].push_back({a, c});
    }
    parent.resize(20, vector<int>(n + 1));
    dis.resize(20, vector<int>(n + 1));
    first_appear.resize(n + 1);
    height.resize(n + 1);
    dfs(0, -1, 0);
    sparse_table_lca lca;
    sparse_table table;
    int t;
    cin >> t;

    while (t--) {
        int a, b;
        cin >> a >> b;
        int c = lca.query(a, b);
        cout << table.get_sum(a, height[a] - height[c]) + table.get_sum(b, height[b] - height[c]) << endll;
    }
    return 0;
}
