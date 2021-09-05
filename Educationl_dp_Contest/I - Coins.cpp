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

const int MOD = 1e9 + 7;
const int N = 1e5 + 10;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

unordered_map<pair<int, int>, int, pairhash> k;

void solve() {
    int n;
    cin >> n;
    vector<double> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    double dp[n + 1][n + 1];
    double ans = 0;
    dp[1][0] = 1 - vec[0];
    dp[1][1] = vec[0];
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= i; j++) { // head
            if (j == 0) {
                dp[i][j] = dp[i - 1][j] * (1 - vec[i - 1]);
            } else {
                dp[i][j] = dp[i - 1][j] * (1 - vec[i - 1]) + dp[i - 1][j - 1] * vec[i-1];
            }
        }
    }
    for (int i = (n + 1) / 2; i <= n; i++) {
        ans += dp[n][i];
    }
    cout << setprecision(10) << ans << endl;
}

int main() {
    IO;
    int t = 1;
    while (t--) {
        solve();
    }
}
