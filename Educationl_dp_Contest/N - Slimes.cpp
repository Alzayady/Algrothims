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
const int BLOCK = 450;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

int n;
vector<int> vec;
vector<int> sum;

int sumRange(int a, int b) {
    int ans = sum[b];
    if (a) ans -= sum[a - 1];
    return ans;
}

int dp[N][N];

int solve(int a, int b) {
    if (a == b) {
        return 0;
    }
    if (a + 1 == b) {
        return sumRange(a, b);
    }
    if (dp[a][b] != -1) {
        return dp[a][b];
    }
    int ans = 1e15;
    for (int i = a; i < b; i++) {
        ans = min(ans, solve(a, i) + solve(i + 1, b) + sumRange(a, b));
    }
    return dp[a][b] = ans;
}

int32_t main() {
    IO;
    cin >> n;
    vec.resize(n);
    sum.resize(n);
    int last = 0;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        sum[i] = vec[i] + last;
        last += vec[i];
    }
    memset(dp, -1, sizeof dp);
    cout << solve(0, n - 1) << endl;
    return 0;
}
