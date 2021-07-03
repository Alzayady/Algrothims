class Solution {
public:
    int solve(vector<int> & v , int tar){
        int ans = INT_MIN ;
        int n = v.size();
        vector<int>pre(n);
        pre[0] = v[0];
        map<int , int> m;
        m[0];
        for(int i = 1 ; i < n ; i ++){
            pre[i] = pre[i-1] + v[i];
        }
        for(int i = 0 ;i < n ; i ++){
            int need = pre[i] - tar ;
            auto it = m.lower_bound(need);
            if(it!=m.end())
                  ans = max(ans,pre[i] - it->first);
            m[pre[i]];

        }
        return ans;
    }
    int maxSumSubmatrix(vector<vector<int>>& matrix, int tar) {
        int n = matrix.size();
        int m = matrix[0].size();
        int ans = INT_MIN ;
        for(int i = 0; i < n ; i ++){
            vector<int>here(m,0);
            for(int j = i  ; j >=0 ; j --){
                for(int k = 0 ; k < m ; k ++ ){
                    here[k] +=matrix[j][k];
                }
               ans = max(ans, solve(here , tar));
            }
        }
        return ans;
    }
};
