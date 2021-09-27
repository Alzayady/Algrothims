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
        for (int i = 0; i < n; i++) {
            update(i, 1);
        }
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
};

int32_t main() {
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    fenwick f = fenwick(n);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        int l = 0;
        int r = n - 1;
        int ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int pre = f.sum(mid);
            if (pre < t) {
                l = mid + 1;
            } else {
                ans = mid;
                r = mid - 1;
            }
        }
        cout << vec[ans] << " ";
        f.update(ans, -1);
    }
    return 0;
}
