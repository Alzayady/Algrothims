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
    int n, m;
    cin >> n >> m;
    map<int, int> rep;
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        rep[-1 * num]++;
    }
    for (int i = 0; i < m; i++) {
        int num;
        cin >> num;
        auto ans = rep.lower_bound(-1 * num);
        if (ans == rep.end()) {
            cout << -1 << endl;
            continue;
        }
        int here = ans->first * -1;
        cout << here << endl;
        rep[ans->first]--;
        if (rep[ans->first] == 0) {
            rep.erase(ans->first);
        }
        
    }
}
