int n, m;
vector<vector<int>> graph;
vector<bool> visited;
vector<int> low;
vector<int> tin;

int tim = 0;
unordered_set<int>ans;
void dfs(int node, int p) {
    tin[node] = low[node] = tim++;
    int c = 0;
    visited[node] = true;
    for (int next : graph[node]) {
        if (next == p)continue;
        if (visited[next]) {
            low[node] = min(low[node], tin[next]);
            continue;
        }
        c++;
        dfs(next, node);
        low[node] = min(low[node], low[next]);
        if ( p != -1 && low[next] >= tin[node]) {
        // node can be duplicated so we store them in set 
            ans.insert(node);
        }
    }
    if (c > 1 && p == -1) {
        ans.insert(node);
    }
}
