struct hopcroftKarp {
    /*
     *  1 -  first we make bsf from all unmatched nodes in lest set
     *  2 -  bfs form left to right :
     *         if right node is unmatched before then the augmented path is ended
     *         if right node is matched before then the bfs is continued using the corresponding node ( the node which is matched with right node )
     *         the bfs stop when get all augmented path
     *   3 -  we add all augmented paths to matching ones using dfs , by using the parent of each node stored from the last step
     *
     *   ----- original algrothim storing all possible augmented path which may intersected so it has more complexity to remove them , but this one count only possible paths
     *         without needing to remove anything
     */
    vector<vector<int>> g;
    const static int n = 1000;
    vector<int> parent;
    vector<int> mat;
    vector<int> mat_rev;
    unordered_set<int> leftSet;
    unordered_set<int> matchedSet2;

    hopcroftKarp(vector<vector<int>> g_,  unordered_set<int> leftSet_) {
        g = g_;
        leftSet = leftSet_;
        mat.resize(n + 1, -1);
        mat_rev.resize(n + 1, -1);
        parent.resize(n + 1, -1);
    }

    vector<int> bfs() {
        vector<int> ans;
        queue<int> q;
        unordered_set<int> vis;
        for (int i: leftSet) {
            if (mat[i] == -1) {
                q.push(i);
                vis.insert(i);
            }
        }
        while (q.size()) {
            int last = q.front();
            q.pop();
            for (int next: g[last]) {
                if (vis.count(next))continue;
                vis.insert(next);
                parent[next] = last;

                if (matchedSet2.count(next)) {
                    q.push(mat_rev[next]);
                    parent[mat_rev[next]] = next;
                } else {
                    ans.push_back(next);
                    break;
                }
            }
        }
        return ans;
    }

    void makeboth(int a, int b) {
        // a in left set and b in right set

        if (mat[a] != -1) {
            mat_rev[mat[a]] = -1;
            mat[a] = -1;
            matchedSet2.erase(mat[a]);
        }
        if (mat_rev[b] != -1) {
            mat[mat_rev[b]] = -1;
            mat_rev[b] = -1;
        }
        mat[a] = b;
        mat_rev[b] = a;
        matchedSet2.insert(b);
    }

    vector<pair<int, int >> match() {
        vector<int> augmentedPath = bfs();
        while (augmentedPath.size()) {
            for (int endNode: augmentedPath) {
                vector<int> path;
                path.push_back(endNode);
                while (parent[endNode] != -1) {
                    int lastNode = parent[endNode];
                    path.push_back(lastNode);
                    parent[endNode] = -1;
                    endNode = lastNode;
                }
                if (leftSet.count(endNode) && mat[endNode] == -1) {
                    // update path
                    assert(path.size() % 2 == 0);
                    for (int i = path.size() - 1; i >= 0; i -= 2) {
                        makeboth(path[i], path[i - 1]);
                    }
                }
            }
            augmentedPath = bfs();
        }
        vector<pair<int, int>> ans;
        for (int i = 0; i <= n; i++) {
            if (mat[i] != -1) {
                ans.push_back({i, mat[i]});
            }
        }
        return ans;
    }
};
