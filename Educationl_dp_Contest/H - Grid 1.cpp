#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <time.h>
#include <bits/stdc++.h>

#define IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long int ll;
const ll INF=1e18+5;
int w , h;
string grid[1005];
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
  cin>>h>>w;
  for(int i =0 ;i < h ;i++)cin>>grid[i];
  int dp[h+2][w+2];
  dp[0][0]=1;
  for(int i =0 ;i< h ; i++){
      for(int j =0 ;j < w ;j ++){
          if(i==0&&j==0)continue;
          if(grid[i][j]=='#')dp[i][j]=0;
          else{
              dp[i][j]=0;
              if(i!=0)dp[i][j]+=dp[i-1][j];
              if(j!=0)dp[i][j]+=dp[i][j-1];
              dp[i][j]%=(1000000007);
          }
      }
  }
  cout<<dp[h-1][w-1]<<endl;
    return 0;
}
