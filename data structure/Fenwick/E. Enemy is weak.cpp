#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

template<typename T, typename U>
pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first + r.first, l.second + r.second};
}

template<typename T, typename U>
pair<T, U> operator-(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first - r.first, l.second - r.second};
}

priority_queue<int, vector<int>, greater<int> > m_pq;

// link : https://codeforces.com/contest/61/problem/E
struct fenwic {
    vector<int> tree;
    int n;

    fenwic(int n) {
        this->n = n + 1;
        tree.resize(this->n);
    }

    void add(int index, int value) {
        for (++index; index < n; index += (index & (-index))) {
            tree[index] += value;
        }
    }

    int sum(int index) {
        int ans = 0;
        for (++index; index > 0; index -= (index & (-index))) {
            ans += tree[index];
        }
        return ans;
    }
};

int main() {
    IO;
    int n;
    cin >> n;
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        vec[i] = {num, i};
    }
    sort(vec.rbegin(), vec.rend());
    vector<int> pre(n);
    vector<int> suf(n);
    fenwic *f = new fenwic(n);
    for (int i = 0; i < n; i++) {
        pre[i] = f->sum(vec[i].second);
        f->add(vec[i].second, 1);
    }
    f->tree.clear();
    f->tree.resize(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = f->sum(n - 1) - f->sum(vec[i].second);
        f->add(vec[i].second, 1);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += 1ll * pre[i] * suf[i];
    }
    cout << ans << endl;

}
