#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
//#define int long long
#define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>
// Finding the number of element  strictly less than k=4 o_set.order_of_key(4)

struct fenwick {
    vector<int> tree;
    int n;

    fenwick(int n) {
        this->n = n + 1;
        tree.resize(n + 10);
    }

    fenwick(vector<int> vec) {
        this->n = vec.size() + 1;
        tree.resize(n + 10);
        for (int i = 0; i < n; i++) {
            update(i, vec[i]);
        }
    }

    int sum(int index) {
        int ans = 0;
        for (++index; index > 0; index -= index & -index) {
            ans += tree[index];
        }
        return ans;
    }

    void update(int index, int v) {
        for (++index; index < n; index += index & -index) {
            tree[index] += v;
        }
    }

    int range(int a, int b) {
        int ans = sum(b);
        if (a) {
            ans -= sum(a - 1);
        }
        return ans;
    }
};


int32_t main() {
    int n;
    scanf("%d", &n);
    vector<pair<int, int> > vec(n);
    vector<int> all;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &vec[i].first, &vec[i].second);
        all.push_back(vec[i].first);
        all.push_back(vec[i].second);
    }
    sort(all.begin(), all.end());
    vector<int> un;
    for (int i = 0; i < all.size(); i++) {
        if (i == all.size() - 1 || all[i] != all[i + 1]) {
            un.push_back(all[i]);
        }
    }
    auto decode = [&](int num) {
        return std::lower_bound(un.begin(), un.end(), num) - un.begin();
    };
    for (int i = 0; i < n; i++) {
        vec[i].first = decode(vec[i].first);
        vec[i].second = decode(vec[i].second);
    }
    int r = un.size();
    vector<vector<int>> start(r);
    vector<vector<int>> end(r);
    for (int i = 0; i < n; i++) {
        start[vec[i].first].push_back(i);
        end[vec[i].second].push_back(i);
    }
    vector<int> end_here(r);
    for (int i = 0; i < n; i++) {
        end_here[vec[i].second]++;
    }
    fenwick fen = fenwick(end_here);
    fenwick fenwickSecond = fenwick(r);
    vector<int> ans1(n);
    vector<int> ans2(n);
    for (int i = 0; i < r; i++) {
        for (int j: start[i]) {
            int e = vec[j].second;
            ans1[j] = fen.range(i, e);
        }
        for (int j: start[i]) {
            int e = vec[j].second;
            fen.update(e, -1);
        }
        for (int j: start[i]) {
            int e = vec[j].second;
            fenwickSecond.update(e, 1);
        }
        for (int j: start[i]) {
            int e = vec[j].second;
            ans2[j] = fenwickSecond.range(e, r - 1);
        }

    }
    for (int i: ans1) {
        printf("%d ", i - 1);
    }
    printf("\n");
    for (int i: ans2) {
        printf("%d ", i - 1);
    }
    printf("\n");
    return 0;
}
