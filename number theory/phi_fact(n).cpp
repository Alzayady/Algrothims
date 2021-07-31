ll phi_factn(int n) { // phi for n!
    ll ans = 0;
    for (int i = 2; i <= n; i++) {
        ans += ans * (is_prime(i) ? i - 1 : i);
    }
    return ans;
}
