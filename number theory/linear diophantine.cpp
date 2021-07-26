ll linear_diophantine(ll a, ll b, ll c, ll &x, ll &y, bool &found) {
    ll g = extended_eclid(a, b, x, y);
    found = (c % g == 0);
    if (found) {
        x *= c / g;
        y *= c / g;
    }
    return g;
}
