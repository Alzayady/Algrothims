#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 301;
const int N = 302;
const int MOD = 1e9 + 7;

int main() {
    IO;
    int n, k;
    cin >> n >> k;
    vector<ll> vec(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> vec[i];
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1));
    dp[0][0] = 1;
    vector<ll> pre(k + 1, 1);
    for (int i = 1; i <= n; i++) {
        for (ll j = 0; j <= k; j++) {
            if(j - vec[i] - 1 <0 ){
                dp[i][j] = pre[j];
            }else{
                ll t = pre[j] - pre[j - vec[i] - 1];;
                if(t<MOD){
                    t+=MOD;
                }
                dp[i][j] = t;
            }
            dp[i][j]%=MOD;
        }
        pre[0] = dp[i][0];
        for (int j = 1; j <= k; j++) {
            pre[j] = pre[j - 1] + dp[i][j];
            pre[j] %= MOD;
        }
    }
    cout << dp[n][k] << endl;
    return 0;
}
