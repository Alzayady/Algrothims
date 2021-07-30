#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
priority_queue<int, vector<int>, greater<int> > m_pq;
const int N = 1e6;
const int MOD = 1e9 + 7;
const float EBS = 1e-9;
const int INF = 1e8;

ll extended_eclid(ll a, ll b, ll &x, ll &y) {
    if (a < 0) {
        ll r = extended_eclid(-1 * a, b, x, y);
        x *= -1;
        return r;
    }
    if (b < 0) {
        ll r = extended_eclid(a, -1 * b, x, y);
        y *= -1;
        return r;
    }
    if (b == 0) {
        y = 0;
        x = 1;
        return a;
    }
    ll g = extended_eclid(b, a % b, y, x);
    y -= x * (a / b);
    //  gcd(x,gcd(y,z)) = ax+ b gcd(y,z) , then c, d such that gcd(y,z)=cy+dz. Finally we obtain  gcd(x,y,z)=ax+bcy+bdz
    return g;
}


vector<ll> extended(vector<ll> vec) {
    int g = -1;
    int n = vec.size();
    vector<ll> g_nxt(n);
    g_nxt[n - 1] = vec[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        g_nxt[i] = __gcd(vec[i], g_nxt[i + 1]);
    }
    vector<ll> coff(n);
    ll pre = 1;
    for (int i = 0; i < n - 1; i++) {
        ll xx;
        ll yy;
        ll gg = extended_eclid(vec[i], g_nxt[1 + i], xx, yy);
        if (g == -1) {
            g = gg;
        }
        coff[i] = xx * pre;
        pre *= yy;
    }
    coff[n - 1] = pre;
    return coff;
}

ll linear_diophantine(ll a, ll b, ll c, ll &x, ll &y, bool &found) {

    ll g = extended_eclid(a, b, x, y);
    found = (c % g == 0);
    if (found) {
        x *= c / g;
        y *= c / g;
    }
    return g;
}

vector<ll> liner_modular(ll a, ll b, ll m) {
    // a X == b  ( mod m )
    // a X - b = m * y
    // a X - m * y = b
    ll xx;
    ll yy;
    bool f;
    ll g = linear_diophantine(a, m, b, xx, yy, f);
    if (f) {
        xx = (((xx % m) + m) % m);
        vector<ll> ans;
        for (int i = 0; i < g; i++) {
            ans.push_back((xx + i * m / g) % m);
        }
        sort(ans.begin(), ans.end());
        return ans;  // has only # gcd solutions unlike dlp which has INF solutions
    }
    return {};
}


void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

ll fp(ll num, int p) {
    if (p == 0)return 1;
    ll ans = fp(num, p / 2);
    ans *= ans;
    if (p % 2 == 1) {
        ans *= num;
    }
    return ans;
}

int main() {
    IO;
    vector<int> s(1e6 + 100, -1);
    for (ll i = 2; i <= N; i++) {
        if (s[i] == -1) {
            s[i] = i;
            for (ll j = i * i; j <= N; j += i) {
                s[j] = i;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll ans = 1;
        ll te = n ;
        while (n > 1) {
            ll l = s[n];
            int k = 0;
            while (n % l == 0) {
                k++;
                n /= l;
            }
            ans *= (fp(l, k + 1) - 1) / (l - 1);
        }
        cout << ans - te << "\n";
    }
}
