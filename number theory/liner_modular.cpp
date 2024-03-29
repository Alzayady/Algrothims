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
