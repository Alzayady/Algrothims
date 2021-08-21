#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1e9 + 7;
const float EBS = 1e-9;
const int INF = 1e8;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
const static int N = 1e5 + 10;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
// Finding the number of element  strictly less than k=4 o_set.order_of_key(4)


int main() {
    IO;
    ll n, m, u;
    cin >> n >> m >> u;
    vector<ll> vec(n);
    ll s =  4096;
    vector<vector<ll> > b(s + 1);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        b[i / s].push_back(vec[i]);
    }
    for (int i = 0; i <= s; i++) {
        if (b[i].size()) sort(b[i].begin(), b[i].end());
    }
    while (m--) {
        ll l, r, v, p;
        cin >> l >> r >> v >> p;
        l--;
        r--;
        p--;
        ll ans = 0;
        for (int i = l; i <= r;) {
            if (i % s == 0 and i + s - 1 <= r ) {
                ans += lower_bound(b[i / s].begin(), b[i / s].end(), v) - b[i / s].begin();
                i += s;
            } else {
                if (vec[i] < v) {
                    ans++;
                }
                i++;
            }
        }
        ll val = u * ans / (r - l + 1);
        ll last = vec[p];
        vec[p] = val;
        vector<ll> &temp = b[p / s];
        int cur = 0;
        while (cur < temp.size() and temp[cur] != last)cur++;
        temp[cur] = val;
        while (cur > 0 and temp[cur - 1] > temp[cur]) {
            swap(temp[cur - 1], temp[cur]);
            cur--;
        }
        int pp = temp.size();
        pp--;
        while (cur < pp and temp[cur + 1] < temp[cur]) {
            swap(temp[cur + 1], temp[cur]);
            cur++;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << vec[i] << "\n";
    }
    return 0;
}
