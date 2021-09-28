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

struct fenwick {
    vector<int> tree;
    int n;

    fenwick(int n) {
        this->n = n + 1;
        tree.resize(n + 10);
    }

    int sum(int index) {
        int ans = 0;
        for (++index; index > 0; index -= index & -index) {
            ans += tree[index];
        }
        return ans;
    }

    void update(int index, int v) {
        for (++index; index < n; index += index & -index) {
            tree[index] += v;
        }
    }

    int range(int a, int b) {
        int ans = sum(b);
        if (a) {
            ans -= sum(a - 1);
        }
        return ans;
    }
};

int32_t main() {
    IO;
    int n, t;
    cin >> n >> t;
    vector<int> vec(n);
    fenwick f = fenwick(1e6);
    vector<int> temp;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        temp.push_back(vec[i]);
    }
    vector<vector<int>> q(t, vector<int>(3));
    for (int i = 0; i < t; i++) {
        char ty;
        int a, b;
        cin >> ty >> a >> b;
        q[i][1] = a;
        q[i][2] = b;
        if (ty == '?') {
            q[i][0] = 0;
            temp.push_back(a);
            temp.push_back(b);
        } else {
            q[i][0] = 1;
            temp.push_back(b);
        }
    }
    sort(temp.begin(), temp.end());
    auto decode = [&](int a) {
        return std::lower_bound(temp.begin(), temp.end(), a) - temp.begin();
    };
    for (int i = 0; i < n; i++) {
        f.update(decode(vec[i]), 1);
    }
    for (int i = 0; i < t; i++) {
        if (q[i][0] == 0) {
            int a = decode(q[i][1]);
            int b = decode(q[i][2]);
            cout << f.range(a, b) << "\n";
        } else {
            int a = q[i][1];
            int b = q[i][2];
            a--;
            int num = decode(vec[a]);
            f.update(num, -1);
            vec[a] = b;
            f.update(decode(b), 1);
        }
    }
    return 0;
}
