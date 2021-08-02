class Solution {
public:
   
    vector<vector<int>>vec;
    vector<vector<int>>id;
    vector<vector<int>>cell_to_id;
    vector<int>id_to_ans;
    vector<int>dx={0,0,1,-1};
    vector<int>dy={1,-1,0,0};
    int cur_id = 0 ;
    int n ;
    void dfs(int x , int y , int _id){
        if(x<0 or x >= n or y < 0 or y >=n)return ;
        if(vec[x][y]==0)return ;
        if(cell_to_id[x][y]!=-1)return ;
        int ans_here = 0;
        cell_to_id[x][y] = _id;
        for(int d = 0 ; d < 4 ; d++){
            dfs(x+dx[d],y+dy[d],_id);
        }
        id_to_ans[_id]++;
    }
    int largestIsland(vector<vector<int>>& vec) {
       this->vec = vec;
         n = vec.size();
        id.resize(n,vector<int>(n,-1));
        cell_to_id.resize(n,vector<int>(n,-1));
        for(int i = 0 ;i < n ; i++){
            for(int j = 0 ;j < n ; j++){
                if(vec[i][j]){
                    id_to_ans.push_back(0);
                    dfs(i,j,cur_id++);
                }
            }
        }
        int ans = 0 ;
        for(int i : id_to_ans){
            ans = max(ans,i);
        }
        for(int i = 0; i < n ; i ++){
            for(int j = 0; j < n ; j++){
                if(vec[i][j]==0){
                    map<int, int> m;
                    for(int d = 0 ; d < 4 ; d++){
                        int nx = i + dx[d];
                        int ny = j + dy[d];
                        if(nx<0 or nx >= n or ny < 0 or ny >=n)continue;
                        if(vec[nx][ny])
                              m[cell_to_id[nx][ny]] = id_to_ans[cell_to_id[nx][ny]];
                    }
                    int x = 1 ;
                    for(pair<int, int> k : m){
                        x+=k.second;
                    }
                    ans = max(ans,x);
                }
            }
        }
        return ans;
    }
};
