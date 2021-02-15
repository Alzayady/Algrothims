#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
typedef long double ld;
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

int n;
const int N = 2400000;
int head[N], nxt[N], to[N];
int ne;
vector<int> ans;
unordered_set<int> visitedEdge;
vector<string> vec;

void init() {
    ne = 0;
    memset(head, -1, (10 * n) * sizeof head[0]);
    ans.clear();
    visitedEdge.clear();
    vec.clear();
}

void addEdge(int f, int t) {
    to[ne] = t;
    nxt[ne] = head[f];
    head[f] = ne++;
}

void Euler(int f) {
    for (int e = head[f]; ~e; e = nxt[e]) {
        if (visitedEdge.count(e))continue;
        visitedEdge.insert(e);
        Euler(to[e]);
        ans.push_back(e);
    }
}

int main() {
    IO;
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        init();
        vec.resize(n);
        char st = 'z';
        vector<int> deg(27);
        vector<int> I(n);
        for (int i = 0; i < n; i++) {
            cin >> vec[i];
            st = min(st, vec[i][0]);
            deg[vec[i][0] - 'a']++;
            deg[vec[i].back() - 'a']--;
            I[i] = i;
        }
        sort(I.begin(), I.end(), [&](int a, int b) {
            return vec[a] > vec[b];
        });
        for (int i = 0; i < n; i++) {
            int a = vec[I[i]][0] - 'a';
            int b = vec[I[i]].back() - 'a';
            addEdge(a, b);
        }
        bool ok = 1;
        int c = 0;
        for (int j = 'a'; j <= 'z'; j++) {
            int i = j - 'a';
            if (deg[i] == 0 || deg[i] == -1)continue;
            if (deg[i] == 1) {
                st = i + 'a';
                c++;
            } else {
                ok = false;
            }
        }
        if (c > 1)ok = false;
        if (ok) {
            Euler(st - 'a');
            if (ans.size() != n) {
                ok = 0;
            } else {
                for (int i = n - 1; i >= 0; i--) {
                    cout << vec[I[ans[i]]];
                    if (i) {
                        cout << ".";
                    }
                }
                cout << endl;
            }
        }
        if (!ok) {
            cout << "***" << '\n';
        }
    }
    return 0;
}
