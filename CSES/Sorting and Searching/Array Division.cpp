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

int32_t main() {
    IO;
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    int ans = 0;
    int l = 0;
    int r = 1e18;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        l = max(l, vec[i]);
    }
    while (l <= r) {
        int mid = (l + r) / 2;
        bool can = true;
        int num = 1;
        int s = 0;
        for (int i = 0; i < n; i++) {
            if (s + vec[i] > mid) {
                num++;
                s = vec[i];
            } else {
                s += vec[i];
            }
        }
        if (num > k) {
            can = false;
        }
        if (can) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
