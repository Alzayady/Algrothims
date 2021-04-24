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
// link :  https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1266
ll n , m ;
vector<ll>vec;
ll solve(ll mask){
    ll lcm = 1 ;
    for(int i = 0; i < m ; i ++){
        if((mask>>i)&1){
            lcm = lcm*(vec[i])/__gcd(lcm,vec[i]);
        }
    }
    return n/lcm;
}
int main(){
    while (cin>>n>>m){
      vec.clear();
      vec.resize(m);
      for(int i = 0; i < m ; i++){
         cin>>vec[i];
      }
      ll ans = n;
      ll all = (1ll<<m)-1;
      for(int i = 1 ; i<=all ; i++){
          int count = __builtin_popcount(i);
          if(count%2==0){
              ans+=solve(i);
          }else{
              ans-=solve(i);
          }
      }
      cout<<ans<<endl;
    }
}
