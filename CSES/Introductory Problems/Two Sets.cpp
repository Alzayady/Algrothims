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

int main() {
    IO;
    ll n;
    cin >> n;
    ll all = n * (n + 1) / 2;
    if (all % 2 == 1) {
        cout << "NO" << endl;
        return 0;
    }
    cout<<"YES"<<endl;
    vector<int> ans;
    unordered_set<int> ss;
    ll s = all / 2;
    for (int i = n; i > 0; i--) {
        if (s >= i) {
            ans.push_back(i);
            ss.insert(i);
            s -= i;
        }
    }
    cout << ans.size() << endl;
    for (int num : ans) {
        cout << num << " ";
    }
    cout << endl;
    cout << n - ans.size() << endl;
    for (int i = 1; i <= n; i++) {
        if (!ss.count(i)) {
            cout << i << " ";
        }
    }
    cout << endl;

}
