#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;


int fastPow(int num, int p) {
    if (p == 0)return 1;
    int ans = fastPow(num, p / 2);
    ans *= ans;
    if (p % 2 == 1)ans *= num;
    return ans;
}

vector<int> nums;

int dp[100][100][10][2];
int limit;
int K;

int solve(bool smaller, int mod, int sum, int index) {
    if (sum > K)return 0;
    if (index == nums.size()) {
        if (mod == 0 and sum == 0) return 1;
        return 0;
    }
    if (dp[mod][sum][index][smaller] != -1) {
        return dp[mod][sum][index][smaller];
    }
    int limit = 0;
    if (smaller) {
        limit = 9;
    } else {
        limit = nums[index];
    }
    int ans = 0;
    for (int i = 0; i <= limit; i++) {
        int nxSum = sum + i;
        nxSum%=K;
        int nextMod = mod + i * fastPow(10, (int) nums.size() - index - 1);
        nextMod %= K;
        bool nextSmaller = smaller;
        if (smaller == 0 and i < nums[index]) nextSmaller = 1;
        ans += solve(nextSmaller, nextMod, nxSum, index + 1);
    }
    return dp[mod][sum][index][smaller] = ans;
}

int solveNum(int num) {
    if (num < 0)return 0;
    nums.clear();
    while (num) {
        nums.push_back(num % 10);
        num /= 10;
    }
    reverse(nums.begin(), nums.end());
    memset(dp, -1, sizeof dp);
    int ans = solve(0, 0, 0, 0);
//    cout << num << " " << ans << endl;
    return ans;
}

int solveTest() {
    ll a, b, k;
    cin >> a >> b >> k;
    K = k;
    if (k > 100)return 0;
    int ansA = solveNum(a - 1);
    int ansB = solveNum(b);
    return ansB - ansA;
}

int main() {
    IO;
    int t;
    cin >> t;
    int tt = 1;
    while (t--) {
        cout << "Case " << tt++ << ": " << solveTest() << endl;
    }
    return 0;
}
