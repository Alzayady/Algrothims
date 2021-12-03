#include <bits/stdc++.h>

using namespace std;


using ll = long long int;
const ll INF = LONG_LONG_MAX;
#define int long long
vector<int> vec;

const int N = 2000100;
vector<int> m;
vector<bool> p;
unordered_set<int> s;

void mob() {
    m.resize(N);
    p.resize(N);
    for (int i = 0; i <= N; i++) {
        m[i] = -1;
        p[i] = 1;
    }
    for (ll i = 2; i <= N; i++) {
        if (p[i]) {
            m[i] = 1;
            for (ll j = 2 * i; j < N; j += i) {
                p[j] = 0;
                m[j] = j % (i * i) == 0 ? 0 : -m[j];
            }
        }
    }
}

vector<int> phi;

void phi_calc(int n) { // from 1 to n
    phi.resize(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}


int phi_n(int n) { // only n
    ll ans = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            ans -= ans / i;
        }
    }
    if (n > 1)ans -= ans / n;
    return ans;
}


int32_t main() {
#ifdef  _SHIT
    freopen("../in", "r", stdin);
    freopen("../out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<vector<int>> all(N, vector<int>(30));
    phi_calc(N);
    for (int i = 1; i < N; i++) {
        int num = 0;
        int cur = i;
        while (cur != 1) {
            num++;
            cur = phi[cur];
        }
        all[i][num]++;
    }
    for (int i = 2; i < N; i++) {
        for (int j = 0; j < 30; j++) {
            all[i][j] += all[i - 1][j];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        int ans = 0 ;
        for(int i = 0 ; i< 30 ; i ++){
            int c = all[b][i] - all[a-1][i];
            ans += c * i;
        }
        cout<<ans<<endl;
    }
    return 0;
}
