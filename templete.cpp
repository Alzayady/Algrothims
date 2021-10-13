#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
// #define int long long

typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;

mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
const int N = 1e5;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};
priority_queue<int, vector<int>, greater<int> > min_pq;

