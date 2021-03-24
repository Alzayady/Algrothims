#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

// link : https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1811
vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b, ll mod) {
    int n = a.size();
    int m = b[0].size();
    int t = b.size();
    vector<vector<ll >> ans(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < t; k++) {
                ans[i][j] += a[i][k] * b[k][j];
                ans[i][j] %= mod;
            }
        }
    }
    return ans;
}

vector<vector<ll>> solve(vector<vector<ll>> vec, ll n, ll b) {
    if (n == 0) {
        int s = vec.size();
        vector<vector<ll>>res(s,vector<ll>(s,0));
        for(int i = 0 ;i <s ; i++){
            res[i][i] = 1 ;
        }
        return res;
    }
    vector<vector<ll>> ans = solve(vec, n / 2, b);
    ans = mul(ans, ans, b);
    if (n % 2 == 1) {
        ans = mul(ans, vec, b);
    }
    return ans;

}

int main() {
    while (true) {
        ll d, n, m;
        scanf("%lld %lld %lld", &d, &n, &m);
        if (d + n + m == 0) {
            return 0;
        }
        vector<vector<ll>> base(d, vector<ll>(d, 0));
        for (int i = 0; i < d; i++) {
            scanf("%lld", &base[0][i]);
        }
        vector<ll> best_case(d);
        for (int i = 0; i < d; i++) {
            scanf("%lld", &best_case[i]);
        }
        for (int i = 1; i < d; i++) {
            base[i][i - 1] = 1;
        }
        if (n <= d) {
            printf("%lld\n", best_case[n - 1] % m);
            continue;
        }
        vector<vector<ll>> ans = solve(base, n - d, m);
        ll res = 0;
        for (int i = 0; i < d; i++) {
            res += ans[0][i] * best_case[d - i - 1];
            res %= m;
        }
        printf("%lld\n", res);
    }
    return 0;

}
