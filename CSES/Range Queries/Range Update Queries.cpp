#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
// Finding the number of element  strictly less than k=4 o_set.order_of_key(4)

struct sq_tree_lazy {
    vector<int> tree;
    vector<int> lazy;
    vector<int> vec;
    int n;

    sq_tree_lazy(vector<int> vec) {
        this->vec = vec;
        n = vec.size();
        tree.resize(n * 5);
        lazy.resize(n * 5);
        build(1, 1, n);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = vec[l - 1];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
    }

    void propagate(int node, int l, int r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        tree[node] += lazy[node];
        lazy[node] = 0;
    }

    void update(int node, int l, int r, int ql, int qr, int u) {
        if (l >= ql and r <= qr) { // all inside
            lazy[node] += u;
            return;
        }
        if (l > qr || r < ql)return;
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr, u);
        update(node * 2 + 1, mid + 1, r, ql, qr, u);
    }

    int get_value(int node, int l, int r, int tn) {
        propagate(node, l, r);
        if (tn < l)return 1e18;
        if (tn > r)return 1e18;
        if (l == r) {
            assert(l==tn);
            return tree[node];
        }
        int mid = (l + r) / 2;
        int a = get_value(node * 2, l, mid, tn);
        int b = get_value(node * 2 + 1, mid + 1, r, tn);
        return min(a, b);
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
    sq_tree_lazy sqTreeLazy = sq_tree_lazy(vec);
    while (q--) {
        int type;
        cin >> type;
        if (type == 2) {
            int tu;
            cin >> tu;
            cout << sqTreeLazy.get_value(1, 1, n, tu) << endl;
        } else {
            int a, b, u;
            cin >> a >> b >> u;
            sqTreeLazy.update(1, 1, n, a, b, u);
        }
    }
    return 0;
}
