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

struct sg {
    vector<int> tree;
    vector<int> vec;
    int n;

    sg(vector<int> vec) {
        this->vec = vec;
        n = vec.size();
        tree.resize(n * 5);
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
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }


    int extract(int node, int l, int r, int tar) {
        if (tree[node] < tar)return 0;
        if (l == r) {
            assert(tree[node] >= tar);
            tree[node] -= tar;
            return l;
        }
        int mid = (l + r) / 2;
        int ans = 0;
        if (tree[node * 2] >= tar) {
            ans = extract(node * 2, l, mid, tar);
        } else {
            ans = extract(node * 2 + 1, mid + 1, r, tar);
        }
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
        return ans;
    }

};

int32_t main() {
    IO;
    int n, m;
    cin >> n >> m;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    sg tree = sg(vec);
    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;
        cout << tree.extract(1, 1, n, num) << " ";
    }
    cout << endl;
    return 0;
}
