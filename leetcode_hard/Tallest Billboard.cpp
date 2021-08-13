class Solution {
public:
    int dp[2501][21];
    int n ;
    vector<int>vec;
    int solve(int diff , int index){
        if(index == n or diff > 2500){
            if(diff == 0 )return 0 ;
            return -1000000;
        }
        if(dp[diff][index]!=-1){
            return dp[diff][index];
        }
        int a = diff + vec[index];
        int b = abs(diff - vec[index]);
        return dp[diff][index] = max({
            solve(diff,index+1) , vec[index] + solve(a,index+1) , vec[index] + solve(b,index+1)
        });
        
    }
    int tallestBillboard(vector<int>& rods) {
        vec = rods;
        n = vec.size();
        memset(dp,-1,sizeof dp);
        return solve(0,0)/2;
    }
};
