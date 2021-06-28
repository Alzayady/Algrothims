class Solution {
public:
    int candy(vector<int> ratings) {
        priority_queue<pair<int, int >> pq;
        int n = ratings.size();
        for (int i = 0; i < n; i++) {
            pq.push({ratings[i], i});
        }
        int ans = 0;
        vector<bool> vis(n, 0);
        while (pq.size()) {
            pair<int, int> last = pq.top();
            pq.pop();
            if (vis[last.second])continue;
            int length_left = 0;
            int length_right = 0;
            int it = last.second + 1;
            while (it < n and ratings[it] < ratings[it - 1]) {
                length_right += 1;
                it++;
            }
            it = last.second - 1;
            while (it >= 0 and ratings[it] < ratings[it + 1]) {
                length_left += 1;
                it--;
            }
            ans+= max(length_left, length_right) + 1;
            int first_right = length_right;
            for (int i = 0; i < length_right; i++) {
                if (!vis[last.second + i + 1]) {
                    ans += first_right;
                    vis[last.second + i + 1] = 1;
                }
                    first_right--;
            }
            int first_left = length_left;
            for (int i = 0; i < length_left; i++) {
                if (!vis[last.second - i - 1]) {
                    ans += first_left;
                    vis[last.second - i - 1] = 1;
                }
                    first_left--;
            }

        }
        return ans;
    }
};

