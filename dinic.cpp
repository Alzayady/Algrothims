struct dinic {
    const static int N = 100;
    vector<vector<int>> vec;
    vector<vector<int>> cap;
    vector<int> next;
    vector<int> level;
    int s ,  t ;
    void read() {
        cin >> n >> m;
        // this line will be updated acording to problem
        s = 1 , t = n ;
        vec.resize(n + 1);
        next.resize(n + 1);
        level.resize(n + 1);
        cap.resize(n + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            cap[a][b] += c;
            // if bidrectional
            // cap[b][a]+=c;
            vec[a].push_back(b);
            vec[b].push_back(a);
        }
    }

    bool bfs() {
        queue<int> q;
        fill(level.begin(), level.end(), -1);
        q.push(s);
        level[s] = 0;
        while (q.size()) {
            int last = q.front();
            q.pop();
            for (int next_ed : vec[last]) {
                if (cap[last][next_ed]) {
                    if (level[next_ed] == -1) {
                        q.push(next_ed);
                        level[next_ed] = level[last] + 1;
                    }
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int node, int sink, int flow = INT_MAX) {
        if (sink == node) return flow;
        int ss = vec[node].size();
        for (int i = next[node]; i < ss; i++, next[node]++) {
            int next_node = vec[node][i];
            if (cap[node][next_node]) {
                if (level[next_node] == level[node] + 1) {
                    int can = dfs(next_node, sink, min(flow, cap[node][next_node]));
                    if (can) {
                        cap[node][next_node] -= can;
                        cap[next_node][node] += can;
                        return can;
                    }
                }
            }
        }
        return 0;
    }

    int max_flow() {
        int ans = 0;
        while (bfs()) {
            fill(next.begin(), next.end(), 0);
            while (int num = dfs(s, t)) {
                ans += num;
            }
        }
        return ans;
    }
};
