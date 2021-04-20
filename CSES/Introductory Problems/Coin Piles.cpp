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
ll pw(int num , int p){
    if(p==0){
        return 1;
    }
    ll ans = pw(num,p/2);
    ans*=ans;
    ans%=MOD;
    if(p&1){
        ans*=num;
        ans%=MOD;
    }
    return ans;
}
int main() {
    IO;
    int t;
    cin>>t;
    while (t--){
        ll a , b ;
        cin>>a>>b ;
        if(a>b)swap(a,b);
        cout<<(((a+b)%3==0 && a * 2>= b ) ?"YES" :"NO")<<endl;
    }
}
