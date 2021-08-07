class Solution {
public:
    vector<vector<int>>is_palid;
    int n ;
    string s;
    bool solve(int l , int r){
        if(l>r)return 0 ;
        if(l==r){
            return is_palid[l][r] = 1 ;
        }
        if(l+1==r){
            return is_palid[l][r] = (s[l]==s[r]);
        }
        if(is_palid[l][r]!=-1){
            return is_palid[l][r];
        }
        solve(l+1,r);
        solve(l,r-1);
        bool b = solve(l+1,r-1);
        bool ans =  is_palid[l][r] = (b and s[l]==s[r]);
        return ans;
    }
    vector<vector<int>> is_valid;
    
    vector<int>dp;
    int solve2(int l) {
        if(l==n){
            return 0 ;
        }
        if(dp[l]!=-1)
        {
            return dp[l];
        }
        if(is_palid[l][n-1]){
            return 0 ;
        }
        int ans = INT_MAX;
        for(int i = l; i <=n-1 ; i++){
            if(is_palid[l][i]){
                int s = solve2(i+1);
                if(s!=INT_MAX){
                    ans = min(ans,1+s);
                }
            }
        }
        return dp[l] = ans;
         
    }
    int minCut(string s) {
         n = s.size();
        this->s = s;
        is_palid.resize(n+1,vector<int>(n+1,-1));
        dp.resize(n+1,-1);
        solve(0,n-1);
        return solve2(0);
        
    }
};
