class Solution {
public:
    
vector<int>dp;

int n;
vector<int>start;
vector<vector<int>>all;
int solve(int index ){
    if(index == n)return 0 ;
    if(dp[index]!=-1){
        return dp[index];
    }
    int  s =  all[index][1] ;
    int next = lower_bound(start.begin(),start.end(),s) - start.begin();
    int sec = 0;
    if(next!=start.size()&& s<= start[next]){
        sec = solve(next);
    }
    return dp[index] = max( solve(index+1),all[index][2]+sec);


}

    
    int jobScheduling(vector<int>&s, vector<int>& d, vector<int>& v) {
    n = s.size();
    dp.resize(n,-1);
    for(int i = 0; i< n; i++){
        all.push_back({s[i],d[i],v[i]});
        
    }
    start=s;
    sort(start.begin(),start.end());
    sort(all.begin(),all.end());
    return solve(0);
    }
};
