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
        tree.resize(this->n);
    }

    void add(int index, int value) {
        for (++index; index < n; index += index & -index) {
            tree[index] += value;
        }
    }

    int sum(int index) {
        int ans = 0;
        for (++index; index > 0; index -= index & -index) {
            ans += tree[index];
        }
        return ans;
    }

    int range(int l, int r) {
        int ans = sum(r);
        if (l) {
            ans -= sum(l - 1);
        }
        return ans;
    }

};

int32_t main() {
    IO;
    int n, s;
    cin >> n >> s;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    map<int, int> m;
    int ans = 0;
    fenwick f = fenwick(n);
    for (int i = 0; i < n; i++) {

        if (m.count(vec[i])) {
            f.add(m[vec[i]], -1);
        }
        m[vec[i]] = i;
        f.add(m[vec[i]], 1);

        int l = 0;
        int r = i;
        int cur = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int sum = f.range(i - mid, i);
            if (sum > s) {
                r = mid - 1;
            } else {
                l = mid + 1;
                cur = mid;
            }
        }
        assert(cur != -1);
        ans +=  cur + 1;
    }
    cout << ans << endl;
    return 0;
}
