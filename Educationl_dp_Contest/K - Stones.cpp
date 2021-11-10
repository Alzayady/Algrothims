#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define endll "\n"
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
const ll INF = 1e15;
const int N =1e5+2;
bool dp[N][2];
bool vis[N][2];
vector<int>vec;
int n ;
bool solve(int stones , bool cur){ // return true if player one wins
    if(vis[stones][cur]){
        return dp[stones][cur];
    }
    vis[stones][cur]=true;
    if(!cur){
      // second
      for(int i = 0 ;i<n ; i++){
          if(stones-vec[i]>=0){
              if(!solve(stones-vec[i],true)){
                  return dp[stones][cur]=false;
              }
          }
      }
      return dp[stones][cur]=true;
    }
    for(int i = 0 ;i<n ; i++){
        if(stones-vec[i]>=0){
            if(solve(stones-vec[i],false)){
                return dp[stones][cur]=true;
            }
        }
    }
    return dp[stones][cur]=false;

}
int main() {
    IO;
    cin>>n;
    int k;
    cin>>k;
    vec.resize(n);
    for(int i =0 ;i<n ; i ++){
        cin>>vec[i];
    }
    cout<<(solve(k,true)?"First":"Second")<<endl;

    return 0;
}
