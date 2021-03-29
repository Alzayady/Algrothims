#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9;
// link : https://www.spoj.com/problems/SEQ/en/
vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b) {
    int n = a.size();
    int m = b[0].size();
    assert(a[0].size() == b.size());
    vector<vector<ll>> ans(n, vector<ll>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < b.size(); k++) {
                ans[i][j] += a[i][k] * b[k][j];
                ans[i][j] %= MOD;
            }
        }
    }
    return ans;
}

vector<vector<ll>> pow(vector<vector<ll>> vec, int n) {
    if (n == 0) {
        vector<vector<ll>> ans(vec.size(), vector<ll>(vec.size()));
        for (int i = 0; i < vec.size(); i++) {
            ans[i][i] = 1;
        }
        return ans;
    }
    vector<vector<ll>> ans = pow(vec, n / 2);
    ans = mul(ans, ans);
    if (n & 1) {
        ans = mul(ans, vec);
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        vector<ll> vec(k);
        for (int i = 0; i < k; i++) {
            cin >> vec[i];
        }
        vector<vector<ll>> base(k, vector<ll>(k));
        for (int i = 0; i < k; i++) {
            cin >> base[0][i];
        }
        for (int i = 1; i < k; i++) {
            base[i][i - 1] = 1;
        }
        int n;
        cin >> n;
        if (n <= k) {
            cout << vec[n - 1] << endl;
            continue;
        }
        vector<vector<ll>> ans = pow(base, n - k  );
        ll res = 0;
        for (int i = 0; i < k; i++) {
            res += ans[0][i] * vec[k - i - 1];
            res %= MOD;
        }
        cout << res<<endl;
    }
}
