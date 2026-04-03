class Solution {
public:
    vector<int> robots,distance,walls ;
    vector<pair<int , int>> vec;
    vector<vector<int>> dp;
    int solve(int index , bool before_right, int end_right) {
        if(index == robots.size()) return 0 ;
        if(dp[index][before_right] != -1) return dp[index][before_right];
        int start_r = lower_bound(walls.begin(), walls.end() , robots[index] - distance[index]) - walls.begin();
        int start = max(end_right,start_r);
        int end = upper_bound(walls.begin(), walls.end() , robots[index]) - walls.begin();
        int take = end - start ;
        int next = solve(index + 1 , 0 , upper_bound(walls.begin(), walls.end() , robots[index]) - walls.begin());
        int ans = take + next;
        start = lower_bound(walls.begin(), walls.end(),robots[index]) -  walls.begin();
        int d = robots[index] + distance[index] ;
        if(index !=robots.size() -1 ) {
            d = min(d, robots[index + 1] - 1);
        }
        end = upper_bound(walls.begin(), walls.end() , d) - walls.begin();
        take = end - start;
        next = solve(index + 1 , 1 , end) ;
        ans = max(ans, take + next);
        return dp[index][before_right] = ans;
    }
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        this->robots = robots;
        this->distance = distance;
        this->walls = walls;
        int n = robots.size();
        vec.resize(n);
        for(int i = 0 ; i < n ; i ++) {
            vec[i] = {robots[i] , distance[i]};
        }
        sort(vec.begin(),vec.end());
        for(int i = 0 ; i < n ; i ++) {
            this->robots[i] = vec[i].first;
            this->distance[i] = vec[i].second;
        }
        sort(this->walls.begin(),this->walls.end());
        dp.resize(n,vector<int>(2,-1));
        return solve(0,0,0);
    }
};
