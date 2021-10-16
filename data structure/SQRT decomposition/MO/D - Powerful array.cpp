#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int BLOCK_SIZE;

struct query {
    int l{}, r{};
    int index{};
    int block{};

    query();

    query(int l, int r, int index) {
        this->l = l;
        this->r = r;
        this->index = index;
        block = l / BLOCK_SIZE;
    }

    bool operator<(const query &y) const {
        if (block != y.block)return block < y.block;
        return r < y.r;
    }
};

query::query() = default;

int32_t main() {
    IO;
    int n, t;
    cin >> n >> t;
    vector<int> vec(n);
    BLOCK_SIZE = sqrt(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    vector<query> test(t);
    for (int i = 0; i < t; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        test[i] = query(a, b, i);
    }
    sort(test.begin(), test.end());
    int p1 = 0;
    int p2 = -1;
    vector<int> ans(t);
    int cur = 0;
    vector<int> freq(1000'000, 0);
    auto append = [&](int num) {
        cur -= freq[num] * freq[num] * num;
        freq[num]++;
        cur += freq[num] * freq[num] * num;
    };
    auto remove = [&](int num) {
        cur -= freq[num] * freq[num] * num;
        freq[num]--;
        cur += freq[num] * freq[num] * num;
    };
    for (int i = 0; i < t; i++) {
        int l = test[i].l;
        int r = test[i].r;
        while (p2 < r) {
            p2++;
            append(vec[p2]);
        }
        while (p2 > r) {
            remove(vec[p2]);
            p2--;
        }
        while (p1 > l) {
            p1--;
            append(vec[p1]);
        }
        while (p1 < l) {
            remove(vec[p1]);
            p1++;
        }
        ans[test[i].index] = cur;
    }
    for (auto it: ans) {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}
