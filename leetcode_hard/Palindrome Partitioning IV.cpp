class Solution {
public:
    bool checkPartitioning(string s) {
        int n = s.size();
        vector<vector<bool>>p (n,vector<bool>(n,0));
        for(int i = n-1 ;i >=0 ; i --){
            for(int j = i ; j < n ; j++ ){
                if(i ==j){
                    p[i][j] = 1 ;
                }else if(i+1==j){
                    if(s[i]==s[j]){
                        p[i][j] = 1;
                    }else{
                        p[i][j] = 0 ;
                    }
                }else{
                    if(s[i]==s[j] and p[i+1][j-1]){
                        p[i][j] = 1 ;
                    }
                }
            }
        }
        for(int i = 1 ;i < n-1; i ++){
            for(int j = i  ; j < n-1 ; j ++){
                if(p[0][i-1] and p[i][j] and p[j+1][n-1])return 1;
            }
        }
        return 0;
    }
};
