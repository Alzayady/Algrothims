#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
const int MOD = 1e9 + 7;
const float EBS = 1e-9;
const int INF = 1e8;
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

template<typename T, typename U>
pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first + r.first, l.second + r.second};
}

template<typename T, typename U>
pair<T, U> operator-(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first - r.first, l.second - r.second};
}

struct fenwick {
    vector<int> tree;
    int n;

    fenwick(int n) {
        this->n = n + 1;
        tree.resize(this->n);
    }

    void add(int index, int v) {
        for (++index; index < n; index += index & -index) {
            tree[index] += v;
        }
    }

    int get_(int index) {
        int ans = 0;
        for (++index; index > 0; index -= index & -index) {
            ans += tree[index];
        }
        return ans;
    }

    int get_range(int l, int r) {
        int ans = get_(r) - get_(l - 1);
        return ans;
    }
    
};

int main() {
    int n, k;
    cin >> n >>k ;
    k = 1;
    fenwick *f = new fenwick(n + 1);
    for (int i = 1; i <= n; i++) {
        f->add(i, 1);
    }
    int cur = 1;
    int all = n;
    unordered_set<int> done;
    while (all > 0) {
        int l = cur;
        int r = n;
        int rest = f->get_range(l, n);
        int dist = k;
        if (rest <= dist) {
            l = 1;
            r = n;
            dist -= rest;
            cur = 1;
        }
        dist %= all;
        dist++;
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int num = f->get_range(cur, mid);
            if (num >= dist) {
                r = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }
        f->add(ans, -1);
        cout << ans << endl;
        done.insert(ans);
        cur = ans;
        all--;
    }

    return 0;
}
