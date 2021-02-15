#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
int n, m;
const int N = 4e5;
int head[N], nxt[N], to[N];
int ne;
vector<int> ans;

void init() {
    ne = 0;
    memset(head, -1, (2 * n + 100) * sizeof head[0]);
    ans.clear();
}

int s;

void addEdge(int f, int t) {
    to[ne] = t;
    nxt[ne] = head[f];
    head[f] = ne++;
}

void Euler(int node) {
    for (int &e = head[node]; ~e;) {
        int next = to[e];
        int h = e;
        e = nxt[e];
        Euler(next);
        s = node;
        ans.push_back(h);
    }
}

int main() {
    IO;
    while (true) {
        cin >> n >> m;
        if (n + m == 0)return 0;
        init();
        int a, b;
        vector<int> deg(n + 1);
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            addEdge(a, b);
            deg[a]++;
            deg[b]--;
        }
        int st = 0;
        int c = 0;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 1) {
                st = i;
                c++;
            } else if (deg[i] > 1) {
                c = 2;
            }
        }
        if (c > 1) {
            cout << "Impossible" << endl;
            continue;
        }
        Euler(st);
        if (ans.size() == m) {
            vector<int> ansHere;
            cout << s << " ";
            for (int i = ans.size() - 1; i >= 0; i--) {
                cout << to[ans[i]] << " ";
            }
            cout << endl;
        } else {
            cout << "Impossible" << endl;
        }
    }
    return 0;
}
