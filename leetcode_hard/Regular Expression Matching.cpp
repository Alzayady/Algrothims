class Solution {
public:
    int dp[21][31];
    string s , p ;
    bool solve(int i , int j ){
        if(i== s.size() and j == p.size()){
            return true;
        }
        if(i==s.size()){
            if(j+1==p.size()){
                return false;
            }
            if(p[j+1]=='*'){
                return solve(i,j+2);
            }
        }
        if(i>=s.size() || j >=p.size()){
            
            return false;
        }
        if(dp[i][j]!=-1){
            return (bool)dp[i][j];
        }
        if(p[j]=='.'){
            if(j+1==p.size()){
                return dp[i][j] = solve(i+1,j+1);
            }
            if(p[j+1]=='*'){
                int cur = i ;
                bool can = false;
                if(solve(i,j+2)){
                    return dp[i][j] = true;
                }
                while(cur < s.size() ){
                    if(solve(cur+1,j+2)){
                        can = true;
                        break;
                    }
                    cur++;
                }
                return dp[i][j] = can;
            }else{
                return dp[i][j] = solve(i+1,j+1);
            }

        }else {
            if(j+1==p.size()){
                if(s[i]==p[j]){
                    return dp[i][j] = solve(i+1,j+1);
                }else{
                    return false;
                }
            }else{
                if(p[j+1]=='*'){
                    int cur = i ;
                    bool can = false;
                    if(solve(i,j+2)){
                        return dp[i][j] = true;
                    }
                    while(cur < s.size() and s[cur] == p[j]){
                        if(solve(cur+1,j+2)){
                            can = true;
                            break;
                        }
                        cur++;
                    }
                    return dp[i][j] = can;
                }else{
                    if(s[i]==p[j]){
                        return dp[i][j] = solve(i+1,j+1);
                    }else{
                        return false;
                    }
                }
            }
        }
    }
    bool isMatch(string &s, string &p) {
        this->s =s ;
        this->p = p ;
        memset(dp,-1,sizeof dp);
        return solve(0,0);

    }
};
