#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
using namespace std;

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
mt19937 rng((unsigned long long) chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
using namespace __gnu_pbds;

template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Finding the number of element  strictly less or equal than k=4 o_set.order_of_key(4)


int32_t main() {
    IO;
    int n, k;
    cin >> n >> k;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    map<int, int> pre, post;
    int preSum = 0;
    int postSum = 0;
    int preCount = 0;
    int postCount = 0;
    int preSize = 0;
    int postSize = 0;
    if (k % 2 == 0) {
        preCount = postCount = k / 2;
    } else {
        preCount = k / 2;
        postCount = k - preCount;
    }
    auto erase = [](map<int, int> &m, int num) {
        m[num]--;
        if (m[num] == 0) {
            m.erase(num);
        }
    };

    for (int i = 0; i < n; i++) {
        pre[vec[i]]++;
        preSum += vec[i];
        preSize++;
        while (preSize > preCount) {
            auto it = pre.end();
            it--;
            int g = (*it).first;
            erase(pre, g);
            post[g]++;
            preSum -= g;
            postSum += g;
            preSize--;
            postSize++;
        }
        while (true) {
            if (preSize != preCount || postSize != postCount || preCount == 0)break;
            auto it = pre.end();
            it--;
            int maxPre = (*it).first;
            int minPost = (*post.begin()).first;
            if (maxPre > minPost) {
                erase(pre, maxPre);
                erase(post, minPost);
                pre[minPost]++;
                post[maxPre]++;
                preSum -= maxPre;
                postSum -= minPost;
                preSum += minPost;
                postSum += maxPre;
            } else {
                break;
            }
        }
        if (i + 1 >= k) {
            int median = (*post.begin()).first;
            cout << preCount * median - preSum + postSum - postCount * median << " ";
            int rem = vec[i - k + 1];
            if (pre.count(rem)) {
                preSum -= rem;
                erase(pre, rem);
                preSize--;
            } else {
                postSum -= rem;
                erase(post, rem);
                postSize--;
            }
        }
    }
    return 0;
}
