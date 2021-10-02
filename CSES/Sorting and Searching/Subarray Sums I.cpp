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
    int n, s;
    cin >> n >> s;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    map<int, int> m;
    m[0] = 1;
    int ans = 0;
    int pre = 0;
    for (int i = 0; i < n; i++) {
        pre += vec[i];
        ans += m[pre - s];
        m[pre]++;
    }
    cout << ans << endl;
    return 0;
}
