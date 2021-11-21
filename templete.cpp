#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long

typedef long long ll;
typedef long double ld;
using namespace std;
using namespace __gnu_pbds;

mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 1e9 + 7;
const int N = 405;
const int BLOCK = 200;

struct pairhash {
public:
    template<typename T, typename U>
    size_t operator()(const pair<T, U> &x) const {
        return hash<T>()(x.first) ^ hash<U>()(x.second);
    }
};

void MAIN() {
    return;
}


int32_t main() {
    IO;
#ifdef DEBUG
    freopen(NAME".in", "r", stdin);
    freopen(NAME".out", "w", stdout);
#endif
    auto start = std::chrono::high_resolution_clock::now();
    int t = 1 ;
    cin >> t;
    while (t--) {
        MAIN();
    }
    auto end = std::chrono::high_resolution_clock::now();
#ifdef PERVEEVM_LOCAL
    std::cerr << "Execution time: "
                          << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                          << " ms" << std::endl;
#endif
    return 0;
}
