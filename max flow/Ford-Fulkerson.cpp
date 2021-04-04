#include <bits/stdc++.h>
#define endll "\n";
using namespace std;
int c[1000][1000];
vector<int>p;
int n , m ;

bool bfs(){
    p.clear();
    p.resize(n+1,-1);
    vector<bool>vis(n);
    vis[0] = true;
    queue<int>q;
    q.push(0);
    while(q.size()){
        int last = q.front();
        q.pop();
        for(int i = 0 ; i <n ; i++){
            if(c[last][i] > 0 && vis[i] == false){
                p[i] = last;

                if(i==n-1){
                    return true;
                }
                vis[i] = true;
                q.push(i);

            }
        }
    }
    return false;
}
int main() {
    int t ;
    cin>>t;
    while(t--){
        cin>>n>>m ;
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j ++){
                c[i][j]=c[j][i]=0;
            }
        }
        for(int i = 0 ; i < m ; i++){
            int a , b ,cc ;
            cin>>a>>b>>cc;
            // if piderictional 
            c[a-1][b-1]+=cc;
            c[b-1][a-1]+=cc;
            // else 
            //  c[a-1][b-1]+=cc;

        }
        int ans = 0;
        while(bfs()){
            int d = n-1 ;
            int max_flow = INT_MAX;
            while(p[d]!=-1){
                max_flow=min(max_flow,c[p[d]][d]);
                d=p[d];
            }
            ans+=max_flow;
            d= n-1 ;
            while(p[d]!=-1){
                c[p[d]][d]-=max_flow;
                c[d][p[d]]+=max_flow;
                d=p[d];
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
