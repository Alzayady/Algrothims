#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

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
        return {{1, 0, 0},
                {0, 1, 0},
                {0, 0, 1}};
    }
    vector<vector<ll>> ans = solve(vec, n / 2, b);
    ans = mul(ans, ans, b);
    if (n % 2 == 1) {
        ans = mul(ans, vec, b);
    }
    return ans;

}

int main() {
    int c = 1;
    while (true) {
        ll  a, b;
        scanf("%lld %lld", &a, &b);
        if (a + b == 0) {
            return 0;
        }
        printf("Case %lld: %lld %lld ", c, a, b);

        if(b == 1){
            printf("0\n");
            c++;
            continue;
        }
        if (a < 2) {
            printf("1\n");
            c++;
            continue;
        }
        vector<vector<ll>> base = {{1, 1, 1},
                                   {1, 0, 0},
                                   {0, 0, 1}};

        vector<vector<ll>> ans = solve(base, a - 1, b);
        ll res = (ans[0][0] + ans[0][1] + ans[0][2]) % b;
        printf("%lld\n", res);
        c++;
    }
}
