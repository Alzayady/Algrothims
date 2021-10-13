#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
#define int long long


struct SegmentTreeLazyPropagation {
    vector<int> tree;
    vector<int> lazy;
    vector<int> pre;

    void propagate(int node) {
        if (lazy[node]) {
            lazy[node * 2] += lazy[node];
            tree[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
            tree[node * 2 + 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    SegmentTreeLazyPropagation(int n, vector<int> pre) {
        tree.resize(n * 6);
        lazy.resize(n * 6);
        this->pre = pre;
        build(1, 0, n - 1);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = pre[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    int getMax(int node, int l, int r, int ql, int qr) {
        propagate(node);
        if (l >= ql and r <= qr) {
            return tree[node];
        }
        if (r < ql or l > qr)return -1e18;
        int mid = (l + r) / 2;
        int left = getMax(node * 2, l, mid, ql, qr);
        int right = getMax(node * 2 + 1, mid + 1, r, ql, qr);
        return max(left, right);
    }

    void insert(int node, int l, int r, int ql, int qr, int v) {
        propagate(node);
        if (l >= ql and r <= qr) {
            tree[node] += v;
            lazy[node] += v;
            return;
        }
        if (r < ql or l > qr)return;
        int mid = (l + r) / 2;
        insert(node * 2, l, mid, ql, qr, v);
        insert(node * 2 + 1, mid + 1, r, ql, qr, v);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }
};

struct Fenwick {
    vector<int> tree;
    int n;

    Fenwick(int n) {
        this->n = n + 1;
        tree.resize(n + 10);
    }

    void insert(int index, int v) {
        for (++index; index < n; index += index & -index) {
            tree[index] += v;
        }
    }

    int sum(int index) {
        int ans = 0;
        for (++index; index > 0; index -= index & -index) {
            ans += tree[index];
        }
        return ans;
    }
};

int32_t main() {
    IO;
    int n, q;
    cin >> n >> q;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    vector<int> pre(n);
    pre[0] = vec[0];
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i - 1] + vec[i];
    }
    SegmentTreeLazyPropagation segmentTreeLazyPropagation = SegmentTreeLazyPropagation(n, pre);
    Fenwick fenwick = Fenwick(n);
    for (int i = 0; i < n; i++) {
        fenwick.insert(i, vec[i]);
    }
    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            a--;
            fenwick.insert(a, -1 * vec[a] + b);
            segmentTreeLazyPropagation.insert(1, 0, n - 1, a, n - 1, -1 * vec[a] + b);
            vec[a] = b;
        } else {
            int ans = 0;
            a--;
            b--;
            ans = segmentTreeLazyPropagation.getMax(1, 0, n - 1, a, b);
            ans -= fenwick.sum(a - 1);
            cout << max(0ll, ans) << endl;
        }
    }
    return 0;
}
