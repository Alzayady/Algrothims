#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;

template<typename T, typename U>
pair <T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r) {
    return {l.first + r.first, l.second + r.second};
}

template<typename T, typename U>
pair <T, U> operator-(const std::pair<T, U> &l, const std::pair<T, U> &r) {
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

int ans;
int n;

void update(int a, int b, vector<int> &vec, vector<int> &here, int forbidden) {
    int num = here[a];
    int last_num = num - 1;
    if (last_num != 0 && last_num != forbidden) {
        if (vec[last_num] < vec[num]) {
            if (b <= vec[last_num]) {
                ans++;
            }
        } else {
            if (b >= vec[last_num]) {
                ans--;
            }
        }
    }
    int next_num = num + 1;
    if (next_num != n + 1 && next_num != forbidden) {
        if (vec[num] < vec[next_num]) {
            if (b >= vec[next_num]) {
                ans++;
            }
        } else {
            if (b <= vec[next_num]) {
                ans--;
            }
        }
    }
}

int main() {
    IO;
    int q;
    cin >> n >> q;
    vector<int> vec(n + 1);
    vector<int> here(n + 1);
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        vec[num] = i;
        here[i] = num;
    }
    ans = 1;
    int last = -1;
    for (int i = 1; i <= n; i++) {
        if (vec[i] <= last) {
            ans++;
        }
        last = vec[i];
    }


    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        update(a, b, vec, here, -1);
        update(b, a, vec, here, here[a]);
        swap(vec[here[a]], vec[here[b]]);
        swap(here[a], here[b]);
        cout << ans << endl;
    }
}
