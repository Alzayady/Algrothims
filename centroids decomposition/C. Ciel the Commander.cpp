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

const int N = 1e5 + 10;
vector<vector<int>> g;
char ans[N];
int size_[N];

int get_size(int cur, int p = -1) {
    size_[cur] = 1;
    for (auto next : g[cur]) {
        if (next == p)continue;
        if (ans[next] == -1) {
            size_[cur] += get_size(next,cur);
        }
    }
    return size_[cur];
}

int get_centroids(int cur, int p, int sz) {
    for (int next: g[cur]) {
        if (next == p)continue;
        if (ans[next] == -1) {
            if (size_[next] * 2 > sz) {
                return get_centroids(next, cur, sz);
            }
        }
    }
    return cur;
}

void solve(int cur, char c, int p) {
    get_size(cur, p);
    int centroid = get_centroids(cur, p, size_[cur]);
    ans[centroid] = c;
    for (auto next : g[centroid]) {
        if (ans[next] == -1) {
            solve(next, c + 1, centroid);
        }
    }
}

int main() {
    int n;
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a , b ;
        scanf("%d %d",&a,&b);
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    memset(ans, -1, sizeof ans);
    solve(0, 'A', -1);
    for(int i = 0; i <n ; i ++){
        printf("%c ",ans[i]);
    }
    cout<<endl;
    return 0;
}
