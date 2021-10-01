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
    vector<pair<int, int >> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i].first;
        vec[i].second = i;
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int p1 = j + 1;
            int p2 = n - 1;
            int need = s - vec[i].first - vec[j].first;
            while (p1 < p2) {
                if (vec[p1].first + vec[p2].first == need) {
                    cout << vec[i].second + 1 << " " << vec[j].second + 1 << " " << vec[p1].second + 1 << " "
                         << vec[p2].second + 1 << endl;
                    return 0;
                }
                if (vec[p1].first + vec[p2].first < need) {
                    p1++;
                } else {
                    p2--;
                }
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}
