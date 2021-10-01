#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
//#define int long long
#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
// Finding the number of element  strictly less than k=4 o_set.order_of_key(4)


int32_t main() {
    IO;
    int n;
    cin >> n;
    vector<pair<int, int >> vec(n);
    vector<int> all;
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
        all.push_back(vec[i].first);
        all.push_back(vec[i].second);
    }
    sort(all.begin(), all.end());
    vector<int> un;
    for (int i = 0; i < all.size(); i++) {
        if (i == all.size() - 1 or all[i] != all[i + 1]) {
            un.push_back(all[i]);
        }
    }
    auto decode = [&](int num) {
        return std::lower_bound(un.begin(), un.end(), num) - un.begin();
    };
    for (int i = 0; i < n; i++) {
        vec[i].first = decode(vec[i].first);
        vec[i].second = decode(vec[i].second);
    }
    int g = un.size();
    vector<vector<int>> start(g + 1);
    vector<vector<int>> end(g + 1);
    for (int i = 0; i < n; i++) {
        start[vec[i].first].push_back(i);
        end[vec[i].second].push_back(i);
    }
    vector<int> allow;
    vector<int> ans(n);
    int cur = 0;
    for (int i = 0; i < g; i++) {
        for (int j: start[i]) {
            if (allow.size()) {
                ans[j] = allow.back();
                allow.pop_back();
            } else {
                cur++;
                ans[j] = cur;
            }
        }
        for (int j: end[i]) {
            allow.push_back(ans[j]);
        }
    }
    cout << cur << endl;
    for (auto it: ans) {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}
