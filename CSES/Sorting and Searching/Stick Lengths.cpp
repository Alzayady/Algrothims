#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;

template<typename T, typename U>
pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first + r.first, l.second + r.second};
}

template<typename T, typename U>
pair<T, U> operator-(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first - r.first, l.second - r.second};
}

class myComparator {
public:
    bool operator()(const pair<int, char> &p1, const pair<int, char> &p2) {

        return p1.first > p2.first || (p1.first == p2.first && (p1.second < p2.second));

    }
};

vector<int> sei;

void pre() {
    sei.resize(1e7 + 10, -1);
    for (int i = 2; i <= 1e7; i++) {
        if (sei[i] == -1) {
            sei[i] = i;
            for (ll j = 1ll * i * i; j <= 1e7; j += i) {
                sei[j] = i;
            }
        }
    }
}

int main() {
    IO;
    int n;
    cin >> n;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    ll l = 0;
    ll r = 1e9;
    auto cost = [&](ll num) {
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(num - vec[i]);
        }
        return ans;
    };
    while (r - l >= 3) {
        ll th = (r - l) / 3;
        ll p1 = l + th;
        ll p2 = p1 + th;
        if (cost(p1) > cost(p2)) {
            l = p1;
        } else {
            r = p2;
        }
    }
    ll ans = 1e15;
    for (ll i = l; i <= r; i++) {
        ans = min(ans, cost(i));
    }
    cout << ans << endl;
}
