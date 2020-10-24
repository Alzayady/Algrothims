#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 301;
const int N = 302;
const int MOD = 1e9 + 7;

int n;
vector<vector<int>> graph;
vector<int> euler;
vector<int> first_appear;
vector<int> height;

void dfs(int node, int par, int h) {
    first_appear[node] = euler.size();
    euler.push_back(node);
    height[node] = h;
    for (int next : graph[node]) {
        if (next == par)continue;
        dfs(next, node, h + 1);
        euler.push_back(node);
    }
}

struct segmentTree {
    vector<int> vec;

    segmentTree() {
        vec.resize(euler.size() * 4);
        build(1, 0, euler.size() - 1);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            vec[node] = euler[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        if (height[vec[node * 2]] < height[vec[node * 2 + 1]]) {
            vec[node] = vec[node * 2];
        } else {
            vec[node] = vec[node * 2 + 1];
        }
    }

    int query(int node, int l, int r, int index_l, int index_r) {
        if (l >= index_l && r <= index_r) {
            return vec[node];
        }
        if (index_r < l || r < index_l) {
            return -1;
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, index_l, index_r);
        int right = query(node * 2 + 1, mid + 1, r, index_l, index_r);
        if (left == -1)return right;
        if (right == -1)return left;
        if (height[left] < height[right]) {
            return left;
        } else {
            return right;
        }
    }

    int query(int l, int r) {
        l = first_appear[l];
        r = first_appear[r];
        if (l > r) {
            swap(l, r);
        }
        return query(1, 0, euler.size() - 1, l, r);
    }

};

int main() {
    IO;
    int t;
    cin >> t;
    int casee = 1 ;
    while (t--) {
        cout<<"Case "<<casee<<":"<<endll;
        casee++;
        cin >> n;
        graph.clear();
        graph.resize(n + 1);
        first_appear.resize(n + 1);
        height.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            int num;
            cin >> num;
            for (int j = 0; j < num; j++) {
                int a;
                cin >> a;
                graph[i].push_back(a);
            }
        }
        dfs(1, -1, 0);
        segmentTree segmentTree;
        int q;
        cin >> q;
        while (q--) {
            int a, b;
            cin >> a >> b;
            cout << segmentTree.query(a, b) << endll;
        }
    }

    return 0;
}
