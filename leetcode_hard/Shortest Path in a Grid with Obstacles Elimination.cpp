class Solution {
public:
    vector<pair<int , int >> dx = {{1,0},{0,1},{-1,0},{0,-1}};
    int shortestPath(vector<vector<int>>& vec, int k) {
        int n = vec.size();
        int m =vec[0].size();
        queue<pair<pair<int , int> , int >> bfs;
        bfs.push({{0,0},k});
        int ans = 0 ;
        int vis[n][m];
        memset(vis,-1,sizeof vis);
        vis[0][0]= k ;
        while(bfs.size()){
            int s= bfs.size();
            while(s--){
                pair<pair<int , int> , int> last = bfs.front();
                bfs.pop();
                int x = last.first.first;
                int y = last.first.second;
                if(last.first.first == n-1 and last.first.second == m-1){
                    return ans;
                }
                for(int i = 0; i < 4 ; i ++){
                    int nx =  x +  dx[i].first;
                    int ny =  y +  dx[i].second;
                    int nk = last.second ;
                    if(nx>=0 and nx<n and ny>=0 and ny < m and  nk >=0){
                        if(vec[x][y]==1){
                            nk --;
                        }
                        if(nk==-1)continue;
                        if(vis[nx][ny]>=nk)continue;
                        vis[nx][ny] = nk;
                        bfs.push({{nx,ny},nk});
                    }
                }
            }
            ans ++;
        }
        return -1;
    }
};
