#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
priority_queue<int, vector<int>, greater<int> > m_pq;
const int N = 10;
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

vector<int> dsu;

int get_parent(int a) {
    if (a == dsu[a])return a;
    return dsu[a] = get_parent(dsu[a]);
}

void make_parent(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    dsu[a] = b;
}

void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

ll insersect(ll s1, ll s2, ll r1, ll r2) {

    ll a = r1;
    ll b = -1 * r2;
    ll c = s2 - s1;
    if (c == 0)return s1;
    if (a == 0 and b == 0)return -1;
    ll x1;
    ll x2;
    bool f;
    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;
    ll g = linear_diophantine(a, b, c, x1, x2, f);
    if (!f)return -1;
    a /= g;
    b /= g;
    shift_solution(x1, x2, a, b, (0 - x1) / b);
    if (x1 < 0) {
        shift_solution(x1, x2, a, b, sign_b);
    }
    if (x2 < 0) {
        shift_solution(x1, x2, a, b, -1 * (0 - x2) / a);
        if (x2 < 0) {
            shift_solution(x1, x2, a, b, -1 * sign_a);
        }
    }

    bool o = x1 > 0 and x2 > 0;
    if (!o)return -1;
    return s1 + x1 * r1;
}

int32_t main() {
    IO;
    int t;
    cin >> t;
    while (t--) {

        ll f, e, a, b;
        cin >> f >> e >> a >> b;
        dsu.clear();
        dsu.resize(e + 10);
        for (int i = 0; i <= e; i++) {
            dsu[i] = i;
        }
        vector<ll> rep(e);
        vector<ll> start(e);
        for (int i = 0; i < e; i++) {
            cin >> rep[i];
            cin >> start[i];
        }
        for (int i = 0; i < e; i++) {
            for (int j = i + 1; j < e; j++) {
                ll o = insersect(start[i], start[j], rep[i], rep[j]);
                if (o == -1) {
                    continue;
                }
                if (o >= f)continue;
                make_parent(i, j);
            }
        }
        vector<bool> contains_start(e + 10, 0);
        vector<bool> contains_end(e + 10, 0);
        for (int i = 0; i < e; i++) {
            if (a < start[i])continue;
            if (a == start[i]) {
                contains_start[i] = 1;
                continue;
            }
            int dif = a - start[i];
            if (dif % rep[i] == 0) {
                contains_start[i] = 1;
            }
        }
        for (int i = 0; i < e; i++) {
            if (b < start[i])continue;
            if (b == start[i]) {
                contains_end[i] = 1;
                continue;
            }
            int dif = b - start[i];
            if (dif % rep[i] == 0) {
                contains_end[i] = 1;
            }
        }
        bool ok = false;
        map<int, pair<int, int >> m;
        for (int i = 0; i < e; i++) {
            int p = get_parent(i);
            if (contains_start[i]) {
                m[p].first = 1;
            }
            if (contains_end[i]) {
                m[p].second = 1;
            }
            if (m[p].first and m[p].second) {
                ok = true;
                break;
            }
        }
        if (ok) {
            cout << "It is possible to move the furniture." << endl;
        } else {
            cout << "The furniture cannot be moved." << endl;
        }
    }
}
