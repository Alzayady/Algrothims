class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        if(solve(grid))return true;
        int n = grid.size();
        int m = grid[0].size(); 
        vector<vector<int>> ng(m,vector<int>(n));
    for(int j = 0 ; j < m ; j ++) {
        for(int i = 0 ; i < n ; i ++){
                ng[j][i] = grid[i][j];
            }
        }
        return solve(ng);
    }
    // 38

    bool solve(vector<vector<int>> grid) {
        int n = grid.size(); // 1
        int m = grid[0].size(); // 2
        vector<long > vec(n,0);
        // cout <<"input " << n << endl;
        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ; j < m ; j ++) {
                vec[i] += grid[i][j];
            }
        }
        for(int i = 1 ; i < n ; i ++){
            vec[i] += vec[i-1];
        }
        for(int i = 0 ; i < n ; i ++){
            if(vec[i] * 2 == vec.back())return true;
        }

        for(int i = 0 ; i < n ; i ++) {
            for(int j = 0 ; j < m ; j ++) {
                int all = vec.back();
                int y = vec.back() / 2 ;
                int x = y + grid[i][j];
                // CUT BEFORE D, rest is bigger 
                // x + y + d = all
                // y = x + d
                // 2x + 2d = all
                // x = all / 2 - d 
                // x = 125 - 50 = 75 
                // y = 125 
                // d = 50 

                // all = 250 
                // d = 50 
                // x = 250 / 2 + 50 = 175 
                // y = 175 + 50 = 225 
                
                // x + y + d = all 
                // x = y 
                // x = all / 2 + d
                // x = 4
                // y = 4 
                // all = 10 

                int s = (vec.back()  - grid[i][j]) / 2; //  10 / 2 - 2 = 3
                int ans = lower_bound(vec.begin(),vec.end(), s) - vec.begin();
                if(ans < i and vec[ans] == s and (vec.back()  - grid[i][j]) %2 == 0) {
                    if( (i != n -1 || j == 0 || j == m -1) or ans != n -2 ) {
                        if(m == 1 and (i != 0 and i != n - 1)) {

                        }
                        else {
                        return true;
                        }
                    }
                }

                // CUT after D, rest is smaller 
                // x + y + d = all
                // x = y 
                // 2x  + d = all 
                // x = (all - d) / 2 
                s = (vec.back()  - grid[i][j]) / 2 + grid[i][j]; // (38 - 2 ) / 2 + 2
                ans = upper_bound(vec.begin(),vec.end(), s) - vec.begin() -1;

                if(ans < vec.size()  and ans >= i and vec[ans] == s and (vec.back()  - grid[i][j])%2 == 0) {
                    if(ans != 0 || j == 0 || j == m -1) {
                        if(m == 1 and (i != 0 and i != n - 1) and ans != i) continue;
                        // cout << vec[ans] << endl;
                        return true;
                    }
                }

            }
        }
        return false;
    }
};
