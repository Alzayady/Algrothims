class Solution {
public:
    vector<int>dx = {-1,1,0,0};
    vector<int>dy = {0,0,1,-1};
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        auto can = [&](int i ){
          if(i<grid[0][0])return false;
          queue<pair<int , int >> bfs ;
          vector<vector<bool>>vis(n , vector<bool>(m,0));
          vis[0][0] = 1 ;
          bfs.push({0,0});
          while(bfs.size()){
              pair<int , int >last = bfs.front();
              bfs.pop();
              for( int j = 0 ; j < 4 ; j ++){
                  int nx = last.first  +  dx[j];
                  int ny = last.second + dy[j];
                  if(nx>=0 and nx< n and ny >= 0 and ny< m and grid[nx][ny] <=i){
                      if(!vis[nx][ny]){
                          vis[nx][ny] = 1 ;
                          bfs.push({nx,ny});
                      }
                  }
              }
          }
            
            return vis[n-1][n-1] == 1 ;
        };
        int l = 0 ;
        int r = 1e5 ;
        int ans = 0 ;
        while(l<=r){
            int mid = (l+r)/2;
            if(can(mid)){
                ans = mid;
                r = mid -1 ;
            }else{
                l = mid +  1 ;
            }
        }
        return ans;
      
    }
};
