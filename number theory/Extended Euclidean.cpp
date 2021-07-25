ll extended_eclid(ll a, ll b, ll &x, ll &y) {
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

int g = -1;

vector<ll> extended(vector<ll> vec) {
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
