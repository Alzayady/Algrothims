#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

typedef long long ll;
typedef long double ld;
using namespace std;

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9 + 7;
priority_queue<int, vector<int>, greater<int> > m_pq;
 int BLOCK_SIZE = 100;

// link : https://www.spoj.com/problems/KQUERY/
struct query {
    int index;
    int l;
    int r;
    int k;
    int block;

    query() {

    }

    query(int l, int r, int k, int index) {
        this->l = l;
        this->r = r;
        this->k = k;
        this->index = index;
        block = l / BLOCK_SIZE;
    }

    bool operator<(const query &y) const {
        if (block != y.block) {
            return block < y.block;
        }
        return r < y.r;
    }
};

struct fenwick {
    vector<int> tree;
    int n;
    fenwick(int n) {
        this->n = n +1;
        tree.resize(this->n);
    }

    void add(int index) {
        for (++index; index < n; index += (index & -index)) {
            tree[index]++;
        }
    }

    void remove(int index) {
        for (++index; index < n; index += (index & -index)) {
            tree[index]--;
        }
    }

    int sum(int index) {
        int ans = 0;
        for (++index; index > 0; index -= (index & -index)) {
            ans += tree[index];
        }
        return ans;
    }

    int get_range(int l, int r) {
        int ans = sum(r);
        if (l != 0) {
            ans -= sum(l - 1);
        }
        return ans;
    }

};

void process(vector<query> vec, int n, vector<int> nums) {
    sort(vec.begin(), vec.end());
    fenwick *f = new fenwick(n);
    int l = 1;
    int r = 0;
    vector<int> ans(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        while (l < vec[i].l)f->remove(nums[l++]);
        while (l > vec[i].l)f->add(nums[--l]);
        while (r < vec[i].r)f->add(nums[++r]);
        while (r > vec[i].r)f->remove(nums[r--]);
        ans[vec[i].index] = f->get_range(vec[i].k + 1, n - 1);
    }
    for (int i : ans) {
        printf("%d\n",i);
    }

}


int main() {
    int n;
    scanf("%d",&n);
    vector<int> vec(n);
    unordered_set<int> all;
    for (int i = 0; i < n; i++) {
        scanf("%d",&vec[i]);
        all.insert(vec[i]);
    }
    int q;
    scanf("%d",&q);
    vector<query> qu(q);
    BLOCK_SIZE = sqrt(n);
    for (int i = 0; i < q; i++) {
        int a, b, c;
        scanf("%d%d%d",&a,&b,&c);
        a--;
        b--;
        qu[i] = query();
        qu[i].l = a;
        qu[i].r = b;
        qu[i].k = c;
        qu[i].index = i;
        qu[i].block = a / BLOCK_SIZE;
        all.insert(c);
    }
    unordered_map<int, int> decode;
    vector<int> dis;
    for (auto it : all) {
        dis.push_back(it);
    }
    sort(dis.begin(), dis.end());
    for (int i = 0; i < dis.size(); i++) {
        decode[dis[i]] = i;
    }
    for (int i = 0; i < q; i++) {
        qu[i].k = decode[qu[i].k];
    }
    for (int i = 0; i < n; i++) {
        vec[i] = decode[vec[i]];
    }
    process(qu, dis.size() , vec);
    return 0;
}

