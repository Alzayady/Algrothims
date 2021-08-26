

#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
// Finding the number of element  strictly less than k=4 o_set.order_of_key(4)


priority_queue<int, vector<int>, greater<int> > min_pq;

struct CompareHeight {
    bool operator()(int const &p1, int const &p2) {
        return p1 < p2;
    }
};

int dp[(1 << 22)][22];
int n;
vector<vector<int>> vec;
const int MOD = 1e9 + 7;

int solve(int index, int mask) {
    if (index == n)return 1;
    if (index > n)return 0;
    if (dp[mask][index] != -1)return dp[mask][index];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (vec[index][i] == 1) {
            if ((mask & (1 << i)) == 0) {
                ans += solve(index + 1, mask + (1 << i));
                ans %= MOD;
            }
        }
    }
    return dp[mask][index] = ans;
}

int main() {
    IO;
    cin >> n;
    vec.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> vec[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0) << endl;
    return 0;
}
