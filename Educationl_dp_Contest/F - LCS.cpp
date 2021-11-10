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
int dp[3005][3005];
int  dp_track[3005][3005];
vector<int>rep_word2[27];
string world1,world2;
int size1;
int size2;
int solve (int index1 , int index2 ){
    if(index1>=size1||index2>=size2)return 0;
    if(dp[index1][index2]!=-1)return dp[index1][index2];
    int charc=world1[index1]-'a';
    int index_world2=lower_bound(rep_word2[charc].begin(),rep_word2[charc].end(),index2)-rep_word2[charc].begin();
    if(index_world2==rep_word2[charc].size()){
        dp[index1][index2]=solve(index1+1,index2);
        dp_track[index1][index2]=index2;
    } else{
        int num1 =solve(index1+1,index2);
        int num2=1+solve(index1+1,rep_word2[charc][index_world2]+1);
        if(num1>num2){
            dp_track[index1][index2]=index2;
        } else{
            dp_track[index1][index2]=rep_word2[charc][index_world2]+1;
        }
        dp[index1][index2]=max(num1,num2);
    }
    return dp[index1][index2];
}
void print_track(int index1 ,int index2){
    if(index1>=size1||index2>=size2)return;
    int next_index2=dp_track[index1][index2];
    if(next_index2!=index2){
        cout<<world1[index1];
    }
    print_track(index1+1,next_index2);
}
int main() {
#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    IO;
     cin>>world1>>world2;
     size1=world1.size();
     size2=world2.size();
    for(int i = 0; i<size2 ; i++ ){
        rep_word2[world2[i]-'a'].push_back(i);
    }
    memset(dp,-1, sizeof(dp));
    solve(0,0);
    print_track(0,0);
   // cout<<solve(0,0)<<endl;
    return 0;
}
//"ezupkr"
//"ubmrapg"
