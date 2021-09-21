class Solution {
public:
    const static int N = 1001;
    int dp[N][101][2];
    vector<int>vec;
    int k;
    int solve(int index , int trans , bool buy){
        if(index==vec.size()){
            return 0;
        }
        if(trans == k){
            return 0 ;
        }
        if(dp[index][trans][buy]!=-1){
            return dp[index][trans][buy];
        }
        int ans = solve(index+1,trans,buy);
        if(buy){
            ans = max(ans , solve(index+1,trans+1,0)+vec[index]);
        }else{
            ans = max(ans , solve(index+1, trans,1) - vec[index]);
        }
        return dp[index][trans][buy] = ans;
    }
    int maxProfit(int k, vector<int>& prices) {
        vec= prices;
        this->k = k ;
        memset(dp,-1,sizeof dp);
        return solve(0,0,0);
    }
};
