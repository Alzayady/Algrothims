class Solution {
public:
    const static int N = 1e5+10;
    int dp[N][4];
    vector<int>vec;
    int solve(int index , int state){
        if(state==4){
            return 0;
        }
        if(index==vec.size()){
            if(state==2){
                return 0 ;
            }
            return -1000000;
        }
        if(dp[index][state]!=-1){
            return dp[index][state];
        }
        int ans = solve(index+1,state);
        if(state==0){
            ans = max(ans,solve(index+1,state+1)-vec[index]);
        }
        if(state==1){
            ans = max(ans,solve(index+1,state+1)+vec[index]);
        }
        if(state==2){
            ans = max(ans,solve(index+1,state+1)-vec[index]);
        }
        if(state==3){
            ans = max(ans, solve(index+1,state+1)+vec[index]);
        }
        return dp[index][state]= ans;
    }
    int maxProfit(vector<int>& prices) {
       memset(dp,-1,sizeof dp);
        vec=prices;
        return max(0,solve(0,0));
    }
};
