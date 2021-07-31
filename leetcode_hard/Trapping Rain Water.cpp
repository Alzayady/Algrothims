class Solution {
public:
    int trap(vector<int>& vec) {
        int n = vec.size();
        vector<int>last(1e5+10);
        int pre = 0; 
        for(int i = 0; i < n ;i ++){
            if(vec[i] > pre){
                for(int j = pre+1 ; j <= vec[i] ; j++){
                    last[j] = i ; 
                }
                pre = vec[i];
            }
        }
        vector<int>nxt(1e5+10);
        pre = 0 ;
        for(int i = n-1 ; i>=0 ; i--){
            if(vec[i] > pre){
                for(int j = pre+1 ; j<=vec[i] ; j++){
                    nxt[j] = i ;
                }
                pre = vec[i];
            }
        }
        int ans = 0 ;
        for(int i = 1 ; i<=pre ; i ++){
            ans += (nxt[i] - last[i] + 1);
        }
        for(int i = 0 ; i < n ; i++){
            ans-=vec[i];
        }
        return ans;
    }
};
