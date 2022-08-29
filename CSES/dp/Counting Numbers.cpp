#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long

typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;

mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
const int N = 405;
const int BLOCK = 200;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

vector<int> vec;
int dp[20][11][2];

int solve_dp(int index, int last, int smaller) {
    if (index == vec.size())return 1;
    if (dp[index][last][smaller] != -1) {
        return dp[index][last][smaller];
    }
    int limit = vec[index];
    if (smaller) limit = 9;
    int ans = 0;
    for (int i = 0; i <= limit; i++) {
        int next_smaller = smaller;
        if (i < limit) next_smaller = true;
        if (i == last) continue;
        int next_last = i;
        if (i == 0 and last == 10) next_last = 10;
        ans += solve_dp(index + 1, next_last, next_smaller);
    }
    return dp[index][last][smaller] = ans;
}

int solve(int num) {
    vec.clear();
    while (num) {
        vec.push_back(num % 10);
        num /= 10;
    }
    reverse(vec.begin(), vec.end());
    memset(dp, -1, sizeof dp);
    return solve_dp(0, 10, 0);
}

int32_t main() {
    IO;
    long long a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a - 1);
    return 0;

}
