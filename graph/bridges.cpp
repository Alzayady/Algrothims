vector<bool>visited;
vector<int>low;
int tim = 0 ;
vector<vector<int>>graph;
vector<pair<int , int>>bridges;
void dfs(int node , int parent =-1){
    visited[node]=true;
    int disc= low[node]=tim++;
    for(int n : graph[node]){
        if(n==parent)continue;
        if(!visited[n])dfs(n , node);
        if(disc<low[n]){
            bridges.emplace_back(node,n);
        }
        low[node]=min(low[node],low[n]);
    }
}
