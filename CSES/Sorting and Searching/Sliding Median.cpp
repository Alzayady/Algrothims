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

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Finding the number of element  strictly less or equal than k=4 o_set.order_of_key(4)

int32_t main() {
    IO;
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    int cur = 0;
    ordered_set<pair<int, int >> s;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        s.insert({vec[i], cur++});
        if (i >= k - 1) {
            cout << (*s.find_by_order((k - 1) / 2)).first << " ";
            s.erase(s.lower_bound({vec[i - k + 1], 0}));
        }
    }
    return 0;
}
