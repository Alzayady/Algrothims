#include <bits/stdc++.h>

using namespace std;


using ll = long long int;
const ll INF = LONG_LONG_MAX;
#define int long long
#define int long long
vector<int> vec;

const int N = 1e6 + 10;
vector<int> m;
vector<int> p;


void mob() {
    m.resize(N);
    p.resize(N);
    for (int i = 0; i <= N; i++) {
        m[i] = -1;
        p[i] = i;
    }
    for (int i = 2; i <= N; i++) {
        if (p[i] == i) {
            for (int j = i * i; j <= N; j += i) {
                p[j] = i;
            }
        }
    }
    for (ll i = 2; i <= N; i++) {
        if (p[i] == i) {
            m[i] = 1;
            for (ll j = 2 * i; j < N; j += i) {
                m[j] = j % (i * i) == 0 ? 0 : -m[j];
            }
        }
    }
}

unordered_set<int> fac(int num) {
    unordered_set<int> ans;
    while (num != 1) {
        ans.insert(p[num]);
        num /= p[num];
    }
    return ans;
}

vector<int> get_div(unordered_set<int> s) {
    vector<int> v;
    for (int num: s) {
        v.push_back(num);
    }
    int n = v.size();
    vector<int> ans;
    for (int i = 1; i < (1 << n); i++) {
        int d = 1;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                d *= v[j];
            }
        }
        ans.push_back(d);
    }
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
    mob();
    int n;
    cin >> n;
    vec.resize(n);
    unordered_map<int, int> s;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        unordered_set<int> ff = fac(vec[i]);
        vector<int> div = get_div(ff);
        for (auto it: div) {
            s[it]++;
        }
    }
    int ans = n * (n - 1) / 2;
    for (int i = 2; i <= N; i++) {
        ans -= m[i] * (s[i] * (s[i] - 1)) / 2;
    }
    cout << ans << endl;
    return 0;
}
