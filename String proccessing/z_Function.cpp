void z(){
    string str;
    int n = str.size();
    vector<int> z(n);
    z[0] = 0;
    int left = 0;
    int right = 0;
    for (int k = 1; k < n; k++) {
        if (right < k) {
            left = right = k;
            while (right < n and str[right] == str[right - left]) {
                right++;
            }
            z[k] = right - left;
            right--;
        } else {
            int sec = k - left;
            if (k + z[sec] <= right) {
                z[k] = z[sec];
            } else {
                left = k;
                while (right < n and str[right] == str[right - left]) {
                    right++;
                }
                z[k] = right - left;
                right--;
            }
        }
    }
}
