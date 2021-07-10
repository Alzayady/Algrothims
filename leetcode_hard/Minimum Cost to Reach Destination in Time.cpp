class Solution {
public:
    const static int N = 1e3 + 7 ;
    const int INF = 1e8;
    
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        
        int n = passingFees.size();
        vector<vector<pair<int , int >>>g(n+10);
        vector<vector<int>>dp(maxTime+10,vector<int>(n+10,INF));
        dp[0][0] = passingFees[0] ;
        for(auto it : edges){
            g[it[0]].push_back({it[1],it[2]});
            g[it[1]].push_back({it[0],it[2]});
        }
        for(int i = 0; i <=maxTime ; i ++){
            for(int j = 0; j < n ; j ++){
                if(dp[i][j]==INF)continue;
                for(pair<int , int> next : g[j]){
                    int next_time = i + next.second ;
                    if(next_time > maxTime)continue;
                    dp[next_time][next.first] = min( dp[next_time][next.first],dp[i][j] + passingFees[next.first]);
                }
            }
        }
        int ans = INF;
        for(int i = 0 ; i<=maxTime ; i++){
            ans = min(ans,dp[i][n-1]);
        }
        if(ans == INF)return -1;
        return ans;
    }
};
