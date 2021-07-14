class Solution {
public:
    vector<vector<int>>all;
    int n , m ;
    const int MOD = 1e9+7;
    int N=1001;
    int M=250;
    vector<vector<int>>dp;
    bool valid(vector<int> & vec){
        for(int i = 1; i < m ; i++){
            if(vec[i] == vec[i-1])return false;
        }
        return true;
    }
    void append(vector<int> cur , int index  ){
        if(index == m){
            if(valid(cur)){
                all.push_back(cur);
            }
            return ;
        }
        for(int i = 1 ; i<=3 ; i ++){
            cur[index] = i ;
            append(cur,index+1);
        }
        
    }
    bool can_follow(int i , int j){
        for(int k = 0 ; k < m ; k++){
            if(all[i][k]==all[j][k])return false;
        }
        return true;
    }
    int solve(int last_row , int index_row){
        if(index_row == n)return 1 ;
        if(dp[index_row][last_row]!=-1){
            return dp[index_row][last_row];
        }
        int ans = 0 ;
        for(int i = 0 ; i <all.size() ; i ++){
            if(can_follow(i,last_row)){
                ans +=solve(i,index_row+1);
                ans%=MOD;
            }
        }
        return dp[index_row][last_row] = ans;
    }
    int colorTheGrid(int m, int n) {
        this->n = n ;
        this->m = m ;
        vector<int>vec(m,0);
        append(vec,0);
        dp.resize(n,vector<int>(M,-1));
        int ans = 0;
        for(int i = 0; i < all.size() ; i++){
            ans+=solve(i,1);
            ans%=MOD;
        }
        return ans;
        
        
        
    }
};
