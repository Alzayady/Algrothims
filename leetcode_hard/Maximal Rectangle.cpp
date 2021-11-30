class Solution {
public:
    int maximalRectangle(vector<vector<char>>& vec) {
        int n = vec.size();
        if(n==0)return 0;
        int m = vec[0].size();
        int dp[n][m];
        int ans = 0;
        vector<vector<int>> row(n,vector<int>(m));
        for(int i = 0; i < n ; i ++){
            for(int j = 0;  j < m ;  j ++){
                    if(vec[i][j]=='1'){
                        row[i][j] = 1 ;
                        if(j){
                            row[i][j] += row[i][j-1];
                        }
                        if(i==0 and j == 0 ){
                            dp[i][j] = 1 ;
                        }else if(i == 0){
                            dp[i][j] = 1 + dp[i][j-1];
                        }else if(j == 0){
                            dp[i][j] = 1 +  dp[i-1][j];
                        }else{
                             int pre = m ;
                             dp[i][j] = 0 ;
                             for(int k = i ; k >=0 ; k --){
                                 pre = min(pre, row[k][j]);
                                 dp[i][j] = max(dp[i][j] , pre * (i - k + 1));
                             }
                        }
                        ans = max(ans,dp[i][j]);
                    }else{
                        dp[i][j] = 0 ;
                    }
               }
            }
        
        return ans;
    }
};
