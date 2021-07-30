int num_of_divisor(int n) {
    // it must be seperate function
    vector<int> s(1e6 + 100, -1);
    for (ll i = 2; i <= N; i++) {
        if (s[i] == -1) {
            s[i] = i;
            for (ll j = i * i; j <= N; j += i) {
                s[j] = i;
            }
        }
    }
    int ans = 1;
    while (n > 1) {
        int k = 0;
        int l = s[n];
        while (n % l == 0) {
            k++;
            n /= l;
        }
        ans *= (k + 1);
    }
    return ans;
}
