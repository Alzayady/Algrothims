

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

int dp[(1 << 10)][1001];
int n, m;
const int MOD = 1e9 + 7;

bool isBit(int mask, int b) {
    return mask & (1 << b);
}

bool valid(int curMask, int lastMask) {
    for (int i = 0; i < n; i++) {
        if (isBit(lastMask, i)) {
            if (!isBit(curMask, i))return 0;
        }
    }
    int z = 0;
    for (int i = 0; i < n; i++) {
        if (!isBit(curMask, i)) {
            z++;
        } else {
            if (z % 2)return 0;
            z = 0;
        }
    }
    return z % 2 == 0;
}

int getMask(int lastMask, int curMask) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!isBit(lastMask, i) and isBit(curMask, i)) {
            ans += (1 << i);
        }
    }
    return ans;
}

void gen(int lastMask, int curMask, int i, vector<int> &g) {
    if (i == n) {
        g.push_back(curMask);
        return;
    }
    if (isBit(lastMask, i)) {
        gen(lastMask, curMask, i + 1, g);
    }
    if (!isBit(lastMask, i)) {
        gen(lastMask, curMask + (1 << i), i + 1, g);
    }
    if (i != n - 1) {
        if (!isBit(lastMask, i) and !isBit(lastMask, i + 1)) {
            gen(lastMask, curMask, i + 2, g);
        }
    }
}

int solve(int index, int mask) {
    if (index == m)return mask == 0;
    if (dp[mask][index] != -1)return dp[mask][index];
    int ans = 0;
    vector<int> g;
    gen(mask, 0, 0, g);
    for (int i: g) {
        int o = solve(index + 1, i);
        ans += o;
        ans %= MOD;
    }
    return dp[mask][index] = ans;
}

int main() {
    IO;
    cin >> n >> m;
    memset(dp, -1, sizeof dp);
    cout << solve(0, 0) << endl;
    return 0;
}
