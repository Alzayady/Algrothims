#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
vector<int> sei;
vector<int> dx = {1, 0, 0, -1};
vector<int> dy = {0, -1, 1, 0};


// link  :  https://www.spoj.com/problems/DQUERY/
struct FenwickTree {
    vector<int> tree;
    vector<int> original;
    vector<int> last_index;
    int n;

    explicit FenwickTree(int s) {
        n = s + 1;
        tree.resize(n);
        last_index.resize(1e6 + 10, -1);
    }

    void add(int idx, int val) {
        for (++idx; idx < n; idx += (idx & -idx)) {
            tree[idx] += val;
        }
    }

    int sum(int idx) {
        int ans = 0;
        for (++idx; idx > 0; idx -= (idx & -idx)) {
            ans += tree[idx];
        }
        return ans;
    }


    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add_distinct(int idx, int val) {
        if (last_index[val] == -1) {
            last_index[val] = idx;
            add(idx, 1);
        } else {
            add(last_index[val], -1);
            last_index[val] = idx;
            add(idx, 1);
        }
    }

};

int main() {
    IO;
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    int t;
    cin >> t;
    vector<pair<pair<int, int>, int> > q(t);
    for (int i = 0; i < t; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        q[i] = {{b, a}, i};
    }
    sort(q.begin(), q.end());
    int p = 0;
    vector<int> ans(t);
    FenwickTree *f = new FenwickTree(n);
    for (int i = 0; i < n; i++) {
        f->add_distinct(i, vec[i]);
        while (p < t && q[p].first.first <= i) {
            ans[q[p].second] = f->sum(q[p].first.second, q[p].first.first);
            p++;
        }
    }
    for (int i = 0; i < t; i++) {
        cout << ans[i] << endl;
    }
}
